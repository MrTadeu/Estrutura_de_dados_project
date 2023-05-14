#ifndef HISTORICO_H_INCLUDED
#define HISTORICO_H_INCLUDED

#include "../includes/ListaLigada.h"
#include "../includes/TipoDados.h"

typedef struct{ 
    // Vetor de listas
    Lista **alfabeto; // Vai servir para procurar pelo nome do ciente
    Lista **caixasHistorico; // Vai servir para procurar pelo id de caixa
}HistoricoHashTable;

void initinitHistorico();
int alfabetoIndex(char *nome);
void *criarHistorico();

#endif