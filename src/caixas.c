#include "../includes/TipoDados.h"

void criarCaixaInit(){
    Global.caixas = criarLista();
    for (int i = 0; i < Opcoes.numCaixasTotal; i++){
        CaixaStruct *caixa = (CaixaStruct *) malloc(sizeof(CaixaStruct));
        caixa->id = i+1;
        pthread_mutex_init(&caixa->lock, NULL);

        caixa->aberta = 0;
        caixa->threadAberta = 0;
        caixa->funcionario = NULL;
        caixa->fecharUrgencia = 0;
        caixa->tempoTotalEspera = 0;
        
        caixa->listaPessoas = criarLista(); 
        AddElementoFim(Global.caixas, criarElemento(caixa));
    }
}

void destruirCaixa(void *Caixa){
    destruirLista(((CaixaStruct *)Caixa)->listaPessoas, destruirCliente);
    free(Caixa);
}

/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/
void atualizarAtrasos(Lista *lista, ClienteStruct *pessoaEmAtendimento){
    if(!lista){
        printf("\t\n[red]Error![/red] lista NULL.\n");
        return;
    }

    int atrasoMaximo = (int)(pessoaEmAtendimento->tempoEstimadoCaixa * Opcoes.percentagemParaAtraso);
    int atraso = Aleatorio(-atrasoMaximo, atrasoMaximo);
    pessoaEmAtendimento->tempoAtraso = atraso;

    Elemento *aux = lista->head;
    aux = aux->next;
    ClienteStruct *pessoa;
    pthread_mutex_lock(&caixa->lock);
    while(aux){
        pessoa = (ClienteStruct *) aux->Info;
        pessoa->tempoBrinde += atraso;
        aux = aux->next;
    }
    pthread_mutex_unlock(&caixa->lock); 
}

void fecharUrgencia(CaixaStruct *caixa){
    if (!caixa){
        printc("\n\t[red]Error[/red] Given caixa is NULL\n");
        return;
    }
    
    caixa->aberta = 0;
    pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
    caixa->listaPessoas->tail->next = Global.PessoasAcabaramTempoDeCompra->head;
    Global.PessoasAcabaramTempoDeCompra->head = caixa->listaPessoas->head;
    pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);
    caixa->listaPessoas->head = NULL;
    caixa->listaPessoas->quantidadeElementos = 0;
}

void atenderPessoa(CaixaStruct *caixa){
    if (!caixa || caixa->listaPessoas->head == NULL){
        printc("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }
    ClienteStruct *cliente = (ClienteStruct *) caixa->listaPessoas->head->Info;

    cliente->tempoEstimadoFila = 0;
    int tempoEstimadoCaixaAux = cliente->tempoEstimadoCaixa, 
    tempoAtrasoAux = cliente->tempoAtraso,
    tempo = cliente->tempoEstimadoCaixa + cliente->tempoAtraso;

    while(tempo>0){
        (tempo < 1000) ? dormir(tempo), tempo = 0 : dormir(1000), tempo -= 1000;

        if (Opcoes.VerTransacoes == 1 || 1==1){
            printf("\nCaixa %dº Pessoa: %s Tempo: %d",caixa->id, cliente->nome, tempo);
        }
        if (cliente->tempoEstimadoCaixa){
            cliente->tempoEstimadoCaixa--;
            pthread_mutex_lock(&caixa->lock);
            caixa->tempoTotalEspera--;
            pthread_mutex_unlock(&caixa->lock); 
        }
        else if (cliente->tempoAtraso > 0) 
            cliente->tempoAtraso--;
    }
    pthread_mutex_lock(&caixa->lock);
    caixa->tempoTotalEspera -= cliente->tempoEstimadoCaixa;
    pthread_mutex_unlock(&caixa->lock); 
    cliente->tempoEstimadoCaixa = tempoEstimadoCaixaAux;
    cliente->tempoAtraso = tempoAtrasoAux;
}
/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

CaixaStruct *MelhorCaixa(){ // o melhor index que tem o menor tempo
    Elemento *caixaAux = Global.caixas->head;
    CaixaStruct *maior = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *menor = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *SegundaMenor = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *primeiraCaixaFechada = (CaixaStruct *)caixaAux->Info;

    //!IMPEDIR QUE SE MANDE ALGUEM PARA UMA CAIXA FECHADA POR URGENCIA  
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
        if(n_funcionariosAtivos >= n_funcionarios){
            return NULL;
        }
        if (menor->funcionario == NULL){ 
            menor->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        menor->aberta = 1;
        Opcoes.numCaixasAbertas++;
        if (menor->listaPessoas->head == NULL){
            menor->threadAberta = 1;
            pthread_t threadCaixa;
            pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)menor);
            pthread_detach(threadCaixa);
        }
        return menor;
        
    }

    //ABRIR CAIXA SE O TEMPO DA MENOR CAIXA FOR MAIOR QUE O LIMITE SUPERIOR (CASO EXISATA AINDA CAIXAS FECHADAS)
    if (menor->tempoTotalEspera >= Opcoes.TempoLimiteSuperior && Opcoes.numCaixasAbertas < Opcoes.numCaixasTotal){ 
        if(n_funcionariosAtivos >= n_funcionarios){
            return NULL;
        }
        if (primeiraCaixaFechada->funcionario == NULL){
            primeiraCaixaFechada->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        primeiraCaixaFechada->aberta = 1;
        Opcoes.numCaixasAbertas++;
        if (primeiraCaixaFechada->listaPessoas->head == NULL){
            primeiraCaixaFechada->threadAberta = 1;
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

    // SE NAO FECHARMOS CAIXAS OU ABRIRMOS CAIXAS A MELHOR CAIXA É A MENOR
    if(menor->tempoTotalEspera < Opcoes.TempoLimiteSuperior && menor->aberta == 1){
        if(menor->threadAberta == 0){
            menor->threadAberta = 1;
            pthread_t threadCaixa;
            pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)menor);
            pthread_detach(threadCaixa);
        }
        return menor;
    }
    else if(menor->tempoTotalEspera < Opcoes.TempoLimiteSuperior && menor->aberta == 0){
        return NULL;
    }

    if(menor->tempoTotalEspera >= Opcoes.TempoLimiteSuperior){
        return NULL;
    }
    printc("\n\t[red]Error![/red] Não foi possivel selecionar a melhor caixa\n");
    return NULL;
}

void SelecionarCaixa(){ // seleciona e adiciona a melhor caixa para o cliente
    pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
        pthread_mutex_lock(&ClientesLock);
            Elemento *pessoaEnviar = Global.PessoasAcabaramTempoDeCompra->head;
            CaixaStruct* melhorCaixa;
            while(pessoaEnviar != NULL){
                melhorCaixa = MelhorCaixa();
                if (melhorCaixa == NULL){
                    pthread_mutex_unlock(&ClientesLock);
                    pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);
                    return;   
                }
                pthread_mutex_lock(&melhorCaixa->lock);
                    AddElementoFim(melhorCaixa->listaPessoas, RemElementoInicio(Global.PessoasAcabaramTempoDeCompra));
                    //Add info Qt pessoa instante --> threadCalculoEstatistico
                    melhorCaixa->tempoTotalEspera += ((ClienteStruct *)pessoaEnviar->Info)->tempoEstimadoCaixa;
                pthread_mutex_unlock(&melhorCaixa->lock);

                ((ClienteStruct*)pessoaEnviar->Info)->tempoBrinde = ((ClienteStruct*) melhorCaixa->listaPessoas->head->Info)->tempoAtraso;
                if (Opcoes.VerTransacoes == 1 && Opcoes.lojaAberta == 1){
                    printc("\n\n[green]Tempo de atraso: %d[/green]", ((ClienteStruct*) melhorCaixa->listaPessoas->head->Info)->tempoAtraso);
                    printc("\n[green]novo tempo de atraso: %d[/green]", ((ClienteStruct*)pessoaEnviar->Info)->tempoAtraso);
                } 
                pessoaEnviar = pessoaEnviar->next;
            } 
        pthread_mutex_unlock(&ClientesLock);
    pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

void *ThreadCaixa(void *arg){
    CaixaStruct *caixa = (CaixaStruct *) arg;
    int n_vendas = 0, atrasoSum = 0;
    float valorProdutoOferecido = 0.0, movimentoSaldoCliente = 0.0;
    ClienteStruct *pessoaEmAtendimento;

    while(1){
        /* pthread_mutex_lock(&caixa->lock); */
        if(caixa->listaPessoas->quantidadeElementos > 0){
            pessoaEmAtendimento = (ClienteStruct *) caixa->listaPessoas->head->Info;
        }
        else{
            caixa->threadAberta = 0;
            /* pthread_mutex_unlock(&caixa->lock); */
            return NULL;
        }
        printf("\n\n\n\t\t\t\tola %d\n\n\n\n\n\n", caixa->id);
        //ATRASOS ATUALIZADOS
        /* pthread_mutex_lock(&ClientesLock);//todo valgrind */
        printf("\n\n\n\t\t\t\tola1 %d\n\n\n\n\n\n", caixa->id);
        atualizarAtrasos(caixa->listaPessoas, pessoaEmAtendimento);
        printf("\n\n\n\t\t\t\tola2 %d\n\n\n\n\n\n", caixa->id);
        valorProdutoOferecido = oferecerBrinde(pessoaEmAtendimento);
        printf("\n\n\n\t\t\t\tola3 %d\n\n\n\n\n\n", caixa->id);
        movimentoSaldoCliente = atualizarSaldoCliente(pessoaEmAtendimento);
        printf("\n\n\n\t\t\t\tola4 %d\n\n\n\n\n\n", caixa->id);
        atrasoSum += pessoaEmAtendimento->tempoAtraso;
    
        //atenderPessoa(caixa); // simula os tempos e atualiza valores em tempo real para melhor precisao
        printf("\n\n\n\t\t\t\tola5 %d\n\n\n\n\n\n", caixa->id);
        atualizarDadosFuncionario(caixa->funcionario, atrasoSum / ++n_vendas);
        printf("\n\n\n\t\t\t\tola6 %d\n\n\n\n\n\n", caixa->id);

        //guardarhistorico
        /*  AddHistorico_Hash(caixa, movimentoSaldoCliente, valorProdutoOferecido) */;
        printf("\n\n\n\t\t\t\tola7 %d\n\n\n\n\n\n", caixa->id);

        //Add info Qt pessoa instante --> threadCalculoEstatistico
        //Remover da fila
        pthread_mutex_lock(&caixa->lock);
        //RemElementoInicio(caixa->listaPessoas); // Free do elemento, nao da pessoa em si
        pthread_mutex_unlock(&caixa->lock); 

        /* if(caixa->fecharUrgencia)
            fecharUrgencia(caixa); */
            
        //Desocupar pessoa
        /* pthread_mutex_lock(&ClientesLock); */
        //DesocuparCliente(pessoaEmAtendimento);
        /* pthread_mutex_unlock(&ClientesLock); */
        /* pthread_mutex_unlock(&caixa->lock); */
        dormir(100);
    }
    //Por a zero os tempos para reutilizacao da caixa
    caixa->threadAberta = 0;
            printf("\n\n\n\t\t\t\tola12 bye %d\n\n\n\n\n\n", caixa->id);

}
