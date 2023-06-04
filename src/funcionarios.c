#include "../includes/TipoDados.h"

float getBonusFuncionario(FuncionarioStruct *funcionario){
    return (funcionario->atrasoMedio < 0) ? (Opcoes.eurosPorSegundoAdiantamentoFuncinario/100) * abs(funcionario->atrasoMedio/100) : 0;
}

int encontrarIdFuncionario(int id){
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i]->id == id){
            return i;
        }
    }
    return -1;
}

NivelFuncionarioStruct  getNivelFuncionario(FuncionarioStruct *funcionario){
    if (funcionario->n_vendas <= Opcoes.nivelFuncionario[0].n_vendas){
        return Opcoes.nivelFuncionario[0];
    }
    if (funcionario->n_vendas<= Opcoes.nivelFuncionario[1].n_vendas){
        return Opcoes.nivelFuncionario[1];
    }
    return Opcoes.nivelFuncionario[2];
}

void verFuncionarios(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("[yellow]Listar Todos Funcionarios:[/yellow]\n");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2fs Bonus: %.2f€", Funcionarios[i]->id, Funcionarios[i]->nome, (getNivelFuncionario(Funcionarios[i])).salario, Funcionarios[i]->n_vendas, Funcionarios[i]->atrasoMedio/1000.0, getBonusFuncionario(Funcionarios[i]));
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void verFuncionariosCaixa(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    if(Opcoes.lojaAberta == 0){
        printc("\n\n[yellow]A loja está fechada! Não é possível ver os Funcionarios em caixa.[/yellow]");
    }
    else{
        printc("[yellow]Listar Todos Funcionarios em caixa:[/yellow]\n");
        for (int i = 0; i < n_funcionariosAtivos; i++){
            printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f€", Funcionarios[i]->id, Funcionarios[i]->nome, (getNivelFuncionario(Funcionarios[i])).salario, Funcionarios[i]->n_vendas, Funcionarios[i]->atrasoMedio/1000.0, getBonusFuncionario(Funcionarios[i]));
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void verFuncionariosInativos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("[yellow]Listar Todos Funcionarios Inativos:[/yellow]\n");
    for (int i = n_funcionariosAtivos; i < n_funcionarios; i++){
        printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f€", Funcionarios[i]->id, Funcionarios[i]->nome, (getNivelFuncionario(Funcionarios[i])).salario, Funcionarios[i]->n_vendas, Funcionarios[i]->atrasoMedio/1000.0, getBonusFuncionario(Funcionarios[i]));
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarFuncionariosID(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    
    int id;
    scanfs("%d", &id, "Insira o ID do funcionario que pretende pesquisar: ", "Apenas pode inserir números inteiros!");

    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printc("[red]\nFuncionario não encontrado![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f€", Funcionarios[pos]->id, Funcionarios[pos]->nome, (getNivelFuncionario(Funcionarios[pos])).salario, Funcionarios[pos]->n_vendas, Funcionarios[pos]->atrasoMedio/1000.0, getBonusFuncionario(Funcionarios[pos]));
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}

void pesquisarFuncionariosNome(){
    char nome[100];
    scanfv("%[^\n]", &nome, "Insira o nome do funcionário que pretende pesquisar: ", "Input invalido, tente novamente: ", validateIsAlphabetic);

    printf("\n\nResultados semelhantes: \n");
    int flag = 0;
    for (int i = 0; i < n_funcionarios; i++){
        if (PesquisaParecido(nome, Funcionarios[i]->nome) <= 4){
            printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f€", Funcionarios[i]->id, Funcionarios[i]->nome, (getNivelFuncionario(Funcionarios[i])).salario, Funcionarios[i]->n_vendas, Funcionarios[i]->atrasoMedio/1000.0, getBonusFuncionario(Funcionarios[i]));
            flag = 1;
        }
    }
    if (flag == 0){
        printc("[red]Não foram encontrados resultados semelhantes![/red]\n");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    return;
}

void editarFuncionarios(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    int id;
    scanfs("%d", &id, "Insira o ID do funcionario que pretende editar: ", "Apenas pode inserir números inteiros!\n");
    
    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printc("[red]\nFuncionario não encontrado![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        printc("[yellow]Listar Dados do Funcionario a editar:[/yellow]\n");
        printf("\nID: %d \nNome: %s \nSalario: %.2f€ \nNumero Vendas: %d \nAtraso medio: %.2f \nBonus: %.2f€", Funcionarios[pos]->id, Funcionarios[pos]->nome, (getNivelFuncionario(Funcionarios[pos])).salario, Funcionarios[pos]->n_vendas, Funcionarios[pos]->atrasoMedio/10000.0, getBonusFuncionario(Funcionarios[pos]));

        char nome[100];
        /* bufferclear(); */
        scanfs("%[^\n]", &nome, "\nNome do funcionario: ", "Input invalido, tente novamente: ");
        free(Funcionarios[pos]->nome);
        Funcionarios[pos]->nome = malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(Funcionarios[pos]->nome, nome);

        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    exportarDados(guardarFuncionarioTxt, FUNCIONARIOS);
}

void adicionarFuncionario(){
    char nome[100];
    Funcionarios = (FuncionarioStruct **) realloc(Funcionarios, sizeof(FuncionarioStruct *) * (n_funcionarios + 1));
    Funcionarios[n_funcionarios] = (FuncionarioStruct *) malloc(sizeof(FuncionarioStruct));
    Funcionarios[n_funcionarios]->id = generateID(encontrarIdFuncionario);
    Funcionarios[n_funcionarios]->ativo = 0;
    printc("[blue]Introduza os dados do Funcionario:[/blue]\n");
    printc("\n\n[yellow]ID FUNCIONARIO: %d[/yellow]\n", Funcionarios[n_funcionarios]->id);

    scanfv("%[^\n]", &nome, "Nome: ", "Input invalido, tente novamente: ", validateIsAlphabetic);
    Funcionarios[n_funcionarios]->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(Funcionarios[n_funcionarios]->nome, nome);    

    n_funcionarios++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarDados(guardarFuncionarioTxt, FUNCIONARIOS);
}



void removerFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    verFuncionariosInativos();
    int id;
    scanfs("%d", &id, "Insira o ID do funcionario que pretende remover: ", "Apenas pode inserir números inteiros!");
    
    int pos = encontrarIdFuncionario(id);

    if (pos == -1){
        printc("[red]\nFuncionario não encontrado![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else if (Funcionarios[pos]->ativo == 1){
        printc("[red]Funcionario está ativo não pode remove-lo![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
        return;
    }
    else{
        free(Funcionarios[pos]->nome);
        free(Funcionarios[pos]);
        Funcionarios[pos] = Funcionarios[--n_funcionarios];
        Funcionarios = (FuncionarioStruct **) realloc(Funcionarios, sizeof(FuncionarioStruct *) * n_funcionarios);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    exportarDados(guardarFuncionarioTxt, FUNCIONARIOS);
}
    
void atualizarDadosFuncionario(FuncionarioStruct *funcionario, float atrasoMedio){
    funcionario->n_vendas++;
    if(Opcoes.VerTransacoes == 1){
        float salario = (getNivelFuncionario(funcionario)).salario;
        if((getNivelFuncionario(funcionario)).salario != salario){
            NivelFuncionarioStruct nivelFuncionario = getNivelFuncionario(funcionario);
            printc("\n\t[green]Promoção[/green] Funcionario com id %d promovido para o nível %d com novo salario de %.2f euros\n", funcionario->id, nivelFuncionario.nivel, nivelFuncionario.salario);
        }
    }
    funcionario->atrasoMedio = (int)((funcionario->atrasoMedio + atrasoMedio) / 2);
}

FuncionarioStruct *escolherFuncionarios(){
    if(n_funcionariosAtivos >= n_funcionarios){
        printf("\n\tErro! Nao existem mais funcionarios disponiveis.\n");
        return NULL;
    }
    FuncionarioStruct *funcionario;

    int index = Aleatorio(n_funcionariosAtivos, n_funcionarios - 1);
    funcionario = Funcionarios[index];
    funcionario->ativo = 1;
    
    /* pthread_mutex_lock(&ClientesLock); */
    Funcionarios[index] = Funcionarios[n_funcionariosAtivos];
    Funcionarios[n_funcionariosAtivos] = funcionario;
    n_funcionariosAtivos++;

    return funcionario;
    /* pthread_mutex_unlock(&ClientesLock); */
}

void desocuparFuncionario(FuncionarioStruct* funcionario){
    int pos = encontrarIdFuncionario(funcionario->id);
    (pos == -1 || pos >= n_funcionariosAtivos) ? printf("\n\tErro! Funcionario não encontrado.\n") : (void)NULL;
    
    funcionario = Funcionarios[pos];
    funcionario->ativo = 0;
    Funcionarios[pos] = Funcionarios[--n_funcionariosAtivos];
    Funcionarios[n_funcionariosAtivos] = funcionario;
}