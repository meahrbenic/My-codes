//TP 2018/2019: Zadaća 1, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>

enum class Kriterij {Veca,Manja,Jednaka}; 

int ProizvodCifara(int br){
    int novi=1;
    do{
        int c=br%10; 
        novi=novi*c; 
        br=br/10; 
    }while(br!=0);
    return novi;
}

int MO(int n){
    int k=0;
    n=std::abs(n);
   while(n>9){
        n=ProizvodCifara(n);
        k++;
        if(k>11) break; 
   };
    return k;
}

void BrisiDuple(std::vector<int> &v){
    for(int i=0; i<v.size(); i++){
        for(int j=i+1; j<v.size(); j++){
            if(v.at(i)==v.at(j)){
                v.erase(v.begin()+j); 
                j--;
            }
        }
    }
}

std::vector<int> IBSZMU(std::vector<int> v, int otpornost,Kriterij krit){
    std::vector<int> novi; 
    
      for(int i=0; i<v.size(); i++){
            int m=MO(v.at(i));
            if(krit==Kriterij::Jednaka){
                if(m==otpornost) novi.push_back(v.at(i));
            }
            if(krit==Kriterij::Veca){
                if(m>otpornost) novi.push_back(v.at(i));
             }
            if(krit==Kriterij::Manja){
                if(m<otpornost) novi.push_back(v.at(i));
            }
        }
        BrisiDuple(novi);
    return novi; 
}

int main ()
{   
    int br; 
    std::vector<int> vektor; 

    std::cout<<"Unesite slijed brojeva (0 za kraj): "; 

    for(;;){
        std::cin>>br; 
        if(br==0) break; 
        else vektor.push_back(br);
    }

    int k; 
    std:: cout<<"Unesite zeljeni prag za multiplikativnu otpornost: "; 
    std::cin>>k; 

    std::cout<<std::endl; 

    Kriterij kr=Kriterij::Manja; 

    std::vector<int> vektor2(IBSZMU(vektor, k, kr));

    std::cout<<"Brojevi cija je multiplikativna otpornost manja od zadane: ";
    if(vektor2.size()!=0){
        for(int x : vektor2) std::cout<<x<<" "; 
    }
    else{
        std::cout<<"Nema takvih brojeva";
    }

    std::cout<<std::endl; 

    kr=Kriterij::Veca; 

    vektor2.resize(0);

    vektor2=IBSZMU(vektor, k, kr);
    std::cout<<"Brojevi cija je multiplikativna otpornost veca od zadane: ";

    if(vektor2.size()!=0){
        for(int x : vektor2) std::cout<<x<<" ";
    }
    else {
        std::cout<<"Nema takvih brojeva";
    }

    std::cout<<std::endl; 

    kr=Kriterij::Jednaka; 

    vektor2.resize(0);

    vektor2=IBSZMU(vektor, k, kr);

    std::cout<<"Brojevi cija je multiplikativna otpornost jednaka zadanoj: "; 

    if(vektor2.size()!=0){
        for(int x : vektor2) std::cout<<x<<" ";
    }
    else{
        std::cout<<"Nema takvih brojeva"; 
    }
    

   // int br=12; 
   // std::cout<<" "<<MO(br);
   //std::cout<<MO(br);
    
	return 0;
}