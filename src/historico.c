#include "../includes/TipoDados.h"

void initHistorico(){
    for (int i = 0; i < 26; i++)
        HistoricoDados.historico[i] = criarLista();
}

void initDadosEstatisticos(){
    dadosEstatisticos = (DadosEstatisticosStruct*) malloc(sizeof(DadosEstatisticosStruct));

    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 6; j++){
            dadosEstatisticos->dadosIntantaneosdiarios[i][j].numeroClienteFilaCadaCaixa = (int*) malloc(sizeof(int)*Opcoes.numCaixasTotal);
            dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEsperaCadaCaixa = (int*) malloc(sizeof(int)*Opcoes.numCaixasTotal);

            dadosEstatisticos->mediaDiaria.numeroMedioClienteFilaCadaCaixa = (float*) malloc(sizeof(float)*Opcoes.numCaixasTotal);
            dadosEstatisticos->mediaDiaria.tempoMedioEsperaCadaCaixa = (float*) malloc(sizeof(float)*Opcoes.numCaixasTotal);
        }
    }
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
    return -1;
}

void *criarSubStructClienteHistorico(ClienteStruct *cliente){
    HistoricoSubStructCliente *elementoCliente = (HistoricoSubStructCliente *) malloc(sizeof(HistoricoSubStructCliente));
    elementoCliente->nome = (char*) malloc(strlen(cliente->nome)+1);
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista**) malloc(sizeof(Lista*)*Opcoes.numCaixasTotal);
    for (int i = 0; i < Opcoes.numCaixasTotal; i++)
        elementoCliente->caixas[i] = criarLista();
    return elementoCliente;
}

void *criarInfoHistorico(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido){
    ClienteStruct *pessoa = (ClienteStruct*) caixa->listaPessoas->head->Info;
    HistoricoSubStructInfo *infoHistorico = (HistoricoSubStructInfo*) malloc(sizeof(HistoricoSubStructInfo));
    infoHistorico->funcionario = caixa->funcionario;
    infoHistorico->listaProdutos = pessoa->listaProdutos;
    infoHistorico->tempoEstimadoCaixa = pessoa->tempoEstimadoCaixa;
    infoHistorico->tempoAtraso = pessoa->tempoAtraso;
    infoHistorico->movimentoCartaoCliente = movimentoSaldoCartao;
    infoHistorico->precoTotal = pessoa->precoTotalProdutos;
    infoHistorico->valorProdutoOferecido = valorProdutoOferecido;
    // infoHistorico->dataTransacao = convertTimeDate(getDataMilliseconds()); 
    // infoHistorico.hora
    return infoHistorico;
}


//              |a|b|c|d|...         __HistoricoSubStructCliente
//              |        ___________/      /
//              V       V                 /
//            |Nome, Id|  --> |1|2|3|4|5|...
//                             | 
//                          |Info|  <--- HistoricoSubStructInfo

void guardarHistorico(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido){
    if(!caixa){
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");         
        return;                                                       
    } 
    if(!caixa->listaPessoas->head->Info){                                                
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");        
        return;                                                         
    }

    ClienteStruct* pessoaAtendida = (ClienteStruct*) malloc(sizeof(ClienteStruct));
    pthread_mutex_lock(&ClientesLock);
    memcpy(pessoaAtendida, caixa->listaPessoas->head->Info, sizeof(ClienteStruct));     
    pthread_mutex_unlock(&ClientesLock);

    FuncionarioStruct* funcionario = (FuncionarioStruct*) malloc(sizeof(FuncionarioStruct));
    memcpy(funcionario, caixa->funcionario, sizeof(FuncionarioStruct));


    int flag = 0, hashIndex = alfabetoIndex(pessoaAtendida->nome); 
    Elemento *Aux = HistoricoDados.historico[hashIndex]->head;
    while(Aux){
        HistoricoSubStructCliente *guardado = (HistoricoSubStructCliente*) Aux->Info;
        if(strcmp(pessoaAtendida->nome, guardado->nome) == 0 && pessoaAtendida->id == guardado->id){
            AddElementoInicio(guardado->caixas[caixa->id-1], criarElemento(criarInfoHistorico(caixa, movimentoSaldoCartao, valorProdutoOferecido)));
            flag = 1;
            break;
        }
        Aux = Aux->next;
    }
    if(!flag){
        AddElementoInicio(HistoricoDados.historico[hashIndex], criarElemento(criarSubStructClienteHistorico(pessoaAtendida)));
        guardarHistorico(caixa, movimentoSaldoCartao, valorProdutoOferecido);
    }
       
}

/* void atualizarDadosEstatisticos(){

} */