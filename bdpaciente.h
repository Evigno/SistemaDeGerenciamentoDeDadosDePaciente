#ifndef BDPACIENTE_H
#define BDPACIENTE_H

#include "paciente.h"

typedef struct BDPaciente BDPaciente;

BDPaciente* criar_bdpaciente();

void liberar_bdpaciente(BDPaciente* bd);
int carregar_bd_do_csv(BDPaciente* bd, const char* nome_arquivo);
int salvar_bd_para_csv(const BDPaciente* bd, const char* nome_arquivo);

void inserir_paciente(BDPaciente* bd);
void consultar_paciente(const BDPaciente* bd);
void remover_paciente(BDPaciente* bd);
void atualizar_paciente(BDPaciente* bd);
void imprimir_lista_pacientes(const BDPaciente* bd);

#endif //BDPACIENTE_H