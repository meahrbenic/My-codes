// TP 2021/2022: Zadaća 3, Zadatak 4
#include <cmath>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

bool SlovoIliBroj(char c){
    if(c>='A' && c<='Z') return true; 
    if(c>='a' && c<='z') return true; 
    if(c>='0' && c<='9') return true; 
    return false; 
}

int Size(std::string s){
    int duzina=0; 
    for(int i=0; i<s.length(); i++){
        if(SlovoIliBroj(s.at(i))) duzina++; 
    }
    return duzina;
}


std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> djeca,int k) {
    
    if(k<1 || k>djeca.size()) throw std::logic_error("Razvrstavanje nemoguce");
    int n = djeca.size();
    std::list<std::string> l;
    std::vector<std::set<std::string>> raspored(k);

    double a=n/k; 
    int broj_prvih=n-(a*k);
    int clanovi1=n/k+1;
    int clanovi2=n/k; 
   
    for (int i = 0; i < djeca.size(); i++){
        l.push_back(djeca.at(i));
    }

    auto pocetak = l.begin();
    auto kraj=l.end(); 
    auto it = l.begin();

    int korak= Size(djeca.at(0));
    int stari= Size(djeca.at(0)); 

    int j=0;
    int velicina_tima=1;

    raspored.at(j).insert(*it); 
    it=l.erase(it); 
    if(k==n){
        while (l.size() != 0) {
            korak=stari;
            for (int i = 0; i < korak; i++){

                if (i == korak -1){
                    stari=Size(*it);
                    j++;
                    raspored.at(j).insert(*it); 
                      
                    it = l.erase(it);
                    }
                    else if(it!=kraj){
                        it++;
                    }
                    if(it==kraj){
                        pocetak=l.begin(); 
                        kraj=l.end(); 
                        it=pocetak; 
                    }
            }   

        }
    }
    else{

    while (l.size() != 0) {
        korak=stari;

            for (int i = 0; i < korak; i++){

                if (i == korak -1){
                stari=Size(*it);
                
                if(j<broj_prvih){
                    if(velicina_tima<clanovi1){
                       raspored.at(j).insert(*it); 
                       velicina_tima++; 
                    }
                    if(velicina_tima==clanovi1){
                       velicina_tima=0;
                       j++;  
                    }       
                }
                else{
                    if(velicina_tima<clanovi2){
                       raspored.at(j).insert(*it); 
                       velicina_tima++; 
                    }
                    if(velicina_tima==clanovi2){
                       velicina_tima=0;
                       j++;  
                    } 
                }
    
                it = l.erase(it);
                }
                else if(it!=kraj){
                it++;
                }
                if(it==kraj){
                    pocetak=l.begin(); 
                    kraj=l.end(); 
                    it=pocetak; 
                }
            }

        }
    }

    return raspored;
}

int main() {
    
    std::cout<<"Unesite broj djece: "; 
    int vel=0; 
    std::cin>>vel; 
    std::vector<std::string> p(vel);
    
    std::cout<<"Unesite imena djece: "; 
    std::string znak; 
    std::getline(std::cin,znak); 
    for(int i=0; i<vel; i++){
        std::getline(std::cin,p.at(i));
    }
/*
    std::cout<<"STA JE UNESENO: "<<std::endl; 

    for(auto x:p){
        std::cout<<"."<<x;
        std::cout<<std::endl; 
    }
*/
    std::cout<<"Unesite broj timova: "; 
    int k=0; 
    std::cin>>k; 

    try{
        auto q = Razvrstavanje(p, k);
        for(int i=0; i<k; i++){
            int zadnji=q.at(i).size();
            std::cout<<"Tim "<<i+1<<": "; 
            for(auto x : q.at(i)){
                zadnji--; 
                if(zadnji==0) std::cout<<x;
                else std::cout<<x<<", ";
            }
            std::cout<<std::endl;
        }
    }
    catch(std::logic_error e){
        std::cout<<"Izuzetak: "<<e.what();
    }

  return 0;
}
