#include "../includes/ListaLigada.h"
#include "../includes/TipoDados.h"

Lista *criarLista(){
    Lista *NovaLista = (Lista*) malloc(sizeof(Lista));
    NovaLista->head = NULL;
    NovaLista->tail = NULL;
    NovaLista->quantidadeElementos = 0;
    return NovaLista;
}

Elemento *criarElemento(void *elemento){
    if(!elemento){
        printf("\tError! Given element is NULL\n");
        return NULL; 
    } 

    Elemento *NovoElemento = (Elemento*) malloc(sizeof(Elemento));
    NovoElemento->Info = elemento;
    NovoElemento->next = NULL;
    return NovoElemento;
}

void AddElementoInicio(Lista *lista, Elemento *elemento){
    if(!lista){ 
       printf("\tError! List is NULL\n"); 
       return;
    }
    if(!elemento){
         printf("\tError! Given node is NULL");
        return; 
    } 

    if(!lista->head)
        lista->tail = elemento;

    elemento->next = lista->head;
    lista->head = elemento;
    lista->quantidadeElementos++;
}

void AddElementoFim(Lista *lista, Elemento *elemento){
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return;
    }
    if(!elemento){
         printf("\tError! Given node is NULL");
        return; 
    } 

    if(!lista->head)
        AddElementoInicio(lista, elemento);

    lista->tail->next = elemento;
    lista->tail = elemento;
    lista->quantidadeElementos++;
}

void EscolherCriarElementoAddLista(Lista *lista, int Qt, void*(*escolherProduto)()){
    for(int i = 0; i < Qt; i++)
        AddElementoFim(lista, criarElemento(escolherProduto()));
}

Elemento *RemElementoUltimo(Lista *lista){
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return NULL;
    }
    if(!lista->head){
        printf("\tError! Empty list\n");
        return NULL;
    }  

    Elemento *prev = lista->head, *curr = lista->head, *removido = lista->tail;
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
    
    lista->quantidadeElementos--;
    return removido;
}

Elemento *RemElementoInicio(Lista *lista){
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return NULL;
    }
    if(!lista->head){
        printf("\tError! Empty list\n");
        return NULL;
    }  

    Elemento *removido = lista->head;
    lista->head = lista->head->next;
    lista->quantidadeElementos--;
    if(!lista->head)
        lista->tail = NULL;
    return removido;
}

Elemento *RemElementoIndex(Lista *lista, int index){// Devolve o Elemento removido para o podermos detruir e adicionar info ao historico
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return NULL;
    }
    if(!lista->head){
        printf("\tError! Empty list\n");
        return NULL;
    }  
    if(index >= lista->quantidadeElementos){
        printf("\tError! Index out of range\n");
        return NULL;
    }

    Elemento *prev = lista->head, *curr = lista->head, *removido;
    int index_curr = 0;

    while(index_curr < index){
        prev = curr;
        curr = curr->next;
        index_curr++;
    }

    if(!index){
        removido = RemElementoInicio(lista);
        if(index == lista->quantidadeElementos-1)
            lista->tail = NULL;
    }
    else{
        if(index == lista->quantidadeElementos-1)
            lista->tail = prev;
        removido = prev->next;
        prev->next = prev->next->next;
        lista->quantidadeElementos--;
    }
    return removido;
}

Elemento *RemElementoPesquisa(Lista *lista, Elemento *elemento, int (compareInfo)(void*, void*)){
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return NULL;
    }
    if(!lista->head){
        printf("\tError! Empty list\n");
        return NULL;
    }
    if(!elemento){
        printf("\tError! Given node is NULL");
        return NULL; 
    } 

    Elemento *prev = lista->head, *curr = lista->head, *removido;
    while(curr){
        if(compareInfo(curr, elemento))
            break;
        prev = curr;
        curr = curr->next;
    }

    if(!curr){
        printf("\tError! Element not found\n");
        return NULL;
    }
    else if(prev == curr)
        removido = RemElementoInicio(lista);
    else{
        removido = prev->next;
        prev->next = prev->next->next;
        lista->quantidadeElementos--;
    }
    return removido;
}

void mostrarLista(Lista *lista, void (mostrarInfo)(void *, int), int indentLevel){
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return;
    }
    Elemento *Aux = lista->head;
    while(Aux){
        mostrarInfo(Aux->Info, indentLevel);
        Aux = Aux->next;
        if(!Aux->next)
            printf("<----------------------------->");
    }
}

void destruirLista(Lista *lista, void (destruirInfo)(void *)){
    if(!lista){
       printf("\tError! List is NULL\n"); 
       return;
    }

    Elemento *Aux = lista->head, *Temp;
    while(Aux){
        Temp = Aux->next;
        destruirInfo(Aux->Info);
        free(Aux);
        Aux = Temp;
    }
}