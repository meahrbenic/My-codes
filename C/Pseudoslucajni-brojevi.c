#include <math.h>
#include <stdio.h>

int broj_cifara(int br) {
  int cifre = 0;
  while (br != 0) {
    cifre++;
    br = br / 10;
  }
  return cifre;
}

double step(int b) {
  double stepen = 1;
  int i;
  for (i = 0; i < b; i++) {
    stepen *= 10;
  }
  return stepen;
}

int slucajni(int broj) {
  double x;
  int c = broj_cifara(broj);
  x = (double)broj / step(c);
  x = x / step(8 - c);
  // printf(" %g ",x);
  x = sqrt(x);
  // printf(" %lf ",x);
  x = x * 10000;
  // printf(" %lf ",x);
  int pom = x;
  // printf("%d",pom);
  double ostatak;
  ostatak = x - pom;
  // printf(" %lf ",ostatak);
  ostatak = ostatak * 100000000;
  // printf(" %lf ",ostatak);
  int fin = ostatak;
  return fin;
}

int main() {
  printf("%d", slucajni(12345678));

  return 0;
}
