#include <math.h>
#include <stdio.h>
#include <string.h>
#define eps 0.001

struct Student {
  char ime[20], prezime[20];
  int ocjene[1000];
  int br_ocjena;
};

int prosjeci(struct Student *studenti, int vel) {
  int i, j, k;
  double prosjek[1000], pr;
  double zbir_ocjena = 0;
  double max_prosjek = 0;
  int maxi = 0;

  for (i = 0; i < vel; i++) {
    zbir_ocjena = 0;
    for (j = 0; j < studenti[i].br_ocjena; j++) {
      zbir_ocjena += studenti[i].ocjene[j];
    }
    pr = zbir_ocjena / studenti[i].br_ocjena;
    prosjek[i] = pr;
    if (prosjek[i] > max_prosjek) {
      max_prosjek = prosjek[i];
      maxi = i;
    }
  }
  struct Student najveci_prosjek = studenti[maxi];

  for (i = 0; i < vel; i++) {
    for (j = i; j < vel - 1; j++) {
      if (fabs(prosjek[i] - prosjek[j + 1]) < eps) {
        for (k = j + 1; k < vel - 1; k++) {
          studenti[k] = studenti[k + 1];
          prosjek[k] = prosjek[k + 1];
        }
        vel--;
        j--;

        for (k = i; k < vel - 1; k++) {
          studenti[k] = studenti[k + 1];
          prosjek[k] = prosjek[k + 1];
        }
        vel--;
        i--;
      }
    }
  }
  if (vel > 0)
    printf("%s %s\n", najveci_prosjek.prezime, najveci_prosjek.ime);

  return vel;
}

int main() {
  /* AT5: Pet istih - treba izbaciti sve takve */
  struct Student niz[] = {{"Simo", "Simic", {5, 5, 4, 4, 3, 3}, 6},
                          {"Hamo", "Hamic", {3, 4, 5}, 3},
                          {"Sara", "Saric", {5, 3}, 2},
                          {"Hana", "Hanic", {4, 4, 4, 4}, 4},
                          {"Una", "Unic", {4, 4, 4, 4}, 4},
                          {"Din", "Dinic", {3, 4, 5, 5, 4}, 5}};
  int i;
  int vel = prosjeci(niz, 6);
  printf("Poslije funkcije (%d):\n", vel);
  for (i = 0; i < vel; i++) {
    printf("%s %s\n", niz[i].prezime, niz[i].ime);
  }
  /*	Dinic Din
  Poslije funkcije (1):
  Dinic Din*/
  return 0;
}
