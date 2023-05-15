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

ClienteHistoricoStruct *criarElementoClienteHistorico(ClienteStruct *cliente){
    ClienteHistoricoStruct *elementoCliente = (ClienteHistoricoStruct *) malloc(sizeof(ClienteHistoricoStruct));
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista**) malloc(sizeof(Lista*)*Opcoes.numCaixasTotal);
    for (int i = 0; i < Opcoes.numCaixasTotal; i++)
        elementoCliente->caixas[i] = criarLista();
    return elementoCliente;
}

void *criarInfoHistorico(CaixaStruct *caixa, ClienteStruct *pessoa, float movimentoSaldoCartao){
    TransacaoHistoricoStruct *infoHistorico = (TransacaoHistoricoStruct*) malloc(sizeof(TransacaoHistoricoStruct));
    infoHistorico->funcionario = caixa->funcionario;
    infoHistorico->listaProdutos = pessoa->listaProdutos;

    infoHistorico->tempoEstimadoCaixa = pessoa->tempoEstimadoCaixa;
    infoHistorico->tempoAtraso = pessoa->tempoAtraso;
    infoHistorico->movimentoCartaoCliente = movimentoSaldoCartao;
    /* infoHistorico->dataTransacao =  */
    return infoHistorico;
}

int inserirNoHistorico(int hashIndex, CaixaStruct *caixa, ClienteStruct *cliente, float movimentoSaldoCartao){
    if(!cliente){
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");
        return 0;
    }

    int flag = 0;
    Elemento *Aux = HistoricoDados.historico[hashIndex]->head;
    while(Aux){
        ClienteHistoricoStruct *guardado = Aux->Info;
        if(strcmp(cliente->nome, guardado->nome) == 0 && cliente->id == guardado->id){
            AddElementoInicio(guardado->caixas[caixa->id-1], criarElemento(criarInfoHistorico(caixa, cliente, movimentoSaldoCartao)));
            flag = 1;
            break;
        }
    }
    if(!flag){
        AddElementoInicio(HistoricoDados.historico[hashIndex], criarElemento(criarElementoClienteHistorico(cliente)));
    }
}

void guardarHistorico(Elemento *pessoaAtendida, CaixaStruct *caixa, float movimentoSaldoCartao){//enviar isto e o saldo antigo e atualizado em estrutura
    if(!pessoaAtendida){
        printf("\n\t[red]Error![/red] Given elemento is NULL\n");
        return;
    }
    if(!caixa){
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }



}