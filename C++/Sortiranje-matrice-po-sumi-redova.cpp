//TP 2021/2022: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template<typename Tip>
bool Kriterij(std::vector<Tip> v1, std::vector<Tip> v2){
    Tip suma1{},suma2{};
    for(int i=0; i<v1.size(); i++) suma1=suma1+v1.at(i);
    for(int i=0; i<v2.size(); i++) suma2=suma2+v2.at(i);
    if(suma1!=suma2) return suma1>suma2;
    else return v1>v2;
} 

template<typename Tip>
void SortirajPoSumiRedova(std::vector<std::vector<Tip>> &mat){
    std::sort(mat.begin() ,mat.end() ,Kriterij<Tip>);    
}

int main ()
{
    
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): "; 
    std::vector<std::vector<int>> m;
    bool kraj=false;
    int i=0; 
    for(;;){
        int unos; 
        kraj=false;
        int j=0; 
        for(;;){
            std::cin>>unos; 
            if(!std::cin){
                if(j==0) kraj=true; 
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                break;
            }
            m.resize(i+1);
            m.at(i).push_back(unos);
            j++;
        }
        if(kraj) break;
        i++;
    }

    SortirajPoSumiRedova(m);
    std::cout<<"Matrica nakon sortiranja: "<<std::endl;
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m.at(i).size();j++){
            std::cout<<m.at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
    }

	return 0;
}
