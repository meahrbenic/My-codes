// TP 2021/2022: Zadaća 1, Zadatak 2
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>


#define eps 0.0000000001

typedef std::vector<std::vector<double>> matrica;

matrica KreirajMatricu(int broj_redova, int broj_kolona) {
  return matrica(broj_redova, std::vector<double>(broj_kolona));
}

int BrojRedova(matrica mat) { return mat.size(); }
int BrojKolona(matrica mat) { return mat.at(0).size(); }
int BrojKolona(matrica mat, int kolona) { return mat.at(kolona).size(); }

matrica UnesiMatricu(int n, int m){
    auto pocetna=KreirajMatricu(n, m); 
    for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++) {
        std::cin >> pocetna.at(i).at(j);
    } 
 }  
 return pocetna;
}

bool IspravnaMatrica(matrica mat) {
  for (int i = 0; i < BrojRedova(mat) - 1; i++) {
    if (BrojKolona(mat, i) != BrojKolona(mat, i + 1))
      return false;
  }
  return true;
}

matrica MnozenjeMatrica(matrica mat1, matrica mat2) {
    matrica pomnozena; 
    int brojKolona1,brojRedova1,brojKolona2,brojRedova2;
    if(mat1.empty()){
        brojKolona1=0;
        brojRedova1=0;
    }
    else{
        brojKolona1=BrojKolona(mat1);
        brojRedova1=BrojRedova(mat1);
    }
    if(mat2.empty()){
        brojKolona2=0;
        brojRedova2=0;
    }
    else{
        brojKolona2=BrojKolona(mat2);
        brojRedova2=BrojRedova(mat2);
    }

    if (brojKolona1 != brojRedova2) throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    if (brojKolona1 < 0 || brojRedova1 < 0 || brojKolona2 < 0 || brojRedova2 < 0) { throw std::domain_error("Matrice nisu saglasne za mnozenje!");}
    if (!IspravnaMatrica(mat1) || !IspravnaMatrica(mat2)) throw std::domain_error("Neispravna matrica!");

    pomnozena = KreirajMatricu(brojRedova1, brojKolona2);

    if(pomnozena.size()!=0){
        for (int i = 0; i < BrojRedova(pomnozena); i++) {
            for (int j = 0; j < BrojKolona(pomnozena); j++) {
                for (int k = 0; k < BrojKolona(mat1); k++) {
                pomnozena.at(i).at(j) += mat1.at(i).at(k)* mat2.at(k).at(j);
                }
            }
        }
    }

    return pomnozena;
}

std::array<matrica, 2> DoolittleLU(matrica H) {
    int brojKolona,brojRedova;
  if(H.empty()){
      brojKolona=0; brojRedova=0; 
  }  
    else{
        brojKolona=BrojKolona(H); 
        brojRedova=BrojRedova(H);
    }

  if (brojKolona != brojRedova) throw std::domain_error("Matrica mora biti kvadratna!");
  if (!IspravnaMatrica(H)) throw std::domain_error("Neispravna matrica!");

  int n = brojKolona;
  std::array<matrica, 2> lu;

  matrica L = KreirajMatricu(n, n);
  matrica U = KreirajMatricu(n, n);

  double suma;
  int p = 0;
  for (int j = 0; j < n; j++) {
    for (int i = 0; i <= j; i++) {
      suma = H.at(i).at(j);
      for (int k = 0; k <= i - 1; k++) {
        suma = suma - H.at(i).at(k) * H.at(k).at(j);
      }
      H.at(i).at(j) = suma;
    }
    p = j;
    for (int i = j + 1; i < n; i++) {
      suma = H.at(i).at(j);
      for (int k = 0; k <= j - 1; k++) {
        suma = suma - H.at(i).at(k) * H.at(k).at(j);
      }
      H.at(i).at(j) = suma;
      if (std::fabs(suma) > std::fabs(H.at(p).at(j)))
        p = i;
    }

    if (std::fabs(H.at(j).at(j)) < 0.0000000001)
      throw std::domain_error("Matrica je singularna!");

    double mi = 1 / H.at(j).at(j);
    for (int i = j + 1; i < n; i++) {
      H.at(i).at(j) *= mi;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j)
        L.at(i).at(j) = 1;
      else if (j > i)
        L.at(i).at(j) = 0;
      else
        L.at(i).at(j) = H.at(i).at(j);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j < i)
        U.at(i).at(j) = 0;
      else
        U.at(i).at(j) = H.at(i).at(j);
    }
  }

  lu.at(0) = L;
  lu.at(1) = U;

  return lu;
}

bool ProvjeriFaktorizaciju(matrica H, std::array<matrica, 2> trodim){
    try{
        matrica provjera = MnozenjeMatrica(trodim.at(0), trodim.at(1));
        int n;
        if(H.empty()){
            n=0;
        }
        else{
           n=BrojKolona(H); 
        }
    
         for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if( !(std::fabs(H.at(i).at(j) - provjera.at(i).at(j)) <eps  ))  return false; 
            }
        }
    }
    catch(...){
        return false;
    }
    return true;
}


int main() {

  int n=0;
  std::cout << "Broj redova/kolona matrice: ";
  std::cin >> n;
  std::cout << "Elementi matrice: ";

  matrica pocetna= UnesiMatricu(n, n);
 
  try {
    std::array<matrica, 2> proba = DoolittleLU(pocetna);

    std::cout << std::endl;
    std::cout << "Matrica L: ";
    std::cout << std::endl;
    
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        std::cout << proba.at(0).at(i).at(j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Matrica U: ";
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        std::cout << proba.at(1).at(i).at(j) << " ";
      }
      std::cout << std::endl;
    }
  }
   catch (...) {
    std::cout << "LU faktorizacija ne postoji, jer je matrica singularna!";
  }

  return 0;
}
