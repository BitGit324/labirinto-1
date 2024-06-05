#ifndef MAPPA_H
#include "../include/mappa.h"
#include <stdio.h>
#endif // MAPPA_H

void visualizzaMappa(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info,
                     int nebbia[MAX_RIGHE][MAX_COLONNE]) {
  for (int i = 0; i < info.righe; i++) {
    for (int j = 0; j < info.colonne; j++) {
      if (i == info.rY && j == info.rX) {
        printf(" 0 ");
      } else if (mappa[i][j] == 'E' || nebbia[i][j] == 0) {
        printf(" %c ", mappa[i][j]);
      } else {
        printf(" ? ");
      }
    }
    printf("\n");
  }
}

void aggiungiOstacoli(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info,
                      int nrOstacoli) {
  for (int i = 0; i < nrOstacoli; i++) {
    int x = rand() % (info.righe - 2) + 1; // escludo la prima riga
    int y = rand() % info.colonne;

    if (mappa[x][y] == '.') { // se la mappa è libera
      mappa[x][y] = '#';      // metto l'ostacolo
    } else {
      --i;
    }
  }
}

#if VERSIONE > 2

void aggiungiChiave(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info) {
  for (int i = 0; i < 1; i++) {
    int x = rand() % (info.righe - 2) + 1; // escludo la prima riga
    int y = rand() % info.colonne;

    if (mappa[x][y] == '.') { // se la mappa è libera
      mappa[x][y] = 'C';      // metto l'ostacolo
    } else {
      --i;
    }
  }
}
#endif

#if VERSIONE == 3

void aggiungiBonus(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info, int nrBonus) {
  for (int i = 0; i < nrBonus; i++) {
    int x = rand() % (info.righe - 2) + 1; // escludo la prima riga
    int y = rand() % info.colonne;

    if (mappa[x][y] == '.') { // se la mappa è libera
      mappa[x][y] = 'B';      // metto l'ostacolo
    } else {
      --i;
    }
  }
}
#endif

void creaMappa(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info) {
  for (int i = 0; i < info.righe; ++i) {
    for (int j = 0; j < info.colonne; ++j) {
      mappa[i][j] = '.'; // mappa vuota
    }
  }
}
// all'inizio non vedo nulla -> nebbia=0
void calcolNebbia(int nebbia[MAX_RIGHE][MAX_COLONNE], MappaInfo info) {
  for (int i = info.rY - 1; i <= info.rY + 1; i++) {
    for (int j = info.rX - 1; j <= info.rX + 1; j++) {
      if ((i >= 0 && i < info.righe) && (j >= 0 && j < info.colonne)) {
        nebbia[i][j] = 0;
      }
    }
  }
}

char movimento(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo *info) {
  char t;
  // info->rY è (*info).rY
  int Y = info->rY, X = info->rX;
  do {
    printf("muoviti con W-A-S-D:   ");
    scanf(" %c", &t);
  } while (!(t == 'w' || t == 'W' || t == 'a' || t == 'A' || t == 's' ||
             t == 'S' || t == 'd' || t == 'D'));

  switch (t) {
  case 'w':
  case 'W':
    Y--;
    break;
  case 'a':
  case 'A':
    X--;
    break;
  case 's':
  case 'S':
    Y++;
    break;
  case 'd':
  case 'D':
    X++;
    break;
  }

  if (X >= 0 && X < info->colonne && Y >= 0 && Y < info->righe &&
      mappa[Y][X] != '#') {
    info->rX = X;
    info->rY = Y;
  }

  // bonus chiave
  return t;
}