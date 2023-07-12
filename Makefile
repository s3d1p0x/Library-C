# Makefile

# Variables pour le compilateur et les options de compilation
CC = gcc
CFLAGS = -Wall -Werror

# Nom de l'exécutable
EXEC = c-library

# Listes des fichiers objets
OBJ = main.o gestion.o

# Règle par défaut (première règle)
all: $(EXEC)

# Crée l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Crée les fichiers objets à partir des fichiers source
main.o: main.c gestion.h
	$(CC) $(CFLAGS) -c main.c -o main.o

gestion.o: gestion.c gestion.h
	$(CC) $(CFLAGS) -c gestion.c -o gestion.o

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)