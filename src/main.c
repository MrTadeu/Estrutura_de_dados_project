#include "../includes/TipoDados.h"
#include "../includes/ListaLigada.h"


//GLOBAL VARIABLES
GlobalStruct Global;
ClienteStruct *Clientes;
FuncionarioStruct *Funcionarios;
ProdutoStruct *Produtos;
int n_clientes, n_clientesAtivos = 0, n_funcionarios, n_funcionariosAtivos = 0, n_produtos;




int main(){
    srand(time(NULL));
    setlocale(LC_ALL, NULL);
    printf("\nClientes");

    importarDados(importarClientes, CLIENTES);
    printc("\n[red]Hello World1[/red]");
    importarDados(importarFuncionarios, FUNCIONARIOS);
    printc("\n[red]Hello World2[/red]");
    importarDados(importarProdutos, PRODUTOS);
    printc("\n[red]Hello World3[/red]");



    printf("\nClientes");
    for (int i = 0; i < n_clientes; i++){
        printf("\nLinha %d: ID: %d NOME: %s SALDOCARTAO: %f DATANASC: %d/%d/%d", i+1,Clientes[i].id, Clientes[i].nome, Clientes[i].saldoCartaoCliente, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
    }
    printf("\n\nFuncionarios");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nLinha %d: ID: %d NOME: %s BONUS: %f SALARIO: %f EXPERIENCIA: %d ATRASOMEDIO: %f", i+1,Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].bonus, Funcionarios[i].salario, Funcionarios[i].experiencia, Funcionarios[i].atrasoMedio);
    } 
    printf("\n\nProdutos");
    for (int i = 0; i < n_produtos; i++){
        printf("\nLinha %d: ID: %d NOME: %s PRECO: %f TCOMPRA: %f TCAIXA %f", i+1,Produtos[i].id, Produtos[i].nome, Produtos[i].preco, Produtos[i].tempoCompra, Produtos[i].tempoCaixa);
    }



    exportarDados(guardarClienteTxt, CLIENTES);
    exportarDados(guardarFuncionarioTxt, FUNCIONARIOS);
    exportarDados(guardarProdutoTxt, PRODUTOS);
    




    pthread_t thread_global;
    Global.lotacao_maxima_da_Loja = 1000;
    Global.probabilidadeGerarPessoa = 100;

    int erro = pthread_create(&thread_global, NULL, ThreadGlobal, NULL);
     if (erro != 0){
        printc("[red]Erro[/red] ao criar thread global\n");
        exit(1);
    } 
    
    printc("\n[red]Hello World[/red]");
    pthread_join(thread_global, NULL);

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

   

    
    

    /* printf("\n\nFuncionarios");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nLinha %d: ID: %d NOME: %s", i+1,Funcionarios[i].id, Funcionarios[i].nome);
    } 

    Lista* l = criarLista();
    EscolherCriarElementoAddLista(l, 4, escolherFuncionarios);

    printf("\n\nFuncionarios");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nLinha %d: ID: %d NOME: %s", i+1, Funcionarios[i].id, Funcionarios[i].nome);
    }  */


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

