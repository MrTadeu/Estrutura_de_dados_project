#include "../includes/TipoDados.h"

void atualizarAtrasos(Lista *lista, int atraso){
    if(!lista){
        printf("\t\n[red]Error![/red] lista NULL.\n");
        return;
    }
    Elemento *aux = lista->head;
    ClienteStruct *pessoa;
    while(aux){
        pessoa = (ClienteStruct *) aux->Info;
        pessoa->tempoAtraso += atraso;
    }
}

/* fecharUrgencia(Lista *lista){
    
} */

void DesocuparCliente(ClienteStruct *pessoa){
    int index = pesquisarClienteVetor(pessoa);
    batenteChange(&Clientes[index], &Clientes[n_clientesAtivos-1], sizeof(ClienteStruct), &n_clientesAtivos, '-');
    pessoa->ativo = 0;
}

void AtualizarDadosTemposCaixa(CaixaStruct *caixa){
    if (!caixa) return;
    Elemento *aux = caixa->listaPessoas->head;

    int countTempoEstimadoCaixa = 0;
    while (aux){
        ClienteStruct *cliente = (ClienteStruct *)aux->Info;

        countTempoEstimadoCaixa += cliente->tempoEstimadoCaixa;
        cliente->tempoEstimadoFila = countTempoEstimadoCaixa - cliente->tempoEstimadoCaixa;

        aux = aux->next;
    }
    caixa->tempoTotalEspera = countTempoEstimadoCaixa;
}

void AtenderClientes(CaixaStruct *caixa, ClienteStruct *clientes){
    if (!caixa || !clientes) return;
    //Atualizar dados
    DesocuparCliente(clientes);
    
    clientes->tempoEstimadoFila = 0;
    int tempo = clientes->tempoEstimadoCaixa + clientes->tempoAtraso;

    //Adicionar no ficheiro Histórico
    /*   DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD    FUNÇÃO   DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD */

    /* while (tempo >= 0){
        if (clientes->tempoAtraso < 0){
            if (tempo == 0){
                caixa->tempoTotalEspera -= clientes->tempoEstimadoCaixa;
                clientes->tempoEstimadoCaixa = 0;
                break;
            }
            clientes->tempoEstimadoCaixa--;
            caixa->tempoTotalEspera--;
        }
        else if (clientes->tempoAtraso == 0){
            if (tempo == 0){
                break;
            }
        }
        tempo--;
        dormir(1000);
        if (clientes->tempoAtraso > 0){
            if (clientes->tempoEstimadoCaixa != 0){
                clientes->tempoEstimadoCaixa--;
                caixa->tempoTotalEspera--;
                continue;
            }
            clientes->tempoAtraso--;
        }
        
    } */
    while (tempo){
        dormir(1000);
        tempo--;
        if (clientes->tempoEstimadoCaixa){
            clientes->tempoEstimadoCaixa--;
            caixa->tempoTotalEspera--;
        }
        else if (clientes->tempoAtraso > 0) Clientes->tempoAtraso--;
    }
    caixa->tempoTotalEspera -= clientes->tempoEstimadoCaixa;
    clientes->tempoEstimadoCaixa = 0;
    
    //Remover da fila
    RemElementoInicio(caixa->listaPessoas);
}


/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

int CaixaIndex(Lista *caixa){ // o melhor index que tem o menor numero de clientes
    int pos = 0, index = 0;
    Elemento *caixaAux = caixa->head;
    Elemento *menor = caixaAux;

    CaixaStruct *caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *menorInfo = (CaixaStruct *)menor->Info;
    if (menorInfo->aberta == 0){ // se o primeiro caixa estiver fechado, procura o primeiro aberto
        menorInfo = caixaAuxInfo;
        index = pos;
        while (menorInfo->aberta == 0 && caixaAux){ // NÃO ESQUECER DE VERIFICAR SE TODAS ESTÃO FECHADAS TRATAR DO ASSUSNTO
            caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
            if(caixaAuxInfo->aberta == 1){
                menorInfo = caixaAuxInfo;
                index = pos;
            }
            caixaAux = caixaAux->next;
            pos++;
        }
    }
    
    pos = 0;
    while(caixaAux){ // procura o caixa com menos clientes
        caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
        if(caixaAuxInfo->tempoTotalEspera < menorInfo->tempoTotalEspera && caixaAuxInfo->aberta == 1){
            menorInfo = caixaAuxInfo;
            index = pos;
        }
        caixaAux = caixaAux->next;
        pos++;
    }
    return index;
}

void SelecionarCaixa(Lista *caixas, Elemento *cliente){ // seleciona (adiciona) a melhor caixa para o cliente
    int index = CaixaIndex(caixas);
    Elemento *caixaAux = caixas->head;
    while(index){
        caixaAux = caixaAux->next;
        index--;
    }
    CaixaStruct *caixaAuxInfo = (CaixaStruct* )caixaAux->Info;
    AddElementoFim(caixaAuxInfo->listaPessoas, cliente);
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

void *ThreadCaixa(CaixaStruct *caixa){

    int atraso, n_vendas = 0;
    float atrasoMaximo, atrasoMedio;
    Elemento *elemento;
    ClienteStruct *pessoa;

    while(caixa->listaPessoas->quantidadeElementos > 0){
        if(caixa->fecharUrgencia){
            fecharUrgencia(caixa->listaPessoas);
        }
        pessoa = (ClienteStruct *) caixa->listaPessoas->head->Info;

        atrasoMaximo = pessoa->tempoEstimadoCaixa * caixa->percentagemParaAtraso;
        atraso = Aleatorio(-atrasoMaximo, atrasoMaximo);
        atualizarAtrasos(caixa->listaPessoas, atraso);
        

        






        atrasoMedio += atraso;
        n_vendas++;
        atenderPessoa(pessoa);
    }
    atrasoMedio /= n_vendas;
    caixa->funcionario->atrasoMedio = (caixa->funcionario->atrasoMedio + atrasoMedio) / 2;
    caixa->funcionario->experiencia += n_vendas;
}

