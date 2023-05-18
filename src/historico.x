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

void *criarSubStructClienteHistorico(ClienteStruct *cliente){
    HistoricoSubStructCliente *elementoCliente = (HistoricoSubStructCliente *) malloc(sizeof(HistoricoSubStructCliente));
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista**) malloc(sizeof(Lista*)*Opcoes.numCaixasTotal);
    for (int i = 0; i < Opcoes.numCaixasTotal; i++)
        elementoCliente->caixas[i] = criarLista();
    return elementoCliente;
}

void *criarInfoHistorico(CaixaStruct *caixa, ClienteStruct *pessoa, float movimentoSaldoCartao, float precoTotal){
    HistoricoSubStructInfo *infoHistorico = (HistoricoSubStructInfo*) malloc(sizeof(HistoricoSubStructInfo));
    infoHistorico->funcionario = caixa->funcionario;
    infoHistorico->listaProdutos = pessoa->listaProdutos;
    infoHistorico->tempoEstimadoCaixa = pessoa->tempoEstimadoCaixa;
    infoHistorico->tempoAtraso = pessoa->tempoAtraso;
    infoHistorico->movimentoCartaoCliente = movimentoSaldoCartao;
    infoHistorico->precoTotal = precoTotal;
    infoHistorico->dataTransacao = convertTimeDate(getDataMilliseconds()); 
    return infoHistorico;
}

void guardarHistorico(ClienteStruct *pessoaAtendida, CaixaStruct *caixa, float movimentoSaldoCartao, float precoTotal){
    if(!pessoaAtendida){
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");        //    |a|b|c|d|...        __//!HistoricoSubStructCliente 
        return;                                                         //     |       __________/      /
    }                                                                   //     |      V                V
    if(!caixa){                                                         //   |Nome, Id|  --> |1|2|3|4|5|...
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");          //                    | 
        return;                                                         //                  |Info|  //!<--- HistoricoSubStructInfo
    }

    int flag = 0, hashIndex = alfabetoIndex(pessoaAtendida->nome); 
    Elemento *Aux = HistoricoDados.historico[hashIndex]->head;
    while(Aux){
        HistoricoSubStructCliente *guardado = (HistoricoSubStructCliente*) Aux->Info;
        if(strcmp(cliente->nome, guardado->nome) == 0 && cliente->id == guardado->id){
            AddElementoInicio(guardado->caixas[caixa->id-1], criarElemento(criarInfoHistorico(caixa, pessoaAtendida, movimentoSaldoCartao, precoTotal)));
            flag = 1;
            break;
        }
    }
    if(!flag)
        AddElementoInicio(HistoricoDados.historico[hashIndex], criarElemento(criarSubStructClienteHistorico(pessoaAtendida)));
}