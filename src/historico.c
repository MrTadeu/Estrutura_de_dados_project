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

void criarElementoClienteHistorico(ClienteStruct *cliente){
    ClienteHistoricoStruct *elementoCliente = (ClienteHistoricoStruct *) malloc(sizeof(ClienteHistoricoStruct));
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista**) malloc(sizeof(Lista*)*Opcoes.numCaixasTotal);
    for (int i = 0; i < Opcoes.numCaixasTotal; i++)
        elementoCliente->caixas[i] = criarLista();
}

/* void *criarInfoHistorico(CaixaStruct *caixa, ClienteStruct *pessoa){
    TransacaoHistoricoStruct *infoHistorico = (TransacaoHistoricoStruct*) malloc(sizeof(TransacaoHistoricoStruct));
    infoHistorico->caixa = caixa;
    infoHistorico->pessoa = pessoa;
    return infoHistorico;
} */

int inserirNoHistorico(CaixaStruct *caixa, ClienteStruct *cliente){
    if(!cliente){
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");
        return 0;
    }
    
    HistoricoDados.historico[]
}

void guardarHistorico(Elemento * pessoaAtendida, CaixaStruct *caixa){
    if(!pessoaAtendida){
        printf("\n\t[red]Error![/red] Given elemento is NULL\n");
        return;
    }
    if(!caixa){
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }


}