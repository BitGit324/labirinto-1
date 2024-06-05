#ifndef CONFIG_H
#define CONFIG_H
// VERSIONE
#define VERSIONE 1
// configurazione mappa
#define MAX_RIGHE 30
#define MAX_COLONNE 30
#define MAX_OSTACOLI 25
#define MAX_BONUS 25
// configurazione partita
#define DEFAULT_RIGHE 15
#define DEFAULT_COLONNE 15
#define DEFAULT_OSTACOLI 15

#if VERSIONE == 3
#define DEFAULT_BONUS 30
#define DEFAULT_PUNTI 1050
#define VALORE_BONUS 500
#define DECREMENTO_PASSO 50
#endif
// configurazione salvataggio
#define MAX_PERCORSO (MAX_RIGHE * MAX_COLONNE)
#define NOMEFILE "../salvataggi/percorso.txt"

#endif // CONFIG_H