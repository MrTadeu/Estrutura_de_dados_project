#include "../includes/TipoDados.h"

int encontrarIdFuncionario(int id){
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].id == id){
            return i;
        }
    }
    return -1;
}

float convertNumeroDeVendasSalario_vetor(int pos){
    if(!funcionario){
        printc("\n\t[red]Error![/red] Given funcionario is NULL\n");
        return -1;
    }
    if (Funcionarios[pos].n_vendas <= Opcoes.nivelFuncionario[0][0]) return Opcoes.nivelFuncionario[0][1];
    else if (Funcionarios[pos].n_vendas<= Opcoes.nivelFuncionario[1][0] ) return Opcoes.nivelFuncionario[1][1];
    else return Opcoes.nivelFuncionario[2][1];
}

float convertVendasToSalario_lista(FuncionarioStruct *funcionario){
    if(!funcionario){
        printc("\n\t[red]Error![/red] Given funcionario is NULL\n");
        return -1;
    }
    if (funcionario->n_vendas <= Opcoes.nivelFuncionario[0][0]) return Opcoes.nivelFuncionario[0][1];
    else if (funcionario->n_vendas<= Opcoes.nivelFuncionario[1][0] ) return Opcoes.nivelFuncionario[1][1];
    else return Opcoes.nivelFuncionario[2][1];
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
            printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[i].id, Funcionarios[i].nome, convertNumeroDeVendasSalario(i));
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
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[pos].id, Funcionarios[pos].nome, convertNumeroDeVendasSalario(pos));
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
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[pos].id, Funcionarios[pos].nome, convertNumeroDeVendasSalario(pos));
        printf("Insira o novo nome do funcionario: ");
        scanf("%s", Funcionarios[pos].nome);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}

void adicionarFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printf("Insira o nome do funcionario: ");
    scanf("%s", Funcionarios[n_funcionarios].nome);
    Funcionarios[n_funcionarios].id = generateID(encontrarIdFuncionario, -1);
    Funcionarios[n_funcionarios].ativo = 0;
    n_funcionarios++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

/* void removerFuncionario(){

} */