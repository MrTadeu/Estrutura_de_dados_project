#include "../includes/TipoDados.h"
#include "../includes/ListaLigada.h"


//GLOBAL VARIABLES
ClienteStruct *Clientes;
FuncionarioStruct *Funcionarios;
ProdutoStruct *Produtos;
int n_clientes, n_funcionarios, n_produtos;

int main(){
    printf("Hello World");

    srand(time(NULL));

    /* int total;
    FuncionarioStruct *DadosPessoa = importarFuncionarios(&total, "DadosFornecidos/funcionarios.csv");

    FuncionarioStruct *novoFuncionario = (FuncionarioStruct *) malloc(sizeof(FuncionarioStruct));
    escolherAleatorioVetor(DadosPessoa, total, sizeof(FuncionarioStruct), novoFuncionario);

    printf("id: %d, nome: %s", novoFuncionario->id, novoFuncionario->nome);
    free(DadosPessoa);
    free(novoFuncionario); */
    
    return 0;
}