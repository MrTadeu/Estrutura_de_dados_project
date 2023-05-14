#include "../includes/TipoDados.h"

void initHistorico(){
    for (int i = 0; i < 26; i++)
        historico.alfabeto[i] = criarLista();
}

int alfabetoIndex(char *nome){
    if(!nome){
        printf("\n\t[red]Error![/red] Given name is NULL\n");
        return -1;
    }
    if(nome[0] >= 65 && nome[0] <= 90)
        return nome[0] - 65;
    if(nome[0] >= 97 && nome[0] <= 122)
        return nome[0] - 97;
}

void *criarHistorico(CaixaStruct *caixa, ClienteStruct *pessoa){
    HistoricoStruct *infoHistorico = (HistoricoStruct*) malloc(sizeof(HistoricoStruct));
    infoHistorico->caixa = caixa;
    infoHistorico->pessoa = pessoa;
    return infoHistorico;
}

void guardarNoHistorico(Elemento * pessoaAtendida, ){

}