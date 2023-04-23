#include "../includes/TipoDados.h"


/* void *ThreadGlobal(int prob){
    while(1){
        if (Aleatorio(0, 100) <= prob){
            //Global.semaforo[CaixaIndex(Caixas)] = 1;

        }
        
        dormir(1000);
    }
} */

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

/* void *ThreadCaixa(CaixaStruct *caixa){ // EM DESENVOLVIMENTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
    while(caixa->aberta){
        
    }
}

void *ThreadCliente(Lista *ListaClientesNaLoja, ClienteStruct *cliente)[ // Vai inserir o cliente na fila da thread global
    

]

void *ThreadClienteGlobal(Lista *ListaClientesNaLoja, ClienteStruct *cliente){ // Cria uma lista de clientes gigante que terminaram o tempo de compra e estão na fila
    while(cliente->tempoEstimadoCompra){
        if(cliente->naFila == 1){

        }
    }
} */

void criarListaThreads(Lista *listaThreads){ // criar um remover lista threads
    pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t));
    pthread_create(&thread, NULL, ThreadCaixa, NULL);
    AddElementoFim(listaThreads, criarElemento(thread));
}

/* void criarCaixas(Lista *caixas){ // EM DESENVOLVIMENTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

} */