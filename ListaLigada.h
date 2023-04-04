#ifndef LISTALIGADA_H_INCLUDED
#define LISTALIGADA_H_INCLUDED


typedef struct nog{
    void *Info;
    struct nog *next;
}NOG;

typedef struct{
    NOG *head, *tail;
    int n_el;
}LG;

LG *criarLG();
NOG *criarNOG(void *elemento);
void AddNOG_fim(LG *lista, NOG *elemento);
NOG *RemNOG_inicio(LG *lista);
void MostrarLG(LG *lista, void (MostrarInfo)(void *));
void DestruirLG(LG *lista, void (DestruirInfo)(void *));

#endif