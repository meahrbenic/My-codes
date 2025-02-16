#include <iostream>
#include <utility> 
#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

template<typename TipKljuca,typename TipVrijednosti>
class Mapa{
    public:
    Mapa(){}
    virtual ~Mapa(){}
    virtual TipVrijednosti &operator[] (TipKljuca k)=0;
    virtual TipVrijednosti operator[] (const TipKljuca k)const=0;
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca &kljuc)=0;
};

template <typename TipKljuca, typename TipVrijednost>
class AVLStabloMapa : public Mapa<TipKljuca,TipVrijednost>{
    int vel=0; 
    struct Cvor{
        TipKljuca kljuc; 
        TipVrijednost vrijednost; 
        Cvor *lijevo = nullptr; 
        Cvor*desno = nullptr; 
        Cvor *parent=nullptr; 
        int balans=0; 
        Cvor(const TipKljuca &k, const TipVrijednost &vr){
            kljuc =k; vrijednost=vr; parent=nullptr; lijevo=nullptr; desno=nullptr;  
        }
    }; 

    Cvor* vrh=nullptr; 
    void rotirajLijevo( Cvor *n){
        Cvor *lijevi_desnog; 
        int uslov=0; 
        lijevi_desnog=n->desno->lijevo; 
        n->balans=0;
        Cvor *desni=n->desno; 
        Cvor* desni_rod; 
        desni_rod=n->parent; 
        desni->parent=desni_rod; 
        desni->lijevo=n; 

        if(!desni->parent && !uslov){
            vrh=desni; 
            uslov=1; 
        }
        else if(desni_rod->desno==n && !uslov){
            desni->parent->desno=desni; 
            uslov =1; 
        }
        if(uslov==0){
            desni->parent->lijevo=desni; 
        }
        desni->balans=0; 
        if(lijevi_desnog){
            lijevi_desnog->parent=n; 
        }
        n->desno=lijevi_desnog; 
        n->parent=desni; 
    }
    
    void rotirajDesno(Cvor *n){
        Cvor *desni_lijevog;
        int uslov=0; 
        desni_lijevog=n->lijevo->desno; 
        n->balans=0; 
        Cvor *lijevi=n->lijevo; 
        Cvor *lijevi_rod; 
        lijevi_rod=n->parent; 
        lijevi->parent=lijevi_rod; 
        lijevi->desno=n; 

        if(!lijevi->parent && !uslov){
            vrh=lijevi; 
            uslov=1; 
        }
        else if(lijevi_rod->desno ==n && !uslov){
            lijevi->parent->desno=lijevi; 
            uslov=1; 
        }
        if(uslov==0){
            lijevi->parent->lijevo=lijevi;
        }
        lijevi->balans=0; 
        if(desni_lijevog){
            desni_lijevog->parent =n; 
        }
        n->lijevo=desni_lijevog; 
        n->parent=lijevi;
    }

    void azurirajBalans(Cvor *n, int sadrzi=0){
        if(!n) return; 
        else if(sadrzi){
            n->balans=n->balans-1; 
        }
        else{
            n->balans=n->balans+1;
        }
        int b=n->balans; 
        if(n->parent){
            if(n->parent->desno==n) sadrzi=1; 
            else sadrzi=0; 
        }
        if(b==2){
            if(n->lijevo->balans==1) rotirajDesno(n);
            else{
                rotirajLijevo(n->lijevo); 
                rotirajDesno(n);
            }
        }
        else if(b==-2){
            if(n->desno->balans==-1) rotirajLijevo(n);
            else{
                rotirajDesno(n->desno);
                rotirajLijevo(n); 

            }
        }
        else{
            if(!b) return;
            azurirajBalans(n->parent,sadrzi);
        }
    }
    void kopiraj(Cvor *&c1, Cvor *c2){
        if(c2!=nullptr){
            c1=new Cvor(c2->kljuc, c2->vrijednost); 
            c1->parent=c2->parent; 
            c1->lijevo=nullptr; 
            c1->desno=nullptr; 
            c1->balans=c2->balans; 
            kopiraj(c1->lijevo,c2->lijevo); 
            kopiraj(c1->desno, c2->desno);
        }
    }

    public: 

    AVLStabloMapa() : vrh(nullptr), vel(0){}
    AVLStabloMapa(const AVLStabloMapa &p){
        kopiraj(vrh, p.vrh); 
        vel=p.vel; 
    }
    ~AVLStabloMapa(){ if(vel!=0) obrisi();}
    int brojElemenata()const{
        return vel;
    }
   TipVrijednost &operator [](TipKljuca k){
        Cvor *p1;
        p1=vrh;
        while(p1){
            if((p1->kljuc)==k)return p1->vrijednost;
            else if(k>p1->kljuc){
                p1=p1->desno;
             }
             else{
                 p1=p1->lijevo;
             }   
        }
        if(!p1){
            vel=vel+1;
            Cvor*p3,*p4;
            p3=vrh;
            p4=nullptr;
            TipVrijednost pom=TipVrijednost();
            p1=new Cvor(k,pom);
            while(p3){
                p4=p3;
                if((p3->kljuc)>(p1->kljuc)){
                    p3=p3->lijevo;
                }
                else{
                    p3=p3->desno;
                }
            }
            if(!p4){
                vrh=p1;
            }
            else if(p4->kljuc>p1->kljuc){
                p4->lijevo=p1;
                p1->parent=p4;
            }
            else{
                p4->desno=p1;
                p1->parent=p4;
            }
            if(!p4)return p1->vrijednost; 
            //dodano azuriranje balansa
            if(p4->lijevo && p4->desno)p4->balans=0;
            else{
                int sadrzi;
                if(p4->lijevo)sadrzi=0;
                if(p4->desno)sadrzi=1;
                azurirajBalans(p4,sadrzi);
            }
        }
        return p1->vrijednost;
    }

    TipVrijednost operator [](const TipKljuca k)const {
        Cvor*p1=vrh; 
        while(p1){
            if(p1->kljuc==k)return p1->vrijednost; 
            else if((p1->kljuc) > k) p1=p1->lijevo;
            else p1=p1->desno;
        }
        TipVrijednost vr=TipVrijednost(); 
        return vr; 
    }

    void obrisi(){ while(vrh) obrisi(vrh->kljuc); }
    void obrisi(const TipKljuca &obrisati){
        Cvor *p1; Cvor* r=nullptr; 
        p1=vrh; 
        Cvor*p2=nullptr; 
        while(p1!=0 && p1->kljuc !=obrisati){
            r=p1; 
            if(p1->kljuc < obrisati) p1=p1->desno; 
            else p1=p1->lijevo; 
        }
        if(!p1) return; 
        Cvor *p3, *p4; 
        if(! (p1->lijevo)) { p2=p1->desno; p3=r; }
        else {
            if(!(p1->desno)){
                p2=p1->lijevo; p3=r; 
            }
            else {
                p2=p1->lijevo; 
                p4=p2->desno; 
                p3=p1; 
                while(p4){
                    p3=p2; 
                    p2=p4; 
                    p4=p2->desno; 
                }
                if(p1!=p3){
                    p3->desno=p2->lijevo; 
                    if(p2->lijevo) p2->lijevo->parent=p3; 
                    p2->lijevo=p1->lijevo; 
                    if(p1->lijevo) p1->lijevo->parent=p2;
                }
                p2->desno=p1->desno; 
                if(p1->desno) p1->desno->parent=p2;
            }
        }
        if(!r) vrh=p2; 
        else {
            if(r->lijevo==p1){
                r->lijevo=p2; 
                r->balans=r->balans-1; 
            }
            else{
                r->desno=p2; 
                r->balans=r->balans+1; 
            }
        }
        if(p2) p2->parent =r; 
        p1->desno=nullptr; 
        p1->lijevo=nullptr; 
        p1->parent=nullptr; 
        delete p1; 
        vel--; 
    }
    AVLStabloMapa &operator=(const AVLStabloMapa &p){
        if(this==&p) return *this; 
        obrisi();
        kopiraj(vrh, p.vrh); 
        vel=p.vel; 
        return *this; 
    }
    
    AVLStabloMapa &operator=(AVLStabloMapa &&p){
        if(this==&p) return *this; 
        obrisi();
        vrh=p.vrh; 
        vel=p.vel; 
        return *this; 
    }

};



template <typename TipKljuca,typename TipVrijednost>
struct Cvor{
    TipKljuca kljuc; 
    TipVrijednost vrijednost; 
    Cvor *lijevi=nullptr;
    Cvor *desni=nullptr;
    Cvor *rod=nullptr;
};

template <typename TipKljuca,typename TipVrijednost>
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednost>{

    Cvor<TipKljuca,TipVrijednost> *korijen; 
    int duzina; 

    Cvor<TipKljuca, TipVrijednost> *&pretragaBST(const TipKljuca &klj, Cvor<TipKljuca, TipVrijednost> *&kor1,Cvor<TipKljuca, TipVrijednost> *&p ){
        p=kor1; 
        while(p!=nullptr && klj != p->kljuc){
            if(klj < p->kljuc){
                p=p->lijevi;
            }
            else p= p->desni; 
        }
        return p;
    }
    
    Cvor<TipKljuca, TipVrijednost> *pretragaBST(const TipKljuca &klj, Cvor<TipKljuca, TipVrijednost> *kor1) const {
        while(kor1!=nullptr && klj != kor1->kljuc){
            if(klj < kor1->kljuc){
                kor1=kor1->lijevi;
            }
            else kor1 = kor1->desni; 
        }
        return kor1; 
    }
    
    bool brisiCvorBST(const TipKljuca &klj, Cvor<TipKljuca, TipVrijednost> *&kor1){
        Cvor<TipKljuca, TipVrijednost> *p=kor1; 
        Cvor<TipKljuca, TipVrijednost> *roditelj=nullptr; 
        while(p!=nullptr && klj != p->kljuc){
            roditelj=p; 
            if(klj < p->kljuc){
                p=p->lijevi;
            }
            else p= p->desni; 
        }

        if(p==nullptr) return false; 

        Cvor<TipKljuca, TipVrijednost> *m =nullptr; 
        Cvor<TipKljuca, TipVrijednost> *m1=nullptr; 

        Cvor<TipKljuca, TipVrijednost> *privremeni=nullptr; 

        if(p->lijevi == nullptr){
            m=p->desni; 
        }
        else if(p->desni==nullptr){
            m=p->lijevi; 
        }
        else{
            m1=p; m = p->lijevi;  privremeni = m->desni; 

            while(privremeni != nullptr ){
                m1=m; m=privremeni; privremeni = m->desni; 
            }
            if(m1!=p){
                m1->desni = m->lijevi; 
                m->lijevi = p->lijevi; 
            }
            m->desni = p->desni; 
        }

        if(roditelj == nullptr){
            kor1= m; 
        }
        else{
            if(p==roditelj->lijevi){
                roditelj->lijevi=m; 
            }   
            else{
                roditelj -> desni= m; 
            }

        }
        delete p; 
        p=nullptr; 
        return true; 
    }

    void obrisiSve(Cvor<TipKljuca, TipVrijednost> *&kor){
        if(kor){
            obrisiSve( kor->lijevi);
            obrisiSve( kor->desni); 
            delete kor; 
        }
    }

    void kopirajBST(Cvor<TipKljuca, TipVrijednost> *&prviKor, Cvor<TipKljuca, TipVrijednost> *drugiKor){
        if(drugiKor==nullptr ) return; 

        Cvor<TipKljuca, TipVrijednost> *p = drugiKor; 
        prviKor= new Cvor<TipKljuca, TipVrijednost>(); 
        prviKor->kljuc = p->kljuc; prviKor->vrijednost= p->vrijednost; 
        prviKor->lijevi= nullptr; prviKor->desni=nullptr; 

        kopirajBST(prviKor->lijevi, p->lijevi);
        kopirajBST(prviKor->desni, p->desni); 
        if(prviKor->lijevi != nullptr) prviKor->lijevi ->rod = prviKor; 
        if(prviKor->desni != nullptr) prviKor ->desni->rod = prviKor; 
        duzina++; 
    }

    void umetniBST(Cvor<TipKljuca, TipVrijednost> *&prviKor, Cvor<TipKljuca, TipVrijednost>*&novi){

        Cvor<TipKljuca, TipVrijednost> * y=nullptr; 
        Cvor<TipKljuca, TipVrijednost> * x= prviKor; 
        while(x!=nullptr){
            y=x; 
            if(novi ->kljuc < x->kljuc) x= x->lijevi; 
            else x=x->desni; 
        }
        if(y==nullptr)
            prviKor= novi; 
        else{
                if(novi->kljuc < y->kljuc) y->lijevi=novi;
                else y->desni = novi; 
            }
    }

    public: 

    BinStabloMapa():korijen(nullptr), duzina(0){}
    BinStabloMapa(const Cvor<TipKljuca, TipVrijednost> &bs) : korijen(nullptr), duzina(0){ kopirajBST(korijen, bs.korijen);}
    ~BinStabloMapa(){ obrisiSve(korijen); korijen=nullptr; duzina=0;}

    BinStabloMapa<TipKljuca, TipVrijednost> &operator = ( const BinStabloMapa<TipKljuca, TipVrijednost> &bs){
        if(this==&bs){
            return *this;
        }
        obrisiSve(korijen); 
        duzina=0; 
        korijen=nullptr; 
        kopirajBST(korijen, bs.korijen); 
        return *this; 
    }

    int brojElemenata() const { return duzina; }

    TipVrijednost &operator[](TipKljuca kljuc){
        Cvor<TipKljuca, TipVrijednost> *pom= pretragaBST(kljuc, korijen); 

        if(pom==nullptr)  {
            pom= new Cvor<TipKljuca, TipVrijednost>(); 
            pom->kljuc= kljuc; pom->lijevi=nullptr; pom->vrijednost= TipVrijednost(); 
            umetniBST(korijen, pom); 
            duzina++;
        }
        return pom->vrijednost; 
    }

    TipVrijednost operator[](TipKljuca kljuc) const {
        Cvor<TipKljuca, TipVrijednost> *pom= pretragaBST(kljuc, korijen); 
        if(pom==nullptr) return TipVrijednost(); 
        else return pom->vrijednost;
    }
    void obrisi(){
        obrisiSve(korijen); korijen=nullptr; duzina=0; 
    }
    void obrisi(const TipKljuca &klj){
        Cvor<TipKljuca, TipVrijednost> *pom=nullptr; 
        pretragaBST(klj, korijen, pom); 
        if(pom!=nullptr){
            brisiCvorBST(pom->kljuc, korijen); pom=nullptr; duzina--; 
        }
    }
};

int main(){
    BinStabloMapa<int, int> binarno; 
    AVLStabloMapa<int, int> avl; 
    clock_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12; 
    t1=clock(); 
    for(int i=0; i<666666; i++){
        avl[rand()]=rand();
    }
    t2=clock(); 

    t3=clock(); 
    for(int i=0; i<666666; i++){
        binarno[rand()]=rand();
    }
    t4=clock(); 

    std::cout<<" AVLStabloMapa dodavanje: "<< (t2-t1)/(CLOCKS_PER_SEC/1000) <<" ms. "<<std::endl; 
    std::cout<<" BinStabloMapa dodavanje: "<< (t4-t3)/(CLOCKS_PER_SEC/1000) <<" ms. "<<std::endl; 

    t1=clock(); 
    for(int i=0; i<666666; i++){
        avl.obrisi();
    }
    t2=clock(); 

    t3=clock(); 
    for(int i=0; i<666666; i++){
        binarno.obrisi();
    }
    t4=clock(); 

    std::cout<<" AVLStabloMapa brisanje: "<< (t2-t1)/(CLOCKS_PER_SEC/1000) <<" ms. "<<std::endl; 
    std::cout<<" BinStabloMapa brisanje: "<< (t4-t3)/(CLOCKS_PER_SEC/1000) <<" ms. "<<std::endl; 

    t1=clock(); 
    for(int i=0; i<555; i++){
        avl[i]=356;
    }
    t2=clock(); 

    t3=clock(); 
    for(int i=0; i<555; i++){
        binarno[i]=356;
    }
    t4=clock(); 

    std::cout<<" AVLStabloMapa pronalazak elementa: "<< (t2-t1)/(CLOCKS_PER_SEC/1000) <<" ms. "<<std::endl; 
    std::cout<<" BinStabloMapa pornalazak elementa: "<< (t4-t3)/(CLOCKS_PER_SEC/1000) <<" ms. "<<std::endl; 

    /*
    Binarno stablo brze dodaje i brise random elemente, avl stablo brze pronalazi trazeni element
    */ 
    return 0; 
}