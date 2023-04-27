#include "../includes/TipoDados.h"


void criarCaixaInit(){
    for (size_t i = 0; i < Opcoes.numCaixasTotal; i++){
        CaixaStruct *caixa = (CaixaStruct *) malloc(sizeof(CaixaStruct));
        caixa->id = i;
        caixa->aberta = 0;
        caixa->fecharUrgencia = 0;
        caixa->tempoTotalEspera = 0;
        caixa->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        caixa->listaPessoas = criarLista(); 
        AddElementoFim(Global.caixas, criarElemento(caixa));
    }
}

/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/
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
        aux = aux->next;
    }
}

/* fecharUrgencia(Lista *lista){
    
} */

/* void AtualizarDadosTemposCaixa(CaixaStruct *caixa){
    if(!caixa){
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    } 
    Elemento *aux = caixa->listaPessoas->head;

    int countTempoEstimadoCaixa = 0;
    while (aux){
        ClienteStruct *cliente = (ClienteStruct *)aux->Info;

        countTempoEstimadoCaixa += cliente->tempoEstimadoCaixa;
        cliente->tempoEstimadoFila = countTempoEstimadoCaixa - cliente->tempoEstimadoCaixa;

        aux = aux->next;
    }
    caixa->tempoTotalEspera = countTempoEstimadoCaixa;
} */

Elemento *atenderPessoa(CaixaStruct *caixa){
    if (!caixa){
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");
        return NULL;
    }
    if(!caixa->listaPessoas->head){
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");
        return NULL;
    }
    ClienteStruct *cliente = (ClienteStruct *) caixa->listaPessoas->head->Info;
    cliente->tempoEstimadoFila = 0;
    int tempo = cliente->tempoEstimadoCaixa + cliente->tempoAtraso;

    while(tempo){
        dormir(1000);
        tempo--;
        if (cliente->tempoEstimadoCaixa){
            cliente->tempoEstimadoCaixa--;
            caixa->tempoTotalEspera--;
        }
        else if (cliente->tempoAtraso > 0) cliente->tempoAtraso--;
    }
    caixa->tempoTotalEspera -= cliente->tempoEstimadoCaixa;
    cliente->tempoEstimadoCaixa = 0;

    //Remover da fila
    return RemElementoInicio(caixa->listaPessoas);
}
/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

/* CaixaStruct gerarCaixa(){ // gerarCaixa na ordem
    
}*/

CaixaStruct *MelhorCaixa(){ // o melhor index que tem o menor tempo
    Elemento *caixaAux = Global.caixas->head;
    CaixaStruct *menor = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *SegundaMenor = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *temp = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *maior = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *primeiraCaixaFechada = (CaixaStruct *)caixaAux->Info;

    while (caixaAux){
        CaixaStruct *caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
        

        
        if (caixaAuxInfo->aberta == 1 && caixaAuxInfo->tempoTotalEspera < menor->tempoTotalEspera && menor->aberta == 1){
            SegundaMenor = menor;
            menor = caixaAuxInfo;
        }
        else if (caixaAuxInfo->tempoTotalEspera < SegundaMenor->tempoTotalEspera || menor->tempoTotalEspera == SegundaMenor->tempoTotalEspera && caixaAuxInfo->aberta == 1){
            SegundaMenor = caixaAuxInfo;
        }
        
        if (caixaAuxInfo->aberta == 1 && caixaAuxInfo->tempoTotalEspera > maior->tempoTotalEspera && maior->aberta == 1){
            maior = caixaAuxInfo;
        }
        if (caixaAuxInfo->aberta == 0 && primeiraCaixaFechada == (CaixaStruct *)Global.caixas->head->Info){
            primeiraCaixaFechada = caixaAuxInfo;
        }
        caixaAux = caixaAux->next;
        /* if (menor == ((CaixaStruct *)caixaAux->Info) && caixaAux->next == NULL){
            SegundaMenor = temp;
        }
        else{
            if (caixaAuxInfo->aberta == 1 && caixaAuxInfo->tempoTotalEspera < SegundaMenor->tempoTotalEspera){
                temp = menor;
                SegundaMenor = caixaAuxInfo;
            }
        } */
    }

    if (menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior){
        Opcoes.numCaixasAbertas++;
        primeiraCaixaFechada->aberta = 1;
        return primeiraCaixaFechada;
    }
    if (maior->tempoTotalEspera < Opcoes.TempoLimiteInferior && menor != SegundaMenor && Opcoes.numCaixasAbertas > 1){
        Opcoes.numCaixasAbertas--;
        menor->aberta = 0;
        return SegundaMenor;
    }
    return menor;

/*     CaixaStruct *caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
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
    while(caixaAux){ // procura o caixa com menos tempo
        caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
        if(caixaAuxInfo->tempoTotalEspera < menorInfo->tempoTotalEspera && caixaAuxInfo->aberta == 1){
            menorInfo = caixaAuxInfo;
            index = pos;
        }
        caixaAux = caixaAux->next;
        pos++;
    }
    return index; */
}

void SelecionarCaixa(){ // seleciona e adiciona a melhor caixa para o cliente
    Elemento *pessoaEnviar = Global.PessoasAcabaramTempoDeCompra->head;
    printc("\n\n\t[green]OLa1[/green]\n");
    CaixaStruct melhorCaixa;
    while(pessoaEnviar){

        melhorCaixa = MelhorCaixa();

        //Atualizar o tempo de atraso consoante a pessoa a ser atendida no momento
        printc("\n\n\t[greenTESTE[/green]\n");
        ((ClienteStruct *)pessoaEnviar->Info)->tempoAtraso = ((ClienteStruct *)melhorCaixa->listaPessoas->head->Info)->tempoAtraso; 

        printc("\n\n\t[green]PESSSOA ADD Caixa[/green]\n");
        AddElementoFim(melhorCaixa->listaPessoas, criarElemento(pessoaEnviar->Info));
        RemElementoInicio(Global.PessoasAcabaramTempoDeCompra);

        pessoaEnviar = pessoaEnviar->next;
    }
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

void *ThreadCaixa(CaixaStruct *caixa){

    int atraso, n_vendas = 0;
    float atrasoMaximo, atrasoMedio = 0;
    ClienteStruct *pessoaEmAtendimento;

    while(caixa->listaPessoas->quantidadeElementos > 0){
        if(caixa->fecharUrgencia){
            /* fecharUrgencia(caixa->listaPessoas); */
        }
        pessoaEmAtendimento = (ClienteStruct *) caixa->listaPessoas->head->Info;

        atrasoMaximo = pessoaEmAtendimento->tempoEstimadoCaixa * Opcoes.percentagemParaAtraso;
        atraso = Aleatorio(-atrasoMaximo, atrasoMaximo);
        atualizarAtrasos(caixa->listaPessoas, atraso);
        printc("\n\n\t[green]ATRASOS ATUALIZADOS[/green]\n");

        AddElementoFim(Global.PessoasAtendidas, atenderPessoa(caixa));
        printc("\n\n\t[green]PESSOA ATENDIDA[/green]\n");

        atrasoMedio += atraso;
        n_vendas++;
    }
    atrasoMedio /= n_vendas;
    atualizarDadosFuncionario(caixa->funcionario, atrasoMedio, n_vendas);
    return NULL;
}

