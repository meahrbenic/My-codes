#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename TipKljuca, typename TipVrijednost> class Mapa {
public:
  Mapa() {}
  virtual ~Mapa(){};
  virtual int brojElemenata() const = 0;
  virtual void obrisi(const TipKljuca &kljuc) = 0;
  virtual void obrisi() = 0;
  virtual const TipVrijednost operator[](const TipKljuca &kljuc) const = 0;
  virtual TipVrijednost &operator[](const TipKljuca &kljuc) = 0;
};

template <typename TipKljuca, typename TipVrijednost>
class NizMapa : public Mapa<TipKljuca, TipVrijednost> {
  int kapacitet, brEl;
  std::pair<TipKljuca, TipVrijednost> *par;
  TipVrijednost prazno;
  void povecaj() {
    kapacitet *= 2;
    std::pair<TipKljuca, TipVrijednost> *p =
        new std::pair<TipKljuca, TipVrijednost>[kapacitet];
    int br = 0;
    while (br < brEl) {
      p[br].first = par[br].first;
      p[br].second = par[br].second;
      br++;
    }
    delete[] par;
    par = p;
  }

public:
  NizMapa()
      : kapacitet(1000), brEl(0),
        par(new std::pair<TipKljuca, TipVrijednost>[1000]),
        prazno(TipVrijednost()) {}
  ~NizMapa() { delete[] par; }
  NizMapa(const NizMapa<TipKljuca, TipVrijednost> &map)
      : kapacitet(map.kapacitet), brEl(map.brEl),
        par(new std::pair<TipKljuca, TipVrijednost>[1000]) {
    int br = 0;
    while (br < brEl) {
      par[br].first = map.par[br].first;
      par[br].second = map.par[br].second;
      br++;
    }
  }

  NizMapa<TipKljuca, TipVrijednost> &
  operator=(const NizMapa<TipKljuca, TipVrijednost> &m) {
    if (&m == this)
      return *this;
    delete[] par;
    kapacitet = m.kapacitet;
    brEl = m.brEl;
    par = new std::pair<TipKljuca, TipVrijednost>[1000];
    int br = 0;
    while (br < brEl) {
      par[br].first = m.par[br].first;
      par[br].second = m.par[br].second;
      br++;
    }
    return *this;
  }

  int brojElemenata() const override { return brEl; }

  TipVrijednost &operator[](const TipKljuca &k) override {
    for (int i = 0; i < brEl; i++) {
      if (par[i].first == k)
        return par[i].second;
    }
    if (brEl == kapacitet)
      povecaj();
    par[brEl].first = k;
    par[brEl].second = TipVrijednost();
    return par[brEl++].second;
  }

  const TipVrijednost operator[](const TipKljuca &k) const override {
    for (int i = 0; i < brEl; i++) {
      if (par[i].first == k)
        return par[i].second;
    }
    return prazno;
  }

  void obrisi() override { brEl = 0; }

  void obrisi(const TipKljuca &k) override {
    for (int i = 0; i < brEl; i++) {
      if (par[i].first == k) {
        par[i].first = par[brEl - 1].first;
        par[i].second = par[brEl - 1].second;
        brEl--;
        return;
      }
    }
    throw std::domain_error("Kljuc nije pronadjen");
  }
};

void Test1() {
  NizMapa<std::string, std::vector<std::string>> m;
  std::vector<std::string> albumi;
  albumi.push_back("Midnights");
  albumi.push_back("Reputation");
  albumi.push_back("Red");
  albumi.push_back("Evermore");
  albumi.push_back("Folklore");

  m["Taylor Swift"] = albumi;
  std::cout << "The last album : " << m["Taylor Swift"][0] << std::endl;

  for (int i = 0; i < albumi.size(); i++) {
    std::cout << m["Taylor Swift"][i] << std::endl;
  }

  albumi.resize(0);
}

void Test2() {
  NizMapa<int, std::vector<int>> nekiBrojevi;
  nekiBrojevi[1] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  nekiBrojevi[10] = {11, 12, 14, 15, 16, 17, 17, 18, 19};
  nekiBrojevi[20] = {21, 22, 23, 24, 25, 26, 27, 28, 29};

  for (int j = 0; j < 8; j++) {
    std::cout << nekiBrojevi[1][j] << " ";
  }
  std::cout << std::endl;

  for (int j = 0; j < 8; j++) {
    std::cout << nekiBrojevi[10][j] << " ";
  }
  std::cout << std::endl;

  for (int j = 0; j < 8; j++) {
    std::cout << nekiBrojevi[20][j] << " ";
  }
  nekiBrojevi.obrisi(1);
}

void Test3() {
  NizMapa<std::string, std::deque<int>> fam;
  std::deque<int> godine = {5, 20, 22, 40, 50};
  fam["Filipovic"] = godine;
  godine = {5, 25, 26};
  fam["Hrbenic"] = godine;

  std::cout << "Najmladji clan porodice Filipovic ima " << fam["Filipovic"][0]
            << " godina.";
}

void Test4() {
  NizMapa<std::string, std::vector<std::string>> m;
  std::vector<std::string> clanovi = {"Alex", "Jamie", "Matt", "???"};
  m["Arctic Monekys"] = clanovi;
  clanovi = {"Brandon"};
  m["p!atd"] = clanovi;
  std::cout << m.brojElemenata() << " ";
  m.obrisi("p!atd");
  std::cout << m.brojElemenata();
}

void Test5() {
  NizMapa<std::string, std::vector<std::string>> m;
  std::vector<std::string> albumi;
  albumi.push_back("Midnights");
  albumi.push_back("Reputation");
  albumi.push_back("Red");
  albumi.push_back("Evermore");
  albumi.push_back("Folklore");
  albumi.push_back("Self-titled");
  albumi.push_back("Lover");
  albumi.push_back("1989");
  albumi.push_back("Speak Now");
  albumi.push_back("Fearless");

  m["Taylor Swift"] = albumi;

  m["Taylor Swift (Taylors Version)"] = albumi;
  m.obrisi("Taylor Swift");

  for (int i = 0; i < albumi.size(); i++) {
    std::cout << m["Taylor Swift (Taylors Version)"][i] << std::endl;
  }
  auto nova = m;

  m.obrisi();
  std::cout << std::endl;

  for (int i = 0; i < albumi.size(); i++) {
    std::cout << nova["Taylor Swift (Taylors Version)"][i] << std::endl;
  }
}

int main() {
  Test1();
  std::cout << std::endl;
  Test2();
  std::cout << std::endl;
  Test3();
  std::cout << std::endl;
  Test4();
  std::cout << std::endl;
  Test5();
  return 0;
}