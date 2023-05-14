#include "../includes/TipoDados.h"

int encontrarIdFuncionario(int id){
    for (int i = 0; i < n_funcionarios; i++){
        if (Funcionarios[i].id == id){
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
        printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario, Funcionarios[i].n_vendas, Funcionarios[i].atrasoMedio, Funcionarios[i].bonus);
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
            printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario, Funcionarios[i].n_vendas, Funcionarios[i].atrasoMedio, Funcionarios[i].bonus);
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
        printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario, Funcionarios[i].n_vendas, Funcionarios[i].atrasoMedio, Funcionarios[i].bonus);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarFuncionariosID(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    
    int id;
    int invalid = 0;
    do{
        printf("Insira o ID do funcionario que pretende pesquisar: ");
        invalid = scanf("%d", &id);
        invalid != 1 ? printc("[red]Apenas pode inserir números inteiros![/red]\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);
    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printc("[red]\nFuncionario não encontrado![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f", Funcionarios[pos].id, Funcionarios[pos].nome, (getNivelFuncionario(&Funcionarios[pos])).salario, Funcionarios[pos].n_vendas, Funcionarios[pos].atrasoMedio, Funcionarios[pos].bonus);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}

void pesquisarFuncionariosNome(){
    char nome[100];
    printf("Insira o nome do funcionário que pretende pesquisar: ");
    bufferclear();
    if(scanf("%[^\n]", nome) != 1) return;
    printf("\n\nResultados semelhantes: \n");
    int flag = 0;
    for (int i = 0; i < n_funcionarios; i++){
        if (PesquisaParecido(nome, Funcionarios[i].nome) <= 4){
            printf("\nID: %d Nome: %s Salario: %.2f€ Numero Vendas: %d Atraso medio: %.2f Bonus: %.2f", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario, Funcionarios[i].n_vendas, Funcionarios[i].atrasoMedio, Funcionarios[i].bonus);
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
    int id, invalid = 0;
    do{
        printf("Insira o ID do funcionario que pretende editar: ");
        invalid = scanf("%d", &id);
        invalid != 1 ? printc("[red]Apenas pode inserir números inteiros![/red]\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);

    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printc("[red]\nFuncionario não encontrado![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        printc("[yellow]Listar Dados do Funcionario a editar:[/yellow]\n");
        printf("\nID: %d \nNome: %s \nSalario: %.2f€ \nNumero Vendas: %d \nAtraso medio: %.2f \nBonus: %.2f", Funcionarios[pos].id, Funcionarios[pos].nome, (getNivelFuncionario(&Funcionarios[pos])).salario, Funcionarios[pos].n_vendas, Funcionarios[pos].atrasoMedio, Funcionarios[pos].bonus);

        char nome[100];
        printf("\n\nNome do funcionario: ");
        bufferclear();
        if(scanf("%[^\n]", nome) != 1) return;
        free(Funcionarios[pos].nome);
        Funcionarios[pos].nome = malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(Funcionarios[pos].nome, nome);

        invalid = 0;
        do{
            printf("\nNumero de vendas do funcionario: ");
            invalid = scanf("%d", &Funcionarios[pos].n_vendas);
            invalid != 1 ? printc("[red]Apenas pode inserir números inteiros![/red]\n"),  bufferclear() : (void)NULL;
        }while(invalid != 1);

        invalid = 0;
        do{
            printf("\nAtraso medio do funcionario: ");
            invalid = scanf("%f", &Funcionarios[pos].atrasoMedio);
            invalid != 1 ? printc("[red]Apenas pode inserir números inteiros![/red]\n"),  bufferclear() : (void)NULL;
        }while(invalid != 1);

        invalid = 0;
        do{
            printf("\nBonus do funcionario: ");
            invalid = scanf("%f", &Funcionarios[pos].bonus);
            invalid != 1 ? printc("[red]Apenas pode inserir números inteiros![/red]\n"),  bufferclear() : (void)NULL;
        }while(invalid != 1);

        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}

void adicionarFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    printf("Insira o nome do funcionario: ");
    bufferclear();
    if(scanf("%[^\n]", nome) != 1) return;
    Funcionarios[n_funcionarios].nome = malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(Funcionarios[n_funcionarios].nome, nome);

    Funcionarios[n_funcionarios].id = generateID(encontrarIdFuncionario);
    Funcionarios[n_funcionarios].ativo = 0;
    n_funcionarios++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void removerFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    verFuncionariosInativos();
    int id;
    int invalid = 0;
    do{
        printf("\nInsira o ID do funcionario que pretende remover: ");
        invalid = scanf("%d", &id);
        invalid != 1 ? printc("[red]Apenas pode inserir números inteiros![/red]\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);
    
    int pos = encontrarIdFuncionario(id);

    if (pos == -1){
        printc("[red]\nFuncionario não encontrado![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else if (Funcionarios[pos].ativo == 1){
        printc("[red]Funcionario está ativo não pode remove-lo![/red]\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
        return;
    }
    else{
        free(Funcionarios[pos].nome);
        for (int i = pos; i < n_funcionarios; i++){
            Funcionarios[i] = Funcionarios[i + 1];
        }

        n_funcionarios--;
        Funcionarios = realloc(Funcionarios, sizeof(Funcionarios) * n_funcionarios);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}
    
void atualizarDadosFuncionario(FuncionarioStruct *funcionario, float atrasoMedio, int n_vendas){
    funcionario->n_vendas++;
    float salario = (getNivelFuncionario(funcionario)).salario;
    if(Opcoes.VerTransacoes == 1){
        if((getNivelFuncionario(funcionario)).salario != salario){
            float novoSalario = (getNivelFuncionario(funcionario)).salario;
            for (int  i = 1; i < 3; i++){
                if((Opcoes.nivelFuncionario[i]).salario == novoSalario)
                    printc("\n\t[green]Promoção[/green] Funcionario com id %d promovido para o nível %d com novo salario de %.2f euros\n", funcionario->id, Opcoes.nivelFuncionario->nivel, Opcoes.nivelFuncionario->salario);
            }
        }
    }
    funcionario->atrasoMedio = (funcionario->atrasoMedio + atrasoMedio) / 2;
    if(funcionario->atrasoMedio < 0)
        funcionario->bonus += Opcoes.eurosPorSegundoAdiantamentoFuncinario * funcionario->atrasoMedio;
}