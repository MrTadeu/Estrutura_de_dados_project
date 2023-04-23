#ifndef LISTALIGADA_H_INCLUDED
#define LISTALIGADA_H_INCLUDED
    typedef struct elementoG{
        void *Info;
        struct elementoG *next;
    }Elemento;

    typedef struct{
        Elemento *head, *tail;
        int quantidadeElementos;
    }Lista;

    Lista *criarLista();
    Elemento *criarElemento(void *elemento);
    void AddElementoInicio(Lista *lista, Elemento *elemento);
    void AddElementoFim(Lista *lista, Elemento *elemento);
    void EscolherCriarElementoAddLista(Lista *lista, int Qt, void *(*escolherElemento)());
    Elemento *RemElementoInicio(Lista *lista);
    Elemento *RemElementoUltimo(Lista *lista);
    Elemento *RemElementoIndex(Lista *lista, int index);// Devolve o Elemento removido para o podermos detruir e adicionar info ao historico
    Elemento *RemElementoPesquisa(Lista *lista, Elemento *elemento, int (compareInfo)(void*, void*));
    void mostrarLista(Lista *lista, void (mostrarInfo)(void *, int), int indentLevel);// Enviar 0 como indentLevel
    void destruirLista(Lista *lista, void (destruirInfo)(void *));

#endif