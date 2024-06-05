#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef STRUTTURE_H // se non è gia definito STRUTTURE_H
#include "../include/strutture.h"
#endif

#ifndef CONFIG_H
#include "../include/config.h"
#endif

#include "../include/mappa.h"
#include "../include/salvataggio.h"

int menu() {

  int scelta;
  int file;
  FILE *percorso = fopen(NOMEFILE, "r");
  printf("Benvenuto al labirinto! versione n.%d \n", VERSIONE);
  printf("1. Nuova partita con impostazioni di default\n");
  printf("2. Nuova partita con impostazioni personalizzate\n");
  printf("3. Esci\n");
  if (percorso) {
    printf("4. visualizza ultimo percorso vincente\n");
    fclose(percorso);
  }

  printf("Scegli un'opzione: ");
  do {
    scanf("%d", &scelta);
  } while (scelta != 0 && scelta != 1 && scelta != 2 && scelta != 3 &&
           scelta != 4);
  // ritorno la decisione
  return scelta;
}

int main() {
  int nebbia[MAX_RIGHE][MAX_COLONNE];
  int righe, colonne, nrOstacoli, victory;
  int scelta;
  char t;
  Percorso strada[MAX_PERCORSO];
  int ultimoPasso;

  while (1) {
    srand(time(NULL));

    scelta = menu();
    // int scelta = 2; //debug

    if (scelta == 3) {
      return 0;
    }
    if (scelta == 4) {
      carica();
      return 0;
    }

    if (scelta == 2) {
      do {
        printf("Inserisci quante righe deve avere la mappa(max %d): ",
               MAX_RIGHE);
        scanf("%d", &righe);
        printf("Inserisci quante colonne deve avere la mappa(max %d): ",
               MAX_COLONNE);
        scanf("%d", &colonne);
        if (righe > MAX_RIGHE || colonne > MAX_COLONNE) {
          printf("Inserisci la dimensione giusta!");
        }
      } while (righe > MAX_RIGHE || colonne > MAX_COLONNE);
      do {
        printf("inserisci il numero di ostacoli (max %d): ", MAX_OSTACOLI);
        scanf("%d", &nrOstacoli);
      } while (nrOstacoli > MAX_OSTACOLI);
    }

    else if (scelta == 1) {
      righe = DEFAULT_RIGHE;
      colonne = DEFAULT_COLONNE;
      nrOstacoli = DEFAULT_OSTACOLI;
    }
#if VERSIONE == 3
    int nrBonus;
    if (scelta == 2) {
      do {
        printf("Inserisci quanti BONUS bisogna aggiungere alla mappa: ");
        scanf("%d", &nrBonus);
        if (nrBonus > MAX_BONUS) {
          printf("Inserisci la dimensione giusta!");
        }
      } while (nrBonus > MAX_BONUS);
    } else {
      nrBonus = DEFAULT_BONUS;
    }

#endif

    MappaInfo info;
    info.righe = righe;
    info.colonne = colonne;

#if VERSIONE >= 2

    info.chiave = 0;
#endif

#if VERSIONE == 3

    info.punti = DEFAULT_PUNTI;
#endif

    char mappa[MAX_RIGHE][MAX_COLONNE];

    for (int i = 0; i < righe; ++i) {
      for (int j = 0; j < colonne; ++j) {
        nebbia[i][j] = 1;
      }
    }
    creaMappa(mappa, info);
    aggiungiOstacoli(mappa, info, nrOstacoli);

#if VERSIONE >= 2
    //aggiungo la chiave alla mappa
    aggiungiChiave(mappa, info);
#endif

#if VERSIONE == 3
    aggiungiBonus(mappa, info, nrBonus);
#endif

    int startY = 0, startX = rand() % colonne, endY = righe - 1,
        endX = rand() % colonne;

    // segno inizio e fine sulla mappa
    mappa[startY][startX] = 'S';
    mappa[endY][endX] = 'E';
    // imposto la partenza del robot
    info.rY = startY;
    info.rX = startX;

    t = ' ';                              // tasto premuto dal giocatore
    victory = 0;                          // diventa 1 a partita vinta
    Percorso strada[righe * colonne * 2]; // mi segno il percorso vincente
    ultimoPasso = -1;
    while (victory == 0) {
      ultimoPasso = ultimoPasso + 1;

#if VERSIONE == 3
      info.punti = info.punti - DECREMENTO_PASSO;
#endif

      calcolNebbia(nebbia, info);

      visualizzaMappa(mappa, info, nebbia);

      //stampo chiave
#if VERSIONE == 2
      if (info.chiave == 0) {
        printf("NON HAI ANCORA TROVATO LA CHIAVE\n");
      } else {
        printf("dirigiti all'uscita\n");
      }
#endif
#if VERSIONE == 3   //stampo puinteggio e chiave
      if (info.chiave == 0) {
        printf("NON HAI ANCORA TROVATO LA CHIAVE  !!!!       PUNTI:   %d\n",
               info.punti);
      } else {
        printf("dirigiti all'uscita  ||||      PUNTI:   %d\n", info.punti);
      }
#endif
      strada[ultimoPasso].x = info.rX;
      strada[ultimoPasso].y = info.rY;

      // se il robottino è sopra l'uscita
      if (mappa[info.rY][info.rX] == 'E') {

#if VERSIONE >= 2
        if (info.chiave == 0) {
          t = movimento(mappa, &info);
          strada[ultimoPasso].passo = t;
          continue; // se non ha la chiave continuo il ciclo
        }
#endif
        printf("Hai vinto!\n");
        victory = 1;

        printf("Vuoi salvare il percorso vincente? (s/n): ");
        char vuoiSalvare;
        scanf(" %c", &vuoiSalvare);
        if (vuoiSalvare == 's' || vuoiSalvare == 'S') {
          salva(mappa, info, strada, ultimoPasso);
        }

      } else {
#if VERSIONE >= 2
        if (mappa[info.rY][info.rX] == 'C') {
          info.chiave = 1;//chiave nell'inventario
          mappa[info.rY][info.rX] = '.'; //raccolgo la chiave
          visualizzaMappa(mappa, info, nebbia);
          printf("HAI TROVATO LA CHIAVE! ora scappa dal labirinto\n");
        }
#endif
#if VERSIONE == 3
        if (mappa[info.rY][info.rX] == 'B') {
          info.punti = info.punti + VALORE_BONUS;
          mappa[info.rY][info.rX] = '.';
          visualizzaMappa(mappa, info, nebbia);
          printf("hai trovato un tesoro!    PUNTI:   %d\n", info.punti);
        }
#endif
        t = movimento(mappa, &info);
        strada[ultimoPasso].passo = t;
      }
    }
    printf("\n");
  }
}