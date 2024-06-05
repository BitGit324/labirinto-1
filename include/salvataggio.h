#ifndef SALVATAGGIO_H
#define SALVATAGGIO_H

#ifndef STRUTTURE_H
#include "../include/strutture.h"
#endif

#ifndef CONFIG_H
#include "../include/config.h"
#endif

//prendo i tipi di file
#ifndef MAPPA_H
#include "../include/mappa.h"
#endif


void carica();

void salva(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info, Percorso strada[MAX_PERCORSO],
   int ultimoPasso);


#endif // SALVATAGGIO_H