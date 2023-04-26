#include "../includes/TipoDados.h"
#include "../includes/ListaLigada.h"

//GLOBAL VARIABLES
OpcaoStruct Opcoes;
GlobalStruct Global;
ClienteStruct *Clientes;
FuncionarioStruct *Funcionarios;
ProdutoStruct *Produtos;
int n_clientes, n_clientesAtivos = 0, n_funcionarios, n_funcionariosAtivos = 0, n_produtos;

void testarCaixas(){
    changeStateThreadGlobal();
}

int main(){
    Init();

    testarCaixas();



    menu();
    closeAll();

   /*
    printf("\n\nFuncionarios");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nLinha %d: ID: %d NOME: %s BONUS: %f SALARIO: %f EXPERIENCIA: %d ATRASOMEDIO: %f", i+1,Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].bonus, Funcionarios[i].salario, Funcionarios[i].experiencia, Funcionarios[i].atrasoMedio);
    } 
    printf("\n\nProdutos");
    for (int i = 0; i < n_produtos; i++){
        printf("\nLinha %d: ID: %d NOME: %s PRECO: %f TCOMPRA: %f TCAIXA %f", i+1,Produtos[i].id, Produtos[i].nome, Produtos[i].preco, Produtos[i].tempoCompra, Produtos[i].tempoCaixa);
    }
 */


    
    




    

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

   



    /*  int total;
    FuncionarioStruct *DadosPessoa = importarFuncionarios(&total, "DadosFornecidos/funcionarios.csv");

    FuncionarioStruct *novoFuncionario = (FuncionarioStruct *) malloc(sizeof(FuncionarioStruct));
    escolherAleatorioVetor(DadosPessoa, total, sizeof(FuncionarioStruct), novoFuncionario);

    printf("id: %d, nome: %s", novoFuncionario->id, novoFuncionario->nome);
    free(DadosPessoa);
    free(novoFuncionario); */

    /* Lista *listaThreadTempoCompra = criarLista();
    for (int i = 0; i < 10; i++){
        pthread_t *thread = (pthread_t *) malloc(sizeof(pthread_t));
        printf("\n\nThread: %p", thread);
        Teste *x = (Teste *) malloc(sizeof(Teste));
        x->pos = i;
        x->ale= Aleatorio(1, 30);
        printf("\n\tpos: %d ale:%d", x->pos, x->ale);
        int status = pthread_create(thread, NULL, print_thread_id, x);
        AddElementoInicio(listaThreadTempoCompra, criarElemento((void *) thread));

        if (status != 0) {
            printf("Error creating thread %d\n", i);
        }
    }

    Elemento *Aux = listaThreadTempoCompra->head;
    while(Aux){
        pthread_t *x = (pthread_t *)Aux->Info;
        printf("\n\nThread final: %p", x);
        if (pthread_kill(*x, 0) == 0) {
            printf("Thread is still running.\n");
        } else {
            printf("Thread has terminated.\n");
        }
        pthread_join(*x, NULL);
        Aux = Aux->next;
    }
    dormir(100000); */
}

