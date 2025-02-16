//TP 2021/2022: Zadaća 5, Zadatak 2
#include <exception>
#include <iostream>
#include <cmath>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional> 
#include <iomanip>
#include <iterator>

class Berza{

    private: 

    int maxCijena,minCijena; 
    std::vector<int> cijene;

    public: 

    Berza(int min, int max){ if(min<0 || max<0) throw std::range_error("Ilegalne granice cijene");  maxCijena=max; minCijena=min; };
    Berza(int max){if(max<0) throw std::range_error("Ilegalne granice cijene");maxCijena=max; minCijena=0; };
    int DajMax(){return maxCijena;}
    int DajMin(){return minCijena;}
    void RegistrirajCijenu(int novaCijena);
    int DajBrojRegistriranihCijena(){ return cijene.size();}
    void BrisiSve(){ cijene.clear();}
    int DajMinimalnuCijenu(){
        if(cijene.size()==0) throw std::range_error("Nema registriranih cijena"); 
        return *std::min_element(cijene.begin(),cijene.end());
    }
    int DajMaksimalnuCijenu(){ 
        if(cijene.size()==0) throw std::range_error("Nema registriranih cijena");
        return *std::max_element(cijene.begin(),cijene.end());
    }
    int DajBrojCijenaVecihOd(int nova){
        int brojCijena=0;
        if(cijene.size()==0) throw std::range_error("Nema registriranih cijena");
        return std::count_if(cijene.begin(),cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1,nova));
    }
    bool operator !(){if(cijene.size()==0) return true; return false;}
    void Ispisi() const;
    double operator [](double x){ if (x>cijene.size() || x<0 ) throw std::range_error("Neispravan indeks"); return cijene.at(x-1);}
    friend Berza &operator ++(Berza &b);
    friend Berza operator ++(Berza &b,int);
    friend Berza &operator --(Berza &b);
    friend Berza operator --(Berza &b,int);
    friend bool operator ==(const Berza &b1, const Berza &b2);
    friend bool operator !=(const Berza &b1, const Berza &b2);
    friend Berza operator +(Berza &b1, int y);
    friend Berza operator +(int y,Berza &b1);
    friend Berza operator +(Berza &b1, Berza &b2);
    friend Berza operator +=(Berza &b, int p);
    friend Berza operator -(Berza &b1, int y);
    friend Berza operator -(int y,Berza &b1);
    friend Berza operator -(Berza &b);
    friend Berza operator -(Berza &b1, Berza &b2);
    friend Berza operator -=(Berza &b, int p);
};

void Berza::RegistrirajCijenu(int novaCijena){
    if(novaCijena>=minCijena && novaCijena<=maxCijena){
        cijene.push_back(novaCijena);
    }
    else throw std::range_error("Ilegalna cijena");
}

    Berza &operator ++(Berza &b){
        std::vector<int> pom(b.cijene.size(),100);
        std::transform(b.cijene.begin(),b.cijene.end(),pom.begin(),b.cijene.begin(), std::plus<int>());
        return b; 
    }
    
    Berza operator ++(Berza &b,int){
        Berza pom=b;
        ++b;
        return pom;
    }
    Berza &operator --(Berza &b){
        std::vector<int> pom(b.cijene.size(),100);
        std::transform(b.cijene.begin(),b.cijene.end(),pom.begin(),b.cijene.begin(), std::minus<int>());
        return b; 
    }

    Berza operator --(Berza &b,int){
        Berza pom=b;
        --b;
        return pom;
    }

    bool operator ==(const Berza &b1, const Berza &b2){
        bool rez;
        if(b1.cijene.size()!=b2.cijene.size()) rez= false;
        else rez=std::equal(b1.cijene.begin(),b1.cijene.end(), b2.cijene.begin(),std::bind( std::equal_to<int>(),std::placeholders::_1,std::placeholders::_2));
        return rez; 
    }

    bool operator !=(const Berza &b1, const Berza &b2){
        if(b1==b2) return false; 
        else return true; 
    }

    Berza operator +(Berza &b1, int y){
        Berza nova=b1; std::vector<int> pom(b1.cijene.size(),y);
        std::transform(nova.cijene.begin(),nova.cijene.end(),pom.begin(),nova.cijene.begin(), std::plus<int>());
        return nova;
    }

    Berza operator +(int y,Berza &b1){
        Berza nova=b1;
        nova=b1+y; 
        return nova;
    }

    Berza operator +(Berza &b1, Berza &b2){
        Berza nova=b1;
        std::transform(nova.cijene.begin(),nova.cijene.end(),b2.cijene.begin(),nova.cijene.begin(), std::plus<int>());
        return nova;
    }

    Berza operator +=(Berza &b, int p){
        std::vector<int> pom(b.cijene.size(),p);
        std::transform(b.cijene.begin(),b.cijene.end(),pom.begin(),b.cijene.begin(), std::plus<int>());
        return b;
    }

    Berza operator -(Berza &b1, int y){
        Berza nova=b1; std::vector<int> pom(b1.cijene.size(),y);
        std::transform(nova.cijene.begin(),nova.cijene.end(),pom.begin(),nova.cijene.begin(), std::minus<int>());
        return nova;
    }

    Berza operator -(int y,Berza &b1){
        Berza nova=b1; std::vector<int> pom(b1.cijene.size(),y);
        std::transform(pom.begin(),pom.end(),nova.cijene.begin(),nova.cijene.begin(), std::minus<int>());
        return nova;
    }
    
    Berza operator -(Berza &b){
        int y=b.DajMax()+b.DajMin();
        return y-b; 
    }

    Berza operator -(Berza &b1, Berza &b2){
        Berza nova=b1;
        std::transform(nova.cijene.begin(),nova.cijene.end(),b2.cijene.begin(),nova.cijene.begin(), std::minus<int>());
        return nova;
    }

    Berza operator -=(Berza &b, int p){
        std::vector<int> pom(b.cijene.size(),p);
        std::transform(b.cijene.begin(),b.cijene.end(),pom.begin(),b.cijene.begin(), std::minus<int>());
        return b;
    }

    void Berza::Ispisi() const {
        std::vector<double> pomocni(cijene.size());
        std::copy(cijene.begin(),cijene.end(),pomocni.begin());
        std::sort(pomocni.begin(),pomocni.end(),std::greater<double>());
        std::transform(pomocni.begin(),pomocni.end(), pomocni.begin(), std::bind(std::divides<double>(),std::placeholders::_1,100));
        std::ostream_iterator<double> ispis(std::cout<<std::fixed<<std::setprecision(2),"\n"); 
        std::copy(pomocni.begin(),pomocni.end(),ispis);
    }

int main ()
{


	return 0;
}