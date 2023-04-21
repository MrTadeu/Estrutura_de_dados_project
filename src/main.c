#include "../includes/TipoDados.h"
#include "../includes/ListaLigada.h"


//GLOBAL VARIABLES
ClienteStruct *Clientes;
FuncionarioStruct *Funcionarios;
ProdutoStruct *Produtos;
int n_clientes, n_clientesAtivos = 0, n_funcionarios, n_funcionariosAtivos = 0, n_produtos;

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, NULL);
    printc("\n[red]Hello World[/red]");
    /* #ifdef _WIN32
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        printf ( "Current local time and date: %s", asctime (timeinfo) );
    #endif
    #ifdef __linux__
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        printf ( "Current local time and date: %s", asctime (timeinfo) );
    #endif*/

    importarDados(importarClientes, CLIENTES);
    printc("\n[red]Hello World1[/red]");
    importarDados(importarFuncionarios, FUNCIONARIOS);
    printc("\n[red]Hello World2[/red]");
    importarDados(importarProdutos, PRODUTOS);
    printc("\n[red]Hello World3[/red]");
    
    printf("\nClientes");
    for (int i = 0; i < n_clientes; i++){
        printf("\nLinha %d: ID: %d NOME: %s DATANASC: %d/%d/%d", i+1,Clientes[i].id, Clientes[i].nome, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
    }
    printf("\n\nFuncionarios");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nLinha %d: ID: %d NOME: %s", i+1,Funcionarios[i].id, Funcionarios[i].nome);
    } 
    printf("\n\nProdutos");
    for (int i = 0; i < n_produtos; i++){
        printf("\nLinha %d: ID: %d NOME: %s PRECO: %f TCOMPRA: %f TCAIXA %f", i+1,Produtos[i].id, Produtos[i].nome, Produtos[i].preco, Produtos[i].tempoCompra, Produtos[i].tempoCaixa);
    }
    /*  int total;
    FuncionarioStruct *DadosPessoa = importarFuncionarios(&total, "DadosFornecidos/funcionarios.csv");

    FuncionarioStruct *novoFuncionario = (FuncionarioStruct *) malloc(sizeof(FuncionarioStruct));
    escolherAleatorioVetor(DadosPessoa, total, sizeof(FuncionarioStruct), novoFuncionario);

    printf("id: %d, nome: %s", novoFuncionario->id, novoFuncionario->nome);
    free(DadosPessoa);
    free(novoFuncionario); */
    
    return 0;
}