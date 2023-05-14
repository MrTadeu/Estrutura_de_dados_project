#include "../includes/Historico.h"

void initHistorico(){
     = (Lista**) malloc(sizeof(Lista*)*26); // 26 é o numero de letras no alfabeto
    for (int i = 0; i < 26; i++){
        historico.alfabeto[i] = criarLista();
    }
}

int alfabetoIndex(char *nome){

}

void *criarHistorico(){

}