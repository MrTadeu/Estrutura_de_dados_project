#include "TipoDados.h"

void *ThreadGlobal(void *arg){

    while(1){
        
    }
}

int CaixaIndex(Lista *caixa){ // o melhor index que tem o menor numero de clientes
    int pos = 0, index = 0;
    Elemento *caixaAux = caixa->head;
    Elemento menor = caixaAux;
    
    while(caixaAux){
        caixaAux->Info = (CaixaStruct *)caixaAux->Info;
        menor->Info = (CaixaStruct *)menor->Info;
        if(caixaAux->Info->tempoTotalEspera < menor->Info->tempoTotalEspera){
            menor = caixaAux;
            index = pos;
        }
        caixaAux = caixaAux->next;
        pos++;
    }
}

void SelecionarCaixa(Lista *caixas, Elemento *cliente){ // seleciona (adiciona) a melhor caixa para o cliente
    int index = CaixaIndex(caixa);
    Lista *caixaAux = caixas->head;
    while(index){
        caixaAux = caixaAux->next;
        index--;
    }
    AddElementoFim(caixaAux, cliente);
}

