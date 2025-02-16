// TP 2021/2022: Zadaća 5, Zadatak 1
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>

class Razlomak {
  long long int brojnik, nazivnik;
  static long long int NZD(long int a, long int b);

public:
  Razlomak(long long int b, long long int n);
  Razlomak(long long int b) : brojnik(b), nazivnik(1) {}
  Razlomak() : brojnik(0), nazivnik(0) {}

  long long int DajNazivnik() const { return nazivnik; }
  long long int DajBrojnik() const { return brojnik; }

  friend Razlomak operator+(const Razlomak &r1, const Razlomak &r2) {
    auto p1 = r1.brojnik, q1 = r1.nazivnik;
    auto p2 = r2.brojnik, q2 = r2.nazivnik;
    auto r = NZD(q1, q2);
    Razlomak zbir((p1 * (q2 / r) + p2 * (q1 / r)), q1 * (q2 / r));
    return zbir;
  }

  friend Razlomak operator-(const Razlomak &r1, const Razlomak &r2) {
    auto p1 = r1.brojnik, q1 = r1.nazivnik;
    auto p2 = r2.brojnik, q2 = r2.nazivnik;
    auto r = NZD(q1, q2);
    Razlomak razlika((p1 * (q2 / r) - p2 * (q1 / r)), q1 * (q2 / r));
    return razlika;
  }

  friend Razlomak operator*(const Razlomak &r1, const Razlomak &r2) {
    auto p1 = r1.brojnik, q1 = r1.nazivnik;
    auto p2 = r2.brojnik, q2 = r2.nazivnik;
    auto s = NZD(p1, q1);
    auto t = NZD(p2, q1);
    Razlomak proizvod((p1 / s) * (p2 / t), (q1 / t) * (q2 / s));
    return proizvod;
  }

  friend Razlomak operator/(const Razlomak &r1, const Razlomak &r2) {
    auto p1 = r1.brojnik, q1 = r1.nazivnik;
    auto p2 = r2.brojnik, q2 = r2.nazivnik;
    auto r = NZD(q1, q2);
    auto u = NZD(p1, p2);
    Razlomak kol((p1 / u) * (p2 / r), (q1 / r) * (q2 / u));
    return kol;
  }

  Razlomak operator-() { return Razlomak(-brojnik, nazivnik); }

  Razlomak operator+() { return Razlomak(brojnik, nazivnik); }

  Razlomak &operator+=(const Razlomak &r1) {
    *this = *this + r1;
    return *this;
  }

  Razlomak operator-=(const Razlomak &r1) {
    *this = *this - r1;
    return *this;
  }

  Razlomak operator*=(const Razlomak &r1) {
    *this = *this * r1;
    return *this;
  }

  Razlomak operator/=(const Razlomak &r1) {
    *this = *this * r1;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Razlomak &r);
  friend std::istream &operator>>(std::istream &is, Razlomak &r);
  Razlomak &operator++() {
    *this = *this + Razlomak(1);
    return *this;
  }
  Razlomak operator++(int) {
    auto pom = *this;
    ++*this;
    return pom;
  }
  Razlomak &operator--() {
    *this = *this - Razlomak(1);
    return *this;
  }
  Razlomak operator--(int) {
    auto pom = *this;
    --*this;
    return pom;
  }
};

Razlomak::Razlomak(long long int b, long long int n) : brojnik(b), nazivnik(n) {
  if (n == 0)
    throw std::logic_error("Nekorektan razlomak");
  long long int nzd = NZD(b, n);
  brojnik = brojnik / nzd;
  nazivnik = nazivnik / nzd;
  if (nazivnik < 0 && brojnik < 0) {
    nazivnik *= (-1);
    brojnik *= (-1);
  } else if (nazivnik < 0) {
    nazivnik *= (-1);
    brojnik *= (-1);
  }
}

long long int Razlomak::NZD(long int a, long int b) {
  if (b == 0)
    return a;
  return NZD(b, a % b);
}

std::ostream &operator<<(std::ostream &os, const Razlomak &r) {
  if (r.brojnik == 0 && r.nazivnik == 0)
    os << 0;
  else if (r.nazivnik == 1)
    os << r.brojnik;
  else
    os << r.brojnik << "/" << r.nazivnik;
  return os;
}
std::istream &operator>>(std::istream &is, Razlomak &r) {
  char znak;
  std::cin >> r.brojnik;
  if (std::cin.peek() != '/') {
    r.nazivnik = 1;
  } else if (std::cin.peek() == '/') {
    std::cin >> znak;
    std::cin >> r.nazivnik;
  }
  return is;
  // std::cin.setstate(std::ios::failbit);
}
int main() {

  Razlomak r, p, q;
  std::cin >> r >> p >> q;
  std::cout << r << " " << p << " " << q;

  return 0;
}
