#include "../includes/TipoDados.h"

pthread_mutex_t listaLock;

void changeStateThreadGlobal(){
    if(Global.lojaAberta == 0){
        Global.lojaAberta = 1;
        pthread_t GlobalThread;

        if (pthread_create(&GlobalThread, NULL, ThreadGlobal, NULL) != 0){
            printc("[red]Erro[/red] ao criar thread global!!!\n");
            exit(1);
        } 
        
        /* pthread_join(GlobalThread, NULL); */// <--- Nao dar join porque a thread global vai ficar sempre a correr
    }
    else if(Global.lojaAberta == 1){
        Global.lojaAberta = 0;
    }
}

void *ThreadGlobal(){
    srand(time(NULL));
    Lista *PessoasAcabaramTempoDeCompra = criarLista();
    pthread_mutex_init(&listaLock, NULL);
    while(Global.lojaAberta == 1){
        if (Aleatorio(0, 100) <= Global.probGerarPessoa && n_clientes <= Global.lotacaoMaxima){
            ThreadTempoDeCompra(PessoasAcabaramTempoDeCompra, escolherCliente());

        }
        dormir(100);
    }
    return NULL;
}

/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/
void ThreadTempoDeCompra(Lista *ListaClientesNaFila, ClienteStruct *pessoa){
    if(!pessoa)
        return;
    pthread_t thread;
    Argumentos *dados = (Argumentos *) malloc(sizeof(Argumentos));
    dados->cliente = pessoa;
    dados->ListaClientesNaFila = ListaClientesNaFila;
    pthread_create(&thread, NULL, ThreadEsperaTempoCompra, dados);
}

void *ThreadEsperaTempoCompra(void *args){
    Argumentos *dados = (Argumentos *)args;
    Lista *ListaClientesNaFila = (Lista*)dados->ListaClientesNaFila;
    ClienteStruct *cliente = (ClienteStruct *)dados->cliente;

    if(Global.VerTransacoes == 1){
        printf("\n\nPessoa Gerada: ");
        printf("\nNome: %s", cliente->nome);
        printf("\nTempo de Compra: %d", cliente->tempoEstimadoCompra);
        printf("\nTempo de Estimado Fila: %d", cliente->tempoEstimadoFila);
        printf("\nTempo de Estimado Caixa: %d", cliente->tempoEstimadoCaixa);
        printf("\nTempo de tempoAtraso: %d", cliente->tempoAtraso);
        /* printf("\nLista de Produtos:");
        Elemento *Aux = cliente->listaProdutos->head;
        while(Aux){
            ProdutoStruct *x = (ProdutoStruct *)Aux->Info;
            printf("\t\nID: %d Nome: %s, Preco: %.2f TCompra: %.2f TCaixa: %.2f",x->id, x->nome, x->preco, x->tempoCompra, x->tempoCaixa );
            Aux = Aux->next; 
        } */
    }
   
    dormir(cliente->tempoEstimadoCompra * 1000);
    if(Global.VerTransacoes == 1){
        printf("\n\n%s acabou de comprar todos os produtos em %ds",cliente->nome, cliente->tempoEstimadoCompra);
    }
    pthread_mutex_lock(&listaLock);
    AddElementoFim(ListaClientesNaFila, criarElemento(cliente));
    pthread_mutex_unlock(&listaLock);
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