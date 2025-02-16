#include <stdio.h>

int da_li_je_kvadrat(char *s) {

  char *p = s;
  char mat[100][100];
  int n = 0, m = 0, i, j;
  int duzina = 0;
  

  while (*p != '\0') {
    if (*p != '\n' && *p != '+' && *p != ' ')
      return 0;
    p++;
  }

  p = s;

  while (*p != '\n' && *p != '\0') {
    n++;
    if (*p == '\n')
      break;
    p++;
  }

  p = s;
  int na_zadnjem = 1;

  while (*p != '\0') {
    if (*p == '\n')
      m++;
    if (*p == '+' && *(p + 1) == '\0') {
      m++;
      na_zadnjem = 0;
    }
    p++;
  }

  p--;
  if (*p == '\n')
    p--;

  int l = 0;

  while (*p != '\n') {
    l++;
    if (*p == '\n')
      break;
    p--;
  }
  if (m != n || m != l)
    return 0;

  char *s1 = s;
  i = 0;
  j = 0;
  while (*s1 != '\0') {
    if (*s1 == '\n') {
      i++;
      s1++;
      // printf("i: %d\n",i);
    } else {
      // printf("string: %c ",*s1);
      mat[i][j] = *s1;
      // printf("matrica: %c ",mat[i][j]);
      j++;
      if (j == n)
        j = 0;
      s1++;
      // printf("j: %d\n",j);
    }
  }

  int jeste = 1;

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (i == 0) {
        if (mat[i][j] != '+')
          jeste = 0;
      } else if (j == 0) {
        if (mat[i][j] != '+')
          jeste = 0;
      } else if (j == n - 1) {
        if (mat[i][j] != '+')
          jeste = 0;
      } else if (i == n - 1) {
        if (mat[i][j] != '+')
          jeste = 0;
      } else if (i > 0 && i < n - 1 && j > 0 && j < n - 1) {
        if (mat[i][j] != ' ')
          jeste = 0;
      }
    }
  }

  return jeste;
}

int main() {
  /* AT1: Kvadrat sirine 1 (funkcija ne smije mijenjati string) */
  printf("%d ", da_li_je_kvadrat("+"));
  printf("%d", da_li_je_kvadrat("-"));
  return 0;
}
