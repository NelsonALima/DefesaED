#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 3  // Define o n�mero m�ximo de alunos que podem ser cadastrados
#define MAX_NOTAS 2   // Define o n�mero m�ximo de notas por aluno

// Define a estrutura Aluno, com nome, notas e m�dia
struct Aluno {
    char nome[50];       // Nome do aluno (m�ximo 50 caracteres)
    float notas[MAX_NOTAS]; // Array que armazena as notas do aluno
    float media;         // M�dia das notas do aluno
};

// Declara��o de um array de alunos e uma vari�vel para contar o total de alunos cadastrados
Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

// Fun��o que salva os dados dos alunos em um arquivo CSV
void salvarArquivo() {
    FILE *arquivo = fopen("alunos.csv", "w"); // Abre o arquivo alunos.csv para escrita (r - Ler) (w - escrever)
    if (arquivo == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Escreve o cabe�alho no arquivo
    fprintf(arquivo, "Nome;Nota1;Nota2;Media\n");
    // Escreve os dados de cada aluno no arquivo
    for (int i = 0; i < totalAlunos; i++) {
        fprintf(arquivo, "%s;%.2f;%.2f;%.2f\n", 
                alunos[i].nome, 
                alunos[i].notas[0], 
                alunos[i].notas[1], 
                alunos[i].media);
    }

    fclose(arquivo); // Fecha o arquivo ap�s escrever
    printf("Dados salvos em alunos.csv\n");
}

// Fun��o para cadastrar um novo aluno
void cadastrarAluno() {
    if (totalAlunos >= MAX_ALUNOS) {  // Verifica se o n�mero m�ximo de alunos foi atingido
        printf("Limite de alunos atingido!\n");
        return;
    }

    Aluno novoAluno; // Declara uma vari�vel do tipo Aluno para armazenar os dados do novo aluno
    printf("Digite o nome do aluno: ");
    getchar();  // Limpa o buffer de entrada
    fgets(novoAluno.nome, sizeof(novoAluno.nome), stdin);  // L� o nome do aluno

    novoAluno.nome[strcspn(novoAluno.nome, "\n")] = '\0';  // Remove o caractere de nova linha no final do nome

    printf("Digite as notas (2 notas):\n");
    // La�o para ler as duas notas do aluno
    for (int i = 0; i < MAX_NOTAS; i++) {
        while (1) { // Loop cont�nuo at� que uma entrada v�lida seja fornecida
            printf("Nota %d (entre 0 e 10): ", i + 1);
            if (scanf("%f", &novoAluno.notas[i]) != 1) {  // L� a nota do aluno
                printf("Entrada invalida. Por favor, insira um n�mero.\n");
                while (getchar() != '\n'); // Limpa o buffer de entrada
                continue;
            }

            // Verifica se a nota est� entre 0 e 10
            if (novoAluno.notas[i] >= 0 && novoAluno.notas[i] <= 10) {
                break;  // Sai do loop se a entrada for v�lida
            } else {
                printf("Nota invalida. A nota deve estar entre 0 e 10.\n");
            }
        }
    }

    // Calcula a m�dia das notas
    novoAluno.media = 0;
    for (int i = 0; i < MAX_NOTAS; i++) {
        novoAluno.media += novoAluno.notas[i];
    }
    novoAluno.media /= MAX_NOTAS;

    alunos[totalAlunos] = novoAluno; // Adiciona o aluno ao vetor de alunos
    totalAlunos++; // Incrementa o contador de alunos cadastrados

    printf("Aluno cadastrado com sucesso!\n");
    salvarArquivo(); // Salva os dados dos alunos no arquivo CSV
}

// Fun��o para listar todos os alunos cadastrados
void listarAlunos() {
    if (totalAlunos == 0) {  // Verifica se h� alunos cadastrados
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("-------------------------------------------------\n");
    printf("%-20s %-10s %-10s %-10s\n", "Nome", "Nota1", "Nota2", "Media");
    printf("-------------------------------------------------\n");

    // Exibe os dados de todos os alunos
    for (int i = 0; i < totalAlunos; i++) {
        printf("%-20s %-10.2f %-10.2f %-10.2f\n", 
                alunos[i].nome, 
                alunos[i].notas[0], 
                alunos[i].notas[1], 
                alunos[i].media);
    }
}

// Fun��o para pesquisar um aluno pelo nome
void pesquisarAluno() {
    if (totalAlunos == 0) {  // Verifica se h� alunos cadastrados
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do aluno para pesquisar: ");
    getchar(); // Limpa o buffer de entrada
    fgets(nomeBusca, sizeof(nomeBusca), stdin);  // L� o nome para pesquisa

    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';  // Remove o caractere de nova linha

    // Pesquisa pelo aluno no array de alunos
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(alunos[i].nome, nomeBusca) == 0) {  // Compara o nome do aluno
            printf("\nAluno encontrado:\n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Notas: %.2f, %.2f\n", alunos[i].notas[0], alunos[i].notas[1]);
            printf("Media: %.2f\n", alunos[i].media);
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

// Fun��o para remover um aluno pelo nome
void removerAluno() {
    if (totalAlunos == 0) {  // Verifica se h� alunos cadastrados
        printf("Nenhum aluno cadastrado para remover.\n");
        return;
    }

    char nome[50];
    printf("Digite o nome do aluno a ser removido: ");
    getchar();  // Limpa o buffer de entrada
    fgets(nome, sizeof(nome), stdin);  // L� o nome do aluno a ser removido
    nome[strcspn(nome, "\n")] = '\0';  // Remove o caractere de nova linha

    int encontrado = -1;
    // Pesquisa o aluno no array
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(alunos[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    // Se o aluno for encontrado, ele � removido
    if (encontrado == -1) {
        printf("Aluno '%s' n�o encontrado.\n", nome);
    } else {
        // Desloca todos os alunos ap�s o aluno removido uma posi��o para tr�s
        for (int i = encontrado; i < totalAlunos - 1; i++) {
            alunos[i] = alunos[i + 1];
        }
        totalAlunos--;  // Decrementa o contador de alunos
        printf("Aluno '%s' removido com sucesso.\n", nome);
    }
}

// Fun��o que carrega os dados dos alunos a partir de um arquivo CSV
void carregarArquivo() {
    FILE *arquivo = fopen("alunos.csv", "r");  // Abre o arquivo para leitura
    if (arquivo == NULL) {  // Se n�o encontrar o arquivo, exibe uma mensagem
        printf("\nNenhum arquivo encontrado.\n");
        return;
    }

    char linha[100];
    fgets(linha, sizeof(linha), arquivo);  // L� a primeira linha (cabe�alho)

    totalAlunos = 0;
    // L� as linhas restantes do arquivo e preenche o array de alunos
    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno aluno;
        
        sscanf(linha, "%49[^;];%f;%f;%f", 
               aluno.nome, 
               &aluno.notas[0], 
               &aluno.notas[1], 
               &aluno.media);  // Extrai os dados da linha
        alunos[totalAlunos++] = aluno;  // Adiciona o aluno ao array
    }

    fclose(arquivo);  // Fecha o arquivo ap�s a leitura
    printf("\nDados carregados com sucesso! %d aluno(s) encontrado(s).\n", totalAlunos);
}

// Fun��o do menu principal que permite ao usu�rio escolher a��es
void menu() {
    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Listar alunos\n");
        printf("3. Pesquisar aluno\n");        
        printf("4. Remover aluno\n"); 
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);  // L� a op��o do menu
        
        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: listarAlunos(); break;
            case 3: pesquisarAluno(); break;
            case 4: removerAluno(); break;
            case 5: printf("Saindo...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n"); break;
        }
    } while (opcao != 5);  // Continua o loop at� que o usu�rio escolha sair
}

int main() {
    carregarArquivo();  // Carrega os dados do arquivo no in�cio
    menu();  // Chama o menu principal para intera��o com o usu�rio
    return 0;  // Finaliza o programa
}

