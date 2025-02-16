#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std; 

template <typename Tip>
class ARed{
    private: 
    void operator =(const ARed&);
    ARed(const ARed&);
    public: 
    ARed(){}
    virtual ~ARed(){}
    virtual void brisi() = 0; 
    virtual void stavi(const Tip&) = 0; 
    virtual Tip skini() =0; 
    virtual Tip& celo() = 0; 
    virtual int brojElemenata() const =0; 
};

template <typename Tip>
class Red : public ARed<Tip>{
    private:
    struct Cvor{
        Tip info; 
        Cvor * sljedeci; 
        Cvor(const Tip &info, Cvor *sljedeci): info(info), sljedeci(sljedeci) {}
    };

    Cvor *pocetak, *kraj; 
    int velicina; 
    void Unisti(); 
    void Kopiraj (const Red &q);

    public: 

    Red() : pocetak(0), kraj(0), velicina(0) {}
    Red(const Red &q) { 
        Cvor *p=q.pocetak; 
        while(p!=nullptr){
        this->stavi(p->info); 
        p=p->sljedeci; 
        }
    }
    ~Red() {Unisti();}
    Red &operator = (const Red &q); 
    void brisi() {Unisti();}
    void stavi(const Tip &info); 
    Tip skini();
    Tip& celo() { return pocetak->info;}
    int brojElemenata() const { return velicina; }
    bool JeLiPrazan() const { return pocetak == nullptr; }
    void prikazi() const; 
};

template <typename Tip> 
void Red<Tip>::Kopiraj(const Red &q){
    Cvor *p=q.pocetak; 
    while(p!=nullptr){
        this->stavi(p->info); 
        p=p->sljedeci; 
    }
}

template <typename Tip> 
Red<Tip> &Red<Tip>::operator = (const Red &q){
    if(&q==this) return *this; 
    Unisti(); Kopiraj(q); return *this;
}

template <typename Tip> 
void Red<Tip>::Unisti(){
    while(!JeLiPrazan()){
        this->skini();
    }
}

template <typename Tip> 
void Red<Tip>::stavi(const Tip &info){
    Cvor *n = new Cvor(info, 0); 
    if(pocetak==nullptr) pocetak=kraj=n; 
    else{
        kraj->sljedeci= n; 
        kraj=kraj->sljedeci;
    }
    velicina++; 
}

template <typename Tip> 
Tip Red<Tip>::skini(){
    if(pocetak == nullptr) throw std::domain_error("Red je prazan!"); 
    Tip info = pocetak->info; 
    Cvor *p=pocetak; 
    if(pocetak==kraj) pocetak=kraj=nullptr;
    else pocetak=pocetak->sljedeci; 
    delete p; 
    velicina--; 
    return info; 
}

template <typename Tip> 
void Red<Tip>::prikazi() const{
    Cvor *p= pocetak; 
    while(p!=nullptr){
        std::cout << p->info <<" ";
        p=p->sljedeci;  
    }
}

void TestStavi(){
    Red<int> r; 
    for( int i=0; i<10; i++) r.stavi(i*2); 
    r.prikazi();
}

void TestSkini(){
    Red<int> r; 
    for( int i=0; i<10; i++) r.stavi(i*2); 
    for(int i=0; i<4; i++) r.skini(); 
    r.prikazi();
}

void TestBroj(){
    Red<int> r; 
    for( int i=0; i<10; i++) r.stavi(i*2); 
    for(int i=0; i<4; i++) r.skini(); 
    r.stavi(4); 
    r.stavi(53); 
    std::cout<<r.brojElemenata();
}

void TestCelo(){
    Red<int> r; 
    for( int i=0; i<10; i++) r.stavi(i*2); 
    for(int i=0; i<4; i++) r.skini(); 
    r.stavi(4); 
    r.stavi(53); 
    r.skini(); 
    std::cout<<r.celo(); 
}

void TestBrisi(){
    Red<int> r; 
    for( int i=0; i<10; i++) r.stavi(i*2); 
    for(int i=0; i<4; i++) r.skini(); 
    r.stavi(4); 
    r.stavi(53); 
    r.skini(); 
    r.brisi(); 
    std::cout<<r.brojElemenata(); 
}

int main(){


int brel;
Red<int> r;
for (int i(1); i<=5; i++)
	r.stavi(i);
    
{
        // Konstruktor kopije
	Red<int> r2(r);
	Red<int> r3;
        // Operator dodjele
	(r3=r).brojElemenata();
        // Destruktivna samododjela
        (r=r).brojElemenata();

	r.skini();
	brel = r2.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << r2.skini() << " ";
	brel = r3.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << r3.skini() << " ";
        
}
brel = r.brojElemenata();
for (int i(0); i<brel; i++)
	std::cout << r.skini() << " ";


    /*
    TestStavi();
    std::cout<<std::endl;
    TestSkini();
    std::cout<<std::endl;
    TestBroj();
    std::cout<<std::endl;
    TestCelo();
    std::cout<<std::endl;
    TestBrisi();*/
    return 0;
}  