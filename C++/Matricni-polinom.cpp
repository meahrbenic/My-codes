// TP 2021/2022: Zadaća 3, Zadatak 3

// pokusaaaj
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>


template <typename TipElemenata> struct Matrica {
  char ime_matrice; // Koristi se samo u funkciji "UnesiMatricu"
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!!!
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona];
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  return mat;
}

template <typename TipElemenata>
void UnesiMatricu(char ime, Matrica<TipElemenata> &mat) {
  mat.ime_matrice = ime;
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
    }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost = 6, bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost)
                << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if (treba_brisati) {
    if (!mat.elementi)
      return;
    for (int i = 0; i < mat.br_redova; i++)
      delete[] mat.elementi[i];
    delete[] mat.elementi;
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {

  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricaSkalar(const Matrica<TipElemenata> &m1, double s) {

  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++) {
    for (int j = 0; j < m1.br_kolona; j++) {

      m3.elementi[i][j] = m1.elementi[i][j] * s;
    }
  }
  return m3;
}

template <typename TipElemenata> Matrica<TipElemenata> DajJedinicnu(int n) {
  try {
    auto I = StvoriMatricu<TipElemenata>(n, n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j)
          I.elementi[i][j] = 1;
        else
          I.elementi[i][j] = 0;
      }
    }
    return I;
  } catch (...) {
    throw;
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,
                                     const Matrica<TipElemenata> &m2) {
  if (m1.br_kolona != m2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  Matrica<TipElemenata> m3;
  m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
  for (int i = 0; i < m1.br_redova; i++) {
    for (int j = 0; j < m2.br_kolona; j++) {
      TipElemenata suma{};
      for (int k = 0; k < m2.br_redova; k++) {
        suma += m1.elementi[i][k] * m2.elementi[k][j];
      }
      m3.elementi[i][j] = suma;
    }
  }
  return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(Matrica<TipElemenata> mat,
                                      std::vector<double> koef) {
  if (mat.br_kolona != mat.br_redova)
    throw std::domain_error("Matrica mora biti kvadratna");

  Matrica<TipElemenata> MP, ZB, NOVA, I, pom;
  if (koef.size() == 0) {
    ZB = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
    for (int i = 0; i < mat.br_redova; i++) {
      for (int j = 0; j < mat.br_kolona; j++) {
        ZB.elementi[i][j] = 0;
      }
    }
    return ZB;
  }
  try {
    MP = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
    // ZB = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
    NOVA = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);

    I = DajJedinicnu<TipElemenata>(mat.br_redova);
    ZB = MatricaSkalar(I, koef.at(0));

    for (int i = 0; i < mat.br_redova; i++) {
      for (int j = 0; j < mat.br_kolona; j++) {
        MP.elementi[i][j] = mat.elementi[i][j];
        NOVA.elementi[i][j] = MP.elementi[i][j];
      }
    }
    Matrica<TipElemenata> pomocna, pomocna2, pomocna3;
    for (int i = 1; i < koef.size(); i++) {
      if (i != 1) {
        pomocna = ProduktMatrica(MP, NOVA);
        for (int k = 0; k < mat.br_redova; k++) {
          for (int j = 0; j < mat.br_kolona; j++) {
            NOVA.elementi[k][j] = pomocna.elementi[k][j];
          }
        }
      }
      //  NOVA = ProduktMatrica(MP, NOVA);
      pomocna2 = MatricaSkalar(NOVA, koef.at(i));
      // ZB = ZbirMatrica(ZB, pomocna2);
      pomocna3 = ZbirMatrica(ZB, pomocna2);
      for (int k = 0; k < mat.br_redova; k++) {
        for (int j = 0; j < mat.br_kolona; j++) {
          ZB.elementi[k][j] = pomocna3.elementi[k][j];
        }
      }

      UnistiMatricu(pomocna);
      UnistiMatricu(pomocna2);
      UnistiMatricu(pomocna3);
    }

  } catch (...) {
    UnistiMatricu(MP);
    UnistiMatricu(ZB);
    UnistiMatricu(NOVA);
    UnistiMatricu(I);
  }
  UnistiMatricu(I);
  UnistiMatricu(MP);
  UnistiMatricu(NOVA);
  UnistiMatricu(I);
  return ZB;
}

int main() {
  Matrica<double> a, c, I, m, k; // AUTOMATSKA INICIJALIZACIJA!!!
  int n;
  std::cout << "Unesite dimenziju kvadratne matrice:\n";
  std::cin >> n;
  try {
    a = StvoriMatricu<double>(n, n, 'A');
    std::cout << "Unesite elemente matrice A: ";
    UnesiMatricu('A', a);
    std::cout << "Unesite red polinoma: ";
    int red;
    std::cin >> red;
    std::cout << "Unesite koeficijente polinoma: ";

    // unos polinoma
    std::vector<double> koef(red + 1);
    for (int i = 0; i < red + 1; i++) {
      std::cin >> koef.at(i);
    }

    IspisiMatricu(c = MatricniPolinom(a, koef), 7);
    /* std::vector<std::vector<double>> c={{24,5},{0, -1}};
     for(int i=0; i<2; i++){
         for(int j=0; j<2; j++){
           std::cout<<"         "<<c.at(i).at(j);
         }
         std::cout<<std::endl;
     }*/
  } catch (std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }

  UnistiMatricu(a);
  UnistiMatricu(c);
  UnistiMatricu(m);
  UnistiMatricu(I);
  UnistiMatricu(k);
  return 0;
}
