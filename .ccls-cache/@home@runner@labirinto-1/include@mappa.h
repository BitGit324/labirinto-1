#ifndef MAPPA_H
#define MAPPA_H

#ifndef STRUTTURE_H
#include "../include/strutture.h"
#endif

#ifndef CONFIG_H
#include "../include/config.h"
#endif

void visualizzaMappa(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info,
                     int nebbia[MAX_RIGHE][MAX_COLONNE]);

void aggiungiOstacoli(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info,
                      int nrOstacoli);

#if VERSIONE >= 2
void aggiungiChiave(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info);
#endif

#if VERSIONE == 3
void aggiungiBonus(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info,
                   int nrBonus);
#endif

void creaMappa(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo info);

void calcolNebbia(int nebbia[MAX_RIGHE][MAX_COLONNE], MappaInfo info);

char movimento(char mappa[MAX_RIGHE][MAX_COLONNE], MappaInfo *info);

#endif // MAPPA_H