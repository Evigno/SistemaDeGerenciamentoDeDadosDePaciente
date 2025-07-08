#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bdpaciente.h"

#define RECORDS_PER_PAGE 10

typedef struct Node {
    Paciente data;
    struct Node* next;
} Node;

struct BDPaciente {
    Node* head;
};

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Aloca a estrutura principal do banco de dados
BDPaciente* criar_bdpaciente() {
    BDPaciente* bd = (BDPaciente*)malloc(sizeof(BDPaciente));
    if (bd != NULL)
        bd->head = NULL;
    return bd;
}

// Libera toda a memória alocada para a lista
void liberar_bdpaciente(BDPaciente* bd) {
    if (bd == NULL) return;
    Node* current = bd->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(bd);
}

static void inserir_node_no_final(BDPaciente* bd, Paciente p) {
    // Alocação de memória
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->data = p;
    newNode->next = NULL;

    // Caso a lista esteja vazia
    if (bd->head == NULL) 
        bd->head = newNode;
    else {
    // Caso não, insere ao final
        Node* current = bd->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Carrega os dados do arquivo .csv para a memória (lista encadeada)
int carregar_bd_do_csv(BDPaciente* bd, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Aviso: Nao foi possivel abrir o arquivo '%s'. Iniciando com banco de dados vazio.\n", nome_arquivo);
        return -1;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula a linha do cabeçalho

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Paciente p;
        sscanf(linha, "%d,%[^,],%[^,],%d,%s", &p.id, p.cpf, p.nome, &p.idade, p.data_cadastro);
        inserir_node_no_final(bd, p);
    }

    fclose(arquivo);
    return 0;
}

// Salva os dados da memória (lista encadeada) de volta para o arquivo .csv
int salvar_bd_para_csv(const BDPaciente* bd, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao salvar o arquivo CSV");
        return -1;
    }

    fprintf(arquivo, "ID,CPF,Nome,Idade,Data_Cadastro\n"); // Escreve o cabeçalho
    
    // Percorre a lista e escreve cada paciente no arquivo
    Node* current = bd->head;
    while (current != NULL) {
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
                current->data.id, current->data.cpf, current->data.nome,
                current->data.idade, current->data.data_cadastro);
        current = current->next;
    }

    fclose(arquivo);
    return 0;
}

// Função p add a formatação (pontos e hífen) ao CPF
static void formatar_cpf(const char* cpf_sem_formatacao, char* cpf_formatado) {
    if (strlen(cpf_sem_formatacao) == 11) {
        sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%.2s",
                cpf_sem_formatacao, cpf_sem_formatacao + 3,
                cpf_sem_formatacao + 6, cpf_sem_formatacao + 9);
    } else
        strcpy(cpf_formatado, cpf_sem_formatacao);
}

// Função p a funcionalidade de Inserir Paciente
void inserir_paciente(BDPaciente* bd) {
    Paciente p;
    char cpf_temp[20], nome_temp[MAX_NOME], data_temp[MAX_DATA];
    int idade_temp;
    
    // Coleta dos dados do usuário
    printf("\n[Sistema] Inserir novo paciente:\n");
    printf("Digite o CPF (apenas digitos): ");
    fgets(cpf_temp, sizeof(cpf_temp), stdin);
    cpf_temp[strcspn(cpf_temp, "\n")] = 0;

    printf("Digite o Nome: ");
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strcspn(nome_temp, "\n")] = 0;

    printf("Digite a Idade: ");
    scanf("%d", &idade_temp);
    limpar_buffer_entrada();

    printf("Digite a Data de Cadastro (AAAA-MM-DD): ");
    fgets(data_temp, sizeof(data_temp), stdin);
    data_temp[strcspn(data_temp, "\n")] = 0;

    // Teste simples dos dados de entrada
    if (strlen(cpf_temp) != 11 || strlen(nome_temp) == 0 || strlen(data_temp) == 0) {
        printf("Erro: Dados invalidos. CPF deve ter 11 digitos e outros campos nao podem ser vazios.\n");
        return;
    }

    // Lógica para gerar um novo ID único
    int max_id = 0;
    Node* current = bd->head;
    while (current != NULL) {
        if (current->data.id > max_id) max_id = current->data.id;
        current = current->next;
    }
    p.id = max_id + 1;
    
    // Preenche a struct Paciente
    p.idade = idade_temp;
    formatar_cpf(cpf_temp, p.cpf);
    strcpy(p.nome, nome_temp);
    strcpy(p.data_cadastro, data_temp);

    // confirmação com o usuário
    printf("\n[Sistema] Confirma a insercao do registro abaixo? (S/N)\n");
    printf("ID: %d\nCPF: %s\nNome: %s\nIdade: %d\nData: %s\n> ", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
    
    char confirm;
    scanf(" %c", &confirm);
    limpar_buffer_entrada();

    if (toupper(confirm) == 'S') {
        inserir_node_no_final(bd, p);
        printf("Registro inserido com sucesso.\n");
    } else {
        printf("Insercao cancelada.\n");
    }
}

// Função para a funcionalidade de Consultar Paciente
void consultar_paciente(const BDPaciente* bd) {
    int opcao;
    char termo[MAX_NOME];

    printf("\n[Sistema] Escolha o modo de consulta:\n");
    printf("1 - Por nome\n2 - Por CPF\n3 - Retornar\n> ");
    scanf("%d", &opcao);
    limpar_buffer_entrada();

    if (opcao == 3) return;
    if (opcao < 1 || opcao > 2) {
        printf("Opcao invalida.\n");
        return;
    }

    printf("Digite o termo de busca (prefixo): ");
    fgets(termo, sizeof(termo), stdin);
    termo[strcspn(termo, "\n")] = 0;

    printf("\nResultados da busca:\n");
    printf("%-5s %-15s %-30s %-5s %-15s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
    printf("----------------------------------------------------------------------\n");

    int encontrados = 0;
    Node* current = bd->head;

    while (current != NULL) {
        int corresponde = 0;

        if (opcao == 1 && strncmp(current->data.nome, termo, strlen(termo)) == 0) {
            corresponde = 1;
        } else if (opcao == 2 && strncmp(current->data.cpf, termo, strlen(termo)) == 0) {
            corresponde = 1;
        }
        
        if (corresponde) {
            printf("%-5d %-15s %-30s %-5d %-15s\n", current->data.id, current->data.cpf, current->data.nome, current->data.idade, current->data.data_cadastro);
            encontrados++;
        }
        current = current->next;
    }

    if (encontrados == 0) printf("Nenhum registro encontrado.\n");
}

void remover_paciente(BDPaciente* bd) {
    int id_remover;
    printf("\nDigite o ID do registro a ser removido (consulte antes se necessario): ");
    scanf("%d", &id_remover);
    limpar_buffer_entrada();

    Node *current = bd->head, *prev = NULL;
    while (current != NULL && current->data.id != id_remover) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Erro: ID %d nao encontrado.\n", id_remover);
        return;
    }
    
    printf("\nTem certeza que deseja excluir o registro abaixo? (S/N)\n");
    printf("ID: %d, Nome: %s\n> ", current->data.id, current->data.nome);
    
    char confirm;
    scanf(" %c", &confirm);
    limpar_buffer_entrada();

    if (toupper(confirm) == 'S') {
        // O nó a ser removido é o 1º
        if (prev == NULL) {
            bd->head = current->next;
        } else {
        // O nó tá no meio ou no fim da lista
            prev->next = current->next;
        }
        free(current); // Libera a memória do nó removido
        printf("Registro removido com sucesso.\n");
    } else
        printf("Remocao cancelada.\n");
}

void atualizar_paciente(BDPaciente* bd) {
    int id_atualizar;
    printf("\nDigite o ID do registro a ser atualizado (consulte antes se necessario): ");
    scanf("%d", &id_atualizar);
    limpar_buffer_entrada();

    // Encontra o nó a ser atualizado
    Node *current = bd->head;
    while (current != NULL && current->data.id != id_atualizar) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Erro: ID %d nao encontrado.\n", id_atualizar);
        return;
    }

    char cpf_temp[20], nome_temp[MAX_NOME], data_temp[MAX_DATA], idade_str[10];

    printf("Digite os novos valores (ou '-' para manter o atual):\n");
    printf("CPF (apenas digitos): ");
    fgets(cpf_temp, sizeof(cpf_temp), stdin);
    cpf_temp[strcspn(cpf_temp, "\n")] = 0;

    printf("Nome: ");
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strcspn(nome_temp, "\n")] = 0;

    printf("Idade: ");
    fgets(idade_str, sizeof(idade_str), stdin);
    idade_str[strcspn(idade_str, "\n")] = 0;

    printf("Data Cadastro (AAAA-MM-DD): ");
    fgets(data_temp, sizeof(data_temp), stdin);
    data_temp[strcspn(data_temp, "\n")] = 0;
    

    char confirm;
    printf("\nConfirma as alteracoes? (S/N)\n> ");
    scanf(" %c", &confirm);
    limpar_buffer_entrada();

    if (toupper(confirm) == 'S') {
        // Chave: Usa 'strcmp' para verificar se o usuário digitou '-', decidindo se atualiza ou mantém o campo
        if (strcmp(cpf_temp, "-") != 0 && strlen(cpf_temp) == 11) formatar_cpf(cpf_temp, current->data.cpf);
        if (strcmp(nome_temp, "-") != 0) strcpy(current->data.nome, nome_temp);
        if (strcmp(idade_str, "-") != 0) current->data.idade = atoi(idade_str);
        if (strcmp(data_temp, "-") != 0) strcpy(current->data.data_cadastro, data_temp);
        printf("Registro atualizado com sucesso.\n");
    } else
        printf("Atualizacao cancelada.\n");
}

void imprimir_lista_pacientes(const BDPaciente* bd) {
    if (bd->head == NULL) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    printf("\n[Sistema] Imprimindo lista de pacientes...\n");
    printf("%-5s %-15s %-30s %-5s %-15s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
    printf("----------------------------------------------------------------------\n");
    
    Node* current = bd->head;
    int count = 0;
    while (current != NULL) {
        printf("%-5d %-15s %-30s %-5d %-15s\n",
               current->data.id, current->data.cpf, current->data.nome,
               current->data.idade, current->data.data_cadastro);
        count++;
        
        // Paginação p pausar a exibição
        if (count % RECORDS_PER_PAGE == 0 && current->next != NULL) {
            printf("\nPressione Enter para continuar ou Q e Enter para sair...");
            char ch = getchar();
            if (toupper(ch) == 'Q') {
                if(ch != '\n') limpar_buffer_entrada();
                break;
            }
            // Não há repetição do cabeçalho aqui -> correção do erro do 1º trabalho
        }
        current = current->next;
    }
    printf("----------------------------------------------------------------------\n");
}
