#include "../includes/TipoDados.h"
#include "../includes/ListaLigada.h"

//GLOBAL VARIABLES
OpcaoStruct Opcoes;
GlobalStruct Global;
HistoricoStruct HistoricoDados; 
pthread_mutex_t ClientesLock, FuncionariosLock, PessoasAcabaramTempoDeCompraLock;
ClienteStruct **Clientes;
FuncionarioStruct **Funcionarios;
ProdutoStruct *Produtos;
int n_clientes, n_clientesAtivos = 0, n_funcionarios, n_funcionariosAtivos = 0, n_produtos;

int main(){
    srand(time(NULL));
    
    Init();
    menu();
    closeAll();
}