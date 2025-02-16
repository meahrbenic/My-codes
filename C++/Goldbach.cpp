//TP 2021/2022: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>

bool JeLiProst(int n){
    if(n==0 || n==1 || n==2) return true;
    for(int i=2; i<=std::sqrt(n); i++){
        if(n%i==0) return false; 
    } 
    return true;
}

int GenerirajProstBroj(int prosli){

    if(prosli<3) return prosli+1; 
    else {
        for(int i=2; ;i++){
            for(int j=2; j*j<=i; j++){
                if(i % j == 0) break; 
                else if(j+1 > std::sqrt(i)){
                    if(i>prosli ) return i;  
                } 
            }
        }
    }
}

void Goldbach( int n, int &p, int &q){
    if(n<=2) throw std::logic_error("Rastava ne postoji");
    p=0; q=0;
    p=1;
    while(p<n){
        p=GenerirajProstBroj(p);
        q=n-p; 
        if(JeLiProst(q)) break; 
    }

    if(p<0 || q<0){
       p=0; q=0; 
    } 
    if(q==0) throw std::logic_error("Rastava ne postoji");
}

int main ()
{   
    int broj; 
    try{
    std::cout<<"Unesi broj: "; 
    std::cin>>broj;
    int p,q; 
    Goldbach(broj, p, q);
    if(q!=0) std::cout<<broj<<" je zbir prostih brojeva "<<p<< " i "<<q;
    }
    catch(...){
        std::cout<<broj<<" nije zbir dva prosta broja!";
    }
	return 0;
}