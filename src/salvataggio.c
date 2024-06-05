// se non è stato definito
#ifndef SALVATAGGIO_H
#include "../include/salvataggio.h"
#include <stdio.h>
#endif // SALVATAGGIO_H

void carica() {
  FILE *fp = fopen(NOMEFILE, "r");
  if (fp != NULL) {
    char buffer[256];

    // leggo il file fino all'ultima riga
    while (fgets(buffer, sizeof(buffer), fp)) {
      printf("%s", buffer);
    }
    fclose(fp);
  } else {
    printf("non è stato possibile caricare il salvataggio.\n");
  }
}

void salva(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info,
           Percorso strada[15], int ultimoPasso) {
  FILE *salvataggio = fopen(NOMEFILE, "w");
  printf("\n salvataggio in corso .");
  if (salvataggio != NULL) {
    // scrivo mappa
    fprintf(salvataggio, "Mappa:\n");
    // scrivo tutta la mappa
    for (int i = 0; i < info.righe; i++) {
      for (int j = 0; j < info.colonne; j++) {
        fprintf(salvataggio, " %c ", mappa[i][j]);
      }
      fprintf(salvataggio, "\n\n");
    }
    printf(".....");
    fprintf(salvataggio, "\n\n");
    fprintf(salvataggio, "percorso vincente:\n");
    for (int i = 0; i < ultimoPasso; i++) {
      fprintf(salvataggio, "(%d,%d) ", strada[i].x, strada[i].y);
      printf(".");
    }
    fprintf(salvataggio, "\n\n");
    fprintf(salvataggio, "Passi vincenti:\n");
    for (int i = 0; i < ultimoPasso; i++) {
      fprintf(salvataggio, " %c ", strada[i].passo);
      printf(".");
    }
    fprintf(salvataggio, "\n");
    fclose(salvataggio);
    printf("\n salvataggio completato\n");
  } else {
    printf("\n non è stato possibile salvare il file.\n");
  }
}