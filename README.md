# HealthSys - Sistema de Gerenciamento de Dados de Pacientes (Parte II)
### Ou: "Uma Jornada Inesperada ao Mundo dos Ponteiros"

## Descrição

A execução deste trabalho consiste na implementação bem-sucedida, e com o mínimo de falhas de segmentação, do sistema completo de gerenciamento de dados de pacientes. Se na Parte I estávamos passeando no parque com um vetor estático, a Parte II nos convidou para escalar o Monte Everest da alocação dinâmica com uma *lista encadeada*.

Este sistema, agora em sua forma final e gloriosa, implementa o temido, porém necessário, *CRUD (Create, Read, Update, Delete)*. Os dados são bravamente carregados de um arquivo bd_paciente.csv e, após uma sessão de árduo trabalho do usuário, são salvos de volta, garantindo que todo o esforço não seja perdido no abismo do void.

*Disciplina:* Estrutura de Dados (A arte de organizar o caos)

*Professor:* Thiago M. Paixão (Nosso guia nesta aventura)

*Alunos (Os sobreviventes):* Maria Eduarda Vitorino Eler, Lucas Silverio Gums

## Como Compilar e Executar

### Passos para Compilação
1.  Clone ou baixe este repositório para o seu ambiente Linux.
2.  Navegue até o diretório raiz do projeto via terminal (onde a mágica acontece).
3.  Execute o feitiço de compilação:
    bash
    make
    
    Se os deuses da compilação estiverem de bom humor, um executável chamado healthsys aparecerá.

### Passos para Execução
1.  Certifique-se de que o arquivo de dados bd_paciente.csv está presente no mesmo diretório. Sem ele, o sistema fica um pouco... vazio.
2.  Execute o sistema com o seguinte comando:
    bash
    ./healthsys
    
3.  O sistema apresentará um menu com todas as funcionalidades conquistadas:
    * 1 - Consultar paciente (O modo detetive)
    * 2 - Atualizar paciente (A cirurgia plástica nos dados)
    * 3 - Remover paciente (O " Thanos Snap" para registros)
    * 4 - Inserir paciente (Dar vida a novos dados)
    * 5 - Imprimir lista de pacientes (O desfile dos nossos dados)
    * Q - Sair e Salvar (A única forma segura de escapar, garantindo que seu trabalho não foi um sonho)

## Estrutura do Repositório

* main.c: O grande maestro que rege a orquestra de funções, e o principal culpado quando o menu entra em loop.
* paciente.h: A certidão de nascimento do nosso struct Paciente. Simples, inocente e, felizmente, sem ponteiros complexos. Uma melhoria de modularização baseada no feedback da Parte I.
* bdpaciente.h: A fronteira entre a sanidade (main.c) e a loucura (bdpaciente.c). Define o que o mundo exterior pode fazer, escondendo o caos que acontece por dentro (também conhecido como "TAD opaco").
* bdpaciente.c: O coração (e a dor de cabeça) do projeto. Onde os ponteiros dançam, a memória é alocada (e, com sorte, liberada) e os segfaults nascem.
* Makefile: Nosso robô de compilação. Um feitiço arcano que transforma nosso sofrimento em um executável funcional, e que agora funciona sem erros, como prometido.
* bd_paciente.csv: O diário sagrado dos nossos pacientes, onde suas histórias são guardadas.

## Principais TADs e Decisões de Implementação (As Escolhas Difíceis)

### 1. Estrutura de Dados Principal: A Lista Encadeada
[_start]Abandonamos a segurança do vetor estático para abraçar a liberdade (e o perigo) da *lista simplesmente encadeada*. É uma corrente de nós (Node), onde cada um bravamente aponta para o próximo, esperando não apontar para NULL cedo demais. Essa escolha nos deu poderes ilimitados de crescimento, mas com grandes poderes vêm grandes responsabilidades de gerenciamento de memória.

### 2. Gerenciamento de Memória: A Arte do malloc e free
A arte de pedir memória emprestada ao sistema com malloc e, mais importante, devolvê-la com free para não enfurecer o sistema operacional. Cada malloc para um novo nó de paciente tem seu free correspondente na função de remoção ou na liberação final da lista. Ignorar isso é o caminho para o lado sombrio dos memory leaks, e nós escolhemos o caminho da luz.

### 3. Persistência de Dados: Para Provar que Não Foi em Vão
Para que o esforço de cadastrar "Cristiano Ronaldo" como paciente não seja perdido toda vez que o programa fecha, o sistema agora salva todas as alterações. Ao sair, o estado atual da lista em memória é heroicamente gravado de volta no arquivo bd_paciente.csv.

### 4. Fluxo de Atualização e Remoção: "Pense Duas Vezes"
Implementamos um fluxo de trabalho seguro. Primeiro, você usa a consulta para achar a vítima... digo, o paciente. Depois, informa o ID para o ato final. Para garantir que não haja "cliques errados", o sistema ainda pergunta "Tem certeza?" antes de uma remoção. Na atualização, adicionamos a conveniência de digitar - para não ter que redigitar todos os campos.

### 5. Modularização e o TAD Opaco
Seguindo o sábio conselho do nosso professor, separamos o Paciente em seu próprio módulo. O TAD BDPaciente esconde sua complexa alma de lista encadeada do main.c, que só conhece as funções da sua interface pública. É como conversar com um caixa de banco: você não precisa saber como o dinheiro é guardado lá dentro, só precisa saber como depositar e sacar.

## Cabou :DD
E, finalmente, depois de incontáveis testes, cafés e diálogos com um pato de borracha, o sistema está completo. Que ele compile de primeira para você!
