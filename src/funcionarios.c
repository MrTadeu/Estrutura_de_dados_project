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
    if (funcionario->n_vendas <= Opcoes.nivelFuncionario[0].n_vendas) 
        return Opcoes.nivelFuncionario[0];
    else if (funcionario->n_vendas<= Opcoes.nivelFuncionario[1].n_vendas) 
        return Opcoes.nivelFuncionario[1];
    else
        return Opcoes.nivelFuncionario[2];
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

void pesquisarFuncionarios(){
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
    float salario = (getNivelFuncionario(funcionario)).salario;
    funcionario->n_vendas += n_vendas;
    if(Opcoes.VerTransacoes == 1){
        if((getNivelFuncionario(funcionario)).salario != salario){
            float novoSalario = (getNivelFuncionario(funcionario)).salario;
            for (int  i = 1; i < 3; i++){
                if((Opcoes.nivelFuncionario[i]).salario == novoSalario)
                    printc("\n\t[green]Promoção[/green] Funcionario com id %d promovido para nível %d com novo salario de %.2f euros\n", funcionario->id, i+1, novoSalario);
            }
        }
    }
    funcionario->atrasoMedio = (funcionario->atrasoMedio + atrasoMedio) / 2;
    if(funcionario->atrasoMedio < 0)
        funcionario->bonus += Opcoes.eurosPorSegundoAdiantamentoFuncinario * funcionario->atrasoMedio;
}