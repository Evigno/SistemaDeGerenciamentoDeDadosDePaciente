#ifndef PACIENTE_H
#define PACIENTE_H

#define MAX_NOME 100
#define MAX_CPF 15
#define MAX_DATA 11

typedef struct {
    int id;
    char cpf[MAX_CPF];
    char nome[MAX_NOME];
    int idade;
    char data_cadastro[MAX_DATA];
} Paciente;

#endif //PACIENTE_H