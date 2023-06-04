#include "../includes/TipoDados.h"

void criarCaixaInit(){
    Global.caixas = criarLista();
    Global.n_pessoasEmLoja = 0;
    for (int i = 0; i < numeroMaximoCaixasPossivel; i++){
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

/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/
void atualizarAtrasos(Lista *lista, ClienteStruct *pessoaEmAtendimento){
    if(!lista){
        printf("\t\n[red]Error![/red] lista NULL.\n");
        return;
    }
    int atrasoMaximo = (int) ((pessoaEmAtendimento->tempoEstimadoCaixa * (Opcoes.percentagemParaAtraso/100.0)));
    if(Aleatorio(0,1) == 1){
        atrasoMaximo *= -1;
    }
    pessoaEmAtendimento->tempoAtraso = atrasoMaximo;

    Elemento *aux = lista->head;
    aux = aux->next;
    ClienteStruct *pessoa;
    while(aux){
        pessoa = (ClienteStruct *) aux->Info;
        pessoa->tempoBrinde += atrasoMaximo;
        aux = aux->next;
    }
}

void fecharEscolherFecharCaixa(){
    int id;
    scanfv("%d", &id, "Id de caixa que deseja fechar: ", "Tem de ser um numero entre 1 e o numero máximo de caixas abertas", validateRange, 1, Opcoes.numCaixasAbertas);
    Elemento *caixa = Global.caixas->head;
    while (caixa){
        if (((CaixaStruct *) caixa->Info)->id == id){
            ((CaixaStruct *) caixa->Info)->fecharUrgencia = 1;
            printf("\n\tCaixa %d por fechar %d\n", id, ((CaixaStruct *) caixa->Info)->fecharUrgencia);
            break;          
        }
        caixa = caixa->next;
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}


void fecharUrgencia(CaixaStruct *caixa){
    if (!caixa){
        printc("\n\t[red]Error[/red] Given caixa is NULL\n");
        return;
    }
    
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
    printf("tempo inicial: %d tempoAtraso:%d\n", tempo, tempoAtrasoAux);

    while(tempo>0){
        int x;
        if(tempo < 1000){
            dormir(tempo);
            x = tempo;
            tempo = 0;
        }
        else{
            dormir(1000);
            x = 1000;
            tempo -= 1000;
        }

        if (Opcoes.VerTransacoes == 1){
            char tempoString[9];
            formatTime(tempo, tempoString);
            printc("\n[red]%dº Caixa[/red]\n Pessoa: [blue]%s[/blue] Tempo: [green]%s[/green]\n",caixa->id, cliente->nome, tempoString);
        }

        if (cliente->tempoEstimadoCaixa > 0){
            pthread_mutex_lock(&caixa->lock);
            caixa->tempoTotalEspera-=x;
            pthread_mutex_unlock(&caixa->lock); 
            cliente->tempoEstimadoCaixa -= x;
        }
        else if (cliente->tempoAtraso > 0){
            if(cliente->tempoAtraso < 1000){
                cliente->tempoAtraso = 0;
            } else{
                cliente->tempoAtraso-=1000;
            }
        }

        printf("\nx: %d tempo:%d  caixa->tempoTotalEspera:%d", x, tempo, caixa->tempoTotalEspera);
    }
    pthread_mutex_lock(&caixa->lock);
    printf("\nfinal antes caixa->tempoTotalEspera:%d",caixa->tempoTotalEspera);
    caixa->tempoTotalEspera += tempoAtrasoAux;
    printf("\nfinal depos caixa->tempoTotalEspera:%d",caixa->tempoTotalEspera);
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
    int i = 0;
  
    //!IMPEDIR QUE SE MANDE ALGUEM PARA UMA CAIXA FECHADA POR URGENCIA  
    while (caixaAux){
        if(i++ >= Opcoes.numCaixasTotal){
            caixaAux = caixaAux->next;
            continue;
        }
            
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
        if (menor->threadAberta == 0){
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
    if(menor->tempoTotalEspera < Opcoes.TempoLimiteSuperior /* && menor->aberta == 1 */){
        if(menor->threadAberta == 0){
            if(menor->aberta == 0){
                menor->aberta = 1;
                menor->threadAberta = 1;
                Opcoes.numCaixasAbertas++;
                if(n_funcionariosAtivos >= n_funcionarios){
                    return NULL;
                }
                if (menor->funcionario == NULL){
                    menor->funcionario = (FuncionarioStruct *) escolherFuncionarios();
                }
                pthread_t threadCaixa;
                pthread_create(&threadCaixa, NULL, ThreadCaixa, (void *)menor);
                pthread_detach(threadCaixa);
            }
        }
        return menor;
    }
    else if(menor->tempoTotalEspera < Opcoes.TempoLimiteSuperior && menor->aberta == 0){
        return NULL;
    }

    if(menor->tempoTotalEspera >= Opcoes.TempoLimiteSuperior){
        return NULL;
    }
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
    if (Opcoes.VerTransacoes){
        printc("\n[red]%dº Caixa [/red]\n Funcionário: [blue]%s[/blue] a ir para caixa", caixa->id, caixa->funcionario->nome);
    }
    dormir(5000);
    if (Opcoes.VerTransacoes){
        printc("\n[red]%dº Caixa [/red][green]Aberta[/green]", caixa->id);
    }
    while(1){
        if(caixa->listaPessoas->quantidadeElementos > 0){
            pessoaEmAtendimento = (ClienteStruct *) caixa->listaPessoas->head->Info;
        }
        else{
            if (Opcoes.VerTransacoes){
                printc("\n[red]%dº Caixa: fechada[/red]\n", caixa->id);
            }
            dormir(10000);
            
            caixa->aberta = 0;
            caixa->threadAberta = 0;
            Opcoes.numCaixasAbertas--;
            ((FuncionarioStruct *)caixa->funcionario)->ativo = 0;
            desocuparFuncionario((FuncionarioStruct *) caixa->funcionario);
            caixa->funcionario = NULL;
            caixa->fecharUrgencia = 0;
            caixa->tempoTotalEspera = 0;
            if(caixa->listaPessoas->head == NULL)
                free(caixa->listaPessoas);
            caixa->listaPessoas = criarLista(); 
            return NULL;
        }
        pthread_mutex_lock(&caixa->lock);
        atualizarAtrasos(caixa->listaPessoas, pessoaEmAtendimento);
        pthread_mutex_unlock(&caixa->lock); 

        valorProdutoOferecido = oferecerBrinde(pessoaEmAtendimento, caixa);
        movimentoSaldoCliente = atualizarSaldoCliente(pessoaEmAtendimento);
        atrasoSum += pessoaEmAtendimento->tempoAtraso;
    
        atenderPessoa(caixa);
        atualizarDadosFuncionario(caixa->funcionario, atrasoSum / ++n_vendas);

        AddHistorico_Hash(caixa, movimentoSaldoCliente, valorProdutoOferecido);

        pthread_mutex_lock(&caixa->lock);
        RemElementoInicio(caixa->listaPessoas); 
        pthread_mutex_unlock(&caixa->lock); 


        if(caixa->fecharUrgencia){ // se quiser realmente ver aumentar o tempo de dormir na threadGlobal para selecionar as pesseoas mais devagar
            fecharUrgencia(caixa);
            /* printf("\n\tCaixa %d ordem de fechamento\n", caixa->id);
            printc("\n\n[yellow]Caixa quantidade %d[/yellow]\n", caixa->listaPessoas->quantidadeElementos);  */           
        }
        
        if (pessoaEmAtendimento->id != -1)
            DesocuparCliente(pessoaEmAtendimento);

        Global.n_pessoasEmLoja--;
    }
    return NULL;
}

void removerCaixa(){
    int confirmacao;
    scanfv("%d", &confirmacao, "Deseja mesmo remover a caixas? (1 - Sim / 2 - Não) ", "Tem que ser um numero intero",validateRange, 1, 2);
    if(confirmacao != 1) return;
    printc("[yellow]A remover caixas necessárias.[/yellow]\n");

    printc("\n [yellow]Quantidade de caixas: [/yellow] (Max: %d)\n", Opcoes.numCaixasTotal);
    printc(" [yellow]Quantidade fucionarios:[/yellow] %d", n_funcionarios);
    int diferenca = Opcoes.numCaixasTotal - n_funcionarios;
    printc("\n [yellow]Quantidade de caixas a remover:[/yellow] %d\n", diferenca);
/*     int diferencaAux = diferenca;
    while (diferenca > 0){
        destruirElemento(RemElementoUltimo(Global.caixas), destruirCaixa);
        diferenca--;
    } */
    Opcoes.numCaixasTotal -= diferenca;
    printc("\n\n [yellow]%d Caixa(s) removida(s) com sucesso. Pressione Enter para continuar...[/yellow]\n\n", diferenca);
    bufferclear();
    getchar();
}

void destruirCaixa(void* Caixa){
    CaixaStruct* caixa = (CaixaStruct*)Caixa;
    destruirLista(caixa->listaPessoas, destruirCliente);
}