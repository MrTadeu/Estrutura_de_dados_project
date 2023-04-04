#include "ListaLigada.h"
#include "TipoDados.h"


LG *criarLG(){
    LG *NovaLG = (LG*) malloc(sizeof(LG));
    NovaLG->head = NULL;
    NovaLG->n_el = 0;
    return NovaLG;
}

NOG *criarNOG(void *elemento){
    if(!elemento) return;

    NOG *NovoNOG = (NOG*) malloc(sizeof(NOG));
    NovoNOG->Info = elemento;
    NovoNOG->next = NULL;
    return NovoNOG;
}

void AddNOG_fim(LG *lista, NOG *elemento){
    if(!lista || !elemento) return;

    lista->tail->next = elemento;
    lista->tail = elemento;
    lista->n_el++;
}

NOG *RemNOG_inicio(LG *lista){                  // Devolve o NOG removido para o podermos detruir e adicionar info ao historico
    if(!lista) return NULL;                     // Fazer mais generico

    NOG *NOG_Removido = lista->head;
    lista->head = lista->head->next;
    return NOG_Removido;
}

void MostrarLG(LG *lista, void (MostrarInfo)(void *)){
    if(!lista) return;

    NOG *Aux = lista->head;
    while(Aux){
        MostrarInfo(Aux->Info);
        Aux = Aux->next;
    }
}

void DestruirLG(LG *lista, void (DestruirInfo)(void *)){
    if(!lista) return;

    NOG *Aux = lista->head;
    while(Aux){
        DestruirInfo(Aux->Info);
        Aux = Aux->next;
    }
}