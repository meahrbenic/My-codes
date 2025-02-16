// TP 2021/2022: Zadaća 3, Zadatak 6

#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>


struct Dijete {
  std::string ime;
  std::shared_ptr<Dijete> sljedeci;
};

bool SlovoIliBroj(char c) {
  if (c >= 'A' && c <= 'Z')
    return true;
  if (c >= 'a' && c <= 'z')
    return true;
  if (c >= '0' && c <= '9')
    return true;
  return false;
}

int Size(std::string s) {
  int duzina = 0;
  for (int i = 0; i < s.length(); i++) {
    if (SlovoIliBroj(s.at(i)))
      duzina++;
  }
  return duzina;
}

std::shared_ptr<Dijete> Lista(std::vector<std::string> djeca) {
  std::shared_ptr<Dijete> pocetak = nullptr, prethodni = nullptr;
  for (int i = 0; i < djeca.size(); i++) {
    std::shared_ptr<Dijete> novi(std::make_shared<Dijete>());
    novi->ime = djeca.at(i);
    novi->sljedeci = nullptr;
    if (!pocetak)
      pocetak = novi;
    else
      prethodni->sljedeci = novi;
    prethodni = novi;
  }
  prethodni->sljedeci = pocetak;
  return pocetak;
}

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> djeca,
                                                 int k) {

  if (k < 1 || k > djeca.size())
    throw std::logic_error("Razvrstavanje nemoguce");
  int n = djeca.size();
  std::vector<std::set<std::string>> raspored(k);

  double a = n / k;
  int broj_prvih = n - (a * k);
  int clanovi1 = n / k + 1;
  int clanovi2 = n / k;

  int korak = Size(djeca.at(0));
  int stari = Size(djeca.at(0));

  int j = 0;
  int velicina_tima = 1;
  int velicina_liste = n;

  raspored.at(j).insert(djeca.at(0));
  djeca.erase(djeca.begin());

  auto it = Lista(djeca);
  if (k == n) {
    while (1) {
      if (velicina_liste == 1)
        break;
      korak = stari;
      for (int i = 0; i < korak; i++) {
        if (i == korak - 2) {
          auto izbaci = it->sljedeci;
          j++;
          raspored.at(j).insert(izbaci->ime);

          stari = Size(izbaci->ime);
          it->sljedeci = it->sljedeci->sljedeci;
          // delete izbaci;
          velicina_liste--;
        } else {
          if (velicina_liste != 1)
            it = it->sljedeci;
        }
      }
    }
  } else {
    while (1) {
      if (velicina_liste == 1)
        break;
      korak = stari;
      for (int i = 0; i < korak; i++) {
        if (i == korak - 2) {
          auto izbaci = it->sljedeci;
          if (j < broj_prvih) {
            if (velicina_tima < clanovi1) {
              raspored.at(j).insert(izbaci->ime);
              velicina_tima++;
            }
            if (velicina_tima == clanovi1) {
              velicina_tima = 0;
              j++;
            }
          } else {
            if (velicina_tima < clanovi2) {
              raspored.at(j).insert(izbaci->ime);
              velicina_tima++;
            }
            if (velicina_tima == clanovi2) {
              velicina_tima = 0;
              j++;
            }
          }
          stari = Size(izbaci->ime);
          it->sljedeci = it->sljedeci->sljedeci;
          // delete izbaci;
          velicina_liste--;
        } else {
          if (velicina_liste != 1)
            it = it->sljedeci;
        }
      }
    }
  }
  it->sljedeci = nullptr;
  return raspored;
}

int main() {

  std::cout << "Unesite broj djece: ";
  int vel = 0;
  std::cin >> vel;
  std::vector<std::string> p(vel);

  std::cout << "Unesite imena djece: ";
  std::string znak;
  std::getline(std::cin, znak);
  for (int i = 0; i < vel; i++) {
    std::getline(std::cin, p.at(i));
  }

  std::cout << "Unesite broj timova: ";
  int k = 0;
  std::cin >> k;

  try {
    auto q = Razvrstavanje(p, k);
    for (int i = 0; i < k; i++) {
      int zadnji = q.at(i).size();
      std::cout << "Tim " << i + 1 << ": ";
      for (auto x : q.at(i)) {
        zadnji--;
        if (zadnji == 0)
          std::cout << x;
        else
          std::cout << x << ", ";
      }
      std::cout << std::endl;
    }
  } catch (std::logic_error e) {
    std::cout << "Izuzetak: " << e.what();
  }

  return 0;
}
