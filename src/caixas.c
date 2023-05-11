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
    if (!caixa){
        printc("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }
    if(caixa->listaPessoas->head == NULL){
        return;
    }
    ClienteStruct *cliente = (ClienteStruct *) caixa->listaPessoas->head->Info;
    cliente->tempoEstimadoFila = 0;
    int tempo = cliente->tempoEstimadoCaixa + cliente->tempoAtraso;
    printf("entrou plau");
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


    //CHAMAR O HISTORICO

    //Remover da fila
    /* pthread_mutex_lock(&caixa->lock); */
    /* RemElementoInicio(caixa->listaPessoas);*/
    caixa->listaPessoas->head = caixa->listaPessoas->head->next;
    caixa->listaPessoas->quantidadeElementos--;
    /* pthread_mutex_unlock(&caixa->lock); */
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
        if (menor->funcionario == NULL){ // precisamos criar um funcionario para o caixa se não tiver uma vez que existe uma função de init caixa que cria sem ou com funcionario
            menor->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        menor->aberta = 1;
        if (primeiraCaixaFechada->listaPessoas->head == NULL){
            pthread_t threadCaixa;
            pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)menor);
            pthread_detach(threadCaixa);
            
        }
        

        /* printc("\n\tmenor [green]Caixa aberta! ID:%d  aberta?%d[/green]", menor->id, menor->aberta);
        printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas); */
        return menor;
    }
    /* printf("numCaixasAbertas %d numCaixasTotal %d", Opcoes.numCaixasAbertas, Opcoes.numCaixasTotal); */
    
    if (menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior && Opcoes.numCaixasAbertas < Opcoes.numCaixasTotal){
        /* if(Opcoes.numCaixasAbertas == Opcoes.numCaixasTotal){
            printc("\n\tmenor [red]Não é possivel abrir mais caixas! ID:%d  aberta?%d[/red]", menor->id, menor->aberta);
            return NULL;
        } */
        Opcoes.numCaixasAbertas++;
        if (primeiraCaixaFechada->funcionario == NULL){
            primeiraCaixaFechada->funcionario = (FuncionarioStruct *) escolherFuncionarios();
        }
        primeiraCaixaFechada->aberta = 1;
        if (primeiraCaixaFechada->listaPessoas->head == NULL){
            pthread_t threadCaixa;
            pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)primeiraCaixaFechada);
            pthread_detach(threadCaixa);
            
        }
        
        
        /* printc("\n\tprimeiraCaixaFechada [green]Caixa aberta! ID:%d  aberta?%d[/green]", primeiraCaixaFechada->id, primeiraCaixaFechada->aberta); */
        /* printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas); */
        return primeiraCaixaFechada;
    }
    if (maior->tempoTotalEspera < Opcoes.TempoLimiteInferior && menor != SegundaMenor && Opcoes.numCaixasAbertas > 1){ // SegundaMenor == menor == maior??????? não pode fechar se todas forem iguais por isso Opcoes.numCaixasAbertas > 1
        Opcoes.numCaixasAbertas--;
        menor->aberta = 0;
       /*  printc("\n\tSegundaMenor [green]Caixa aberta! ID:%d  aberta?%d[/green]", SegundaMenor->id, SegundaMenor->aberta);
        printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas); */
        return SegundaMenor;
    }
    /* printc("\n\tmenor [green]Caixa aberta! ID:%d  aberta?%d[/green]", menor->id, menor->aberta);
    printf("\nTempoLimiteSuperior %d TempoLimiteInferior %d Menor tempo: %d Maior tempo: %d SegundaMenor tempo: %d Caixa Abertas %d",Opcoes.TempoLimiteSuperior, Opcoes.TempoLimiteInferior, menor->tempoTotalEspera, maior->tempoTotalEspera, SegundaMenor->tempoTotalEspera, Opcoes.numCaixasAbertas); */
    /* if (Opcoes.numCaixasAbertas == Opcoes.numCaixasTotal && menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior){
        printc("\n\tmenor [red]Não é possivel abrir mais caixas! ID:%d  aberta?%d[/red]", menor->id, menor->aberta);
        return NULL;
    } */
    return menor;
}

void SelecionarCaixa(){ // seleciona e adiciona a melhor caixa para o cliente

    Elemento *pessoaEnviar = Global.PessoasAcabaramTempoDeCompra->head;

    CaixaStruct* melhorCaixa;
    /* int x = 0; */
    while(pessoaEnviar != NULL){
        
        melhorCaixa = MelhorCaixa();
        if (melhorCaixa == NULL) return;
        /* printc("[blue]-%d-[/blue]", x++); */
        /* printc("\n\tmelhorCaixa [green]Caixa aberta! ID:%d  aberta?%d[/green]", melhorCaixa->id, melhorCaixa->aberta); */
        /* if (Opcoes.VerTransacoes == 1 && Opcoes.lojaAberta == 1){
            printc("\n\n\t[green]PESSSOA ADD:[/green] %s tempoDecompra: %d  [magenta]---Caixa (id) %d--->[/magenta] [red]funcionario:[/red] %s [red]Tempo de Caixa:[/red] %d\n", ((ClienteStruct*)pessoaEnviar->Info)->nome, ((ClienteStruct*)pessoaEnviar->Info)->tempoEstimadoCaixa, melhorCaixa->id, melhorCaixa->funcionario->nome, melhorCaixa->tempoTotalEspera);
        } */

        //Atualizar o tempo de atraso consoante a pessoa a ser atendida no momento
        /* ((ClienteStruct *)pessoaEnviar->Info)->tempoAtraso = ((ClienteStruct *)melhorCaixa->listaPessoas->head->Info)->tempoAtraso; */ // O FILHO DA PUTA TRAVA AQUI!!!! VER ISSO DPS
        
        pthread_mutex_lock(&melhorCaixa->lock);
        AddElementoFim(melhorCaixa->listaPessoas, pessoaEnviar);
        melhorCaixa->tempoTotalEspera +=((ClienteStruct *)pessoaEnviar->Info)->tempoEstimadoCaixa;
        ((ClienteStruct*)pessoaEnviar->Info)->tempoAtraso = ((ClienteStruct*) melhorCaixa->listaPessoas->head->Info)->tempoAtraso;
        pthread_mutex_unlock(&melhorCaixa->lock);

        pthread_mutex_lock(&listaLock);
        RemElementoInicio(Global.PessoasAcabaramTempoDeCompra); 
        pthread_mutex_unlock(&listaLock);

        pessoaEnviar = pessoaEnviar->next;
    }

}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

void *ThreadCaixa(void *arg){
    CaixaStruct *caixa = (CaixaStruct *) arg;
    int atraso, n_vendas = 0;
    float atrasoMaximo, atrasoMedio = 0, atrasoSum = 0;
    ClienteStruct *pessoaEmAtendimento;
    
    while(caixa->listaPessoas->quantidadeElementos > 0){
        pessoaEmAtendimento = (ClienteStruct *) caixa->listaPessoas->head->Info;
        /* fecharUrgencia(caixa->listaPessoas); */
        atrasoMaximo = pessoaEmAtendimento->tempoEstimadoCaixa * Opcoes.percentagemParaAtraso;
        atraso = Aleatorio(-atrasoMaximo, atrasoMaximo);

        //ATRASOS ATUALIZADOS
        pthread_mutex_lock(&caixa->lock);
        atualizarAtrasos(caixa->listaPessoas, atraso);
        pthread_mutex_unlock(&caixa->lock);

        //PESSOA ATENDIDA
        pthread_mutex_lock(&caixa->lock);
        atenderPessoa(caixa); //precisamos de envolver esta funcao numa futura funcao guardarHistorico // a pessoa não é removida da lista de pessoas em atendimento quando sai do caixa E o head é a proxima pessoa a ser atendida desse jeito o espaço de memoria pode ser reutilizado para a matriz de pessoas do historico
        pthread_mutex_unlock(&caixa->lock);

        atrasoSum += atraso;
        n_vendas++;
        atrasoMedio = atrasoSum / n_vendas;
        printf("\ncaixa->funcionario->n_vendas: %d\n", caixa->funcionario->n_vendas);
        atualizarDadosFuncionario(caixa->funcionario, atrasoMedio, n_vendas);
    }
    return NULL;
}