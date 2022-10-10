#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#define N 30

typedef struct{
    int matricula;
    float notas[4];
    char nome[N];
    int turma;
    int faltas;
}
Aluno;

Aluno alunos[N];
int alunos_cadastrados = 0;

// Prototypes
void cadastroAluno(void);
void removeAluno(void);
void atualizaDados(void);
void listarCadastrados(void);
void listarAprovados(void);
void listarReprovadosMedia(void);
void listarReprovadosFaltas(void);
void carregaArquivo(void);
void salvaArquivo(void);
void ordenar(void);
void ordenarMatricula(void);
void ordenarNome(void);
float media(Aluno);
void ordenarMedia(void);
void ordenarFaltas(void);

void (*menuOpcoes[]) (void) = {
    cadastroAluno,
    removeAluno,
    atualizaDados,
    listarCadastrados,
    listarAprovados,
    listarReprovadosMedia,
    listarReprovadosFaltas,
    ordenar
};

int main(void)
{
    atexit(salvaArquivo);
    carregaArquivo();

    int opcao = 0;
    while (opcao != 9)
    {
        printf("\n\n ----------------------- ");
        printf("\n 1 - Cadastrar Aluno ");
        printf("\n 2 - Remover Aluno ");
        printf("\n 3 - Atualizar Dados ");
        printf("\n 4 - Listar Alunos Cadastrados ");
        printf("\n 5 - Listar Alunos Aprovados ");
        printf("\n 6 - Listar Alunos Reprovados por Media ");
        printf("\n 7 - Listar Alunos Reprovados por faltas ");
        printf("\n 8 - Ordenar Dados ");
        printf("\n 9 - Sair ");
        printf("\n\n Escolha uma opcao: ");
        scanf(" %d", &opcao);

        if (opcao > 0 && opcao < 9)
            menuOpcoes[opcao - 1]();
        else if (opcao == 9)
            break;
    }
}

void cadastroAluno(void) {
    int matricula;
    bool eh_possivel_cadastrar = true;

    printf("\nDigite a matricula do aluno %i: ", alunos_cadastrados + 1);
    scanf(" %d", &matricula);
    
    for (int i = 0; i <= alunos_cadastrados; i++)
    {
        if (matricula == alunos[i].matricula)
        {
            printf("Aluno já cadastrado.");
            eh_possivel_cadastrar = false;
            break;
        }
        else if (alunos_cadastrados > N)
        {
            printf("Número de alunos cadastrados excedido.");
            eh_possivel_cadastrar = false;
            break;
        }
    }
    if (eh_possivel_cadastrar)
    {
        alunos[alunos_cadastrados].matricula = matricula;
        printf("\nDigite o nome do aluno: ");
        scanf(" %s", alunos[alunos_cadastrados].nome);

        printf("\nDigite o codigo da turma: ");
        scanf(" %d", &alunos[alunos_cadastrados].turma);

        printf("\nDigite quantas faltas o aluno possui: ");
        scanf(" %d", &alunos[alunos_cadastrados].faltas);

        for (int i = 0; i < 4; i++) {
            printf("\nDigite a nota %d do aluno: ", i + 1);
            scanf(" %f", &alunos[alunos_cadastrados].notas[i]);
        }
        
        alunos_cadastrados++;
    }
    system("pause");
}

void removeAluno(void)
{
    if (alunos_cadastrados == 0) {
        printf("\n Não foi possível remover o aluno, o vetor está vazio!");
        return;
    }

    int matricula;
    printf("\nDigite a matricula do aluno que deseja remover: ");
    scanf(" %d", &matricula);

    for (int i = 0; i < alunos_cadastrados; i++)
    {
        if (matricula == alunos[i].matricula)
        {
            alunos[i].matricula = -1;
            alunos_cadastrados--;
            // organiza();
            return;
        }
    }
    
    printf("\n Não foi possível remover o aluno, aluno não encontrado!");
}

void atualizaDados(void)
{
    if (alunos_cadastrados == 0) {
        printf("\n Não foi possível atualizar o aluno, o vetor está vazio!");
        return;
    }
    
    int matricula;
    printf("\nDigite a matricula do aluno que deseja atualizar: ");
    scanf(" %d", &matricula);

    for (int i = 0; i < alunos_cadastrados; i++)
    {
        if (matricula == alunos[i].matricula)
        {
            printf("Digite a nova quantidade de faltas do aluno de matricula %d: ", matricula);
            scanf(" %d", &alunos[i].faltas);

            for (int j = 0; j < 4; j++)
            {
                printf("Digite a nota %d do aluno: ", j + 1);
                scanf(" %f", &alunos[i].notas[j]);
            }
            break;
        }
    }
    
    printf("\n Não foi possível atualizar o aluno, aluno não encontrado!");
}

void listarCadastrados(void) {
    int turma;
    printf("\nInforme a turma a ser listada: ");
    scanf(" %i", &turma);
    for(int i = 0; i < alunos_cadastrados; i++){
        if(alunos[i].turma == turma){
            printf("\n----------------------- \n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matricula: %d\n", alunos[i].matricula);
            printf("Faltas: %d\n", alunos[i].faltas);
            for(int j = 0; j < 4; j++){
                printf("Nota %d: %.2f\n", j+1, alunos[i].notas[j]);
            }
        }
    }
    printf("----------------------- \n");
}

void listarAprovados(void) {
    int turma;
    printf("\nInforme a turma a ser listada: ");
    scanf(" %i", &turma);
    float media = 0;

    for(int i = 0; i < alunos_cadastrados; i++){
        if(alunos[i].turma == turma){
            for(int j = 0; j < 4; j++){
                media += alunos[i].notas[j];
            }
            media = media/4;
            
            if(media >= 7 && alunos[i].faltas <= 36-21){
            printf("\n----------------------- \n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matricula: %d\n", alunos[i].matricula);
            printf("Faltas: %d\n", alunos[i].faltas);
            for(int j = 0; j < 4; j++){
                printf("Nota %d: %.2f\n", j, alunos[i].notas[j]);
            }
            printf("Media Total: %.2f\n", media);
            }
            media = 0;
    }
    printf("----------------------- \n");
    }
}

void listarReprovadosMedia(void) {
    int turma;
    printf("\nInforme a turma a ser listada: ");
    scanf(" %i", &turma);
    float media = 0;

    for(int i = 0; i < alunos_cadastrados; i++){
        if(alunos[i].turma == turma){

            for(int j = 0; j < 4; j++){
                media += alunos[i].notas[j];
            }
            media = media/4;

            if(media < 7){
            printf("\n----------------------- \n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matricula: %d\n", alunos[i].matricula);
                for(int j = 0; j < 4; j++){
                printf("Nota %d: %.2f\n", j, alunos[i].notas[j]);
                }
            printf("Media Total: %.2f\n", media);
            }
            media = 0;
        }
    printf("----------------------- \n");
    }
}

void listarReprovadosFaltas(void) {
    int turma;
    printf("\nInforme a turma a ser listada: ");
    scanf(" %i", &turma);

    for(int i = 0; i < alunos_cadastrados; i++){
        if(alunos[i].turma == turma){
            if(alunos[i].faltas > 36-21){
                printf("\n----------------------- \n");
                printf("Nome: %s\n", alunos[i].nome);
                printf("Matricula: %d\n", alunos[i].matricula);
                printf("Faltas: %d\n", alunos[i].faltas);
            }
        }
    printf("----------------------- \n");
    }
}

void carregaArquivo(void) {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL)
        return;
    
    for (int i = 0; ; i++) {
        if (fscanf(arquivo, "%d ", &alunos[i].matricula) == EOF)
            break;
        fscanf(arquivo, "%s ", alunos[i].nome);
        fscanf(arquivo, "%d ", &alunos[i].turma);
        for (int j = 0; j < 4; j++) {
            fscanf(arquivo, "%f ", &alunos[i].notas[j]);
        }
        fscanf(arquivo, "%d ", &alunos[i].faltas);
        alunos_cadastrados++;
    }
    
    fclose(arquivo);
}

void salvaArquivo(void) {
    FILE *arquivo = fopen("alunos.txt", "w");
    if (arquivo == NULL)
        return;
    
    for (int i = 0; i < alunos_cadastrados; i++) {
        fprintf(arquivo, "%d\t", alunos[i].matricula);
        fprintf(arquivo, "%s\t", alunos[i].nome);
        fprintf(arquivo, "%d\t", alunos[i].turma);
        for (int j = 0; j < 4; j++) {
            fprintf(arquivo, "%.1f\t", alunos[i].notas[j]);
        }
        fprintf(arquivo, "%d\r\n", alunos[i].faltas);
    }
    
    fclose(arquivo);
}

void ordenar() {
    int valor;
    printf("\n\n ----------------------- ");
    printf("\n 1 - Ordenar por Matricula ");
    printf("\n 2 - Ordenar por Nome ");
    printf("\n 3 - Ordenar por Media ");
    printf("\n 4 - Ordenar por Faltas ");
    printf("\n\n Escolha uma opcao: ");
    scanf(" %d", &valor);

    switch ( valor ) {
        case 1 :
            ordenarMatricula();
            break;

        case 2 :
            ordenarNome();
            break;

        case 3 :
            ordenarMedia();
            break;

        case 4 :
            ordenarFaltas();
            break;
    }
}

void ordenarMatricula(void) {
    Aluno aux;
    for (int i = 0; i < alunos_cadastrados; i++) {
        for (int j = i + 1; j < alunos_cadastrados; j++) {
            if(alunos[i].matricula > alunos[j].matricula) {
                aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = aux;
            }
        }        
    }
}

void ordenarNome(void) {
    Aluno aux;
    for (int i = 0; i < alunos_cadastrados; i++) {
        for (int j = i + 1; j < alunos_cadastrados; j++) {
            if(strcmp(alunos[i].nome, alunos[j].nome) > 0) {
                aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = aux;
            }
        }        
    }
}
 
float media(Aluno aluno) {
    float soma = 0;

    for(int i = 0; i < 4; i++){
        soma += aluno.notas[i];
    }
    return soma / 4;
}

void ordenarMedia(void) {
    Aluno aux;
    for (int i = 0; i < alunos_cadastrados; i++) {
        for (int j = i + 1; j < alunos_cadastrados; j++) {
            if(media(alunos[i]) > media(alunos[j])) {
                aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = aux;
            }
        }
    }
}

void ordenarFaltas(void){
    Aluno aux;
    for (int i = 0; i < alunos_cadastrados; i++) {
        for (int j = i + 1; j < alunos_cadastrados; j++) {
            if(alunos[i].faltas > alunos[j].faltas) {
                aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = aux;
            }
        }        
    }
}
