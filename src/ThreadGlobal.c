#include "../includes/TipoDados.h"

typedef struct{
    Lista *ListaClientesNaFila;
    ClienteStruct *cliente;
}Argumentos;

void *ThreadEsperaTempoCompra(void *args);

void ThreadTempoDeCompra(/* Lista listaThreadTempoCompra,  */Lista *ListaClientesNaFila, ClienteStruct *pessoa){
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
    Elemento *Aux = cliente->listaProdutos->head;
    while(Aux){
        ProdutoStruct *x = (ProdutoStruct *)Aux->Info;
        printf("\t\nID: %d Nome: %s, Preco: %.2f TCompra: %.2f TCaixa: %.2f",x->id, x->nome, x->preco, x->tempoCompra, x->tempoCaixa );
        Aux = Aux->next;
    }
    
    dormir(cliente->tempoEstimadoCompra * 1000);
    AddElementoFim(ListaClientesNaFila, criarElemento(cliente));
    pthread_exit(NULL);
    free(dados);
    return NULL;
}

void *ThreadGlobal(int prob){

    Lista /* *caixas, */ /* *listaThreadTempoCompra = criarLista(), */ *PessoasAcabaramTempoDeCompra = criarLista();

    while(1){
        if (Aleatorio(0, 100) <= prob){
            /* Argumentos *arg = (Argumentos *)malloc(sizeof(Argumentos));
            arg->ListaClientesNaFila = PessoasAcabaramTempoDeCompra;
            arg->cliente = (ClienteStruct *)escolherCliente(); */
            
            ThreadTempoDeCompra(PessoasAcabaramTempoDeCompra, escolherCliente());

        }
        
        dormir(1000);
    }
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

int CaixaIndex(Lista *caixa){ // o melhor index que tem o menor numero de clientes
    int pos = 0, index = 0;
    Elemento *caixaAux = caixa->head;
    Elemento *menor = caixaAux;

    CaixaStruct *caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *menorInfo = (CaixaStruct *)menor->Info;
    if (menorInfo->aberta == 0){ // se o primeiro caixa estiver fechado, procura o primeiro aberto
        menorInfo = caixaAuxInfo;
        index = pos;
        while (menorInfo->aberta == 0 && caixaAux){ // NÃO ESQUECER DE VERIFICAR SE TODAS ESTÃO FECHADAS TRATAR DO ASSUSNTO
            caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
            if(caixaAuxInfo->aberta == 1){
                menorInfo = caixaAuxInfo;
                index = pos;
            }
            caixaAux = caixaAux->next;
            pos++;
        }
    }
    
    pos = 0;
    while(caixaAux){ // procura o caixa com menos clientes
        caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
        if(caixaAuxInfo->tempoTotalEspera < menorInfo->tempoTotalEspera && caixaAuxInfo->aberta == 1){
            menorInfo = caixaAuxInfo;
            index = pos;
        }
        caixaAux = caixaAux->next;
        pos++;
    }
    return index;
}

void SelecionarCaixa(Lista *caixas, Elemento *cliente){ // seleciona (adiciona) a melhor caixa para o cliente
    int index = CaixaIndex(caixas);
    Elemento *caixaAux = caixas->head;
    while(index){
        caixaAux = caixaAux->next;
        index--;
    }
    CaixaStruct *caixaAuxInfo = (CaixaStruct* )caixaAux->Info;
    AddElementoFim(caixaAuxInfo->listaPessoas, cliente);
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

/* void *ThreadCaixa(void *args){ // EM DESENVOLVIMENTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
    while(caixa->aberta){
        
    }
    return NULL;
} */



void criarListaThreads(Lista *listaThreads, void *(*FuncaoThread)(void *), void *arg1, void *arg2){ // criar um remover lista threads
    pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t));
    Argumentos *argumento = (Argumentos *)malloc(sizeof(Argumentos));
    argumento->ListaClientesNaFila = arg1;
    argumento->cliente = arg2;
    pthread_create(thread, NULL, FuncaoThread, (Argumentos *)argumento);
    AddElementoFim(listaThreads, criarElemento(thread));
}