# HealthSys - Sistema de Gerenciamento de Dados de Pacientes (Parte II)

## Descrição

Este projeto é a segunda parte de um sistema de gerenciamento de dados de pacientes de uma clínica, desenvolvido em linguagem C para a disciplina de Estrutura de Dados. Diferente da primeira versão que utilizava um vetor estático, esta implementação é baseada em uma **lista encadeada dinâmica** (`TAD LinkedList`), permitindo um gerenciamento de memória mais eficiente e um número ilimitado de registros.

[cite_start]O sistema implementa todas as funcionalidades de um CRUD (Create, Read, Update, Delete), permitindo ao usuário inserir, consultar, atualizar, remover e listar os registros de pacientes.  Os dados são carregados de um arquivo `bd_paciente.csv` na inicialização e salvos de volta no mesmo arquivo ao encerrar o sistema, garantindo a persistência das informações.

## Como Compilar e Executar

### Pré-requisitos
* [cite_start]Ambiente Linux (recomendado Ubuntu 22.04) [cite: 78]
* [cite_start]Compilador GCC (versão 11 ou compatível) [cite: 78]
* Utilitário `make`

### Compilação
No diretório raiz do projeto, execute o comando:
```bash
make