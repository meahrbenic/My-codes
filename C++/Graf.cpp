#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <list>
#include <queue>

using namespace std;

template <typename TipKljuca, typename TipVrijednost>
struct CvorNovi {
    TipKljuca kljuc;
    TipVrijednost vrijednost;
    CvorNovi *next = nullptr;
};

template<typename TipKljuca, typename TipVrijednost>
class Mapa{
public:
    Mapa(){};
    virtual ~Mapa(){}
    virtual void obrisi() = 0;
    virtual void obrisi(const TipKljuca &kljuc) = 0;
    virtual int brojElemenata() const = 0;
    virtual TipVrijednost &operator[](const TipKljuca kljuc) = 0;
    virtual TipVrijednost operator[](const TipKljuca kljuc) const = 0;
};



////hash mapa
template <typename TipKljuca, typename TipVrijednost>
class HashMapaLan : public Mapa<TipKljuca, TipVrijednost> {
    unsigned int duzina, kapacitetMape;
    CvorNovi<TipKljuca, TipVrijednost> **niz;
    unsigned int (*f)(TipKljuca, unsigned int) = 0;

public:
    HashMapaLan() {
        niz = nullptr;
        kapacitetMape = 100;
        duzina = 0;
    }
    HashMapaLan (HashMapaLan<TipKljuca, TipVrijednost> &map){
        kapacitetMape = map.kapacitetMape;
        duzina = map.duzina;
        f = map.f;

        niz = new CvorNovi<TipKljuca, TipVrijednost> *[kapacitetMape];
        for(int i = 0; i < map.kapacitetMape; i++) 
            niz[i] = nullptr;

        for(int i = 0; i < map.kapacitetMape; i++) {
            if(map.niz[i] != nullptr){
                niz[i] = new CvorNovi<TipKljuca, TipVrijednost>();
                niz[i] -> kljuc = map.niz[i] -> kljuc;
                niz[i] -> vrijednost = map.niz[i] -> vrijednost;
                auto r = niz[i];
                auto p = map.niz[i];
                while(p -> next != nullptr){
                    r -> next = new CvorNovi<TipKljuca, TipVrijednost>();
                    p = p -> next;
                    r -> next -> kljuc = p -> kljuc;
                    r -> next -> vrijednost = p -> vrijednost;
                    
                }
            }
        }
    }

    HashMapaLan(HashMapaLan<TipKljuca, TipVrijednost> &&map) {
        duzina = map.duzina;
        kapacitetMape = map.kapacitetMape;
        niz = map.niz;
        f = map.f;
    }


    HashMapaLan &operator = (const HashMapaLan<TipKljuca, TipVrijednost> &map){
        if(&map != this) {
            for(int i = 0; i < kapacitetMape; i++){
                if(niz[i] != nullptr){
                    while(niz[i] != nullptr){
                        auto trenutni = niz[i];
                        niz[i] = niz[i] -> next;
                        delete trenutni;
                    }
                    niz[i] = nullptr;
                }
            }
        
        delete[] niz;
        kapacitetMape = map.kapacitetMape;
        duzina = map.duzina;
        f = map.f;
        
        niz = new CvorNovi <TipKljuca, TipVrijednost>*[kapacitetMape];
        for(int i = 0;i < kapacitetMape; i++)
            niz[i] = nullptr;
        for(int i = 0; i < map.kapacitetMape; i++){
            if(map.niz[i] != nullptr){
                niz[i] = new CvorNovi<TipKljuca, TipVrijednost>();
                niz[i] -> kljuc = map.niz[i] -> kljuc;
                niz[i] -> vrijednost = map.niz[i] -> vrijednost;
                auto r = niz[i];
                auto p = map.niz[i];
                while(p -> next != nullptr){
                    r -> next = new CvorNovi<TipKljuca, TipVrijednost>();
                    p = p -> next;
                    r -> next -> kljuc = p -> kljuc;
                    r -> next -> vrijednost = p -> vrijednost;
                }
            }
        }
        }
        return *this;
    }

    HashMapaLan &operator = (HashMapaLan<TipKljuca, TipVrijednost> &&map){
        if(this == &map) 
            return *this;

        for(int i = 0; i < kapacitetMape; i++) {
            if(niz[i] != nullptr) {
                while (niz[i] != nullptr) {
                    auto trenutni = niz[i];
                    niz[i] = niz[i] -> next;
                    delete trenutni;
                }
                niz[i] = nullptr;
            }
        }
        delete[] niz;
        kapacitetMape = map.kapacitetMape;
        duzina = map.duzina;
        f = map.f;
        niz = map.niz;
        return *this;
    }

    ~HashMapaLan(){
        this -> obrisi();
    }

    TipVrijednost operator[] (TipKljuca kljuc) const {
        if(f == 0)
            throw std::domain_error("Greska");

        unsigned int adresa = f(kljuc, kapacitetMape);
       if(niz[adresa] != nullptr) {
           auto p = niz[adresa];
           while(p != nullptr) {
               if(p -> kljuc == kljuc)
                return p -> vrijednost;
                p = p -> next;
           }
       }
        return TipVrijednost();
    }

    TipVrijednost &operator[](TipKljuca kljuc){
        if(f == 0)
            throw std::domain_error("Greska");

        unsigned int adresa = f(kljuc, kapacitetMape);
        if(duzina == 0){
            niz = new CvorNovi<TipKljuca, TipVrijednost>*[kapacitetMape];
            niz[adresa] = new CvorNovi<TipKljuca, TipVrijednost>();
            niz[adresa] -> kljuc = kljuc;
            niz[adresa] -> vrijednost = TipVrijednost();
            duzina++;
            
            for(int i = 0; i < kapacitetMape; i++)
                if(i != adresa)
                    niz[i] = nullptr;
            return niz[adresa] -> vrijednost;
        }
        else{
            if(niz[adresa] != nullptr){
                auto p = niz[adresa];
                while(p != nullptr){
                    if(p -> kljuc == kljuc)
                        return p -> vrijednost;
                    p = p -> next;
                }
            }
            if(niz[adresa] == nullptr){
                niz[adresa] = new CvorNovi<TipKljuca, TipVrijednost>();
                niz[adresa]->kljuc = kljuc;
                niz[adresa]->vrijednost = TipVrijednost();
                duzina++;
                return niz[adresa] -> vrijednost;
            }
            else{
                if(kljuc < niz[adresa] -> kljuc){
                    auto pomocni = niz[adresa];
                    niz[adresa] = new CvorNovi<TipKljuca, TipVrijednost>();
                    niz[adresa] -> kljuc = kljuc;
                    niz[adresa] -> vrijednost = TipVrijednost();
                    niz[adresa] -> next = pomocni;
                    duzina++;
                    return niz[adresa] -> vrijednost;
                }
                auto before = niz[adresa];
                auto p = niz[adresa];
                while(p -> next != nullptr && p -> kljuc < kljuc){
                    before = p;
                    p = p -> next;
                }
                if(p -> next == nullptr){
                    p -> next = new CvorNovi<TipKljuca, TipVrijednost>();
                    p -> next -> kljuc = kljuc;
                    p -> next -> vrijednost = TipVrijednost();
                    duzina++;
                   return p -> next -> vrijednost;
                }
                else{
                    auto p1 = new CvorNovi<TipKljuca, TipVrijednost>();
                    p1 -> kljuc = kljuc;
                    p1 -> vrijednost = TipVrijednost();
                    before -> next = p;
                    p1 -> next = niz[adresa];
                    duzina++;
                    return p1 -> vrijednost;
                }
            }
        }
    }  

    void obrisi() {
        if(duzina == 0)
            return;

        for(int i = 0; i < kapacitetMape; i++) {
            if(niz[i] != nullptr) {
                while(niz[i] != nullptr) {
                    auto trenutni = niz[i];
                    niz[i] = niz[i] -> next;
                    delete trenutni;
                }
                niz[i] = nullptr;
            }
        }
        delete[] niz;
        niz = nullptr;
        duzina = 0;
        kapacitetMape = 100;
    }


    void obrisi(const TipKljuca &kljuc) {
        if(duzina == 0)
            throw std::domain_error("Greska");
        unsigned int adresa = f(kljuc, kapacitetMape);
        bool provjera = false;
        if(niz[adresa] != nullptr) {
            if(niz[adresa] -> kljuc == kljuc) {
                provjera = true;
                niz[adresa] -> vrijednost = TipVrijednost();
                duzina--;
                return;
            }
            auto pokaz = niz[adresa];
            while(pokaz != nullptr) {
                if(pokaz -> next != nullptr) {
                    auto p = pokaz -> next;
                    if(p -> kljuc == kljuc) {
                        provjera = true;
                        p -> vrijednost = TipVrijednost();
                        break;
                    }
                }
                pokaz = pokaz -> next;
            }
            duzina--;
        }
        if(!provjera)
            throw std::domain_error("Greska");
    }

    int brojElemenata()const {
        return duzina;
    }

    void definisiHashFunkciju(unsigned int (*fun)(TipKljuca, unsigned int)) {
        if(fun == nullptr)
            throw std::domain_error("Greska");
            f = fun;
    }
};


template <typename InfoTip>
class Grana;
template <typename InfoTip>
class Cvor;
template <typename InfoTip>
class GranaIterator;

template <typename InfoTip>
class UsmjereniGraf {
protected: 
	UsmjereniGraf() {}

public:
	UsmjereniGraf(int) {}
	virtual ~UsmjereniGraf() {};
	virtual int dajBrojCvorova() const = 0;
	virtual void postaviBrojCvorova(int) = 0;
	virtual void dodajGranu(int, int, float = 0) = 0;
	virtual void obrisiGranu(int, int) = 0;
	virtual void postaviTezinuGrane(int, int, float = 0) = 0;
	virtual float dajTezinuGrane(int, int) const = 0;
	virtual bool postojiGrana(int, int) const = 0;
	virtual void postaviOznakuCvora(int, InfoTip) = 0;
	virtual InfoTip dajOznakuCvora(int) const = 0;
	virtual void postaviOznakuGrane(int, int, InfoTip) = 0;
	virtual InfoTip dajOznakuGrane(int, int) const = 0;
	virtual Grana<InfoTip> dajGranu(int, int) = 0;
	virtual const Grana<InfoTip> dajGranu(int, int) const = 0;
	virtual Cvor<InfoTip> dajCvor(int) = 0;
	virtual const Cvor<InfoTip> dajCvor(int) const = 0;
	GranaIterator<InfoTip> dajGranePocetak() {
		return ++GranaIterator<InfoTip>(this, 0, -1);
	}
	const GranaIterator<InfoTip> dajGranePocetak() const {
		return ++GranaIterator<InfoTip>(const_cast<UsmjereniGraf*>(this), 0, -1); 
    }																															
	GranaIterator<InfoTip> dajGraneKraj() {										
		return GranaIterator<InfoTip>(this, dajBrojCvorova(), 0);
	}
	const GranaIterator<InfoTip> dajGraneKraj() const {
		return GranaIterator<InfoTip>(const_cast<UsmjereniGraf*>(this), dajBrojCvorova(), 0);
	}
	
};

template <typename InfoTip>
class Grana {
	UsmjereniGraf<InfoTip>* graf;
	int polazni, dolazni;
public:
	Grana(UsmjereniGraf<InfoTip>* graf, int polazni, int dolazni) : graf(graf), polazni(polazni), dolazni(dolazni) {}
	float dajTezinu() const { 
        return graf -> dajTezinuGrane(polazni, dolazni); 
    }
	void postaviTezinu(float tezina) {
         graf -> postaviTezinuGrane(polazni, dolazni, tezina); 
    }
	InfoTip dajOznaku() const { 
        return graf -> dajOznakuGrane(polazni, dolazni); 
    }
	void postaviOznaku(InfoTip oznaka) { 
        graf -> postaviOznakuGrane(polazni, dolazni, oznaka); 
    }
	Cvor<InfoTip> dajPolazniCvor() { 
        return graf -> dajCvor(polazni); 
    }
	const Cvor<InfoTip> dajPolazniCvor() const { 
        return graf -> dajCvor(polazni); 
    }
	Cvor<InfoTip> dajDolazniCvor() { 
        return graf -> dajCvor(dolazni); 
    }
	const Cvor<InfoTip> dajDolazniCvor() const { 
        return graf -> dajCvor(dolazni); 
    }
};

template <typename InfoTip>
class Cvor {
	UsmjereniGraf<InfoTip> *graf;
	int redniBroj;
public:
	Cvor(UsmjereniGraf<InfoTip> *graf, int redniBroj) : graf(graf), redniBroj(redniBroj) {}
	InfoTip dajOznaku() const { 
        return graf -> dajOznakuCvora(redniBroj); 
    }
	void postaviOznaku(InfoTip oznaka) { 
        graf -> postaviOznakuCvora(redniBroj, oznaka); 
    }
	int dajRedniBroj() const { 
        return redniBroj; 
    }
};

template <typename InfoTip>
class GranaIterator {
	UsmjereniGraf<InfoTip> *graf;
	int i, j;
	void povecaj(int &i, int &j) {
		j + 1 >= graf -> dajBrojCvorova() ? j = 0, i++ : j++;
	}

public:
	GranaIterator(UsmjereniGraf<InfoTip> *graf, int i, int j) : graf(graf), i(i), j(j) {}
	Grana<InfoTip> operator*() { 
        return graf->dajGranu(i, j); 
    }
	const Grana<InfoTip> operator*() const { 
        return graf->dajGranu(i, j); 
    }
	bool operator == (const GranaIterator &iter) const { 
        return i == iter.i && j == iter.j && graf == iter.graf; 
    }
	bool operator != (const GranaIterator &iter) const {
        return !(*this == iter); 
    }
	GranaIterator &operator ++();
	GranaIterator operator ++(int);
};

template <typename InfoTip>
GranaIterator<InfoTip> &GranaIterator<InfoTip>::operator++() {
	do {
		povecaj(i, j);
    }while (i < graf -> dajBrojCvorova() && !graf -> postojiGrana(i, j));
	return *this;
}

template <typename InfoTip>
GranaIterator<InfoTip> GranaIterator<InfoTip>::operator++(int) {
	auto kopija(*this);
	++(*this);
	return kopija;
}


template <typename InfoTip>
class ListaGraf : public UsmjereniGraf<InfoTip> {
	struct Element {
		int cvor;
		float tezina;
		InfoTip oznaka;
		Element(int cvor, float tezina = 0, InfoTip oznaka = InfoTip()) :
			cvor(cvor), tezina(tezina), oznaka(oznaka) {}
	};

	std::vector<std::list<Element>> listaSusjedstva;
	std::vector<InfoTip> oznakeCvorova;

	void validirajCvor(int) const;
	void validirajGranu(int, int) const;
	void validirajPostojanjeGrane(int, int) const;

	typename std::list<Element>::iterator pronadjiElement(int i, int j);
	typename std::list<Element>::const_iterator pronadjiElement(int i, int j) const;

public:
	void ispisi() {
		for (int i = 0; i < listaSusjedstva.size(); i++) {
			std::cout << i << ": ";
			for (Element e : listaSusjedstva[i])
				std::cout << e.cvor << " ";
			std::cout << std::endl;
		}
	}

public:
	ListaGraf(int brojCvorova);
	int dajBrojCvorova() const { 
        return listaSusjedstva.size(); 
        }
	void postaviBrojCvorova(int);
	void dodajGranu(int, int, float = 0);
	void obrisiGranu(int, int);
	void postaviTezinuGrane(int, int, float = 0);
	float dajTezinuGrane(int, int) const;
	bool postojiGrana(int, int) const;
	void postaviOznakuCvora(int, InfoTip);
	InfoTip dajOznakuCvora(int) const;
	void postaviOznakuGrane(int, int, InfoTip);
	InfoTip dajOznakuGrane(int, int) const;

	Grana<InfoTip> dajGranu(int, int);
	const Grana<InfoTip> dajGranu(int, int) const;
	Cvor<InfoTip> dajCvor(int);
	const Cvor<InfoTip> dajCvor(int) const;
};


template <typename InfoTip>
typename std::list<typename ListaGraf<InfoTip>::Element>::iterator ListaGraf<InfoTip>::pronadjiElement(int i, int j) {
	typename std::list<Element>::iterator it;
	for (it = listaSusjedstva[i].begin(); it != listaSusjedstva[i].end(); it++) {
		if (j == it -> cvor)
			return it;
		else if (j < it -> cvor)
			return listaSusjedstva[i].end();
	}
	return it;
}

template <typename InfoTip>
typename list<typename ListaGraf<InfoTip>::Element>::const_iterator ListaGraf<InfoTip>::pronadjiElement(int i, int j) const {
	typename list<Element>::const_iterator it;
	for (it = listaSusjedstva[i].begin(); it != listaSusjedstva[i].end(); it++) {
		if (j == it -> cvor)
			return it;
		else if (j < it -> cvor)
			return listaSusjedstva[i].end();
	}
	return it;
}

template <typename InfoTip>
void ListaGraf<InfoTip>::validirajCvor(int indeks) const {
	if (indeks < 0 || indeks >= dajBrojCvorova())
		throw std::domain_error("Neispravan broj cvora");
}

template <typename InfoTip>
void ListaGraf<InfoTip>::validirajGranu(int i, int j) const {
	validirajCvor(i);
	validirajCvor(j);
}

template <typename InfoTip>
void ListaGraf<InfoTip>::validirajPostojanjeGrane(int i, int j) const {
	validirajGranu(i, j);
	if (!postojiGrana(i, j))
		throw std::domain_error("Grana ne postoji");
}

template <typename InfoTip>
ListaGraf<InfoTip>::ListaGraf(int brojCvorova) {
	if (brojCvorova < 0)
		throw std::domain_error ("Broj cvorova ne moze biti negativan");
	listaSusjedstva = std::vector<std::list<Element>>(brojCvorova, std::list<Element>());
	oznakeCvorova = std::vector<InfoTip>(brojCvorova);
}

template <typename InfoTip>
void ListaGraf<InfoTip>::postaviBrojCvorova(int noviBrojCvorova) {
	if (noviBrojCvorova < dajBrojCvorova())
		throw std::domain_error("Novi broj cvorova ne moze biti manji od trenutnog");
	listaSusjedstva.resize(noviBrojCvorova);
	oznakeCvorova.resize(noviBrojCvorova);
}

template <typename InfoTip>
void ListaGraf<InfoTip>::dodajGranu(int i, int j, float w) {
	validirajGranu(i, j);
	typename std::list<Element>::iterator it;
	for (it = listaSusjedstva[i].begin(); it != listaSusjedstva[i].end() && j > it -> cvor; it++);
	listaSusjedstva[i].insert(it, Element(j, w));
}

template <typename InfoTip>
void ListaGraf<InfoTip>::obrisiGranu(int i, int j) {
	validirajPostojanjeGrane(i, j);
	listaSusjedstva[i].erase(pronadjiElement(i, j));
}

template <typename InfoTip>
void ListaGraf<InfoTip>::postaviTezinuGrane(int i, int j, float w) {
	validirajPostojanjeGrane(i, j);
	pronadjiElement(i, j)->tezina = w;
}

template <typename InfoTip>
float ListaGraf<InfoTip>::dajTezinuGrane(int i, int j) const {
	validirajPostojanjeGrane(i, j);
	return pronadjiElement(i, j)->tezina;
}

template <typename InfoTip>
bool ListaGraf<InfoTip>::postojiGrana(int i, int j) const {
	validirajGranu(i, j);
	return pronadjiElement(i, j) != listaSusjedstva[i].end();
}

template <typename InfoTip>
void ListaGraf<InfoTip>::postaviOznakuCvora(int i, InfoTip oznaka) {
	validirajCvor(i);
	oznakeCvorova[i] = oznaka;
}

template <typename InfoTip>
InfoTip ListaGraf<InfoTip>::dajOznakuCvora(int i) const {
	validirajCvor(i);
	return oznakeCvorova[i];
}

template <typename InfoTip>
void ListaGraf<InfoTip>::postaviOznakuGrane(int i, int j, InfoTip oznaka) {
	validirajPostojanjeGrane(i, j);
	pronadjiElement(i, j)->oznaka = oznaka;

}

template <typename InfoTip>
InfoTip ListaGraf<InfoTip>::dajOznakuGrane(int i, int j) const {
	validirajPostojanjeGrane(i, j);
	return pronadjiElement(i, j) -> oznaka;
}

template <typename InfoTip>
Grana<InfoTip> ListaGraf<InfoTip>::dajGranu(int i, int j) {
	validirajPostojanjeGrane(i, j);
	return Grana<InfoTip>(this, i, j);
}

template <typename InfoTip>
const Grana<InfoTip> ListaGraf<InfoTip>::dajGranu(int i, int j) const {
	validirajPostojanjeGrane(i, j);
	return Grana<InfoTip>(const_cast<ListaGraf*>(this), i, j);
}

template <typename InfoTip>
Cvor<InfoTip> ListaGraf<InfoTip>::dajCvor(int i) {
	validirajCvor(i);
	return Cvor<InfoTip>(this, i);
}

template <typename InfoTip>
const Cvor<InfoTip> ListaGraf<InfoTip>::dajCvor(int i) const {
	validirajCvor(i);
	return Cvor<InfoTip>(const_cast<ListaGraf*>(this), i);
}


template <typename InfoTipOznake>
void dfs(UsmjereniGraf<InfoTipOznake> *graf, vector<Cvor<InfoTipOznake> > &dfs_obilazak, Cvor<InfoTipOznake> cvor) {
	cvor.postaviOznaku(1);
	dfs_obilazak.push_back(cvor);
	for (GranaIterator<InfoTipOznake> it = graf->dajGranePocetak(); it != graf->dajGraneKraj(); ++it) {
		Cvor<InfoTipOznake> susjedni = (*it).dajDolazniCvor();
		if ((*it).dajPolazniCvor().dajRedniBroj() == cvor.dajRedniBroj() && susjedni.dajOznaku() != 1)
			dfs(graf, dfs_obilazak, susjedni);
	}
}

template <typename InfoTipOznake>
void bfs(UsmjereniGraf<InfoTipOznake> *graf, vector<Cvor<InfoTipOznake> > &bfs_obilazak, Cvor<InfoTipOznake> pocetni_cvor) {
	pocetni_cvor.postaviOznaku(1);
	bfs_obilazak.push_back(pocetni_cvor);
	std::queue<Cvor<InfoTipOznake>> red;
	red.push(pocetni_cvor);
	while (!red.empty()) {
		Cvor<InfoTipOznake> c = red.front();
		red.pop();
		for (GranaIterator<InfoTipOznake> it = graf->dajGranePocetak(); it != graf->dajGraneKraj(); ++it) {
			Cvor<InfoTipOznake> susjedni = (*it).dajDolazniCvor();
			if ((*it).dajPolazniCvor().dajRedniBroj() == c.dajRedniBroj() &&
				susjedni.dajOznaku() != 1) {
				susjedni.postaviOznaku(1);
				bfs_obilazak.push_back(susjedni);
				red.push(susjedni);
			}
		}

	}
}

int main() {
    HashMapaLan<std::string,std::string> m;
// Nije definisana hash funkcija!
std::string s1("Sarajevo"), s2("Zagreb");
m[s1] = "BiH";
m[s2] = "Hrvatska";
std::cout << m.brojElemenata() << " " << m[s2];
    return 0;
}