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
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void verFuncionariosInativos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].ativo == 0){
            printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].salario);
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
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
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}

void editarFuncionarios(){
    int id;
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printf("Insira o ID do funcionario que pretende editar: ");
    scanf("%d", &id);
    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printf("Funcionario não encontrado!");
        getchar();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[pos].id, Funcionarios[pos].nome, Funcionarios[pos].salario);
        printf("Insira o novo nome do funcionario: ");
        scanf("%s", Funcionarios[pos].nome);
        printf("Insira o novo salario do funcionario: ");
        scanf("%f", &Funcionarios[pos].salario);
        printf("Insira o novo nivel de experiencia do funcionario: ");
        scanf("%d", &Funcionarios[pos].experiencia);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}

void adicionarFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printf("Insira o nome do funcionario: ");
    scanf("%s", Funcionarios[n_funcionarios].nome);
    printf("Insira o salario do funcionario: ");
    scanf("%f", &Funcionarios[n_funcionarios].salario);
    printf("Insira o nivel de experiencia do funcionario: ");
    scanf("%d", &Funcionarios[n_funcionarios].experiencia);
    Funcionarios[n_funcionarios].id = generateID(encontrarIdFuncionario, -1);
    Funcionarios[n_funcionarios].ativo = 0;
    n_funcionarios++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}
