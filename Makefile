# Definisce il compilatore
CC=gcc

# Opzioni di compilazione
CFLAGS=-Iinclude

# Nome del file eseguibile
#TARGET=labirinto
TARGET=main  #su replit il tasto run cerca l'eseguibile main

# Regola per costruire l'eseguibile
$(TARGET): main.o mappa.o salvataggio.o strutture.o config.o
	$(CC) -o $(TARGET) main.o mappa.o salvataggio.o strutture.o config.o

# Regola per compilare main.c
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

# Regola per compilare mappa.c
mappa.o: src/mappa.c include/mappa.h
	$(CC) $(CFLAGS) -c src/mappa.c

# Regola per compilare salvataggio.c
salvataggio.o: src/salvataggio.c include/salvataggio.h
	$(CC) $(CFLAGS) -c src/salvataggio.c

# Regola per compilare strutture.c
strutture.o: src/strutture.c include/strutture.h
	$(CC) $(CFLAGS) -c src/strutture.c

# Regola per compilare config.c
config.o: src/config.c include/config.h
	$(CC) $(CFLAGS) -c src/config.c

# Pulisce i file oggetto e l'eseguibile
clean:
	rm -f *.o $(TARGET)