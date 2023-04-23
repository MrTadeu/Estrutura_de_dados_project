#include "../includes/TipoDados.h"

typedef struct{
    Lista *ListaClientesNaLoja;
    ClienteStruct *cliente;
}Argumentos;

void *ThreadGlobal(int prob){

    Lista *caixas, *PessoasAcabaramTempoDeCompra;

    while(1){
        if (Aleatorio(0, 100) <= prob){
            Argumentos *arg = (Argumentos *)malloc(sizeof(Argumentos));
            arg->ListaClientesNaLoja = PessoasAcabaramTempoDeCompra;
            arg->cliente = (ClienteStruct *)escolherCliente();
            
            ThreadTempoDeCompra(arg);

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

void *ThreadTempoDeCompra(void *args){ // Vai inserir o cliente na fila da thread global
    Argumentos *argumento = (Argumentos *)args;
    Lista *ListaClientesNaLoja = (Lista*)argumento->ListaClientesNaLoja;
    ClienteStruct *cliente = (ClienteStruct *)argumento->cliente;

    dormir(cliente->tempoEstimadoCompra * 1000);
    AddElementoFim(ListaClientesNaLoja, criarElemento(cliente)); // lista de clientes gigante que terminaram o tempo de compra e estão na fila para entrar no caixa
    return NULL;
}

void criarListaThreads(Lista *listaThreads, void *(*FuncaoThread)(void *), void *arg1, void *arg2){ // criar um remover lista threads
    pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t));
    Argumentos *argumento = (Argumentos *)malloc(sizeof(Argumentos));
    argumento->ListaClientesNaLoja = arg1;
    argumento->cliente = arg2;
    pthread_create(thread, NULL, FuncaoThread, (Argumentos *)argumento);
    AddElementoFim(listaThreads, criarElemento(thread));
}