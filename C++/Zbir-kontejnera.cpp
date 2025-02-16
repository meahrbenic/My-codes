//TP 2021/2022: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>
#include <string>
#include <deque>
#include  <forward_list>
#include <list>


template <typename pok>
int Velicina(pok pok1, pok pok2){
    int br=0; 
    while(pok1!=pok2){
        br++;
        pok1++; 
    }
    return br; 
}

template <typename Kolekcija1, typename Kolekcija2>
auto ZbirKontejnera(Kolekcija1 c1, Kolekcija2 c2){ 
    int veca=0;
    auto p=c1.begin(),kr1=c1.end();
    auto q=c2.begin(),kr2=c2.end();
    int vel1=Velicina(c1.begin(),c1.end()); 
    int vel2=Velicina(c2.begin(),c2.end());
    if(vel1>vel2) veca=vel1; 
    else veca=vel2;
    
    std::vector<decltype(*p+*q)> v(veca);
    int i=0; 
    if(vel1>vel2){
        while(p!=kr1){
        if(q!=kr2){
           v.at(i)= *p + *q; 
           q++; 
        }
        else{
            v.at(i) = *p;
        } 
        p++;
        i++;
        }
    }
    else{
        while(q!=kr2){
        if(p!=kr1){
           v.at(i)= *p + *q; 
           p++; 
        }
        else{
            v.at(i)= *q ;
        }
        q++;
        i++;
        }
    }
    
    return v; 
}

int main ()
{
    
    std::cout<<"Duzina prvog kontejnera: ";
    int n=0; 
    std::cin>>n; 
    std::vector<double> d(n); 
    std::cout<<"Elementi prvog kontejnera: "; 
    for(int i=0; i<n; i++){
        std::cin>>d.at(i);
    }

    std::cout<<"Duzina drugog kontejnera: ";
    int m=0; 
    std::cin>>m; 
    std::vector<double> e(m); 
    std::cout<<"Elementi drugog kontejnera: "; 
    for(int i=0; i<m; i++){
        std::cin>>e.at(i);
    }

    auto v=ZbirKontejnera(d,e);
    std::cout<<"Zbir kontejnera: "; 
    for( auto x : v){
        std::cout<<x<<" ";
    }


	return 0;
}
