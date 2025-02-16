//TP 2021/2022: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include<stdexcept>


bool SlovoIliBroj(char znak){
    if(znak >='A' && znak<='Z') return true; 
    if(znak >='a' && znak<='z') return true;
    if(znak >='0' && znak<='9') return true; 
    return false;
}

void SveUVelika(std::string &r){
    for(int i=0; i<r.length(); i++){
        r.at(i)= toupper(r.at(i));
    }
}

std::array<std::vector<std::string>,100> RazvrstajRijeciPoDuzini(std::string recenica){
    std::array<std::vector<std::string>,100> a; 
    std::string rijec; 

    recenica= ' '+recenica; 
    recenica= recenica+' ';

    //uzimanje rijeci 
    for(int i=0; i<recenica.length(); i++){
       
        if( SlovoIliBroj(recenica.at(i)) ){
            int brojac=0; 
            int pozicija=i; 

            while( SlovoIliBroj(recenica.at(i)) ){
                brojac++; 
                i++; 
            }
            i--;

            if(recenica.substr(pozicija,brojac).length()> 100) throw std::range_error("Predugacka rijec!");
        
            rijec=recenica.substr(pozicija,brojac);

            SveUVelika(rijec);

            a.at(rijec.length()).push_back(rijec);
           // std::cout<<rijec<<std::endl;
        }

    }

    return a; 
}

int main ()
{   
    std::cout<<"Unesite recenicu: ";
    std::string unos; 

    std::getline(std::cin,unos);

    try{
        std::array<std::vector<std::string>,100> b= RazvrstajRijeciPoDuzini(unos);
        for(int i=0; i<b.size();i++){
            if( b.at(i).empty() ) continue; 
            std::cout<<"Duzina "<<i<<": ";
            for(int j=0; j<b.at(i).size();j++){
            
                std::cout<<b.at(i).at(j)<<" ";
            
            }
            std::cout<<std::endl; 
        }
    }
    catch(std::range_error){
        std::cout<<"Greska: Recenica sadrzi predugacku rijec!";
    }
    
	return 0;
}
