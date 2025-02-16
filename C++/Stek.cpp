#include<iostream>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std; 

template <typename Tip>
class AStek{
    private : 
    void operator = (const AStek&); 
    AStek(const AStek&); 
    public:
    AStek(){};
    virtual void brisi() = 0; 
    virtual void stavi(const Tip& el)=0; 
    virtual Tip skini() =0; 
    virtual Tip& vrh()=0;
    virtual int brojElemenata() const =0; 
};

template <typename Tip>
class Stek : public AStek<Tip>{
    private: 
    struct Cvor{
        Tip info; 
        Cvor *sljedeci; 
        Cvor(const Tip &info, Cvor *sljedeci): info(info), sljedeci(sljedeci){}
    }; 
    Cvor* Vrh; 
    int velicina; 
    void Kopiraj(const Stek &s); 

    public: 
    Stek() : Vrh(0), velicina(0){}
    Stek(const Stek &s){ Kopiraj (s);}
    ~Stek(){ brisi();}
    Stek &operator=(const Stek &s);
    void stavi(const Tip &info){  Vrh = new Cvor(info, Vrh); velicina++;}
    Tip skini(); 
    Tip& vrh(); 
    void brisi();
    bool JeLiPrazan() const {return Vrh==0;}
    int brojElemenata() const {return velicina; }
    void prikazi() const; 
};

template <typename Tip>
void Stek<Tip>::Kopiraj(const Stek &s){
    Cvor *q, *p(s.Vrh);
    Vrh=0; 
    velicina = s.velicina; 
    while(p!=nullptr){
        Cvor *n = new Cvor(p->info,0); 
        if(Vrh==0) Vrh=n; 
        else  q->sljedeci=n; 
        p=p->sljedeci; 
        q=n;
    }
}

template <typename Tip>
Stek<Tip> &Stek<Tip>::operator = (const Stek &s){
    if(&s==this) return *this; 
    brisi(); 
    Kopiraj(s); 
    return *this;
}

template <typename Tip>
Tip Stek<Tip>::skini(){
    if(Vrh==nullptr) throw std::domain_error("Stek je prazan!"); 
    Tip info=Vrh->info; 
    Cvor *p= Vrh->sljedeci; 
    delete Vrh; 
    Vrh = p; 
    velicina--; 
    return info; 
}

template <typename Tip>
void Stek<Tip>::brisi(){
    while(!JeLiPrazan()){
        skini();
    }
}

template <typename Tip>
Tip& Stek<Tip>::vrh(){
    if(Vrh==0) throw std::domain_error("Stek je prazan!");
    return Vrh->info;
}

template <typename Tip>
void Stek<Tip>::prikazi() const{
    std::cout<<"Sadržaj steka: "<<std::endl;
    Cvor *p=Vrh; 
    while(p!=nullptr){
        std::cout << p->info<<" "; 
        p=p->sljedeci;
    }
    std::cout<<std::endl;
}

void pretraga(Stek<std::vector<int> >& s, int trazeni){
    if(s.brojElemenata() ==0){
        std::cout<<"Nema elementa";
        return; 
    }
    std::vector<int> v= s.skini(); 
    int vrh=v.size()-1; 
    int dno=0; 
    int srednji; 
    
    while(vrh>=dno){
        srednji=(vrh+dno)/2; 
        if(trazeni==v[srednji]){
            std::cout<< srednji <<" "<<s.brojElemenata(); 
            s.stavi(v); 
            return;   
        }else if(v[srednji]<trazeni){
            dno=srednji+1; 
        }
        else{
            vrh=srednji-1; 
        }
    }
    pretraga(s,trazeni); 
    s.stavi(v);
}

void Test1(){
    std::vector<int> v{1,2,3,4}; 
    Stek<std::vector<int>> s; 
    s.stavi(v); 
    v={43,53,64,214}; 
    s.stavi(v); 
    v={41,51,69}; 
    s.stavi(v); 

    pretraga(s, 4);
}

void Test2(){
    std::vector<int> v{12,23,34,46}; 
    Stek<std::vector<int>> s; 
    s.stavi(v); 
    v={43,53,64,214}; 
    s.stavi(v); 
    v={41,51,69}; 
    s.stavi(v); 

    pretraga(s, 69);
}

void Test3(){
    Stek<std::vector<int>> s; 
    std::vector<int> v; 
    for(int j=0; j<5; j++){
        for(int i=0; i<1000; i++){
        v.push_back(i*j);
        }
        s.stavi(v);
    }
    pretraga(s,3996);
}

int main(){

    Test1();
    std::cout<<std::endl;
    Test2();
    std::cout<<std::endl;
    Test3();
    return 0; 
}