#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal_header.h"


static int mymax(int a,int b){
    if(a>b)
        return a;
    return b;
}


static int mymin(int a,int b){
    if(a<b)
        return a;
    return b;
}


//function to remove leading 0s from an intal
static char* removeleadz(char* str){
    int n=strlen(str);
    int i=0;
    while(i < n && str[i]=='0'){
        i++;
    }

    if(i==n){
        strcpy(str,"0");
        return str;
    }
    
    char* res=(char*)malloc(sizeof(char)*(n-i+1));
    for (int j=i;j<n;j++){
        res[j-i]=str[j];
    }
    res[n-i]='\0';
    //printf("\nREMOVED len: %d\n",strlen(res));
    free(str);
    return res;
}


//helper function to pad 0s at the beginning of an intal
static char* mypadfunc(const char* num1,int l,int newl){ 
   
    int x= newl-l;
    //printf("X : %d\n",x);
    int s= (newl+1)*sizeof(char);
    char* res=(char*)malloc(s);
    memset(res,'0',s-1);
    res[newl]='\0';
   
    for(int i=x; i<newl; i++){
         res[i]=num1[i-x];
    }
    return res;
}


// Returns the sum of two intals.
char* intal_add(const char* intal1, const char* intal2){    
    
    //if any one of the intals are 0
    if (strcmp(intal1,"0")==0){
        char* res=(char*) malloc( (strlen(intal2)+1) *sizeof(char) ) ;
        strcpy(res,intal2);
        return res;    
    }
    
    if (strcmp(intal2,"0")==0){
        char* res=(char*) malloc( (strlen(intal1)+1) *sizeof(char) ) ;
        strcpy(res,intal1);
        return res;    
    }

    // find max length  
    int l1=strlen(intal1);
    int l2=strlen(intal2);
    int l=mymax(l1,l2);
    char* new1=(char*)malloc( (l+1) *sizeof(char));
    char* new2=(char*)malloc( (l+1) *sizeof(char));

    if (l1<l2){
         char *temp=mypadfunc(intal1, l1, l2);
         //printf("\nTEMP: %s\n",temp);
         strcpy(new1,temp);
         strcpy(new2,intal2);
         free(temp);
    }
    else if(l1>l2){        
        char *temp=mypadfunc(intal2, l2, l1);
        //printf("\nTEMP: %s\n",temp);
        strcpy(new2,temp);
         strcpy(new1,intal1);
         free(temp);
    }
    else{        
        strcpy(new1,intal1);
        strcpy(new2,intal2);
    }
    
    char* res=(char*)malloc(sizeof(char)*(l+2));
    memset(res,'0',l+1);
    res[l+1]='\0';
    //printf("\nRES : %s\n",res);
    //char temp[2];
    int carry=0;

    for(int i=l-1;i>=0;i--){
        int sum= new1[i]-'0' + new2[i]-'0' + carry;
        res[i+1]=(sum%10) +'0';   
        if (sum>=10){
            carry=1;
        }
        else{
            carry=0;
        }
    }
    res[0]=(carry==1?'1':'0');

    free(new1);
    free(new2);
    res=removeleadz(res);
    return res;
}


// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char* intal1, const char* intal2){
    int l1=strlen(intal1);
    int l2=strlen(intal2);
    int ans=0;
    if(l2>l1){
        ans=-1;
    }
    else if(l1>l2){
        ans=1;
    }
    else{
        int x= strcmp(intal1,intal2);
        if(x>0){
            ans=1;
        }
        else if (x<0){
            ans=-1;
        }
    }
    return ans;
}


// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(const char* intal1, const char* intal2){
    
    // check if either is zero
    if (strcmp(intal1,"0")==0){
        char *res=(char*)malloc(sizeof(char)*(strlen(intal2)+1));
        strcpy(res,intal2);
        return res;
    }
    if(strcmp(intal2,"0")==0){
        char *res=(char*)malloc(sizeof(char)* (strlen(intal1)+1));
        strcpy(res,intal1);
        return res; 
    }

    int chk=intal_compare(intal1,intal2);
    
    //if the 2 numbers are same, return 0
    if(chk==0){
        char * res=(char*)malloc(sizeof(char)*2);
        strcpy(res,"0");
        return res;
    }

    //store bigger number in num1 and the smaller number in num2
    char* num1=(char*)malloc(sizeof(char)*1001);
    char* num2=(char*)malloc(sizeof(char)*1001);
    
    if (chk==-1){
        strcpy(num1,intal2);
        strcpy(num2,intal1);
    }
    else{
        strcpy(num1,intal1);
        strcpy(num2,intal2);
    }
    //printf("\nnum1:%s   num2:%s",num1,num2);
    int x= strlen(num1)-strlen(num2);
    //last position of the 
    int i=strlen(num1)-1;
    int borrow=0;
    int temp;

    char * res=(char*)malloc(sizeof(char)*(strlen(num1)+1));
    memset(res,0,strlen(num1));
    res[strlen(num1)]='\0';
    while(i>=0){
        if (i-x>=0){            
            //printf("\nDoing num1[i]-num2[i-x]-borrow, i-x=%d num1[i]= %d, num2[i-x]=%d borrow=%d",i-x,num1[i],num2[i-x],borrow);
            temp=num1[i]-0-num2[i-x]-0-borrow;
            if(temp<0){
                borrow=1;
                temp+=10;
            }
            else{
                borrow=0;
            }
        }

        else{
            //printf("\nDoing num1[i]-borrow, num1[i]= %d, borrow=%d",num1[i],borrow);
            temp=(num1[i]-'0')-borrow;
            borrow=0;
        }
        //printf("\ttemp : %c",temp+'0');
        res[i]=temp +'0';
        //printf("\tres : %s ",res);
        i--;
    }

    free(num1);
    free(num2);
    return removeleadz(res);
}


// Returns the product of two intals.
char* intal_multiply(const char* intal1, const char* intal2){

    int l1=strlen(intal1);
    int l2=strlen(intal2);

    if(l1==0 || l2==0){
        char * res=(char*)malloc(sizeof(char)*2);
        strcpy(res,"0");
        return res;
    }
    
    //if any one of the intals are 0
    if (strcmp(intal1,"0")==0 || strcmp(intal2,"0")==0){
        char * res=(char*)malloc(sizeof(char)*2);
        strcpy(res,"0");
        return res;            
    }

    const char* num1 = intal1;
    const char* num2 = intal2;
    //char temp[2];

    char* res=(char* )malloc(sizeof(char)* (l1+l2+1));
    memset(res,'0',l1+l2);
    res[l1+l2]='\0';

    // Below two indexes are used to find positions 
    // in result.  
    int i_n1 = 0,i_n2 = 0;  
      
    // Go from right to left in num1 
    for (int i=l1-1; i>=0; i--) 
    { 
        int carry = 0; 
        int n1 = num1[i] - '0'; 
  
        // To shift position to left after every 
        // multiplication of a digit in num2 
        i_n2 = 0;  
          
        // Go from right to left in num2              
        for (int j=l2-1; j>=0; j--) 
        { 
            // Take current digit of second number 
            int n2 = num2[j] - '0'; 
  
            // Multiply with current digit of first number 
            // and add result to previously stored result 
            // at current position.  
            int sum = n1*n2 + (res[i_n1 + i_n2]-'0') + carry; 
  
            // Carry for next iteration 
            carry = sum/10; 
  
            // Store result
            res[i_n1+i_n2]=(sum%10)+'0'; 
            i_n2++; 
        } 
  
        // store carry in next cell 
        if (carry > 0) {
            int x=res[i_n1+i_n2]-'0' + carry;
            res[i_n1+i_n2]=x + '0';
        }
            
        // To shift position to left after every 
        // multiplication of a digit in num1. 
        i_n1++; 
    } 
    int i=strlen(res)-1;
    while(i>=0 && res[i] ==0){
        i--;
    }

    if(i==-1){
        return "0";
    }
   
    //char t;
    char* finalres=(char*)malloc(sizeof(char)*(strlen(res)+1));
    int m=0,n;
    for(m=0,n=strlen(res)-1;m<strlen(res);m++,n--){
        finalres[m]=res[n];
    }
    finalres[m]='\0';
    free(res);
    return removeleadz(finalres);
}


// Returns intal1 mod intal2 in the range [0, intal2 - 1].
// Assumes intal2 > 1
// Implements an O(log intal1) time taking algorithm.
char* intal_mod(const char* intal1, const char* intal2){
    //check for zero
    if (strcmp(intal1,"0")==0){
        char* res=(char*)malloc(sizeof(char)*2);
        strcpy(res,"0");
        return res;
    }

    if(-1==intal_compare(intal1,intal2)){
        char* res=(char*)malloc(sizeof(char)*1001);
        strcpy(res,intal1);
        return res;
    }
    
    int x=strlen(intal1)-strlen(intal2),l2;
    char* new1=(char*)malloc(sizeof(char)*1001);
    char* new2=(char*)malloc(sizeof(char)*1001);
    
    strcpy(new1,intal1);
    strcpy(new2,intal2);
    char *temp; //malloc
    //char *temp=(char*)malloc(sizeof(char)*1001);
    int chk;

    while(x>=0){    //checking if len(intal1) > = len(intal2) 
        if(x>0){
            l2=strlen(new2);
            //append zeros to make new2 of the same length as intal1
            memset(new2+l2,'0',x);
            new2[l2+x]='\0';
        }
        chk=intal_compare(new1,new2);
        if(-1==chk){
            // in case new2 has a bigger value than intal1 after appending it with zeros,
            //we remove one zero.
            new2[strlen(new2)-1]='\0';
        }
        temp=intal_diff(new1,new2);
        
        //printf("\nTEMP : %s",temp);
        if(-1==intal_compare(temp,intal2)){
            break;
        }
        strcpy(new1,temp);
        free(temp);
        strcpy(new2,intal2);
        x=strlen(new1)-strlen(new2);        
    
    }
    free(new1);
    free(new2);
    char* res=(char*) malloc(sizeof(char)*1001);
    strcpy(res,temp);
    free(temp);
    return res;    
}


// Returns intal1 ^ intal2.
// Implements an O(log n) intal multiplications algorithm.
char* intal_pow(const char* intal1, unsigned int n){
    char *res;
    if (n==0){
        res=(char*)malloc(sizeof(char)*2);
        strcpy(res,"1");
        return res;
    }
    res=(char*)malloc(sizeof(char)*2001);
    strcpy(res,"1");

    char * temp;
    char* new1=(char*)malloc(sizeof(char)*2001);
    strcpy(new1,intal1);

    while(n>0){
        if(n % 2 == 1){
            temp=intal_multiply(new1,res);
            strcpy(res,temp);
            free(temp);
        }
        temp=intal_multiply(new1,new1); 
        strcpy(new1,temp);
        free(temp);
        n=n/2;
    }
    return res;
}


// Returns Greatest Common Divisor of intal1 and intal2.
// Euclid's Algorithm
char* intal_gcd(const char* intal1, const char* intal2){

    int chk=intal_compare(intal1,intal2);
    
    //printf("\n check : %d",chk);
    if(chk==0){
        char * res=(char*)malloc(sizeof(char)*1001);
        strcpy(res,intal1);
        return res;
    }
    char* new1=(char*)malloc(sizeof(char)*1001);
    char* new2=(char*)malloc(sizeof(char)*1001);
    if(chk==1){
        strcpy(new1,intal1);
        strcpy(new2,intal2);
    }
    else{
        strcpy(new1,intal2);
        strcpy(new2,intal1);
    }
    if (strcmp(new2,"0")==0){
        char * res= (char*) malloc(sizeof(char)* 1001);
        strcpy(res,new1);
       // printf("\nJEREEE : new1:%s new2:%s",new1,new2);
        return res;
    }
    char* temp;
    while(strcmp(new2,"0")!=0){
        temp=intal_mod(new1,new2);
        strcpy(new1,new2);
        strcpy(new2,temp);
        free(temp);
    }
    char* res=(char*)malloc(sizeof(char)*1001);
    strcpy(res,new1);
    free(new1);
    free(new2);
    return res; 
    
}


// Returns nth fibonacci number.
char* intal_fibonacci(unsigned int n){
    //printf("\nIN FIB");
    if(n==0){
        return "0"; //malloc
    }
    if(n==1){
        return "1"; //malloc
    }
    //const char* a="0";
    //const char* b="1";
    
    char*c;
    char * a=(char*)malloc(sizeof(char)*1001);
    char * b=(char*)malloc(sizeof(char)*1001);
    strcpy(a,"0");
    strcpy(b,"1");

    for(unsigned int i=2;i<=n;i++){
        c=intal_add(a,b);
        strcpy(a,b);
        strcpy(b,c);
        free(c);
        
       // a=b;
        //b=c;
        
    }
    char* res=(char*)malloc((strlen(b)+1)*sizeof(char));
    //res[strlen(b)]='\0';
    strcpy(res,b);
    free(a);
    free(b);
    return res;
}


// Returns the factorial of a large number.
char* intal_factorial(unsigned int n){
    if(n==1 || n==0){
        return "1";
    }

    char* a=(char*)malloc(sizeof(char)*1001);
    char* b=(char*)malloc(sizeof(char)*1001);
    char* temp=(char*)malloc(sizeof(char)*(n+2));
    char * fact=(char*)malloc(sizeof(char)*1001);
    char * f;

    strcpy(fact,"1");
    strcpy(a,"1");
    strcpy(b,"1");

    for(unsigned int i=2;i<=n;i++){
        sprintf(temp,"%d",i);
        strcpy(b,temp);
        strcpy(a,fact);
        
        f=intal_multiply(a,b);
        strcpy(fact,f);
        free(f);
    }
    char * res=(char*)malloc( sizeof(char) * (strlen(fact)+1) );
    //res[strlen(fact)]='\0';
    strcpy(res,fact);
    free(fact);
    free(a);
    free(b);
    free(temp);

    return res;
}


// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
char* intal_bincoeff(unsigned int n, unsigned int k){
    int r=(k <= n/2)?k:(n-k);
    //printf("\nN,k,r: %d, %d, %d",n,k,r);
    char ** C=(char**) malloc(sizeof(char*)* (r+1));
    for(int i = 0; i <= r; i++) {
		C[i] = (char*) malloc(1001 * sizeof(char));
        memset(C[i],'0',1000); //initialise all strings to be zero
        C[i][1000]='\0'; //null char
    }
    strcpy(C[0],"1");
    //char *temp=(char*)malloc(sizeof(char)*1001);
    char *temp;
    for(int i=1; i <=n; i++){
        for(int j=mymin(i,r);j>0;j--){
            temp=intal_add(C[j],C[j-1]);
            strcpy(C[j],temp);
            free(temp);
        }
    }
    char *res=(char*)malloc(sizeof(char)*(strlen(C[r])+1));
    strcpy(res,C[r]);
    for(int i = 0; i <= r; i++) {
        free(C[i]);
    }
    free(C);
    return res;
    
}


// Returns the offset of the largest intal in the array.
// Returns the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n){
    const char *mmax=arr[0];
    int x=0,pos=0;
    for(int i=1;i<n;i++){
         x=intal_compare(arr[i],mmax);
        if(x==1){
            mmax=arr[i];
            pos=i;
        }
    }
    return pos;
}


// Returns the offset of the smallest intal in the array.
// Returns the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n){
    const char *mmin=arr[0];
    int x,pos=0;
    for(int i=1;i<n;i++){
         x=intal_compare(arr[i],mmin);
        if(x==-1){
            mmin=arr[i];
            pos=i;
        }
    }
    return pos;
}


// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char* key){
    int pos=-1;
    for(int i=0;i<n;i++){
        int x=intal_compare(arr[i],key);
        if(x==0){
            pos=i;
            break;
        }
    }
    return pos;
}


// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
int intal_binsearch(char **arr, int n, const char* key){
    int low=0, high=n-1, x, pos=-1;
    while(low<=high){
        int mid=(low+high)/2;
        x=intal_compare(arr[mid],key);
        if(x==0){
            pos=mid;
            high=mid-1;
            //break;
        }
        else if(x==1){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return pos;
}


// Merges two subarrays of arr[] (array of intals) 
static void merge(char** arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    //int L[n1], R[n2];  
    char** L=(char**)malloc( sizeof(char*)* n1);
    char** R=(char**)malloc( sizeof(char*)* n2);
    for(int i = 0; i < n1; i++) {
		L[i] = (char*) malloc(1001 * sizeof(char));
	}
    for(int i = 0; i < n2; i++) {
		R[i] = (char*) malloc(1001 * sizeof(char));
	}
    
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        strcpy(L[i],arr[l + i]); 
    for (j = 0; j < n2; j++) 
        strcpy(R[j] ,arr[m + 1+ j]); 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        int x=intal_compare(L[i],R[j]);
        if (x==-1 ||x==0) 
        { 
            strcpy(arr[k] , L[i]); 
            i++; 
        } 
        else
        { 
            strcpy(arr[k] , R[j]); 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        strcpy(arr[k] ,L[i]); 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        strcpy(arr[k] , R[j]); 
        j++; 
        k++; 
    } 
     for (i = 0; i < n1; i++){
         free(L[i]);
     } 
   
     for (i = 0; i < n2; i++){
         free(R[i]);
     } 
    free(L);
    free(R);
} 

//helper function for intal_sort()
static void mergeSort(char **arr, int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 

    } 
    //printf("\nDONE");
} 

// Sorts the array of n intals.
// 1 <= n <= 1000
void intal_sort(char **arr, int n){
        mergeSort(arr,0,n-1);
}


// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char* coin_row_problem(char **arr, int n){
    
    char* incl=(char*)malloc(sizeof(char)*1001);
    char* exl=(char*)malloc(sizeof(char)*1001);
    char* exlnew=(char*)malloc(sizeof(char)*1001);
    char* temp=arr[0];
    strcpy(incl,temp);
    strcpy(exl,"0");
    
    for(int i=1;i<n;i++){
        int x=intal_compare(incl,exl);
        if(x>=0){
            strcpy(exlnew,incl);        
        }
        else{
            strcpy(exlnew,exl);
        }
        temp=intal_add(arr[i],exl);
        strcpy(incl,temp);
        free(temp);
        strcpy(exl,exlnew);
    }
    char* res=(char*) malloc(sizeof(char)*1001);
    int ans=intal_compare(incl,exl);
    if (ans>=0){
        strcpy(res,incl);
    }
    else{
        strcpy(res,exl);
    }
    free(incl);
    free(exl);
    free(exlnew);

    return res;
}





