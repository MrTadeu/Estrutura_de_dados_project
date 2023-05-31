#include "../includes/TipoDados.h"

void *ThreadGlobal(){
    pthread_mutex_init(&PessoasAcabaramTempoDeCompraLock, NULL);
    pthread_mutex_init(&ClientesLock, NULL);
    pthread_mutex_init(&FuncionariosLock, NULL);
    pthread_mutex_init(&HistoricoDados.HistoricoTransacoesLock, NULL);

    while(n_clientesAtivos || Opcoes.lojaAberta == 1){
        if (Aleatorio(0, 100) <= Opcoes.probGerarPessoa && Opcoes.lojaAberta == 1 && Opcoes.lotacaoMaxima >= Global.n_pessoasEmLoja){ //Gerar, simular tempo de compra e inserir pessoa na fila da melhor caixa
            ClienteStruct *pessoa = escolherCliente();
            
            if(pessoa){
                if(Opcoes.VerTransacoes == 1){
                    char tempoEstimadoCompra[9], tempoEstimadoCaixa[9];
                    formatTime(pessoa->tempoEstimadoCompra, tempoEstimadoCompra);
                    formatTime(pessoa->tempoEstimadoCaixa, tempoEstimadoCaixa);
                    printc("\n\n[yellow]Pessoa Gerada:[/yellow] \n Nome: [blue]%s[/blue] \n Tempo de Compra: [green]%s[/green] \n Tempo de Estimado Caixa: [green]%s[/green]\n",  pessoa->nome, tempoEstimadoCompra, tempoEstimadoCaixa);
                }
                pthread_t thread;
                pthread_create(&thread, NULL, ThreadEsperaTempoCompra, (void *)pessoa);
                pthread_detach(thread); // para não ficar alocando memoria assim que acabar é como um pthread join
            }
            
        }
        /* printf("\n\n\t[red]Pessoa Nula[/red]\n"); */
        SelecionarCaixa();
        dormir(1000);
    }
    return NULL;
}

/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/
void *ThreadEsperaTempoCompra(void *pessoa){
    ClienteStruct *cliente = (ClienteStruct *)pessoa;
    
    if(cliente->nome == NULL){
        printf("\n\n\t[red]ERRO: Pessoa Nula[/red]\n");
        exit(1);
    }  
    dormir(cliente->tempoEstimadoCompra);
    if(Opcoes.VerTransacoes == 1){
        char tempoEstimadoCompra[9];
        formatTime(cliente->tempoEstimadoCompra, tempoEstimadoCompra);
        printc("\n[yellow]Fim Tempo Compra:[/yellow]\n [blue]%s[/blue] acabou de comprar todos os produtos em [green]%s[/green]\n",cliente->nome, tempoEstimadoCompra);
    }
    pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
    AddElementoFim(Global.PessoasAcabaramTempoDeCompra, criarElemento(cliente));
    pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);
    return NULL;
}
/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/

void changeStateThreadGlobal(){
    if(Opcoes.lojaAberta == 0 && menuvalidarCaixaFuncionarios()){
        Opcoes.lojaAberta = 1;
        pthread_t GlobalThread;

        pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
        if(Global.PessoasAcabaramTempoDeCompra == NULL){
            Global.PessoasAcabaramTempoDeCompra = criarLista();
        }
        pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);


        /* Elemento *CaixaElm = Global.caixas->head;
        for (int i = 0; i < Opcoes.; i++){
            CaixaStruct *caixa = (CaixaStruct *)CaixaElm->Info;
            if(n_funcionariosAtivos >= n_funcisonarios){
                caixa->aberta = 0;
                caixa->funcionario = NULL;
            }
            else{
                caixa->aberta = 1;
                caixa->funcionario = (FuncionarioStruct *) escolherFuncionarios();
            }
            CaixaElm = CaixaElm->next; 
            if(CaixaElm == NULL){
                break;
            }
        } */

        if (pthread_create(&GlobalThread, NULL, ThreadGlobal, NULL) != 0){
            printc("[red]Erro[/red] ao criar thread global!!!\n");
            exit(1);
        } 
        
        /* pthread_join(GlobalThread, NULL); */// <--- Nao dar join porque a thread global vai ficar sempre a correr
    }
    else if(Opcoes.lojaAberta == 1){
        Opcoes.lojaAberta = 0;
    }
}

void *threadSchedule(){
    int minAnterior = formatTimeStruct(tempoEmMilisegundos).minuto;
    while (1){ 
        if (formatTimeStruct(tempoEmMilisegundos).minuto % 10 == 0 && minAnterior != formatTimeStruct(tempoEmMilisegundos).minuto){
            minAnterior = formatTimeStruct(tempoEmMilisegundos).minuto;
            printc("\n\n\t[green]Hora: %d:%d[/green]", formatTimeStruct(tempoEmMilisegundos).hora, formatTimeStruct(tempoEmMilisegundos).minuto);
        } 
        dormir(1000);
    }
    
}

void *threadTempo(){
    tempoEmMilisegundos = getCurrentTimeMillisecounds();
    while(1){
        tempoEmMilisegundos += 1000LL;
        dormir(1000 /* * Opcoes.multiplicadorTempo */);
    }
}

