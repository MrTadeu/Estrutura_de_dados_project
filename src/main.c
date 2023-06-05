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
long long tempoEmMilisegundos = 0;
int n_clientes, n_clientesAtivos = 0, n_funcionarios, n_funcionariosAtivos = 0, n_produtos, numeroMaximoCaixasPossivel = 50;

int main(){
    signal(SIGINT, SignalInstrucao);
    signal(SIGABRT, SignalInstrucao);
    srand(time(NULL));
    
    Init();
    menu();
    if(Opcoes.lojaAberta)
        fechamentoLoja();
    closeAll();
}