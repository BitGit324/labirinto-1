#ifndef STRUTTURE_H
#define STRUTTURE_H

typedef struct {
  int x;
  int y;
  char passo;
} Percorso;

#if VERSIONE == 1

typedef struct {
  int righe;
  int colonne;
  int rX;
  int rY;
} MappaInfo;

#elif VERSIONE == 2

typedef struct {
  int righe;
  int colonne;
  int chiave;
  int rX;
  int rY;
} MappaInfo;

#else

typedef struct {
  int righe;
  int colonne;
  int chiave;
  int punti;
  int rX;
  int rY;
} MappaInfo;

#endif

#endif // STRUTTURE_H