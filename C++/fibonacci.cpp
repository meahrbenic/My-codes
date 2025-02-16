#include <iostream>
#include <cmath>

using namespace std; 

int nzd(int x, int y){
    if(y==0) return x; 
    return nzd(y,x % y);
}

int fib (int n) {
    static int prev=0; 
    static int fibo=1; 
    static int broj=n; 
    if(n<=1) return n; 

    fibo = fibo + prev; 
   
    prev = fibo - prev; 
   
    broj--;
   
    if(broj == 1) return fibo; 
   
    return fib(n-1);
    /*
    if (n<=1) return n; // 0 i 1
    return fib(n-1) + fib(n-2);*/
}

int fib2_0(int n){
    return fib(n);
}

int main(){

    int x=45, y=6;
    std::cout<<nzd(x,y);
    return 0; 
}