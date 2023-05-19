#include "../includes/TipoDados.h"

void criarCaixaInit(){
    Global.caixas = criarLista();
    for (int i = 0; i < Opcoes.numCaixasTotal; i++){
        CaixaStruct *caixa = (CaixaStruct *) malloc(sizeof(CaixaStruct));
        caixa->id = i+1;
        pthread_mutex_init(&caixa->lock, NULL);

        if(i < Opcoes.numCaixasAbertas){
            caixa->aberta = 1;
            caixa->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        else{
            caixa->aberta = 0;
            caixa->funcionario = NULL;
        }
            
        caixa->fecharUrgencia = 0;
        caixa->tempoTotalEspera = 0;
        
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

void destruirCaixa(void *Caixa){
    destruirLista(((CaixaStruct *)Caixa)->listaPessoas, destruirCliente);
    free(Caixa);
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

void atenderPessoa(CaixaStruct *caixa){
    if (!caixa || caixa->listaPessoas->head == NULL){
        printc("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }
    ClienteStruct *cliente = (ClienteStruct *) caixa->listaPessoas->head->Info;

    cliente->tempoEstimadoFila = 0;
    float tempoEstimadoCaixaAux = cliente->tempoEstimadoCaixa, tempoAtrasoAux = cliente->tempoAtraso;
    int tempo = (int) (cliente->tempoEstimadoCaixa + cliente->tempoAtraso)*1000;

    while(tempo){
        if(tempo < 1000){
            dormir(tempo);
            tempo = 0;
        }
        else{
            dormir(1000);
            tempo -= 1000;
        }
        if (Opcoes.VerTransacoes == 1 && Opcoes.lojaAberta == 1){
            printf("\nCaixa %dº Pessoa: %s Tempo: %d",caixa->id, cliente->nome, tempo);
        }
        if (cliente->tempoEstimadoCaixa){
            cliente->tempoEstimadoCaixa--;
            caixa->tempoTotalEspera--;
        }
        else if (cliente->tempoAtraso > 0) cliente->tempoAtraso--;
    } 
    caixa->tempoTotalEspera -= cliente->tempoEstimadoCaixa;
    cliente->tempoEstimadoCaixa = tempoEstimadoCaixaAux;
    cliente->tempoAtraso = tempoAtrasoAux;
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

    //SE NÃO HOUVER CAIXAS ABERTAS ABRIR A PRIMEIRA
    if(Opcoes.numCaixasAbertas == 0){
        menor->aberta = 1;
        Opcoes.numCaixasAbertas++;
        if (menor->funcionario == NULL){ 
            menor->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        if (menor->listaPessoas->head == NULL){
            pthread_t threadCaixa;
            pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)menor);
            pthread_detach(threadCaixa);
            
        }
        return menor;
    }

    //ABRIR CAIXA SE O TEMPO DA MENOR CAIXA FOR MAIOR QUE O LIMITE SUPERIOR (CASO EXISTA AINDA CAIXAS FECHADAS)
    if (menor->tempoTotalEspera >= Opcoes.TempoLimiteSuperior && Opcoes.numCaixasAbertas < Opcoes.numCaixasTotal){ 
        primeiraCaixaFechada->aberta = 1;
        Opcoes.numCaixasAbertas++;
        if (primeiraCaixaFechada->funcionario == NULL){
            primeiraCaixaFechada->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        if (primeiraCaixaFechada->listaPessoas->head == NULL){
            pthread_t threadCaixa;
            pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)primeiraCaixaFechada);
            pthread_detach(threadCaixa);
            
        }
        return primeiraCaixaFechada;
    }

    // FECHAR CAIXA SE O TEMPO DA MAIOR CAIXA FOR MENOR QUE O LIMITE INFERIOR (CASO EXISTA MAIS QUE UMA CAIXA ABERTA)
    if (maior->tempoTotalEspera < Opcoes.TempoLimiteInferior && Opcoes.numCaixasAbertas > 1){
        Opcoes.numCaixasAbertas--;
        menor->aberta = 0;
        return SegundaMenor;
    }

    if(menor->tempoTotalEspera < Opcoes.TempoLimiteSuperior){
        return menor;
    }

    if(menor->tempoTotalEspera >= Opcoes.TempoLimiteSuperior){
        return NULL;
    }

    printc("\n\t[red]Error![/red] Não foi possivel selecionar a melhor caixa\n");
    return NULL;
}

void SelecionarCaixa(){ // seleciona e adiciona a melhor caixa para o cliente
    Elemento *pessoaEnviar = Global.PessoasAcabaramTempoDeCompra->head;


    /* //TESTES
    pthread_mutex_lock(&ClientesLock);
    Elemento *Aux = ((ClienteStruct*)pessoaEnviar)->listaProdutos->head;
    while(Aux){
        ProdutoStruct *x = (ProdutoStruct *)Aux->Info;
        printc("\t\n[blue]ID: %d Nome: %s, Preco: %.2f TCompra: %.2f TCaixa: %.2f[/blue]",x->id, x->nome, x->preco, x->tempoCompra, x->tempoCaixa );
        Aux = Aux->next; 
    }
    pthread_mutex_unlock(&ClientesLock); */



    CaixaStruct* melhorCaixa;
    while(pessoaEnviar != NULL){
        melhorCaixa = MelhorCaixa();
        if (melhorCaixa == NULL) return;
        /* printc("\n\tmelhorCaixa [green]Caixa aberta! ID:%d  aberta?%d[/green]", melhorCaixa->id, melhorCaixa->aberta); */
        /* if (Opcoes.VerTransacoes == 1 && Opcoes.lojaAberta == 1){
            printc("\n\n\t[green]PESSSOA ADD:[/green] %s tempoDecompra: %d  [magenta]---Caixa (id) %d--->[/magenta] [red]funcionario:[/red] %s [red]Tempo de Caixa:[/red] %d\n", ((ClienteStruct*)pessoaEnviar->Info)->nome, ((ClienteStruct*)pessoaEnviar->Info)->tempoEstimadoCaixa, melhorCaixa->id, melhorCaixa->funcionario->nome, melhorCaixa->tempoTotalEspera);
        } */

        pthread_mutex_lock(&melhorCaixa->lock);
        AddElementoFim(melhorCaixa->listaPessoas, pessoaEnviar);
        melhorCaixa->tempoTotalEspera += ((ClienteStruct *)pessoaEnviar->Info)->tempoEstimadoCaixa;
        pthread_mutex_unlock(&melhorCaixa->lock);

        pthread_mutex_lock(&ClientesLock);
        ((ClienteStruct*)pessoaEnviar->Info)->tempoAtraso = ((ClienteStruct*) melhorCaixa->listaPessoas->head->Info)->tempoAtraso;
        if (Opcoes.VerTransacoes == 1 && Opcoes.lojaAberta == 1){
            printc("\n\n[green]Tempo de atraso: %f[/green]", ((ClienteStruct*) melhorCaixa->listaPessoas->head->Info)->tempoAtraso);
            printc("\n[green]novo tempo de atraso: %f[/green]", ((ClienteStruct*)pessoaEnviar->Info)->tempoAtraso);
        }
        pthread_mutex_unlock(&ClientesLock);

        pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
        RemElementoInicio(Global.PessoasAcabaramTempoDeCompra); 
        pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);

        pessoaEnviar = pessoaEnviar->next;
    }
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

void *ThreadCaixa(void *arg){
    CaixaStruct *caixa = (CaixaStruct *) arg;
    int n_vendas = 0;
    float atrasoMaximo, atrasoMedio = 0, atrasoSum = 0, valorProdutoOferecido = 0.0, atraso;
    ClienteStruct *pessoaEmAtendimento;
    
    while(caixa->listaPessoas->quantidadeElementos > 0){
        pessoaEmAtendimento = (ClienteStruct *) caixa->listaPessoas->head->Info;
        /* fecharUrgencia(caixa->listaPessoas); */
        
        if(pessoaEmAtendimento->tempoAtraso > Opcoes.tempoAtrasoMaximoBrinde)
            valorProdutoOferecido = oferecerBrinde(pessoaEmAtendimento);

        //ATRASOS ATUALIZADOS
        atrasoMaximo = pessoaEmAtendimento->tempoEstimadoCaixa * Opcoes.percentagemParaAtraso;
        atraso = 999.0;/* Aleatorio(-atrasoMaximo, atrasoMaximo); */
        pthread_mutex_lock(&caixa->lock);
        atualizarAtrasos(caixa->listaPessoas, atraso);
        pthread_mutex_unlock(&caixa->lock);

        
        
        //ATUALIZAÇÃO DE SALDO CARTÃO CLIENTE   
        float movimentoSaldoCliente = atualizarSaldoCliente(pessoaEmAtendimento);

        atenderPessoa(caixa); // simula os tempos e atualiza valores em tempo real para melhor precisao
        
        //guardarhistorico
        guardarHistorico(caixa, movimentoSaldoCliente, valorProdutoOferecido);

        //Remover da fila
        pthread_mutex_lock(&caixa->lock);
        free(RemElementoInicio(caixa->listaPessoas)); // Free do elemento, nao da pessoa em si
        pthread_mutex_unlock(&caixa->lock);


        //Desocupar pessoa
        pthread_mutex_lock(&ClientesLock);
        DesocuparCliente(pessoaEmAtendimento);
        pthread_mutex_unlock(&ClientesLock);

        atrasoSum += atraso;
        n_vendas++;
        atrasoMedio = atrasoSum / n_vendas;
        atualizarDadosFuncionario(caixa->funcionario, atrasoMedio);
    }
    //Por a zero os tempos para reutilizacao da caixa
    return NULL;
}