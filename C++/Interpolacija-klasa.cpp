// NA 2018/2019: Zadaća 3, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

class AbstractInterpolator {
protected:
  std::vector<std::pair<double, double>> tacke;
  mutable int indeks = 0;

  int Locate(double x) const {
    if (x <= tacke[0].first)
      return 0;
    else if (x > tacke[tacke.size() - 1].first)
      return tacke.size();

    if (indeks != tacke.size() - 1) {
      if (x > tacke[indeks].first && x <= tacke[indeks + 1].first)
        return indeks + 1;
    }
    if (indeks != 0) {
      if (x > tacke[indeks - 1].first && x < tacke[indeks].first)
        return indeks;
    }
    auto it = std::lower_bound(tacke.begin(), tacke.end(), std::make_pair(x, 0),
                               [x](const std::pair<double, double> &p1,
                                   const std::pair<double, double> &p2) {
                                 return p1.first < x && p2.first >= x;
                               });
    indeks = it - tacke.begin() - 1;
    return it - tacke.begin();
  };

public:
  AbstractInterpolator(const std::vector<std::pair<double, double>> &data);
  virtual double operator()(double x) const = 0;
};

AbstractInterpolator::AbstractInterpolator(
    const std::vector<std::pair<double, double>> &data) {
  for (int i = 0; i < data.size(); i++) {
    tacke.push_back(data[i]);
  }

  if (data.size() != 0)
    std::sort(tacke.begin(), tacke.end(),
              [](std::pair<double, double> p, std::pair<double, double> q) {
                return p.first < q.first;
              });
  for (int i = 0; i < tacke.size() - 1; i++) {
    if (tacke.at(i).first == tacke.at(i + 1).first)
      throw std::domain_error("Invalid data set");
  }
};

class LinearInterpolator : public AbstractInterpolator {
public:
  LinearInterpolator(const std::vector<std::pair<double, double>> &data)
      : AbstractInterpolator(data) {}
  double operator()(double x) const override {
    int ind = Locate(x);
    if (ind == 0)
      return (tacke[1].first - x) / (tacke[1].first - tacke[0].first) *
                 tacke[0].second +
             (x - tacke[0].first) / (tacke[1].first - tacke[0].first) *
                 tacke[1].second;
    else if (ind == tacke.size()) {
      int a(tacke.size() - 1);
      return (tacke[a].first - x) / (tacke[a].first - tacke[a - 1].first) *
                 tacke[a - 1].second +
             (x - tacke[a - 1].first) / (tacke[a].first - tacke[a - 1].first) *
                 tacke[a].second;
    }
    return (tacke[ind].first - x) / (tacke[ind].first - tacke[ind - 1].first) *
               tacke[ind - 1].second +
           (x - tacke[ind - 1].first) /
               (tacke[ind].first - tacke[ind - 1].first) * tacke[ind].second;
  }
};

class PolynomialInterpolator : public AbstractInterpolator {
  std::vector<double> Newtonkoef;
  std::vector<double> pom;

public:
  PolynomialInterpolator(const std::vector<std::pair<double, double>> &data);
  double operator()(double x) const override {
    double f = Newtonkoef[Newtonkoef.size() - 1];
    for (int i = Newtonkoef.size() - 1; i >= 1; i--) {
      f = f * (x - tacke[i - 1].first) + Newtonkoef[i - 1];
    }
    return f;
  }
  void AddPoint(const std::pair<double, double> &p);
  std::vector<double> GetCoefficients() const;
};

PolynomialInterpolator::PolynomialInterpolator(
    const std::vector<std::pair<double, double>> &data)
    : AbstractInterpolator(data), Newtonkoef(data.size()) {
  for (int i = 0; i < Newtonkoef.size(); i++) {
    Newtonkoef[i] = tacke[i].second;
  }

  pom.push_back(tacke[tacke.size() - 1].first);
  pom.push_back(tacke[tacke.size() - 1].second);

  for (int j = 1; j < Newtonkoef.size(); j++) {
    for (int i = Newtonkoef.size() - 1; i >= j; i--) {
      Newtonkoef[i] = (Newtonkoef[i] - Newtonkoef[i - 1]) /
                      (tacke[i].first - tacke[i - j].first);
      if (i == Newtonkoef.size() - 1) {
        pom.push_back(Newtonkoef[i]);
      }
    }
  }
}

void PolynomialInterpolator::AddPoint(const std::pair<double, double> &p) {
  for (int i = 0; i < tacke.size(); i++) {
    if (p.first == tacke[i].first)
      throw std::domain_error("Invalid point");
  }
  std::vector<double> tmp(pom.size() + 1);
  tacke.push_back(p);

  tmp[0] = p.first;
  tmp[1] = p.second;

  for (int j = 2; j < tmp.size(); j++) {
    if (j == 2) {
      tmp[j] = (tmp[1] - tacke[tacke.size() - 2].second) /
               (tmp[0] - tacke[tacke.size() - 2].first);
    } else {
      tmp[j] = (tmp[j - 1] - pom[j - 1]) /
               (tacke[tacke.size() - 1].first - tacke[tacke.size() - j].first);
    }
  }
  Newtonkoef.push_back(tmp[tmp.size() - 1]);
  pom = tmp;
}

std::vector<double> PolynomialInterpolator::GetCoefficients() const {

  std::vector<double> w(tacke.size() + 1);
  std::vector<double> p(tacke.size());
  std::vector<double> v(tacke.size() + 1);

  w[0] = 1;
  int n = w.size() - 1;
  for (int i = 1; i <= n; i++) {
    w[i] = w[i - 1];
    for (int j = i - 1; j >= 1; j--) {
      w[j] = w[j - 1] - tacke[i - 1].first * w[j];
    }
    w[0] *= -tacke[i - 1].first;
  }

  for (int i = 0; i < n; i++) {
    double f = 1;
    for (int j = 0; j < n; j++)
      if (j != i) {
        f *= (tacke[i].first - tacke[j].first);
      }
    f = tacke[i].second / f;
    for (int j = 0; j <= n; j++) {
      v[j] = w[j];
    }
    for (int j = n - 1; j >= 0; j--) {
      v[j] += tacke[i].first * v[j + 1];
      p[j] += f * v[j + 1];
    }
  }
  return p;
}

class PiecewisePolynomialInterpolator : public AbstractInterpolator {
  int red;

public:
  PiecewisePolynomialInterpolator(
      const std::vector<std::pair<double, double>> &data, int order);
  double operator()(double x) const override {
    Locate(x);
    int a, b;
    int n = tacke.size();
    if (red % 2 == 0) {
      a = indeks - red / 2;
      b = indeks + red / 2;
    } else {
      a = indeks - (red - 1) / 2;
      b = indeks + (red + 1) / 2;
    }
    if (a < 0) {
      double s = 0;
      int granica;
      if (red % 2 == 0) {
        granica = red + 1;
      } else {
        granica = red;
      }
      for (int i = 0; i <= granica; i++) {
        double p = tacke[i].second;
        for (int j = 0; j <= granica; j++) {
          if (i != j) {
            p = p * (x - tacke[j].first) / (tacke[i].first - tacke[j].first);
          }
        }
        s += p;
      }
      return s;
    } else if (b >= n) {
      double s = 0;
      for (int i = n - 1 - red; i < n; i++) {
        double p = tacke[i].second;
        for (int j = n - 1 - red; j < n; j++) {
          if (i != j) {
            p = p * (x - tacke[j].first) / (tacke[i].first - tacke[j].first);
          }
        }
        s += p;
      }
      return s;
    }

    double s = 0;
    for (int i = a; i <= b; i++) {
      double p = tacke[i].second;
      for (int j = a; j <= b; j++) {
        if (i != j) {
          p = p * (x - tacke[j].first) / (tacke[i].first - tacke[j].first);
        }
      }
      s += p;
    }
    return s;
  }
};

PiecewisePolynomialInterpolator::PiecewisePolynomialInterpolator(
    const std::vector<std::pair<double, double>> &data, int order)
    : AbstractInterpolator(data) {
  if (order < 1 || order >= data.size())
    throw std::domain_error("Invalid order");
  red = order;
}

class SplineInterpolator : public AbstractInterpolator {
  std::vector<double> r;

public:
  SplineInterpolator(const std::vector<std::pair<double, double>> &data);
  double operator()(double x) const override {
    int ind = Locate(x);
    if (ind == 0)
      ind = 1;
    else if (ind == tacke.size())
      ind--;
    double t = x - tacke[ind - 1].first;
    double delx = tacke[ind].first - tacke[ind - 1].first;
    double s = (r[ind] - r[ind - 1]) / (3 * delx);
    double q = (tacke[ind].second - tacke[ind - 1].second) / delx -
               delx * (r[ind] + 2 * r[ind - 1]) / 3;
    return tacke[ind - 1].second + t * (q + t * (r[ind - 1] + t * s));
  }
};

SplineInterpolator::SplineInterpolator(
    const std::vector<std::pair<double, double>> &data)
    : AbstractInterpolator(data) {
  int n = tacke.size();
  double mi;
  r.resize(n);
  std::vector<double> alfa(n - 2);

  for (int i = 1; i < n - 1; i++) {
    alfa[i - 1] = 2 * (tacke[i + 1].first - tacke[i - 1].first);
    r[i] = 3 * ((tacke[i + 1].second - tacke[i].second) /
                    (tacke[i + 1].first - tacke[i].first) -
                (tacke[i].second - tacke[i - 1].second) /
                    (tacke[i].first - tacke[i - 1].first));
  }

  for (int i = 1; i < n - 2; i++) {
    mi = (tacke[i + 1].first - tacke[i].first) / alfa[i - 1];
    alfa[i] -= mi * (tacke[i + 1].first - tacke[i].first);
    r[i + 1] -= mi * r[i];
  }
  r[n - 2] /= alfa[n - 3];
  for (int i = n - 3; i >= 1; i--) {
    r[i] =
        (r[i] - (tacke[i + 1].first - tacke[i].first) * r[i + 1]) / alfa[i - 1];
  }
}

class BarycentricInterpolator : public AbstractInterpolator {
  int red;
  std::vector<double> w;
  int max(int a, int b) {
    if (a < b)
      return b;
    return a;
  }
  int min(int a, int b) {
    if (a > b)
      return b;
    return a;
  }

public:
  BarycentricInterpolator(const std::vector<std::pair<double, double>> &data,
                          int order);
  double operator()(double x) const override {
    double p = 0;
    double q = 0;
    for (int i = 0; i < tacke.size(); i++) {
      if (x == tacke[i].first)
        return tacke[i].second;
      double u = w[i] / (x - tacke[i].first);
      p += (u * tacke[i].second);
      q += u;
    }
    return p / q;
  }
  std::vector<double> GetWeights() const { return w; }
};

BarycentricInterpolator::BarycentricInterpolator(
    const std::vector<std::pair<double, double>> &data, int order)
    : AbstractInterpolator(data), w(tacke.size()) {
  if (order < 0 || order > tacke.size())
    throw std::domain_error("Invalid order");
  int n = tacke.size();
  int k;
  double p;
  for (int i = 0; i < n; i++) {
    w[i] = 0;
    for (k = max(1, i - order); k >= min(i, n - order); k--) {
      p = 1;
      for (int j = k; j < k + order; j++)
        if (j != i)
          p /= (tacke[i].first - tacke[j].first);
    }
    if (k % 2 == 0)
      p = -p;
    w[i] += p;
  }

}

class TrigonometricInterpolator : public AbstractInterpolator {
  TrigonometricInterpolator(const std::vector<std::pair<double, double>> &data);
  double operator()(double x) const override;
};

////////////////////////////////////////////////////TESTOOOVIIII
////////////////////////////////////////////////////////////////////////////
void TestLinearnog() {
  LinearInterpolator li({{0, 8}, {1, 3}, {2, 7}, {4, 5}, {7, 10}});
  std::cout << li(0.6) << std::endl;
  std::cout << li(0.2) << std::endl;
  std::cout << li(1.7) << std::endl;
  std::cout << li(8) << std::endl;
  std::cout << li(-0.6) << std::endl;
  std::cout << li(5);
}

void TestLinearnog2() {
  try {
    LinearInterpolator li({{1, 8}, {1, 3}, {2, 7}, {4, 5}, {7, 10}});
    std::cout << li(0.6) << std::endl;
    std::cout << li(0.2) << std::endl;
    std::cout << li(1.7) << std::endl;
    std::cout << li(8) << std::endl;
    std::cout << li(-0.6) << std::endl;
    std::cout << li(5);
  } catch (std::domain_error e) {
    std::cout << e.what();
  }
}
void test() {
  PolynomialInterpolator pi({{-2, -39}, {0, 3}, {4, 25}, {6, 30}});

  std::cout << pi(2.5) << std::endl;
  std::cout << pi(3.5) << std::endl;
  std::cout << pi(7.5) << std::endl;
  std::cout << pi(-3.5);
  try {
    pi.AddPoint({-2, 3});
  } catch (std::domain_error e) {
    std::cout << e.what();
  }
  std::cout << std::endl;
  std::vector<double> p = pi.GetCoefficients();
  for (double x : p)
    std::cout << x << " ";
}

void Piercetest() {

  PiecewisePolynomialInterpolator pwi(
      {{0, 8}, {1, 3}, {2, 7}, {4, 5}, {6, 8}, {8, 7}, {10, 5}}, 3);
  for (double x : {-1., 0.5, 1.5, 3., 5., 7., 9., 10.5})
    std::cout << pwi(x) << " ";

  try {
    PiecewisePolynomialInterpolator pwi(
        {{0, 8}, {1, 3}, {4, 7}, {2, 5}, {6, 8}, {8, 7}, {10, 5}}, -3);
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
}

void Piercetest3() {
  try {
    PiecewisePolynomialInterpolator pwi(
        {{0, 8}, {1, 3}, {4, 7}, {2, 5}, {6, 8}, {8, 7}, {10, 5}}, 10);
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
}

void testPierce2() {
  double pi = 4 * atan(1);
  PiecewisePolynomialInterpolator p(
      {{0, 8}, {1, 3}, {2, 7}, {4, 5}, {6, 8}, {8, 7}, {10, 5}}, 3);
  std::cout << p(pi) << " " << std::round(std::sin(pi)) << std::endl;
  std::cout << p(pi / 2) << " " << std::sin(pi / 2) << std::endl;
}

void testSpline() {
  const double PI = std::atan(1) * 4;
  std::vector<std::pair<double, double>> data1;
  for (double i = 0; i <= 2 * PI; i += PI / 2)
    data1.push_back({i, std::sin(i)});
  SplineInterpolator si(data1);
  for (int i = -PI / 4; i <= 2 * PI / 2; i++)
    std::cout << si(i) << " " << std::sin(i) << std::endl;
}

void testSpline1() {
  double pi(4 * atan(1));
  SplineInterpolator sp({{0, 0},
                         {pi / 2, 1},
                         {3 * pi / 2, -1},
                         {pi, 0},
                         {pi / 6, 0.5},
                         {-pi / 6, -0.5},
                         {pi / 4, std::sqrt(2.) / 2}});
  std::cout << sp(pi) << " " << std::round(std::sin(pi)) << std::endl;

  std::vector<std::pair<double, double>> data2;
  for (double i = 2 * pi; i >= 0; i -= pi / 2)
    data2.push_back({i, std::sin(i)});
  SplineInterpolator si1(data2);
  for (int i = -pi / 4; i <= 2 * pi / 2; i++)
    std::cout << si1(i) << " " << std::sin(i) << std::endl;
}

void testBari() {
  double pi(4 * atan(1));
  BarycentricInterpolator b({{0, 0},
                             {pi / 2, 1},
                             {3 * pi / 2, -1},
                             {pi, 0},
                             {pi / 6, 0.5},
                             {-pi / 6, -0.5},
                             {pi / 4, std::sqrt(2.) / 2}},
                            5);
  std::cout << b(pi) << " " << std::round(std::sin(pi)) << std::endl;
  std::cout << b(0.5) << " " << std::sin(0.5) << std::endl;
}

void testBarii(){
     BarycentricInterpolator b( 
                            {{1, 3},
                             {2, 5},
                             {4, 4},
                             {5, 2},
                             {7,1} }, 2);
    std::cout<< b(4)<<std::endl;
}

void testBari2() {
  double pi(4 * atan(1));
  try {
    BarycentricInterpolator b({{0, 0},
                               {pi / 2, 1},
                               {3 * pi / 2, -1},
                               {pi, 0},
                               {pi / 6, 0.5},
                               {-pi / 6, -0.5},
                               {pi / 4, std::sqrt(2.) / 2}},
                              -5);
    std::cout << b(pi) << " " << std::round(std::sin(pi)) << std::endl;
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
}

void testBari3() {
  double pi(4 * atan(1));
  try {
    BarycentricInterpolator b({{0, 0},
                               {pi / 2, 1},
                               {3 * pi / 2, -1},
                               {pi, 0},
                               {pi / 6, 0.5},
                               {-pi / 6, -0.5},
                               {pi / 4, std::sqrt(2.) / 2}},
                              20);
    std::cout << b(pi) << " " << std::round(std::sin(pi)) << std::endl;
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
}

void testPoli() {
  double pi(4 * atan(1));
    PolynomialInterpolator p({{0,0},{pi/2, 1},{3*pi/2, -1},{pi,0},{pi/6, 0.5},{-pi/6, -0.5},{pi/4, std::sqrt(2.)/2}});
    std::cout << p(pi) << " " << std::round(std::sin(pi)) << std::endl;
    std::cout << p(1) << " " << std::sin(1) << std::endl;
}

int main() {
    /*
    // provjera sort-a :3
    std::vector<std::pair<double, double>> n;
    std::pair<double, double> par(4.5, 12);
    std::pair<double, double> par2(4, 12);
    std::pair<double, double> par3(5, 12.1);
    std::pair<double, double> par4(3, 12.12);
    n = {par, par2, par3, par4};
    for (int i = 0; i < n.size(); i++)
      std::cout << n.at(i).first << " " << n.at(i).second << std::endl;
    std::sort(n.begin(), n.end(),
              [](std::pair<double, double> p, std::pair<double, double> q) {
                return p.first < q.first;
              });
    std::cout << "Sortirano" << std::endl;
    for (int i = 0; i < n.size(); i++)
      std::cout << n.at(i).first << " " << n.at(i).second << std::endl;

    TestLinearnog();
    std::cout << std::endl;
    TestLinearnog2();
    std::cout << std::endl;
    test();
    std::cout << std::endl;
    Piercetest();
    std::cout << std::endl;
    testPierce2();
    std::cout << std::endl;
    Piercetest3();
    std::cout << std::endl;
    testSpline();
    std::cout << std::endl;
    testSpline1();
    std::cout << std::endl; testPoli();
    std::cout << std::endl;

    testBari();
    std::cout << std::endl;
    testBari2();
    std::cout << std::endl;
    testBari3();
    std::cout << std::endl;
   */
testBarii();
    std::cout << std::endl;


    return 0;
}