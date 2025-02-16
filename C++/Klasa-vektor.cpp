// NA 2019/2020: Zadaća 1, Zadatak 1
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

class Vector {

  std::vector<double> vektor;

public:
  explicit Vector(int n) {
    if (n <= 0)
      throw std::range_error("Bad dimension");
    vektor = std::vector<double>(n);
  };
  Vector(std::initializer_list<double> l) {
    if (l.size() == 0)
      throw std::range_error("Bad dimension");
    Vector::vektor = l;
  };
  int NElems() const { return Vector::vektor.size(); };
  double &operator[](int i) {
    if (i > Vector::vektor.size() || i < 0)
      throw std::range_error("Invalid index");
    return Vector::vektor.at(i);
  };
  double operator[](int i) const {
    if (i > Vector::vektor.size() || i < 0)
      throw std::range_error("Invalid index");
    return Vector::vektor.at(i);
  };
  double &operator()(int i) {
    if (i > Vector::vektor.size() || i < 1)
      throw std::range_error("Invalid index");
    return Vector::vektor.at(i - 1);
  };
  double operator()(int i) const {
    if (i > Vector::vektor.size() || i < 0)
      throw std::range_error("Invalid index");
    return Vector::vektor.at(i);
  };

  double Norm() const {
    double norma = 0;
    for (int i = 0; i < Vector::vektor.size(); i++) {
      norma += vektor.at(i) * vektor.at(i);
    }
    return std::sqrt(norma);
  };

  friend double VectorNorm(const Vector &v) { return v.Norm(); };

  double GetEpsilon() const {
    return 10 * Norm() * std::numeric_limits<double>::epsilon();
  };

  void Print(char separator = '\n', double eps = -1) const {
    if (eps < 0)
      eps = GetEpsilon();
    for (int i = 0; i < vektor.size(); i++) {

      if (std::fabs(vektor[i]) < eps)
        std::cout << 0;
      else
        std::cout << vektor[i];
      if (separator == '\n')
        std::cout << separator;
      else if (i != vektor.size() - 1)
        std::cout << separator;
    }
  };

  friend void PrintVector(const Vector &v, char separator = '\n',
                          double eps = -1) {
    v.Print(separator, eps);
  };

  friend Vector operator+(const Vector &v1, const Vector &v2) {
    if (v1.NElems() != v2.NElems())
      throw std::domain_error("Incompatible formats");
    Vector s(v1.NElems());
    for (int i = 0; i < v1.NElems(); i++)
      s[i] = v1[i] + v2[i];
    return s;
  };
  Vector &operator+=(const Vector &v) {
    if (Vector::vektor.size() != v.NElems())
      throw std::domain_error("Incompatible formats");
    for (int i = 0; i < v.NElems(); i++)
      vektor[i] += v[i];
    return *this;
  };

  friend Vector operator-(const Vector &v1, const Vector &v2) {
    if (v1.NElems() != v2.NElems())
      throw std::domain_error("Incompatible formats");
    Vector s(v1.NElems());
    for (int i = 0; i < v1.NElems(); i++)
      s[i] = v1[i] - v2[i];
    return s;
  };
  Vector &operator-=(const Vector &v) {
    if (Vector::vektor.size() != v.NElems())
      throw std::domain_error("Incompatible formats");
    for (int i = 0; i < v.NElems(); i++)
      vektor[i] -= v[i];
    return *this;
  };

  friend Vector operator*(double s, const Vector &v) {
    Vector p(v.NElems());
    for (int i = 0; i < v.NElems(); i++)
      p[i] = v[i] * s;
    return p;
  };
  friend Vector operator*(const Vector &v, double s) {
    Vector p(v.NElems());
    for (int i = 0; i < v.NElems(); i++)
      p[i] = v[i] * s;
    return p;
  };
  Vector &operator*=(double s) {
    for (int i = 0; i < Vector::vektor.size(); i++)
      vektor[i] *= s;
    return *this;
  };
  friend double operator*(const Vector &v1, const Vector &v2) {
    double suma = 0;
    if (v1.NElems() != v2.NElems())
      throw std::domain_error("Incompatible formats");
    for (int i = 0; i < v1.NElems(); i++) {
      suma += v1[i] * v2[i];
    }
    return suma;
  };
  friend Vector operator/(const Vector &v, double s) {
    if (s == 0)
      throw std::domain_error("Division by zero");
    Vector p(v.NElems());
    for (int i = 0; i < v.NElems(); i++)
      p[i] = v[i] / s;
    return p;
  };
  Vector &operator/=(double s) {
    if (s == 0)
      throw std::domain_error("Division by zero");
    for (int i = 0; i < Vector::vektor.size(); i++)
      vektor[i] /= s;
    return *this;
  };
};

// TESTOVI ZA VEKTOR

void VVektorTestKonstruktora() {
    std::cout<<"Test konstruktora: "<<std::endl;
  Vector v(5), v1(12);
  v.Print(',');
  std::cout << std::endl;
  if (v1.NElems() == 12)
    std::cout << "OK";
}

void VVektorTestKonstrutkoraIzuzeci() {
std::cout<<"Test pogresne velicine: "<<std::endl;
  try {
    Vector v(-1);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VVektorTestInitKonstruktora() {
  std::cout<<"Test sekvencijskog konstruktora: "<<std::endl;
  Vector v{1, 2, 3, 4, 5, 6};
  v.Print(',');
  Vector v1 = {2, 3, 4, 5};
  v1.Print(',');
}

void VVektorTestInitKonstruktoraIzuzeci() {
    std::cout<<"Test sekvencijskog konstruktora (prazna inic. lista): "<<std::endl;
  try {
    Vector v{};
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VElementi(int br) {
    std::cout<<"Test broja elemenata: "<<std::endl;
  Vector v{1, 2, 3, 4};
  if (br == v.NElems())
    std::cout << "ok";
  else
    std::cout << "nope";
}

void VTest() {
  std::cout<<"Test operatora[] : "<<std::endl;
  Vector v{1, 65.2, 72.08, 45, -5, -3.56};
  std::cout << v[5] << std::endl;
  v[3] = 543;
  v.Print(',');
}

void VTestIzuzeci() {
    std::cout<<"Test operatora[] (izvan opsega): "<<std::endl;
  try {
    Vector v{1, 65.2, 72.08, 45, -5, -3.56};
    std::cout << v[98];
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VTestIzuzeci2() {
    std::cout<<"Test operatora[] (negativan indeks): "<<std::endl;
  try {
    Vector v{1, 65.2, 72.08, 45, -5, -3.56};
    v[-1] = 6;
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VTestIzuzeci3() {
    std::cout<<"Test operatora[] (izvan opsega): "<<std::endl;
  try {
    Vector v{65, 54.675, 7238, 43.5, -5.432, -123.56};
    v[123] = 432;
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VTestIzuzeci4() {
    std::cout<<"Test operatora[] (negativan indeks): "<<std::endl;
  try {
    Vector v{1, 65.2, 72.08, 45, -5, -3.56};
    std::cout << v[-4];
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VTestZagrade() {
    std::cout<<"Test operatora() :"<<std::endl;
  Vector v{32, 45, 123, 65, -534, -2.3434, 0.853, 132, -43.2};
  std::cout << v(5) << std::endl;
  v(4) = 0;
  v.Print(',');
}

void VTestZagradeIzuzeci() {
    std::cout<<"Test operatora() ( indeks manji od 1 ):"<<std::endl;
  try {
    Vector v{32, 45, 123, 65, -534, -2.3434, 0.853, 132, -43.2};
    v(0) = 5;
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}
void VTestZagradeIzuzeci2() {
    std::cout<<"Test operatora() ( indeks izvan opsega ):"<<std::endl;
  try {
    Vector v{32, 45, 123, 65, -534, -2.3434, 0.853, 132, -43.2};
    v(542) = 5;
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void VTestPrinta() {
    std::cout<<"Test funkcije Print i PrintVector:"<<std::endl;
  Vector v = {0.54, 2.453, 34.25, 8.13, 53.009};
  v.Print(',');
  std::cout << std::endl;
  v.Print('.');
  std::cout << std::endl;
  v.Print('\n');
  std::cout << "i zadnji " << std::endl;
  PrintVector(v, ',');
  std::cout << std::endl;
  PrintVector(v, '\n');
  Vector v1 = {5.65, -0.09, 23.453};
  v1.Print(',', 1);
  std::cout << std::endl;
  PrintVector(v1, '.', 1);
}

void VSabiranje() {
    std::cout<<"Test sabiranja, oduzimanja :"<<std::endl;
  Vector a = {1, 2, 3, 4, 5};
  Vector b = {3, 4, 5, 6, 7};
  Vector c(5);
  c = a + b;
  c.Print(',');
  std::cout << std::endl;
  c += a;
  c.Print(',');
  std::cout << std::endl;
  Vector d(5);
  d = b - c;
  d.Print(',');
  std::cout << std::endl;
  d -= a;
  d.Print(',');
}

void VSabiranjeIzuzeci1() {
    std::cout<<"Test sabiranja (razlicite velicine):"<<std::endl;
  try {
    Vector a = {1, 2, 3, 4, 5};
    Vector b = {3, 4, 5};
    Vector c(4);
    c = a + b;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Los izuzetak";
  }
}

void VOduzimanjeIzuzeci() {
    std::cout<<"Test oduzimanja (razlicite velicine):"<<std::endl;
  try {
    Vector a = {5, 6, 4, 35, 65};
    Vector b = {3, 4, 5};
    Vector c(4);
    c = a - b;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Los izuzetak";
  }
}

void VSabiranjeIzuzeci2() {
    std::cout<<"Test sabiranja (razlicite velicine):"<<std::endl;
  try {
    Vector a = {1, 2, 3, 4, 5};
    Vector b = {3, 4, 5};
    a += b;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Los izuzetak";
  }
}

void VOduzimanjeIzuzeci2() {
    std::cout<<"Test oduzimanja (razlicite velicine):"<<std::endl;
  try {
    Vector a = {5, 6, 4, 35, 65};
    Vector b = {3, 4, 5};
    b -= a;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Los izuzetak";
  }
}

void VMnozenjeiDijeljenjeSkalarom() {
    std::cout<<"Test mnozenja i dijeljenja skalarom:"<<std::endl;
  Vector v = {4, 6, 7, -2, 34};
  double s = 5;
  v *= s;
  v.Print(',');
  std::cout << std::endl;
  v = v * s;
  v.Print(',');
  std::cout << std::endl;
  v = s * v;
  v.Print(',');
  std::cout << std::endl;
  v = v / s;
  v.Print(',');
  std::cout << std::endl;
  v /= 3;
  v.Print(',');
}

void VMnozenjeVektora() {
    std::cout<<"Test mnozenja vektora:"<<std::endl;
  Vector v = {4, 6, 7, -2, 34};
  Vector v1 = {4.65, 36, 4.7, -2, 3.544};
  double p;
  p = v * v1;
  std::cout << p;
}
void VMnozenjeVektoraIzuzeci() {
    std::cout<<"Test mnozenja vektora (razlicite velicine):"<<std::endl;
  try {
    Vector v = {4, 6, 7, -2, 34};
    Vector v1 = {4.65, -2, 3.544};
    double p;
    p = v * v1;
    std::cout << p;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void Nula1() {
    std::cout<<"Test dijeljenja sa nulom:"<<std::endl;
  try {
    Vector v = {33.3333, 50, 58.3333, -16.6667, 283.333};
    v = v / 0;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void Nula2() {
    std::cout<<"Test dijeljenja sa nulom:"<<std::endl;
  try {
    Vector v = {33.3333, 50, 58.3333, -16.6667, 283.333};
    v /= 0;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

// MATRICA

typedef std::vector<std::vector<double>> mat;
class Matrix {
  mat matrica;

public:
  Matrix(int m, int n) {
    if (m <= 0 || n <= 0)
      throw std::range_error("Bad dimension");
    matrica = mat(m, std::vector<double>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        matrica.at(i).at(j) = 0;
      }
    }
  };
  Matrix(const Vector &v) {
    if (v.NElems() <= 0)
      throw std::range_error("Bad dimension");
    matrica = mat(v.NElems(), std::vector<double>(1));
    for (int i = 0; i < v.NElems(); i++) {
      matrica.at(i).at(0) = v(i);
    }
  };
  Matrix(std::initializer_list<std::vector<double>> l) {
    if (l.size() == 0)
      throw std::range_error("Bad dimension");
    for (auto it = l.begin(); it != l.end(); it++) {
      if (it->size() == 0)
        throw std::range_error("Bad dimension");
    }
    auto pom = l.begin();
    auto vel = pom->size();
    for (auto it = l.begin(); it != l.end(); it++) {
      if (it->size() != vel)
        throw std::logic_error("Bad matrix");
    }

    matrica = l;
  };

  int NRows() const { return matrica.size(); };
  int NCols() const { return matrica.at(0).size(); };
  double *operator[](int i) {
    if (i < 0 || i > matrica.size())
      throw std::range_error("Invalid index");
    return &(matrica[i][0]);
  };
  const double *operator[](int i) const {
    if (i < 0 || i > matrica.size())
      throw std::range_error("Invalid index");
    return &(matrica[i][0]);
  };
  double &operator()(int i, int j) {
    if (i < 1 || j < 1 || i > matrica.size() || j > matrica[0].size())
      throw std::range_error("Invalid index");
    return matrica[i - 1][j - 1];
  };
  double operator()(int i, int j) const {
    if (i < 1 || j < 1 || i > matrica.size() || j > matrica[0].size())
      throw std::range_error("Invalid index");
    return matrica[i - 1][j - 1];
  };
  double Norm() const {
    double norma = 0;
    for (int i = 0; i < matrica.size(); i++) {
      for (int j = 0; j < matrica[0].size(); j++) {
        norma = norma + (matrica[i][j] * matrica[i][j]);
      }
    }
    return std::sqrt(norma);
  };
  friend double MatrixNorm(const Matrix &m) { return m.Norm(); };
  double GetEpsilon() const {
    return 10 * Norm() * std::numeric_limits<double>::epsilon();
  };
  void Print(int width = 10, double eps = -1) const {
    if (eps < 0)
      eps = GetEpsilon();
    for (int i = 0; i < matrica.size(); i++) {
      for (int j = 0; j < matrica.at(0).size(); j++) {
        if (std::fabs(matrica[i][j]) < eps)
          std::cout << std::setw(width) << 0;
        else
          std::cout << std::setw(width) << matrica.at(i).at(j);
      }
      std::cout << std::endl;
    }
  };
  friend void PrintMatrix(const Matrix &m, int width = 10, double eps = -1) {
    m.Print(width, eps);
  };
  friend Matrix operator+(const Matrix &m1, const Matrix &m2) {
    if (m1.NRows() != m2.NRows() || m1.NCols() != m2.NCols())
      throw std::domain_error("Incompatible formats");
    Matrix m(m1.NRows(), m1.NCols());
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        m[i][j] = m1[i][j] + m2[i][j];
      }
    }
    return m;
  };
  Matrix &operator+=(const Matrix &m) {
    if (matrica.size() != m.NRows() || matrica[0].size() != m.NCols())
      throw std::domain_error("Incompatible formats");
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        matrica[i][j] += m[i][j];
      }
    }
    return *this;
  };

  friend Matrix operator-(const Matrix &m1, const Matrix &m2) {
    if (m1.NRows() != m2.NRows() || m1.NCols() != m2.NCols())
      throw std::domain_error("Incompatible formats");
    Matrix m(m1.NRows(), m1.NCols());
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        m[i][j] = m1[i][j] - m2[i][j];
      }
    }
    return m;
  };
  Matrix &operator-=(const Matrix &m) {
    if (matrica.size() != m.NRows() || matrica[0].size() != m.NCols())
      throw std::domain_error("Incompatible formats");
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        matrica[i][j] -= m[i][j];
      }
    }
    return *this;
  };
  friend Matrix operator*(double s, const Matrix &m) {
    Matrix p(m.NRows(), m.NCols());
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        p[i][j] = m[i][j] * s;
      }
    }
    return p;
  };
  friend Matrix operator*(const Matrix &m, double s) {
    Matrix p(m.NRows(), m.NCols());
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        p[i][j] = m[i][j] * s;
      }
    }
    return p;
  };
  Matrix &operator*=(double s) {
    for (int i = 0; i < matrica.size(); i++) {
      for (int j = 0; j < matrica[0].size(); j++) {
        matrica[i][j] = matrica[i][j] * s;
      }
    }
    return *this;
  };
  friend Matrix operator*(const Matrix &m1, const Matrix &m2) {
    if (m1.NCols() != m2.NRows())
      throw std::domain_error("Incompatible formats");

    Matrix nova(m1.NRows(), m2.NCols());

    for (int i = 0; i < nova.NRows(); i++) {
      for (int j = 0; j < nova.NCols(); j++) {
        for (int k = 0; k < m1.NCols(); k++) {
          nova[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
    return nova;
  };
  Matrix &operator*=(const Matrix &m) {
    // if(matrica.size()!=m.NRows()) throw std::domain_error("Incompatible
    // formats");
    *this = *this * m;
    return *this;
  };

  friend Vector operator*(const Matrix &m, const Vector &v) {
    /*Matrix pom(v.NElems(),1);
    for(int i=0; i<v.NElems();i++){
       pom[i][0]=v[i];
    }*/
    if (m.NCols() != v.NElems())
      throw std::domain_error("Incompatible formats");

    Matrix pom(v);
    Matrix pom2(m.NRows(), 1);
    pom2 = m * pom;
    Vector vk(pom2.NRows());
    for (int i = 0; i < pom2.NRows(); i++) {
      vk[i] = pom2[i][0];
    }
    return vk;
  };
  friend Matrix Transpose(const Matrix &m) {
    Matrix t(m.NCols(), m.NRows());
    for (int i = 0; i < m.NRows(); i++) {
      for (int j = 0; j < m.NCols(); j++) {
        t[j][i] = m[i][j];
      }
    }
    return t;
  };
  void Transpose() {

    int m = this->NRows();
    int n = this->NCols();
    Matrix t(n, m);
    if (m != n) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          t[i][j] = matrica[j][i];
        }
      }
      *this = t;
    } else if (m == n) {
      int br = 0;
      for (int i = 0; i < n; i++) {
        for (int j = br; j < n; j++) {
          double pomocna = matrica[i][j];
          matrica[i][j] = matrica[j][i];
          matrica[j][i] = pomocna;
        }
        br++;
      }
    }
  };
};

// TESTOVI ZA MATRICU

void TestKonstruktora() {
    std::cout<<"Test konstrutkora: "<<std::endl;
  Matrix mat1(3, 5);
  mat1.Print(1);
  Matrix mat2(5, 4);
  mat2.Print(1);
}

void TestKonstruktora2() {
    std::cout<<"Test konstrutkora (negativno n): "<<std::endl;
  try {
    Matrix mat1(3, -5);
    mat1.Print(1);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestKonstruktora3() {
    std::cout<<"Test konstrutkora (m manje od 1): "<<std::endl;
  try {
    Matrix mat1(0, 5);
    mat1.Print(1);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestVektorKonstruktora() {
    std::cout<<"Test vektor konstrutkora : "<<std::endl;
  Vector v = {1, 2, 3, 4, 5};
  Matrix mat1(3, 2);
  Matrix mat2(v);
  mat2.Print(1);
}

void TestVektorKonstruktora2() {
    std::cout<<"Test vektor konstrutkora (prazan vektor) : "<<std::endl;
  try {
    Vector v = {};
    Matrix mat1(3, 2);
    Matrix mat2(v);
    mat2.Print(1);
  } catch (std::range_error e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}


void TestInitKonstruktora() {
    std::cout<<"Test sekvencijskog  konstruktora"<<std::endl;
  Matrix m{{2, 5, 4, 1}, {3, 2, 6, 5}, {4, 1, 5, 2}};
  m.Print(1);
  std::cout << std::endl;
  Matrix m1{{7.6, 4.003, -12.3}, {12.4, 5, 8.9}};
  m1.Print(6);
}

void TestInitKonstruktora2() {
    std::cout<<"Test sekvencijskog  konstruktora (prazna matrica)"<<std::endl;
  try {
    Matrix m{};
    m.Print(1);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestInitKonstruktora3() {
    std::cout<<"Test sekvencijskog  konstruktora (prazni vektori)"<<std::endl;
  try {
    Matrix m{{}, {}, {}};
    m.Print(1);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void GrbavaMatrica() {
    std::cout<<"Test na grbavu matricu"<<std::endl;
  try {
    Matrix m{{1, 2, 3}, {3, 4}};
    m.Print(4);
  } catch (std::logic_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestRedoviIKolone() {
    std::cout<<"Test za broj redova i kolona: "<<std::endl;
  Matrix m1{{87, 5, 46, 13}, {3, 2, 6, 5}, {4, 1, 5, 2}, {0, 0, 0, 0}};
  std::cout << m1.NCols() << " " << m1.NRows();
}

void TestZagrada() {
     std::cout<<"Test operatora [] i (): "<<std::endl;
  Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
  std::cout << m1[1][2] << std::endl;
  m1[1][2] = 5;
  std::cout << m1[1][2] << std::endl;
  std::cout << m1(2, 3) << std::endl;
  m1(2, 3) = 65;
  std::cout << m1(2, 3) << std::endl;
  m1.Print(5);

  // druga matrica

  Matrix m2 = {
      {3, 4, 5, 6}, {3.54, 1, -5, 9}, {4, 5, -23, 0.984}, {75, -6, 0.54, 0}};
  std::cout << m2[1][2] << std::endl;
  m1[1][2] = 9;
  std::cout << m2[1][2] << std::endl;
  std::cout << m2(2, 3) << std::endl;
  m2(2, 3) = 65;
  std::cout << m2(2, 3) << std::endl;
  m2.Print(7);
}

void TestZagradaIzuzecia() {
    std::cout<<"Test operatora () indeks manji od 1 "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1(0, 9);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}
void TestZagradaIzuzecib() {
    std::cout<<"Test operatora () indeks manji od 1 "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1(0, 0);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}
void TestZagradaIzuzecic() {
    std::cout<<"Test operatora () indeks negativan "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1(-2, 7);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzecid() {
    std::cout<<"Test operatora () indeks negativan "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1(5, -9);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzecie() {
    std::cout<<"Test operatora () indeks izvan opsega "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1(5, 200);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzecif() {
    std::cout<<"Test operatora () indeks izvan opsega "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1(97, 1);
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzeci2() {
    std::cout<<"Test operatora [] indeksi negativni "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1[-1][0];
    m1[5][-1];
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzeci2a() {
    std::cout<<"Test operatora [] indeks negativan "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1[5][-1];
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzeci2b() {
    std::cout<<"Test operatora [] indeks izvan opsega "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1[5][897];
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZagradaIzuzeci2c() {
    std::cout<<"Test operatora [] indeks izvan opsega "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    m1[59][1];
  } catch (std::range_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestNorme() {
    std::cout<<"norma: "<<std::endl;
  Matrix m4{{1,2,3,4}, {5,6,7,8}};
  Vector v4{1,2,3,4,5,6,7,8};

  double a = m4.Norm(), b = v4.Norm();
  double d = MatrixNorm(m4);
  double e = VectorNorm(v4);
  double c = 1*1 + 2*2 + 3*3 + 4*4 + 5*5 + 6*6 + 7*7 + 8*8;
  c = sqrt(c);
  std::cout << a << " " << b << " " << c << " " << d << " " << e;
}

void TestPrinta() {
    std::cout<<"Test Print i PringMatrix"<<std::endl;
  Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
  m1.Print(5);
  std::cout << std::endl;
  PrintMatrix(m1, 5);
  m1.Print(5, 1);
  PrintMatrix(m1, 5, 1);
}

void TestZaSabiranjeiOduzimanje() {
    std::cout<<"Test za sabiranje i oduzimanje matrica "<<std::endl;
  Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
  Matrix m2 = {{1, 2, 3}, {3, 4, 5}, {4, 15, 9}};
  Matrix nova = m1 + m2;
  nova.Print(6);
  std::cout << std::endl;
  Matrix p = m1 - m2;
  p.Print(6);
  std::cout << std::endl;
  p += m1;
  p.Print(6);
  std::cout << std::endl;
  nova -= m2;
  nova.Print(6);
}

void TestZaSabiranjeIuzeci() {
    std::cout<<"Test za sabiranje  matrica, razlicite dimenzije "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    Matrix m2 = {{1, 2, 3}, {3, 4, 5}};
    Matrix nova = m1 + m2;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZaSabiranjeIuzeci2() {
    std::cout<<"Test za sabiranje  matrica, razlicite dimenzije "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    Matrix m2 = {{1, 2, 3}, {3, 4, 5}};
    m1 += m2;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZaSOduzimanjeIuzeci() {
    std::cout<<"Test za oduzimanje  matrica, razlicite dimenzije "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    Matrix m2 = {{1, 2, 3}, {3, 4, 5}};
    Matrix nova = m1 - m2;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestZaOduzimanjeIuzeci2() {
     std::cout<<"Test za oduzimanje  matrica, razlicite dimenzije "<<std::endl;
  try {
    Matrix m1 = {{1, 2, 3}, {-3, -5, 9}, {6, 4, 0}};
    Matrix m2 = {{1, 2, 3}, {3, 4, 5}};
    m1 -= m2;
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void TestMnozenjeSkalarom() {
     std::cout<<"Test za mnozenje matrice skalarom:  "<<std::endl;
  Matrix m = {{2.345, 3.45, 4.096}, {2.345, 6.435, 76}};
  Matrix m1(2, 3);
  m1 = 4 * m;
  m1.Print(10);
  std::cout << std::endl;
  m1 = m1 * 4;
  m1.Print(10);
  std::cout << std::endl;
  m1 *= 5;
  m1.Print(10);
}


void TestMnozenjaMatrica() {
    std::cout<<"Test za mnozenje matrica:  "<<std::endl;
  Matrix m1 = {{2.345, 3.45, 4.096}, {2.345, 6.435, 76}};
  Matrix m2 = {{1, 4}, {4, 6}, {9, 6}};
  Matrix p = m1 * m2;
  p.Print(10);
  std::cout << std::endl;
  p *= m1;
  p.Print(10);
}

void TestMnozenjaMatricaIzuzeci() {
    std::cout<<"Test za mnozenje matrica ( razlicite dimenzije ):  "<<std::endl;
  try {
    Matrix m1 = {{2.345, 3.45, 4.096}, {2.345, 6.435, 76}};
    Matrix m2 = {{1, 4}, {4, 6}, {9, 6}, {0, 0}};
    Matrix p = m1 * m2;
    p.Print(10);
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}

void MnozenjeMatriceIVektora() {
std::cout<<"Test za mnozenje matrice i vektora:  "<<std::endl;
  Matrix m = {{1, 2, 3}, {1, 3, 4}};
  Vector v = {1, 2, 3};
  v = m * v;
  v.Print(',');
}

void MnozenjeMatriceIVektoraIzuzeci() {
    std::cout<<"Test za mnozenje matrice i vektora:  (razlicite dimenzije)"<<std::endl;
  try {
    Matrix m = {{1, 2, 3}, {1, 3, 4}};
    Vector v = {1, 2, 3, 5, 6, 7, 8};
    v = m * v;
    v.Print(',');
  } catch (std::domain_error e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "Pogresan izuzetak";
  }
}
void EpsilonTest() {
    std::cout<<"Test epsilona";
  Vector v{1, 3.45, 54, 234, 54.234, 35, 234, -234.43};
  Matrix m{{1,3.45,54, }, { 234,54.234, 35 },{234, -234.43, 54}};
  double ve = v.GetEpsilon();
  double me = m.GetEpsilon();
  std::cout << ve << " " << me;
}

void Transponovanje() {
    std::cout<<"Transponovanje matrice"<<std::endl;
  Matrix m{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
  Matrix trans = Transpose(m);
  trans.Print(10);
}

void Transponovanje2() {
    std::cout<<"Transponovanje matrice i kvadratne matrice "<<std::endl;
  Matrix m{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
  m.Transpose();
  m.Print(4);
  std::cout << std::endl;
  Matrix kv{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  kv.Print();
  kv.Transpose();
  kv.Print();
}

int main() {
  // nova
  // testovi za vektor :3

  VVektorTestKonstruktora();
  std::cout << std::endl;
  VVektorTestKonstrutkoraIzuzeci();
  std::cout << std::endl;
  VVektorTestInitKonstruktora();
  std::cout << std::endl;
  VVektorTestInitKonstruktoraIzuzeci();
  std::cout << std::endl;
  VElementi(4);
  std::cout << std::endl;
  VTest();
  std::cout << std::endl;
  VTestIzuzeci();
  std::cout << std::endl;
  VTestIzuzeci2();
  std::cout << std::endl;
  VTestIzuzeci3();
  std::cout << std::endl;
  VTestIzuzeci4();
  std::cout<<std::endl;
  VTestZagrade();
  std::cout << std::endl;
  VTestZagradeIzuzeci();
  std::cout << std::endl;
  VTestZagradeIzuzeci2();
  std::cout << std::endl;
  EpsilonTest();
  std::cout << std::endl;
  VTestPrinta();
  VSabiranje();
  VSabiranjeIzuzeci1();
  std::cout << std::endl;
  VOduzimanjeIzuzeci();
  std::cout << std::endl;
  VSabiranjeIzuzeci2();
  std::cout << std::endl;
  VOduzimanjeIzuzeci2();
  std::cout << std::endl;
  VMnozenjeiDijeljenjeSkalarom();
  std::cout << std::endl;
  VMnozenjeVektora();
  std::cout << std::endl;
  VMnozenjeVektoraIzuzeci();
  std::cout << std::endl;
  Nula2();
  Nula1();

  // testovi za matrix :3

  TestKonstruktora();
  std::cout << std::endl;
  TestKonstruktora2();
  std::cout << std::endl;
  TestKonstruktora3();
  std::cout << std::endl;
  TestVektorKonstruktora();
  std::cout << std::endl;
  TestVektorKonstruktora2();
  std::cout << std::endl;
  TestInitKonstruktora();
  std::cout << std::endl;
  TestInitKonstruktora2();
  std::cout << std::endl;
  TestInitKonstruktora3();
  std::cout << std::endl;
  GrbavaMatrica();
  std::cout << std::endl;
  TestRedoviIKolone();
  std::cout << std::endl;
  TestZagrada();
  std::cout << std::endl;
  TestZagradaIzuzecia();
  std::cout << std::endl;
  TestZagradaIzuzecib();
  std::cout << std::endl;
  TestZagradaIzuzecic();
  std::cout << std::endl;
  TestZagradaIzuzecid();
  std::cout << std::endl;
  TestZagradaIzuzecie();
  std::cout << std::endl;
  TestZagradaIzuzecif();
  std::cout << std::endl;
  TestZagradaIzuzeci2();
  std::cout << std::endl;
  TestZagradaIzuzeci2a();
  std::cout << std::endl;
  TestZagradaIzuzeci2b();
  std::cout << std::endl;
  TestZagradaIzuzeci2c();
  std::cout << std::endl;
  TestNorme();
  std::cout << std::endl;
  TestPrinta();
  std::cout << std::endl;
  TestZaSabiranjeiOduzimanje();
  std::cout << std::endl;
  TestZaSabiranjeIuzeci();
  std::cout << std::endl;
  TestZaSabiranjeIuzeci2();
  std::cout << std::endl;
  TestZaSOduzimanjeIuzeci();
  std::cout << std::endl;
  TestZaOduzimanjeIuzeci2();
  std::cout << std::endl;
  TestMnozenjeSkalarom();
  std::cout << std::endl;
  TestMnozenjaMatricaIzuzeci();
  std::cout << std::endl;
  TestMnozenjaMatrica();
  std::cout << std::endl;
  MnozenjeMatriceIVektora();
  std::cout << std::endl;
  MnozenjeMatriceIVektoraIzuzeci();
  std::cout << std::endl;
  EpsilonTest();
  std::cout << std::endl;
  Transponovanje();
  std::cout << std::endl;
  Transponovanje2();

  return 0;
}
