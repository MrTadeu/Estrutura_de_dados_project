#include "../includes/TipoDados.h"

void atualizarAtrasos(Lista *lista, int atraso){
    if(!head){
        printf("\t\n[red]Error![/red] NULL element.\n");
        return;
    }
    Elemento *aux = lista->head;
    ClienteStruct *pessoa;
    while(aux){
        pessoa = (ClienteStruct *) aux->Info;
        pessoa->tempoEstimadoCaixa += atraso;
    }
}

fecharUrgencia(Lista *lista){
    
}

void atenderPessoa(ClienteStruct *pessoa){
    int index = pesquisaClienteVetor(pessoa);
    batenteChange(&Clientes[index], &Clientes[n_clientesAtivos-1], sizeof(ClienteStruct), &n_clientesAtivos, '-');
    return RemElementoInicio(caixa->listaPessoas);
}

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

        atrasoMaximo = cliente->tempoEstimadoCaixa * caixa->percentagemParaAtraso;
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
