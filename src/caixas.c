#include "../includes/TipoDados.h"

void criarCaixaInit(){
    Global.caixas = criarLista();
    for (int i = 0; i < Opcoes.numCaixasTotal; i++){
        CaixaStruct *caixa = (CaixaStruct *) malloc(sizeof(CaixaStruct));
        caixa->id = i+1;
        caixa->aberta = 0;
        caixa->fecharUrgencia = 0;
        caixa->tempoTotalEspera = 0;
        caixa->funcionario =  NULL/* (FuncionarioStruct *) escolherFuncionarios() */;
        caixa->listaPessoas = criarLista(); 
        AddElementoFim(Global.caixas, criarElemento(caixa));
    }
    /* Elemento *aux = Global.caixas->head;
    while(aux){
        CaixaStruct *caixa = (CaixaStruct *) aux->Info;
        printf("\n\tCaixa %d: %s", caixa->id, caixa->funcionario->nome);
        aux = aux->next;
    }*/
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

    pthread_mutex_lock(&vetorLock);
    DesocuparCliente(cliente);
    pthread_mutex_unlock(&vetorLock);


    //Remover da fila
    return RemElementoInicio(caixa->listaPessoas);
}
/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

/* CaixaStruct gerarCaixa(){ // gerarCaixa na ordem
    
}*/

CaixaStruct *MelhorCaixa(){ // o melhor index que tem o menor tempo
    Elemento *caixaAux = Global.caixas->head;
    CaixaStruct *maior = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *menor = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *SegundaMenor = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *primeiraCaixaFechada = (CaixaStruct *)caixaAux->Info;

    while (caixaAux){
        CaixaStruct *caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
        if (caixaAuxInfo->aberta == 1 && caixaAuxInfo->tempoTotalEspera < menor->tempoTotalEspera && menor->aberta == 1){
            SegundaMenor = menor;
            menor = caixaAuxInfo;
        }
        else if ((caixaAuxInfo->tempoTotalEspera < SegundaMenor->tempoTotalEspera || menor->tempoTotalEspera == SegundaMenor->tempoTotalEspera) && caixaAuxInfo->aberta == 1){ // pode acontecer de ter a menor a primeira e a segundaMenor ser o mesmo por isso com a possibilidade de ser o mesmo fazemos o || menor->tempoTotalEspera == SegundaMenor->tempoTotalEspera (Se tivermos uma caixa aberta SegundaMenor == menor == maior)
            SegundaMenor = caixaAuxInfo;
        }
        
        if (caixaAuxInfo->aberta == 1 && caixaAuxInfo->tempoTotalEspera > maior->tempoTotalEspera && maior->aberta == 1){
            maior = caixaAuxInfo;
        }
        if (caixaAuxInfo->aberta == 0 && primeiraCaixaFechada == (CaixaStruct *)Global.caixas->head->Info){
            primeiraCaixaFechada = caixaAuxInfo;
        }

        caixaAux = caixaAux->next;
    }

    if(Opcoes.numCaixasAbertas == 0){
        menor->aberta = 1;
        Opcoes.numCaixasAbertas++;
        printc("\n\tmenor [green]Caixa aberta! ID:%d  aberta?%d[/green]", menor->id, menor->aberta);
        printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas);
        return menor;
    }
    printf("numCaixasAbertas %d numCaixasTotal %d", Opcoes.numCaixasAbertas, Opcoes.numCaixasTotal);
    
    if (menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior && Opcoes.numCaixasAbertas < Opcoes.numCaixasTotal){
        /* if(Opcoes.numCaixasAbertas == Opcoes.numCaixasTotal){
            printc("\n\tmenor [red]Não é possivel abrir mais caixas! ID:%d  aberta?%d[/red]", menor->id, menor->aberta);
            return NULL;
        } */
        Opcoes.numCaixasAbertas++;
        primeiraCaixaFechada->aberta = 1;
        printc("\n\tprimeiraCaixaFechada [green]Caixa aberta! ID:%d  aberta?%d[/green]", primeiraCaixaFechada->id, primeiraCaixaFechada->aberta);
        printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas);
        return primeiraCaixaFechada;
    }
    if (maior->tempoTotalEspera < Opcoes.TempoLimiteInferior && menor != SegundaMenor && Opcoes.numCaixasAbertas > 1){ // SegundaMenor == menor == maior??????? não pode fechar se todas forem iguais por isso Opcoes.numCaixasAbertas > 1
        Opcoes.numCaixasAbertas--;
        menor->aberta = 0;
        printc("\n\tSegundaMenor [green]Caixa aberta! ID:%d  aberta?%d[/green]", SegundaMenor->id, SegundaMenor->aberta);
        printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas);
        return SegundaMenor;
    }
    printc("\n\tmenor [green]Caixa aberta! ID:%d  aberta?%d[/green]", menor->id, menor->aberta);
    printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas);
    if (Opcoes.numCaixasAbertas == Opcoes.numCaixasTotal && menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior){
        /* printc("\n\tmenor [red]Não é possivel abrir mais caixas! ID:%d  aberta?%d[/red]", menor->id, menor->aberta); */
        return NULL;
    }
    return menor;
}

void SelecionarCaixa(){ // seleciona e adiciona a melhor caixa para o cliente
    Elemento *pessoaEnviar = Global.PessoasAcabaramTempoDeCompra->head;

    CaixaStruct* melhorCaixa;
    while(pessoaEnviar){

        melhorCaixa = MelhorCaixa();
        if (melhorCaixa == NULL) return;
        
        printc("\n\tmelhorCaixa [green]Caixa aberta! ID:%d  aberta?%d[/green]", melhorCaixa->id, melhorCaixa->aberta);
        if (Opcoes.VerTransacoes == 1 && Opcoes.lojaAberta == 1){
            printc("\n\n\t[green]PESSSOA ADD:[/green] %s tempoDecompra: %d  [magenta]---Caixa (id) %d--->[/magenta] [red]funcionario:[/red] %s [red]Tempo de Caixa:[/red] %d\n", ((ClienteStruct*)pessoaEnviar->Info)->nome, ((ClienteStruct*)pessoaEnviar->Info)->tempoEstimadoCaixa, melhorCaixa->id, melhorCaixa->funcionario->nome, melhorCaixa->tempoTotalEspera);
        }

        //Atualizar o tempo de atraso consoante a pessoa a ser atendida no momento
        /* ((ClienteStruct *)pessoaEnviar->Info)->tempoAtraso = ((ClienteStruct *)melhorCaixa->listaPessoas->head->Info)->tempoAtraso; */ // O FILHO DA PUTA TRAVA AQUI!!!! VER ISSO DPS

        AddElementoFim(melhorCaixa->listaPessoas, pessoaEnviar);
        melhorCaixa->tempoTotalEspera +=((ClienteStruct *)pessoaEnviar->Info)->tempoEstimadoCaixa;

        pthread_mutex_lock(&listaLock);
        RemElementoInicio(Global.PessoasAcabaramTempoDeCompra); 
        pthread_mutex_unlock(&listaLock);

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

        //<-----Atualizar Historico Aqui  (tem de ser antes de atender pessoa) ----->//

        destruirElemento(atenderPessoa(caixa), destruirCliente);
        printc("\n\n\t[green]PESSOA ATENDIDA[/green]\n");

        atrasoMedio += atraso;
        n_vendas++;
    }
    atrasoMedio /= n_vendas;
    atualizarDadosFuncionario(caixa->funcionario, atrasoMedio, n_vendas);
    return NULL;
}

