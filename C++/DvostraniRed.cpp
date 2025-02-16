#include<iostream>

template <typename Tip> 
class DvostraniRed{
    struct Cvor{
        Tip el; 
        Cvor *sljedeci; 
        Cvor *prethodni; 
    }; 
    Cvor * pocetak, *kraj;
    int duzina;
    void Iniciraj(); 
    void Unisti(); 

    public: 
    DvostraniRed(){Iniciraj();} 

    ~DvostraniRed(){Unisti();}

    DvostraniRed(const DvostraniRed &d){
        Cvor *p=d.pocetak; 
        duzina=d.duzina; 
        Cvor* novi=nullptr; 
         
        for(int i=0;i<duzina; i++){
            if(i==0){
                novi=new Cvor; 
                novi->el=p->el;
                novi->sljedeci=nullptr; 
                novi->prethodni=nullptr; 
                pocetak=novi; 
                kraj=novi; 
                p=p->sljedeci;
            }
            else{
                novi=new Cvor; 
                novi->el=p->el; 
                kraj->sljedeci=novi; 
                novi->sljedeci=nullptr; 
                novi->prethodni=kraj; 
                kraj=novi; 
                p=p->sljedeci;
            }
            
        }
        novi=nullptr; 
        p=nullptr; 
    }

    void brisi(){
        if(duzina==0) throw std::domain_error("Dek je prazan!"); 
        Unisti();
    }

    int brojElemenata(){ return duzina; }

    void staviNaVrh(const Tip &el){

        Cvor *novi = new Cvor; 
        novi->el= el; 

        if(duzina==0){
            kraj=pocetak=novi;
            novi->sljedeci=nullptr; 
            novi->prethodni=nullptr; 
        }
        else{
            kraj->sljedeci=novi; 
            novi->sljedeci=nullptr;
            novi->prethodni=kraj; 
            kraj=novi; 
        }
        novi=nullptr; 
        duzina++;
    }

    Tip skiniSaVrha(){
        if(duzina==0) throw std::domain_error("Dek je prazan!");
        Cvor *p=nullptr; 
        int izbaceni; 
        if(duzina==1){
            pocetak=nullptr; 
            izbaceni=kraj->el; 
            delete kraj; 
            kraj=nullptr; 
        }
        else{
            p=kraj; 
            kraj=kraj->prethodni; 
            izbaceni=p->el; 
            delete p; 
            p=nullptr; 
            kraj->sljedeci=nullptr; 
        }
        duzina--; 
        return izbaceni; 
    }

    Tip skiniSaCela(){
        if(duzina==0) throw std::domain_error("Dek je prazan!"); 
        Cvor * p= pocetak; 
        Tip izbaceni= pocetak->el; 
        if(duzina==1){
            pocetak=kraj=nullptr; 
            delete p; 
            p=nullptr; 
        }
        else{
            pocetak=pocetak->sljedeci; 
            delete p; 
            p=nullptr; 
            pocetak->prethodni=nullptr; 
        }
        duzina--; 
        return izbaceni; 
    }

    void staviNaCelo(const Tip &el){
        Cvor *novi = new Cvor; novi->el = el; 

        if(duzina==0){
            novi->sljedeci=novi->prethodni=nullptr;
            pocetak=kraj=novi; 
        }
        else{
            novi->sljedeci=pocetak; 
            pocetak->prethodni=novi; 
            novi->prethodni=nullptr; 
            pocetak=novi; 
        }
        novi=nullptr; 
        duzina++; 
    }
    Tip &vrh(){
        if(duzina==0) throw std::domain_error("Dek je prazan! "); 
        return kraj->el;
    }
    Tip &celo(){
        if(duzina==0) throw std::domain_error("Dek je prazan! "); 
        return pocetak->el;
    }
    DvostraniRed &operator=(const DvostraniRed &d){
        if(this==&d) return *this; 
        if(duzina!=0) this->brisi(); 
        Cvor *p=d.pocetak; 
        duzina=d.duzina; 
        Cvor * novi=nullptr; 

         
        for(int i=0;i<duzina; i++){
            if(i==0){
                novi=new Cvor; 
                novi->el=p->el;
                novi->sljedeci=nullptr; 
                novi->prethodni=nullptr; 
                pocetak=novi; 
                kraj=novi; 
                p=p->sljedeci;
            }
            else{
            novi=new Cvor; 
            novi->el=p->el; 
            kraj->sljedeci=novi; 
            novi->sljedeci=nullptr; 
            novi->prethodni=kraj; 
            kraj=novi; 
            p=p->sljedeci;
            }
        }
        novi=nullptr; 
        p=nullptr; 
        return *this; 
    }
};

template <typename Tip>
void DvostraniRed<Tip>::Iniciraj(){
    pocetak=kraj=nullptr; duzina=0; 
}

template <typename Tip>
void DvostraniRed<Tip>::Unisti(){
    if(duzina!=0){
        Cvor* p=pocetak; 
        kraj=nullptr; 
        if(duzina!=1){
            for(int i=0; i<duzina; i++){
                if(i!=duzina-1){
                    pocetak= pocetak->sljedeci; 
                    delete p; 
                    p=pocetak;
                }
                else{
                    pocetak->sljedeci=nullptr; 
                    pocetak=nullptr; 
                    delete p; 
                    p=nullptr;
                }
            }
        }
        else{
            pocetak=nullptr; 
            delete p; 
            p=nullptr;
        }
    duzina=0; 
    }
}

void Test1(){
    DvostraniRed<int> d; 
    d.staviNaCelo(2); 
    d.staviNaCelo(3); 
    d.staviNaCelo(4); 

    std::cout<< d.celo()<<std::endl; 
}

void Test2(){
    DvostraniRed<int> d; 
    d.staviNaVrh(2); 
    d.staviNaVrh(3); 
    d.staviNaVrh(4); 

    std::cout<< d.vrh()<<std::endl; 
}

void Test3(){
    DvostraniRed<int> d; 
    d.staviNaCelo(2); 
    d.staviNaCelo(3); 
    d.staviNaCelo(4); 
    d.skiniSaCela(); 
    d.skiniSaCela();
    std::cout<< d.celo()<<std::endl; 
}

void Test4(){
    DvostraniRed<int> d; 
    d.staviNaVrh(2); 
    d.staviNaVrh(3); 
    d.staviNaVrh(4); 
    d.skiniSaVrha(); 
    d.skiniSaVrha();
    std::cout<< d.vrh()<<std::endl; 
}

void Test5 (){
    DvostraniRed<int> d; 
    d.staviNaVrh(2); 
    d.staviNaVrh(3); 
    d.staviNaVrh(4); 
    d.staviNaCelo(2); 
    d.staviNaCelo(3); 
    d.staviNaCelo(4); 
    d.staviNaVrh(2); 
    d.staviNaVrh(3); 
    d.staviNaVrh(4);

    for(int i=0; i<d.brojElemenata(); i++ ){
        std::cout<<d.vrh(); d.skiniSaVrha(); 
    }

}

int main(){
    Test1(); 
    Test2(); 
    Test3(); 
    Test4(); 
    Test5();
    return 0; 
}