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
        printf("\nID: %d Nome: %s Salario: %.2f€  Nivel de Experiencia: %d\n", Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].salario, Funcionarios[i].experiencia);
    }
    getchar();
    getchar();
}

void pesquisarFuncionarios(){

}