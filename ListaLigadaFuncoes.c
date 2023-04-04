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
    if(!lista->head) return NULL;

    NOG *prev = lista->head, *curr = lista->head, *removido = lista->tail;
    while(curr->next){
        prev = curr;
        curr = curr->next;
    }

    if(prev == curr){
        lista->head = NULL;
        lista->tail = NULL;
    }
    else{
        lista->tail = prev; 
        lista->tail->next = NULL;
    }
    
    lista->n_el--;
    return removido;
}

NOG *RemNOG_inicio(LG *lista){
    if(!lista->head) return NULL;

    NOG *removido = lista->head;
    lista->head = lista->head->next;
    lista->n_el--;
    if(!lista->head)
        lista->tail = NULL;
    return removido;
}

NOG *RemNOG_index(LG *lista, int index){          // Devolve o NOG removido para o podermos detruir e adicionar info ao historico
    if(!lista->head){
        printf("\tError! Empty list\n");
        return NULL;
    }  
    if(index >= lista->n_el){
        printf("\tError! Index out of range\n");
        return NULL;
    }

    NOG *prev = lista->head, *curr = lista->head, *removido;
    int index_curr = 0;

    while(index_curr < index){
        prev = curr;
        curr = curr->next;
        index_curr++;
    }

    if(!index){
        removido = RemNOG_inicio(lista);
        if(index == lista->n_el-1)
            lista->tail = NULL;
    }
    else{
        if(index == lista->n_el-1)
            lista->tail = prev;
        removido = prev->next;
        prev->next = prev->next->next;
        lista->n_el--;
    }
}

NOG *RemNOG_Pesquisa(LG *lista, NOG *elemento, int (compareInfo)(void*, void*)){
    if(!lista->head){
        printf("\tError! Empty list\n");
        return NULL;
    }
    if(!elemento)
        return NULL;

    NOG *prev = lista->head, *curr = lista->head, *removido;
    while(curr){
        if(compareInfo(curr, elemento))
            break;
        prev = curr;
        curr = curr->next;
    }


    if(prev == curr)
        removido = RemNOG_inicio(lista);
    else if(!curr){
        printf("\tError! Element not found\n");
        return NULL;
    }
    else{
        prev->next = prev->next->next;
        lista->n_el--;
    }
}

void MostrarLG(LG *lista, void (mostrarInfo)(void *)){
    if(!lista) return;

    NOG *Aux = lista->head;
    while(Aux){
        mostrarInfo(Aux->Info);
        Aux = Aux->next;
    }
}

void DestruirLG(LG *lista, void (destruirInfo)(void *)){
    if(!lista) return;

    NOG *Aux = lista->head, *Temp;
    while(Aux){
        Temp = Aux->next;
        destruirInfo(Aux->Info);
        free(Aux);
        Aux = Temp;
    }
}