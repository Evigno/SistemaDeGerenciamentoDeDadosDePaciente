# Compilador e flags
CC = gcc
CFLAGS = -Wall -g -std=c11

# Nome do executável
EXEC = healthsys

# Arquivos fonte e objeto
SRC = main.c bdpaciente.c
OBJ = $(SRC:.c=.o)

# Alvo padrão: construir o executável
all: $(EXEC)

# Regra para linkar (vincular) o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Regras explícitas para compilar cada arquivo .c em .o
main.o: main.c bdpaciente.h paciente.h
	$(CC) $(CFLAGS) -c main.c

bdpaciente.o: bdpaciente.c bdpaciente.h paciente.h
	$(CC) $(CFLAGS) -c bdpaciente.c

# Alvo para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Alvo para executar
run: all
	./$(EXEC)

.PHONY: all clean run