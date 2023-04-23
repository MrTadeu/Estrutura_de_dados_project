#include "../includes/TipoDados.h"

int escolherAleatorioVetor(void *vetor, int n_ativos, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento){
    int indice = Aleatorio(n_ativos, tamanhoVetor-1);
    memcpy(ptrElemento, (char *)vetor + indice * tamanhoElemento, tamanhoElemento);
    return indice;
} 

void calculoTemposCliente(ClienteStruct *cliente){
    if(!cliente){
        printf("[red]Error![/red] Given client is NULL");
        return;
    }

    Elemento *Aux = cliente->listaProdutos->head;
    while(Aux){
        ProdutoStruct *produto = (ProdutoStruct *) Aux->Info;
        cliente->tempoEstimadoCaixa += produto->tempoCaixa;
        cliente->tempoEstimadoCompra += produto->tempoCompra;
        Aux = Aux->next;
    }
}

CaixaStruct *criarCaixa(int id){
    CaixaStruct *caixa = (CaixaStruct *) malloc(sizeof(CaixaStruct));
    caixa->id = id;
    caixa->aberta = 1;
    caixa->fecharUrgencia = 0;
    caixa->tempoTotalEspera = 0;
    caixa->funcionario = (FuncionarioStruct *) escolherFuncionarios();
    caixa->listaPessoas = criarLista(); 
    return caixa;
}

ClienteStruct *criarGuest(){
    ClienteStruct *cliente = (ClienteStruct *) malloc(sizeof(ClienteStruct));
    cliente->id = -1;
    cliente->nome = (char *) malloc(sizeof(char)*13);
    strcpy(cliente->nome, "Desconhecido");
    cliente->tempoAtraso = 0;
    cliente->tempoEstimadoCaixa = 0;
    cliente->tempoEstimadoCompra = 0;
    cliente->tempoEstimadoFila = 0;
    return cliente;
}

void batenteChange(void* ptr1, void* ptr2, size_t size, int *batente, char sinal){ // Troca dois elementos de posicao e decrementa batente
    void* temp = malloc(size);
    memcpy(temp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, temp, size);
    free(temp);
    if(sinal == '+')
        *batente = *batente + 1;
    else if(sinal == '-')
        *batente = *batente - 1;
    else
        printf("\n\tError! Invalid Operation.\n");
}

FuncionarioStruct *escolherFuncionarios(){
    if(n_funcionariosAtivos >= n_funcionarios-1){
        printf("\n\tErro! Nao existem mais funcionarios disponiveis.\n");
        return NULL;
    }
    FuncionarioStruct *funcionario = (FuncionarioStruct *) malloc(sizeof(FuncionarioStruct));
    int indice = escolherAleatorioVetor(Funcionarios, n_funcionariosAtivos, n_funcionarios, sizeof(FuncionarioStruct), funcionario);
    Funcionarios[indice].ativo = 1;
    batenteChange(&Funcionarios[n_funcionariosAtivos], &Funcionarios[indice], sizeof(FuncionarioStruct), &n_funcionariosAtivos, '+');
    return funcionario;
}

ClienteStruct *escolherCliente(){
    srand(time(NULL));
    /* printf("\n\tpessoa gerada"); */
    if(n_clientesAtivos >= n_clientes){
            /* printc("\n\t[red]Erro![/red] Nao existem mais clientes disponiveis.\n"); */
        return NULL;
    }
    
    ClienteStruct *cliente = (ClienteStruct *) malloc(sizeof(ClienteStruct)); 
    int indice = escolherAleatorioVetor(Clientes, n_clientesAtivos, n_clientes, sizeof(ClienteStruct), cliente); // Aleatoriamente escolhe um dos clientes do ficheiro txt
    Clientes[indice].ativo = 1;                                                                                 // e armazena os dados na varivel cliente criada acima
    cliente->listaProdutos = criarLista(); 
    batenteChange(&Clientes[n_clientesAtivos], &Clientes[indice], sizeof(ClienteStruct), &n_clientesAtivos, '+');
    EscolherCriarElementoAddLista(cliente->listaProdutos, 2);
    calculoTemposCliente(cliente);
    /* printf("testee"); */
    return cliente;
}

ProdutoStruct *escolherProduto(){
    ProdutoStruct *produto = (ProdutoStruct *) malloc(sizeof(ProdutoStruct));
    escolherAleatorioVetor(Produtos, 0, n_produtos, sizeof(ProdutoStruct), produto);
    return produto;
}

void mostrarFuncionario(void *funcionarioArg, int indentLevel){
    if(!funcionarioArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    FuncionarioStruct *funcionario = (FuncionarioStruct *) funcionarioArg;

    printf("\n%*sFUNCIONARIO INFO:\n%*sId Funcionario: %d\n%*sNome: %s\n%*sExperiencia: %d vendas\n%*sSalario: %f\n%*sAtraso medio: %f\n%*sBonus: %f", 
           indentLevel*4, " ", indentLevel*4, " ", funcionario->id, indentLevel*4, " ", funcionario->nome, indentLevel*4, " ", funcionario->experiencia, indentLevel*4, " ", funcionario->salario, indentLevel*4, " ", funcionario->atrasoMedio, indentLevel*4, " ", funcionario->bonus);
}

void mostrarCaixa(void *caixaArg, int indentLevel){
    if(!caixaArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    CaixaStruct *caixa = (CaixaStruct *) caixaArg;
    
    printf("\n%*sCAIXA INFO:\n%*sId Caixa: %d\n%*sTempo de Espera: %d segundos", 
           indentLevel*4, " ", indentLevel*4, " ", caixa->id, indentLevel*4, " ", caixa->tempoTotalEspera);
    mostrarFuncionario(caixa->funcionario, indentLevel + 1);
    mostrarLista(caixa->listaPessoas, mostrarCliente, indentLevel + 1);
}

void mostrarProduto(void *produtoArg, int indentLevel){
    if(!produtoArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    ProdutoStruct *produto = (ProdutoStruct *) produtoArg;

    printf("\n%*sPRODUTO INFO:\n%*sNome Produto: %s\n%*sCodigo Produto: %d\n%*sPreco: %f\n%*sTempo de Compra: %f\n%*sTempo de Caixa: %f", 
           indentLevel*4, " ", indentLevel*4, " ", produto->nome, indentLevel*4, " ", produto->id, indentLevel*4, " ", produto->preco, indentLevel*4, " ", produto->tempoCompra, indentLevel*4, " ", produto->tempoCaixa);
}

void mostrarCliente(void *clienteArg, int indentLevel){
    if(!clienteArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    ClienteStruct *cliente = (ClienteStruct *) clienteArg;
    
    printf("\n%*sCLIENTE INFO:\n\t%*sId Cliente: %d\n\t%*sNome: %s\n\t%*sData de Nascimento: %d/%d/%d\n\t%*sSaldo do Cartao: %.2f\n\t%*sTempo Estimado de Compra: %d segundos\n\t%*sTempo Estimado de Fila: %d segundos\n\t%*sTempo Estimado de Caixa: %d segundos\n\t%*sTempo de atrado: %d segundos",
        indentLevel*4, " ", indentLevel*4, " ", cliente->id, indentLevel*4, " ", cliente->nome,
        indentLevel*4, " ", cliente->dataNascimento.dia, cliente->dataNascimento.mes, cliente->dataNascimento.ano,
        indentLevel*4, " ", cliente->saldoCartaoCliente, indentLevel*4, " ", cliente->tempoEstimadoCompra,
        indentLevel*4, " ", cliente->tempoEstimadoFila, indentLevel*4, " ", cliente->tempoEstimadoCaixa, indentLevel*4, " ", cliente->tempoAtraso);
    mostrarLista(cliente->listaProdutos, mostrarProduto, indentLevel + 1);
}

int compararProduto(void *ptrProduto1_Info, void * ptrProduto2_Info){
    ProdutoStruct *produto1 = (ProdutoStruct *) ptrProduto1_Info, *produto2 = (ProdutoStruct *) ptrProduto2_Info;
    if(produto1->tempoCaixa != produto2->tempoCaixa || produto1->tempoCompra != produto2->tempoCompra ||
        produto1->preco != produto2->preco || produto1->id != produto2->id || strcpy(produto1->nome, produto2->nome) != 0)
        return 0;
    return 1;
}

int compararListaProdutos(Lista *lista1, Lista *lista2){
    if(!lista1||!lista2){
        printf("\n\t[red]Error![/red] List is NULL\n");
        return -1;
    }
    if(lista1->quantidadeElementos != lista2->quantidadeElementos){
        printf("\n\t[red]Error![/red] Lists have different sizes.\n");
        return -1;
    }
        
    Elemento *aux1 = lista1->head, *aux2 = lista2->head;
    while(!aux1||!aux2){
        if(!compararProduto(aux1->Info, aux2->Info))
            return 0;
        aux1 = aux1->next;
        aux2 = aux2->next;
    }
    return 1;
}

int compararCliente(void *ptrCliente1_Info, void *ptrCliente2_Info){
    ClienteStruct *cliente1 = (ClienteStruct *) ptrCliente1_Info, *cliente2 = (ClienteStruct *) ptrCliente2_Info;
    if(cliente1->id != cliente2->id || cliente1->ativo != cliente2->ativo || cliente1->dataNascimento.ano != cliente2->dataNascimento.ano ||
        cliente1->dataNascimento.mes != cliente2->dataNascimento.mes || cliente1->dataNascimento.dia != cliente2->dataNascimento.dia ||
        strcpy(cliente1->nome, cliente2->nome) != 0 || cliente1->saldoCartaoCliente != cliente2->saldoCartaoCliente || cliente1->tempoAtraso != cliente2->tempoAtraso ||
        cliente1->tempoEstimadoCaixa != cliente2->tempoEstimadoCaixa || cliente1->tempoEstimadoCompra != cliente2->tempoEstimadoCompra ||
        cliente1->tempoEstimadoFila != cliente2->tempoEstimadoFila || cliente1->listaProdutos->quantidadeElementos != cliente2->listaProdutos->quantidadeElementos)
        return 0;

    Elemento *produto1 = cliente1->listaProdutos->head, *produto2 = cliente2->listaProdutos->head;
    while(produto1 && produto2){
        if(!compararProduto(produto1->Info, produto2->Info))
            return 0;
        produto1 = produto1->next;
        produto2 = produto2->next;
    }
    return 1;
}

int pesquisarClienteVetor(ClienteStruct *pessoa){
    if(!pessoa){
        printf("[red]Error![/red] NULL ClienteStruct");
        return -1;
    }
    for (int i = 0; i < n_clientesAtivos; i++){
        if(compararCliente(&Clientes[i], pessoa))
            return i;
    }
    return -1;
}