#include "../includes/TipoDados.h"

int escolherAleatorioVetor(void *vetor, int n_ativos, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento){
    int indice = Aleatorio(n_ativos, tamanhoVetor-1);
    memcpy(ptrElemento, (char *)vetor + indice * tamanhoElemento, tamanhoElemento);
    return indice;
} 

void associarProdutosCliente(ClienteStruct *cliente, Lista *produtos){
    cliente->listaProdutos = produtos;
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

void *escolherFuncionarios(){
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

void *escolherProduto(){
    ProdutoStruct *produto = (ProdutoStruct *) malloc(sizeof(ProdutoStruct));
    escolherAleatorioVetor(Produtos, 0, n_produtos, sizeof(ProdutoStruct), produto);
    return produto;
}

void *escolherCliente(){
    if(n_clientesAtivos >= n_clientes-1){
        printf("\n\tErro! Nao existem mais clientes disponiveis.\n");
        return NULL;
    }
    ClienteStruct *cliente = (ClienteStruct *) malloc(sizeof(ClienteStruct));
    int indice = escolherAleatorioVetor(Clientes, n_clientesAtivos, n_clientes, sizeof(ClienteStruct), cliente);
    Clientes[indice].ativo = 1;
    batenteChange(&Clientes[n_clientesAtivos], &Clientes[indice], sizeof(ClienteStruct), &n_clientesAtivos, '+');
    return cliente;
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