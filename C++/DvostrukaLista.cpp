
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std; 

template <typename Tip> class Iterator; 

template <typename Tip> class Lista{
    public: 
    Lista(){}; 
    virtual ~Lista(){}; 
    virtual int brojElemenata() const=0; 
    virtual Tip &trenutni()=0; 
    virtual Tip trenutni() const =0; 
    virtual bool prethodni() =0; 
    virtual bool sljedeci()=0;  
    virtual void pocetak()=0; 
    virtual void kraj()=0; 
    virtual void obrisi()=0; 
    virtual void dodajIspred(const Tip& el) =0; 
    virtual void dodajIza(const Tip& el) =0;
    virtual Tip operator[] (int indeks) const =0; 
    virtual Tip &operator[] (int indeks)=0; 
};

template <typename Tip>
class DvostrukaLista : public Lista<Tip>{
    private: 
    struct Cvor{
        Tip element; 
        Cvor *sljedeciEl, *prethodniEl; 
        /*Cvor(const Tip &element, Cvor *prev, Cvor *next=0): element(element), prethodniEl(prev), sljedeciEl(next){
            if(prethodniEl!=0) prethodniEl->sljedeciEl=this; 
            if(sljedeciEl!=0) sljedeciEl->prethodniEl=this; 
        }
        Cvor(Cvor* prev=0, Cvor* next=0) : prethodniEl(prev),sljedeciEl(next){ 
            if(prethodniEl!=0) prethodniEl->sljedeciEl=this; 
            if(sljedeciEl!=0) sljedeciEl->prethodniEl=this;
        }*/
    }; 
    Cvor *prvi, *zadnji, *tekuci; 
    int duzina; 
    void Iniciraj(); 
    void Unisti();

    public: 
    //DvostrukaLista(): Lista<Tip>(), prvi(nullptr), zadnji(nullptr),tekuci(nullptr), duzina(0){ }
    DvostrukaLista(int velicina =10) {Iniciraj();}
    DvostrukaLista( const DvostrukaLista<Tip> &l){
        if(l.duzina==0)  throw std::domain_error("Prazna lista >:( ");
        duzina= l.duzina; 
        Cvor *priv = l.prvi, *pomocni= nullptr, *novi = new Cvor; 
        novi->element = priv->element; 
        prvi=novi; 
        prvi->prethodniEl=nullptr; 
        priv = priv->sljedeciEl; 
        pomocni= prvi; 
        while( priv != 0){
            novi = new Cvor; 
            novi->element = priv->element; 
            pomocni->sljedeciEl = novi; 
            novi->prethodniEl = pomocni; 
            if(priv ==l.tekuci) tekuci=novi; 
            if(priv == l.zadnji) zadnji=novi; 
            pomocni = pomocni->sljedeciEl; 
            priv = priv->sljedeciEl; 
        }
        zadnji->sljedeciEl = nullptr; 
    }

    ~DvostrukaLista() 
    {
        Unisti();
        //prvi=nullptr; 
        //tekuci=nullptr;
        //zadnji=nullptr; 
       // lduzina=dduzina=0; 
    }

    int brojElemenata() const{ return duzina;} 
    Tip &trenutni(){ return tekuci->element; } 
    Tip trenutni() const{ return tekuci->element;} 
    bool prethodni(){
        if(duzina==0) throw std::domain_error("Lista je prazna!");
        if(tekuci==prvi) return false; 
        tekuci=tekuci->prethodniEl; 
        return true; 
    };
    bool sljedeci(){
        if(duzina==0) throw std::domain_error("Lista je prazna!");
        if(tekuci==zadnji) return false; 
        tekuci=tekuci->sljedeciEl; 
        return true; 
    }  
    void pocetak(){ tekuci=prvi; } 
    void kraj(){ tekuci= zadnji; } 
    void obrisi(){
        if(duzina ==0) throw std::domain_error("Nista za birsati!"); 
        if(prvi==zadnji){
            tekuci=prvi=nullptr; 
            delete zadnji; 
        }
        else if(prvi== tekuci){
            prvi=prvi->sljedeciEl; 
            Cvor * pomocni= tekuci; 
            tekuci=tekuci->sljedeciEl; 
            prvi->prethodniEl=nullptr; 
            delete pomocni; 
        }
        else if(tekuci==zadnji){
            zadnji=zadnji->prethodniEl; 
            zadnji->sljedeciEl = nullptr; 
            Cvor *pom = tekuci; 
            pom=pom->prethodniEl; 
            delete tekuci; 
            tekuci=pom; 
        }
        else{
            tekuci->prethodniEl->sljedeciEl = tekuci->sljedeciEl; 
            tekuci->sljedeciEl ->prethodniEl= tekuci->prethodniEl; 
            Cvor *pom = tekuci; 
            pom=pom->sljedeciEl; 
            delete tekuci; 
            tekuci=pom;
        }
        duzina--; 
        /*Tip x = tekuci->sljedeciEl->element; 
        Cvor * lprvi= tekuci->sljedeciEl; 
        lprvi->sljedeciEl->prethodniEl = tekuci; 
        tekuci->sljedeciEl= lprvi->sljedeciEl;
        delete lprvi; 
        duzina--; */
        
    }

    void dodajIspred(const Tip& el); 
    void dodajIza(const Tip& el);
    Tip operator[] (int indeks) const; 
    Tip &operator[] (int indeks); 
    DvostrukaLista<Tip> operator = (const DvostrukaLista<Tip> l){
        if(this==&l) return *this; 
        Cvor * pomocni=nullptr; 
        Cvor *priv= prvi; 
        while(priv!= nullptr){
            pomocni=priv; 
            priv= priv->sljedeciEl; 
            delete pomocni; 
        }
        if(l.duzina==0) throw std::domain_error("Lista je prazna!"); 
        duzina= l.duzina; 
        priv = l.prvi; 
        pomocni=nullptr; 

        Cvor  *novi = new Cvor; 
        novi->element = priv->element; 
        prvi=novi; 
        prvi->prethodniEl=nullptr; 
        priv = priv->sljedeciEl; 
        pomocni= prvi; 
        while( priv != 0){
            novi = new Cvor; 
            novi->element = priv->element; 
            pomocni->sljedeciEl = novi; 
            novi->prethodniEl = pomocni; 
            if(priv ==l.tekuci) tekuci=novi; 
            if(priv == l.zadnji) zadnji=novi; 
            pomocni = pomocni->sljedeciEl; 
            priv = priv->sljedeciEl; 
        }
        zadnji->sljedeciEl = nullptr; 
        return *this; 
    }

    friend class Iterator<Tip>;
};


template <typename Tip> 
void DvostrukaLista<Tip>::Iniciraj(){
    tekuci= prvi = zadnji =nullptr;
    duzina=0; 
}

template <typename Tip> 
void DvostrukaLista<Tip>::Unisti(){
    while(prvi!=nullptr){
        tekuci=prvi; 
        prvi=prvi->sljedeciEl; 
        delete tekuci; 
        tekuci= nullptr; 
    }
}

template <typename Tip> 
void DvostrukaLista<Tip>::dodajIza(const Tip& el){
    Cvor * novi = new Cvor; 
    novi->element=el; 
    if(prvi==nullptr){
        novi->sljedeciEl= novi->prethodniEl=nullptr;
        prvi=novi; 
        tekuci=novi; 
        zadnji=novi; 
    } 
    else if(tekuci==zadnji){
        novi->prethodniEl= zadnji;
        novi->sljedeciEl=nullptr;
        zadnji->sljedeciEl=novi;
        zadnji=novi;
    }
    else{
        novi->prethodniEl=tekuci; 
        novi->sljedeciEl= tekuci->sljedeciEl; 
        tekuci->sljedeciEl=novi; 
        novi->sljedeciEl->prethodniEl =  novi; 
    }
    duzina++; 
}

template <typename Tip> 
void DvostrukaLista<Tip>::dodajIspred(const Tip& el){
    /*
    Cvor * novi = new Cvor; 
    novi->element=el; 
    if(prvi==nullptr){
        novi->sljedeciEl= novi->prethodniEl=nullptr;
        prvi=novi; 
        tekuci=novi; 
        zadnji=novi; 
    } 
    else if(tekuci==zadnji){
        tekuci->prethodniEl= novi;
        novi->sljedeciEl=tekuci;
        prvi=novi;
    }
    else{
        novi->prethodniEl=tekuci->prethodniEl; 
       tekuci->prethodniEl =novi; 
       novi->sljedeciEl = tekuci; 
       novi->prethodniEl->sljedeciEl = novi; 
    }
    duzina++; */

    if(duzina==0){
        prvi=new Cvor(); 
        prvi->element=el;
        prvi->sljedeciEl=nullptr;
        prvi->prethodniEl=nullptr; 
        tekuci=prvi; 
        zadnji=prvi; 
        duzina++; 
    }
    else if(tekuci==prvi){
        Cvor *novi = new Cvor();
        novi->element=el; 
        novi->sljedeciEl = prvi; 
        novi->prethodniEl=nullptr; 
        prvi->prethodniEl=novi; 
        prvi=novi; 
        duzina++; 
    }
    else {
        Cvor * novi= new Cvor(); 
        novi->element= el; 
        novi->sljedeciEl=tekuci; 
        Cvor *pomocni=tekuci->prethodniEl; 
        novi->prethodniEl= pomocni;
        pomocni->sljedeciEl= novi; 
        tekuci->prethodniEl=novi; 
        duzina++;  
    }
}

template <typename Tip> 
Tip  DvostrukaLista<Tip>::operator[] (int indeks) const{
    
    if( (indeks<0) || indeks>duzina) throw std::domain_error("Neispravan indeks!"); 
    Cvor * pom=prvi; 
    for(int i=0; i<indeks; i++){
        pom=pom->sljedeciEl; 
    } 
    return pom->element; 
}

template <typename Tip> 
Tip &DvostrukaLista<Tip>::operator[] (int indeks){

    if( (indeks<0) || indeks>duzina) throw std::domain_error("Neispravan indeks!"); 
    Cvor * pom=prvi; 
    for(int i=0; i<indeks; i++){
        pom=pom->sljedeciEl; 
    } 
    return pom->element; 
    /*
    int p=0, ld=lduzina, dd=dduzina; 
    dduzina=dduzina+lduzina-indeks; 
    lduzina=indeks; 
    int k=0; 
    if(indeks < std::abs(indeks-ld) &&  (indeks < (ld+dd)/2) ) {
        k=indeks; 
        tekuci=prvi; 
    }
    else if( std::abs( indeks-ld)< ld+dd-indeks){
        k=indeks-ld;  
    }
    else {
        k = indeks-ld-dd-1; 
        tekuci=zadnji;
    }
    if(k<0){
        for(int i=0; i<std::abs(k); i++){
            tekuci=tekuci->sljedeciEl; 
        }
    }
    else{
        for(int i=0; i<k; i++){
            tekuci=tekuci->sljedeciEl;
        }
    }
    return this->trenutni(); */

}

// treba nam iterator :3 

template <typename Tip>
class Iterator{
    const DvostrukaLista<Tip> *s;
    typename DvostrukaLista<Tip>::Cvor *tren; 
    public: 
    Iterator(const Lista<Tip> &d){
        if(typeid(d) == typeid(DvostrukaLista<Tip>)){
            s = (const DvostrukaLista<Tip> *)&d; 
            tren=s->tekuci;
        }
    }
    Iterator(const DvostrukaLista<Tip> &d){ s=&d; tren= s->tekuci; }
    bool prethodni(){ 
        if(s->duzina==0) throw std::domain_error("Prazna lista ! >:( "); 
        if(tren==s->prvi) return false; 
        tren=tren->prethodniEl; 
        return true; 
    }
    bool sljedeci(){ 
        if(s->duzina==0) throw std::domain_error("Prazna lista ! >:( "); 
        if(tren==s->zadnji) return false; 
        tren=tren->sljedeciEl; 
        return true; 
    }
    void pocetak(){
        tren=s->prvi; 
    }
    void kraj(){
        tren=s->zadnji; 
    }
    Tip &trenutni(){
        return tren->element; 
    }
};

// maxxx :3

template<typename Tip>

Tip dajMaksimum(const Lista<Tip> &l){
    Iterator<Tip> it=l; 
    it.pocetak(); 
    Tip max= it.trenutni(); 
     
    for(int i=1; i<l.brojElemenata();i++){
        it.sljedeci();
        if(it.trenutni()>max) max=it.trenutni(); 
        //it.sljedeci();
    }
    return max; 
}


// TESTOVI //

void Test1(){
    DvostrukaLista<int> l; 
    for(int i=1; i<40; i++){
        l.dodajIspred(i); 
    }
    std::cout<<l.brojElemenata();
}

void Test2(){
    DvostrukaLista<string> rec; 
    rec.dodajIza("archer"); 
    rec.dodajIza("taylor"); 
    rec.sljedeci(); 
    rec.dodajIza("swift"); 
    rec.sljedeci(); 
    rec.dodajIza("2020"); 
    rec.pocetak(); 
    for(int i=0; i<4; i++){
        std::cout<<rec.trenutni()<<" ";
        rec.sljedeci();
    }
}

void Test3(){
    DvostrukaLista<string> rec; 
    rec.dodajIspred("this is me trying"); 
    rec.dodajIspred("taylor"); 
    rec.prethodni(); 
    rec.dodajIspred("swift"); 
    rec.prethodni(); 
    rec.dodajIspred("2020"); 
    rec.pocetak(); 
    for(int i=0; i<4; i++){
        std::cout<<rec.trenutni()<<" ";
        rec.sljedeci();
    }
}

void Test4(){
    DvostrukaLista<int> l; 
    for(int i=1; i<40; i++){
        l.dodajIspred(i); 
    }
    l.pocetak(); 
    std::cout<<l.trenutni();
}

void Test5(){
    DvostrukaLista<int> l; 
    for(int i=1; i<40; i++){
        l.dodajIspred(i); 
    }
    l.kraj(); 
    std::cout<<l.trenutni();
}

void Test6(){
    DvostrukaLista<int> l; 
    for(int i=1; i<40; i++){
        l.dodajIspred(i); 
    }
    std::cout<<l.trenutni()<<" "; 
    //for(int i=0; i<4; i++) l.sljedeci(); 
    l.obrisi(); 
    std::cout<<l.trenutni();
}

void Test7(){
    DvostrukaLista<int> l; 
    for(int i=1; i<40; i++){
        l.dodajIspred(i); 
    }
    l.pocetak();
    for(int i=0; i<l.brojElemenata(); i++){
        std::cout<<l.trenutni()<<" "; 
        l.sljedeci();
    }
}

void Test8(){
    DvostrukaLista<int> l; 
    for(int i=1; i<40; i++){
        l.dodajIspred(i); 
    }
    l.kraj();
    for(int i=0; i<l.brojElemenata(); i++){
        std::cout<<l.trenutni()<<" "; 
        l.prethodni();
    }
}

void TestMaximuma(){
    DvostrukaLista<int> l; 
    l.dodajIspred(5); l.dodajIza(4); l.dodajIspred(54); l.dodajIspred(43); l.dodajIspred(3); l.dodajIza(109);
    std::cout<< dajMaksimum(l)<<std::endl; 
}

int main(){
    Test1();
    std::cout<<std::endl; 
    Test2();
    std::cout<<std::endl; 
    Test3();
    std::cout<<std::endl; 
    Test4();
    std::cout<<std::endl; 
    Test5();
    std::cout<<std::endl; 
    Test6();
    std::cout<<std::endl; 
    Test7();
    std::cout<<std::endl; 
    Test8();
    std::cout<<std::endl; 
    TestMaximuma();

    return 0; 
}