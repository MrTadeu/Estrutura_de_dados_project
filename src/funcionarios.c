#include "../includes/TipoDados.h"

int encontrarIdFuncionario(int id){
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].id == id){
            return i;
        }
    }
    return -1;
}

void verFuncionariosCaixa(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].ativo == 1){
            printf("\nID: %d Nome: %s Salario: %.2f€  Nivel de Experiencia: %d\n", Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].salario, Funcionarios[i].experiencia);
        }
    }
    getchar();
    getchar();
}

void verFuncionariosInativos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].salario);
    }
    getchar();
    getchar();
}

void pesquisarFuncionarios(){
    int id;
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printf("Insira o ID do funcionario que pretende pesquisar: ");
    scanf("%d", &id);
    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printf("Funcionario não encontrado!");
        getchar();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[pos].id, Funcionarios[pos].nome, Funcionarios[pos].salario);
        getchar();
        getchar();
    }
}