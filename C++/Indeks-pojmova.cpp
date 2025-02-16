//TP 2021/2022: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <set>

bool Slovo(char z){
    if(z>='A' && z<='Z') return true; 
    if(z>='a' && z<='z') return true; 
    if(z>='0' && z<='9') return true; 
    return false;
}

std::map<std::string,std::set<int>> KreirajIndeksPojmova(std::string s){
    std::map<std::string,std::set<int>> indeks{}; 

    s=s+' ';
    //s=' '+s;

    for(int i=0; i<s.length(); i++){
        s.at(i)= tolower(s.at(i));
    }

    std::string r;
    
    for(int i=0; i<s.length(); i++){

        if(Slovo( s.at(i) )){

            r.push_back(s.at(i));

            if( !Slovo(s.at(i+1)) && i<s.length()-1){

                int pozicija = i- r.length()+1;
                //std::cout<<r<<" "<<i<<" "<< r.length()<< " ";
                //std::cout<<pozicija<<std::endl; 

                auto it=indeks.find(r); 
                if(indeks.empty() || it==indeks.end()){
                   indeks.insert( {r, {pozicija} }); 
                }
                else{ 
                    it->second.insert(pozicija);
                }
                r="";
            }
            
        }

    }

    return indeks; 
}

void IspisiIndeksPojmova(std::map<std::string,std::set<int>> m){
     for(auto it=m.begin(); it!=m.end(); it++){
        std::cout<<it->first<<": "; 
        int vel=it->second.size();
        for(auto x : it->second){
            vel--;
            if(vel==0) std::cout<<x;
            else std::cout<<x<<","; 
        } 
        std::cout<<std::endl;
    }
}

std::set<int> PretraziIndeksPojmova( std::string rijec, std::map<std::string, std::set<int>> indeks){
    std::set<int> pozicije{};
    for(int i=0; i<rijec.length(); i++){
        rijec.at(i)= tolower(rijec.at(i));
    } 
    auto it= indeks.find(rijec); 
        if(it==indeks.end()) throw std::logic_error("Pojam nije nadjen");
        else{
            for(auto x : it->second){
                pozicije.insert(x);
            }
        }
    return pozicije; 
}

void test(){
    std::string s="abc qwe stsda abc abc dhi qwe hrkw dhi";
    std::string q="pqr, ab/123 (qwe) tt2 ";

    auto m=KreirajIndeksPojmova(s);
    IspisiIndeksPojmova(m);
    std::cout<<std::endl;
    auto n=KreirajIndeksPojmova(q);
    IspisiIndeksPojmova(n);
}


int main ()
{

    //test();
    std::string recenica; 
    std::cout<<"Unesite tekst: "; 
    std::getline(std::cin,recenica);
    auto indeksPojmova=KreirajIndeksPojmova(recenica);
    IspisiIndeksPojmova(indeksPojmova);
    std::string rijec; 

    for(;;){
        std::cout<<"Unesite rijec: ";
        std::getline(std::cin, rijec);
        if(rijec==".") break; 

        try{
           auto pozicije = PretraziIndeksPojmova(rijec,indeksPojmova); 
           
            for(auto x : pozicije){
                std::cout<<x<<" "; 
            }  
            std::cout<<std::endl; 
        }
        catch(std::logic_error e){
            std::cout<<"Unesena rijec nije nadjena!"<<std::endl;
        }

      
    }

	return 0;
}
