#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bdpaciente.h"

void exibir_menu() {
    printf("\n--- HealthSys ---\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair e Salvar\n");
    printf("> ");
}

int main() {
    BDPaciente* bd = criar_bdpaciente();
    if (bd == NULL) {
        fprintf(stderr, "Erro critico: Falha ao alocar memoria.\n");
        return EXIT_FAILURE;
    }

    carregar_bd_do_csv(bd, "bd_paciente.csv");

    char opcao_str[10];
    char opcao_char;

    while (1) {
        exibir_menu();
        if (fgets(opcao_str, sizeof(opcao_str), stdin) == NULL) break;
        
        if (strlen(opcao_str) > 0) {
            opcao_str[strcspn(opcao_str, "\n")] = 0;
        }

        if (strlen(opcao_str) == 1) {
             opcao_char = toupper(opcao_str[0]);
        } else {
             opcao_char = ' ';
        }

        switch (opcao_char) {
            case '1': consultar_paciente(bd); break;
            case '2': atualizar_paciente(bd); break;
            case '3': remover_paciente(bd); break;
            case '4': inserir_paciente(bd); break;
            case '5': imprimir_lista_pacientes(bd); break;
            case 'Q':
                printf("Salvando dados no arquivo bd_paciente.csv...\n");
                salvar_bd_para_csv(bd, "bd_paciente.csv");
                printf("Saindo do sistema.\n");
                liberar_bdpaciente(bd);
                return EXIT_SUCCESS;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    liberar_bdpaciente(bd);
    return EXIT_SUCCESS;
}