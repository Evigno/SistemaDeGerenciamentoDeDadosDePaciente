c
#ifndef BDPACIENTE_H
#define BDPACIENTE_H

#include "paciente.h"

// Define BDPaciente como um tipo opaco.
// A definição real da struct está em bdpaciente.c, escondendo os detalhes
// de implementação (como a lista encadeada) do resto do programa.
// Isso é uma prática central de Tipos Abstratos de Dados (TAD).
typedef struct BDPaciente BDPaciente;

/**
 * @brief Aloca e inicializa uma nova estrutura BDPaciente.
 * @return Ponteiro para a estrutura BDPaciente criada, ou NULL se a alocação falhar.
 */
BDPaciente* criar_bdpaciente();

/**
 * @brief Libera toda a memória associada à estrutura BDPaciente.
 * Percorre a lista encadeada, liberando cada nó, e por fim libera a própria estrutura.
 * Essencial para prevenir vazamentos de memória.
 * @param bd Ponteiro para a estrutura BDPaciente a ser liberada.
 */
void liberar_bdpaciente(BDPaciente* bd);

/**
 * @brief Carrega os dados dos pacientes de um arquivo CSV para a lista encadeada em memória.
 * @param bd Ponteiro para a estrutura BDPaciente que receberá os dados.
 * @param nome_arquivo String contendo o caminho do arquivo CSV.
 * @return 0 em caso de sucesso, ou -1 se o arquivo não puder ser aberto.
 */
int carregar_bd_do_csv(BDPaciente* bd, const char* nome_arquivo);

/**
 * @brief Salva o estado atual da lista de pacientes em memória para um arquivo CSV.
 * Sobrescreve o arquivo existente.
 * @param bd Ponteiro constante para a estrutura BDPaciente contendo os dados a serem salvos.
 * @param nome_arquivo String contendo o caminho do arquivo CSV.
 * @return 0 em caso de sucesso, ou -1 se ocorrer um erro ao criar/escrever no arquivo.
 */
int salvar_bd_para_csv(const BDPaciente* bd, const char* nome_arquivo);

/**
 * @brief Adiciona um novo paciente ao banco de dados.
 * Solicita os dados ao usuário, gera um novo ID e, após confirmação, insere na lista.
 * @param bd Ponteiro para a estrutura BDPaciente.
 */
void inserir_paciente(BDPaciente* bd);

/**
 * @brief Permite ao usuário buscar pacientes por prefixo de Nome ou CPF.
 * Exibe os resultados encontrados na tela.
 * @param bd Ponteiro constante para a estrutura BDPaciente.
 */
void consultar_paciente(const BDPaciente* bd);

/**
 * @brief Remove um paciente do banco de dados, identificado pelo ID.
 * Solicita o ID e uma confirmação antes de remover o registro permanentemente.
 * @param bd Ponteiro para a estrutura BDPaciente.
 */
void remover_paciente(BDPaciente* bd);

/**
 * @brief Modifica os dados de um paciente existente, identificado pelo ID.
 * Permite ao usuário alterar campos específicos ou mantê-los inalterados.
 * @param bd Ponteiro para a estrutura BDPaciente.
 */
void atualizar_paciente(BDPaciente* bd);

/**
 * @brief Imprime na tela a lista de todos os pacientes cadastrados.
 * Utiliza paginação para melhorar a legibilidade.
 * @param bd Ponteiro constante para a estrutura BDPaciente.
 */
void imprimir_lista_pacientes(const BDPaciente* bd);

#endif //BDPACIENTE_H
