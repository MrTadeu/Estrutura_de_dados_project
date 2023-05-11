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
    printf("\nasasdwaeq2234awfzcdsf\n");
    printf("\nasasdwaeq2234awfzcdsf :    || %d <= \n", Opcoes.nivelFuncionario[0].n_vendas);
    if (funcionario->n_vendas <= Opcoes.nivelFuncionario[0].n_vendas){
        printf("\n11111111111asasdwaeq2234awfzcdsf\n");
        return Opcoes.nivelFuncionario[0];
    }
    printf("\nXXXXXXXXXXXXXXXXXXXasasdwaeq2234awfzcdsf\n");
    if (funcionario->n_vendas<= Opcoes.nivelFuncionario[1].n_vendas){
        printf("\n2222222222221asasdwaeq2234awfzcdsf\n");
        return Opcoes.nivelFuncionario[1];
    }
    printf("\nXXXXXXXXXXXXXXXXXXXasasdwaeq2234awfzcdsf\n");
    printf("\n33333333333333333asasdwaeq2234awfzcdsf\n");
    return Opcoes.nivelFuncionario[2];
    printf("\nXXXXXXXXXXXXXXXXXXXasasdwaeq2234awfzcdsf\n");
}

void verFuncionariosCaixa(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    for (int i = 0; i < n_funcionariosAtivos; i++){
        printf("\nID: %d Nome: %s Salario: %.2f €\n", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void verFuncionariosInativos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    for (int i = n_funcionariosAtivos; i < n_funcionarios; i++){
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void pesquisarFuncionariosID(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    
    int id;
    printf("Insira o ID do funcionario que pretende pesquisar: ");
    scanf("%d", &id);
    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printf("Funcionario não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[pos].id, Funcionarios[pos].nome, (getNivelFuncionario(&Funcionarios[pos])).salario);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}

void pesquisarFuncionariosNome(){
    char nome[100];
    printf("Insira o nome do funcionário que pretende pesquisar: ");
    getchar();
    scanf("%[^\n]", nome);
    printf("%s\n", nome);
    printf("Resultados semelhantes: \n");
    int flag = 0;
    for (int i = 0; i < n_funcionarios; i++){
        if (PesquisaParecido(nome, Funcionarios[i].nome) <= 4){
            printf("\nID: %d Nome: %s Salário: %.2f€\n", Funcionarios[i].id, Funcionarios[i].nome, (getNivelFuncionario(&Funcionarios[i])).salario);
            flag = 1;
        }
    }
    if (flag == 0){
        printc("[red]Não foram encontrados resultados semelhantes![/red]\n");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
    return;
}


void editarFuncionarios(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    
    verFuncionariosInativos();
    verFuncionariosCaixa();
    int id;
    printf("Insira o ID do funcionario que pretende editar: ");
    scanf("%d", &id);
    int pos = encontrarIdFuncionario(id);
    if (pos == -1){
        printf("Funcionario não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Salario: %.2f€\n", Funcionarios[pos].id, Funcionarios[pos].nome, (getNivelFuncionario(&Funcionarios[pos])).salario);

        char nome[100];
        printf("Insira o novo nome do funcionario: ");
        getchar();
        scanf("%[^\n]", nome);
        Funcionarios[pos].nome = malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(Funcionarios[pos].nome, nome);

        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}

void adicionarFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    printf("Insira o nome do funcionario: ");
    getchar();
    scanf("%[^\n]", nome);
    Funcionarios[n_funcionarios].nome = malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(Funcionarios[n_funcionarios].nome, nome);

    Funcionarios[n_funcionarios].id = generateID(encontrarIdFuncionario, -1);
    Funcionarios[n_funcionarios].ativo = 0;
    n_funcionarios++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void removerFuncionario(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    verFuncionariosInativos();
    int id;
    printf("\nInsira o ID do funcionario que pretende remover: ");
    scanf("%d", &id);
    int pos = encontrarIdFuncionario(id);

    if (pos == -1){
        printf("Funcionario não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
    else if (Funcionarios[pos].ativo == 1){
        printf("Funcionario está ativo não pode remove-lo!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
        return;
    }
    else{
        for (int i = pos; i < n_funcionarios; i++){
            Funcionarios[i] = Funcionarios[i + 1];
        }

        n_funcionarios--;
        Funcionarios = realloc(Funcionarios, sizeof(Funcionarios) * n_funcionarios);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
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