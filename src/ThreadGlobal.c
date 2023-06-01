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
                    if (Opcoes.VerTransacoes){
                        printc("\n\n[yellow]Pessoa Gerada:[/yellow] \n Nome: [blue]%s[/blue] \n Tempo de Compra: [green]%s[/green] \n Tempo de Estimado Caixa: [green]%s[/green]\n",  pessoa->nome, tempoEstimadoCompra, tempoEstimadoCaixa);
                    }
                }
                pthread_t thread;
                pthread_create(&thread, NULL, ThreadEsperaTempoCompra, (void *)pessoa);
                pthread_detach(thread); // para não ficar alocando memoria assim que acabar é como um pthread join
            }
            
        }
        SelecionarCaixa();
        dormir(1000);
    }
    return NULL;
}

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

void changeStateThreadGlobal(){
    if(Opcoes.lojaAberta == 0 && menuvalidarCaixaFuncionarios()){
        Opcoes.lojaAberta = 1;
        pthread_t GlobalThread;

        pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
        if(Global.PessoasAcabaramTempoDeCompra == NULL){
            Global.PessoasAcabaramTempoDeCompra = criarLista();
        }
        pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);

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

/* void *threadSchedule(){
    DataStruct dataAnterior = formatTimeStruct(tempoEmMilisegundos);
    while (1){
        DataStruct dataAtual = formatTimeStruct(tempoEmMilisegundos);
        if (dataAtual.segundo % 10 == 0 && dataAnterior.segundo != dataAtual.segundo){
            checkIFfileExists("Historico") == 0 ? system("mkdir Historico") : (void)NULL;
            dataAnterior.segundo = formatTimeStruct(tempoEmMilisegundos).segundo;
            // printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
            char dataString[100];
            sprintf(dataString, "Data_%d-%d-%d_%d_%d_%d", dataAtual.dia, dataAtual.mes, dataAtual.ano, dataAtual.hora, dataAtual.minuto, dataAtual.segundo);
            char command[100];
            sprintf(command, "mkdir Historico/%s", dataString);
            printf("%s\n", command);
            checkIFfileExists(dataString) == 0 ? system(command) : (void)NULL;
        }
        if (dataAtual.minuto % 10 == 0 && dataAnterior.minuto != dataAtual.minuto){ // bater de 10 em 10 minutos
            dataAnterior.minuto = formatTimeStruct(tempoEmMilisegundos).minuto;
            printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo);
        }
        if (dataAtual.hora % 1 == 0 && dataAnterior.hora != dataAtual.hora){ // bater de 1 em 1 hora
            dataAnterior.hora = formatTimeStruct(tempoEmMilisegundos).hora;
            // printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
        }
        if (dataAtual.dia % 1 == 0 && dataAnterior.dia != dataAtual.dia){ // bater de 1 em 1 dia
            checkIFfileExists("Historico") == 0 ? system("mkdir Historico") : (void)NULL;
            dataAnterior.dia = formatTimeStruct(tempoEmMilisegundos).dia;
            //char dataString[20];
            //sprintf(dataString, "Data_%d-%d-%d", dataAtual.dia, dataAtual.mes, dataAtual.ano);
            //char command[100];
            //sprintf(command, "mkdir Historico/%s", dataString);
            
            //checkIFfileExists(dataString) == 0 ? system(command) : (void)NULL; 

            // printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
        }
        
    }
} */
void *threadSchedule(){
    DataStruct dataAnterior = formatTimeStruct(tempoEmMilisegundos);
    while (1){
        DataStruct dataAtual = formatTimeStruct(tempoEmMilisegundos);
        if (dataAtual.segundo % 10 == 0 && dataAnterior.segundo != dataAtual.segundo){
          /*   struct stat st;
            stat("Historico", &st) == 0 ? (void)NULL : mkdir("Historico"); // retorna 0 se existir
            dataAnterior.segundo = formatTimeStruct(tempoEmMilisegundos).segundo;
            // printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
            char dataString[100];
            sprintf(dataString, "Historico/Data_%d-%d-%d_%d_%d_%d", dataAtual.dia, dataAtual.mes, dataAtual.ano, dataAtual.hora, dataAtual.minuto, dataAtual.segundo);
            printf("%s\n", dataString);
            stat(dataString, &st) == 0 ?  (void)NULL : mkdir(dataString);
            char imgsString[100];
            sprintf(imgsString, "%s/imgs", dataString);
            printf("%s\n", imgsString);
            stat(imgsString, &st) == 0 ?  (void)NULL : mkdir(imgsString); */
        }
        if (dataAtual.minuto % 10 == 0 && dataAnterior.minuto != dataAtual.minuto){ // bater de 10 em 10 minutos
            dataAnterior.minuto = formatTimeStruct(tempoEmMilisegundos).minuto;
            //printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo);
        }
        if (dataAtual.hora % 1 == 0 && dataAnterior.hora != dataAtual.hora){ // bater de 1 em 1 hora
            dataAnterior.hora = formatTimeStruct(tempoEmMilisegundos).hora;
            /* printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); */
        }
        if (dataAtual.dia % 1 == 0 && dataAnterior.dia != dataAtual.dia){ // bater de 1 em 1 dia
            dataAnterior.dia = formatTimeStruct(tempoEmMilisegundos).dia;
            struct stat st;
            stat("Historico", &st) == 0 ? (void)NULL : mkdir("Historico"); // retorna 0 se existir
            dataAnterior.segundo = formatTimeStruct(tempoEmMilisegundos).segundo;
            // printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
            char dataString[100];
            sprintf(dataString, "Historico/Data_%d-%d-%d", dataAtual.dia, dataAtual.mes, dataAtual.ano);
            //printf("%s\n", dataString);
            stat(dataString, &st) == 0 ?  (void)NULL : mkdir(dataString);
            char imgsString[100];
            sprintf(imgsString, "%s/imgs", dataString);
            //printf("%s\n", imgsString);
            stat(imgsString, &st) == 0 ?  (void)NULL : mkdir(imgsString);

            
        }
        /* dormir(1000); */
    }
}

void *threadTempo(){
    tempoEmMilisegundos = getCurrentTimeMillisecounds();
    while(1){
        tempoEmMilisegundos += 1000LL;
        dormir(1000 /* * Opcoes.multiplicadorTempo */);
    }
}

