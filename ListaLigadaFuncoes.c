#include "ListaLigada.h"
#include "TipoDados.h"

LG *criarLG(){
    LG *NovaLG = (LG*) malloc(sizeof(LG));
    NovaLG->head = NULL;
    NovaLG->tail = NULL;
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

void AddNOG_inicio(LG *lista, NOG *elemento){
    if(!lista || !elemento) return;

    if(!lista->head)
        lista->tail = elemento;

    elemento->next = lista->head;
    lista->head = elemento;
    lista->n_el++;
}


void AddNOG_fim(LG *lista, NOG *elemento){
    if(!lista || !elemento) return;

    if(!lista->head)
        AddNOG_inicio(lista, elemento);

    lista->tail->next = elemento;
    lista->tail = elemento;
    lista->n_el++;
}

NOG *RemNOG_ultimo(LG *lista){
    if(!lista) return NULL;

    NOG *Aux = lista->head, *removido = lista->tail;
    while(Aux->next->next)
        Aux = Aux->next;

    lista->tail = Aux;
    Aux->next = NULL;
    lista->n_el--;
    return removido;
}

NOG *RemNOG_inicio(LG *lista){
    if(!lista) return NULL;

    NOG *removido = lista->head;
    lista->head = lista->head->next;
    lista->n_el;
    return removido;
}

NOG *RemNOG_index(LG *lista, int index){          // Devolve o NOG removido para o podermos detruir e adicionar info ao historico
    if(!lista || index >= lista->n_el) return NULL;    

    NOG *removido;
    if(lista->n_el < 3){
        if(index)
            removido = RemNOG_ultimo(lista);
        else
            removido = RemNOG_inicio(lista);
    }

    NOG *prev = lista->head, *curr = lista->head->next->next;
    int index_c = 2;
    while(index_c <= index && curr){
        prev = prev->next;
        curr = curr->next;
        index_c++;
    }

    if(!curr)
        removido = RemNOG_ultimo(lista);
    else if(lista->head == prev)
        removido = RemNOG_inicio(lista);
    else{
        removido = prev->next;
        prev->next = prev->next->next;
        lista->n_el--;
    }
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