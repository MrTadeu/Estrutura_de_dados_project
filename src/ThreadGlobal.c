#include "../includes/TipoDados.h"

pthread_mutex_t listaLock;

void *ThreadGlobal(){
    srand(time(NULL));
    Lista /* *caixas, */ /* *listaThreadTempoCompra = criarLista(), */ *PessoasAcabaramTempoDeCompra = criarLista();
    /* pthread_mutex_init(&listaLock, NULL); */
    while(1){
        if (Aleatorio(0, 100) <= Global.probabilidadeGerarPessoa && n_clientes <= Global.lotacao_maxima_da_Loja){
            /* Argumentos *arg = (Argumentos *)malloc(sizeof(Argumentos));
            arg->ListaClientesNaFila = PessoasAcabaramTempoDeCompra;
            arg->cliente = (ClienteStruct *)escolherCliente(); */
            
            ThreadTempoDeCompra(PessoasAcabaramTempoDeCompra, escolherCliente());

        }
        dormir(100);
    }
}

/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/
void ThreadTempoDeCompra(Lista *ListaClientesNaFila, ClienteStruct *pessoa){
    if(!pessoa)
        return;
    pthread_t /* * */thread/*  = (pthread_t *) malloc(sizeof(pthread_t)) */;
    Argumentos *dados = (Argumentos *) malloc(sizeof(Argumentos));
    dados->cliente = pessoa;
    dados->ListaClientesNaFila = ListaClientesNaFila;
    pthread_create(&thread, NULL, ThreadEsperaTempoCompra, dados);
    /* AddElementoInicio(listaThreadTempoCompra, criarElemento((void *) thread)); */

    /* Elemento *Aux = listaThreadTempoCompra->head;
    while(Aux){
        pthread_t *x = (pthread_t *)Aux->Info;
        pthread_join(*x, NULL);
        Aux = Aux->next;
    } */
}

void *ThreadEsperaTempoCompra(void *args){
    Argumentos *dados = (Argumentos *)args;
    Lista *ListaClientesNaFila = (Lista*)dados->ListaClientesNaFila;
    ClienteStruct *cliente = (ClienteStruct *)dados->cliente;
    printf("\n\nPessoa Gerada: ");
    printf("\nNome: %s", cliente->nome);
    printf("\nTempo de Compra: %d", cliente->tempoEstimadoCompra);
    printf("\nTempo de Estimado Fila: %d", cliente->tempoEstimadoFila);
    printf("\nTempo de Estimado Caixa: %d", cliente->tempoEstimadoCaixa);
    printf("\nTempo de tempoAtraso: %d", cliente->tempoAtraso);
    printf("\nLista de Produtos:");
   /* Elemento *Aux = cliente->listaProdutos->head;
    while(Aux){
        ProdutoStruct *x = (ProdutoStruct *)Aux->Info;
        printf("\t\nID: %d Nome: %s, Preco: %.2f TCompra: %.2f TCaixa: %.2f",x->id, x->nome, x->preco, x->tempoCompra, x->tempoCaixa );
        Aux = Aux->next; 
    } */
   

    dormir(cliente->tempoEstimadoCompra * 1000);
    printf("\nFinished ");
    printf("\nNome: %s", cliente->nome);
    printf("\nTempo de Compra: %d", cliente->tempoEstimadoCompra);
    /* pthread_mutex_lock(&listaLock); */
    AddElementoFim(ListaClientesNaFila, criarElemento(cliente));
    /* pthread_mutex_unlock(&listaLock); */
    pthread_exit(NULL);
    free(dados);
    return NULL;
}
/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/




/* void *ThreadCaixa(void *args){ // EM DESENVOLVIMENTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
    while(caixa->aberta){
        
    }
    return NULL;
} */