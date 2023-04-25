#include "../includes/TipoDados.h"

int encontrarIdFuncionario(int id){
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].id == id){
            return i;
        }
    }
    return -1;
}

// são 3 niveis de experiencia
void pagarFuncionarios(int id){
    if (encontrarIdFuncionario(id) == -1) return;
    
    if (Funcionarios[encontrarIdFuncionario(id)].experiencia < Global.NivelExperiencia[0]){
        Funcionarios[id].salario = Global.salarioBase[0] + Funcionarios[encontrarIdFuncionario(id)].bonus - Funcionarios[encontrarIdFuncionario(id)].atrasoMedio;
    }
    else if (Funcionarios[encontrarIdFuncionario(id)].experiencia >= Global.NivelExperiencia[0] && Funcionarios[encontrarIdFuncionario(id)].experiencia < Global.NivelExperiencia[1]){
        Funcionarios[id].salario = Global.salarioBase[1] + Funcionarios[encontrarIdFuncionario(id)].bonus - Funcionarios[encontrarIdFuncionario(id)].atrasoMedio;
    }
    else{
        Funcionarios[id].salario = Global.salarioBase[2] + Funcionarios[encontrarIdFuncionario(id)].bonus - Funcionarios[encontrarIdFuncionario(id)].atrasoMedio;
    }
}

void atualizarPagamento(){
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].ativo == 0){
            Funcionarios[i].bonus = 0;
            Funcionarios[i].atrasoMedio = 0;
            Funcionarios[i].salario = 0;
        }
        else{
            pagarFuncionarios(Funcionarios[i].id);
        }
    }
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
        if (Funcionarios[i].ativo == 0){
            printf("\nID: %d Nome: %s Salario: %.2f€  Nivel de Experiencia: %d\n", Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].salario, Funcionarios[i].experiencia);
        }
    }
    getchar();
    getchar();
}