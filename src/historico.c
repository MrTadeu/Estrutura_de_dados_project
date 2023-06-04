#include "../includes/TipoDados.h"

void initHistoricoTransacoes(){
    HistoricoDados.tamanhoVetorHash = 30;
    HistoricoDados.HistoricoTransacoes = (Lista**) malloc(HistoricoDados.tamanhoVetorHash * sizeof(Lista*));
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++)
        HistoricoDados.HistoricoTransacoes[i] = criarLista();
}

void limparHistoricoTransacoes(){
    Lista **Aux = HistoricoDados.HistoricoTransacoes;
    printf("\nolaa1");
    initHistoricoTransacoes();
    printf("\nolaa2");

    destruirHistoricoTransacoes(Aux);
    printf("\nolaa3");
}

void destruirHistoricoTransacoes(Lista **historicoTransacoes){
    for(int i = 0; i < HistoricoDados.tamanhoVetorHash; i++)
        destruirLista(historicoTransacoes[i], destruirHistoricoSubStructCliente);
    free(historicoTransacoes);
}

void initHistoricoDadosEstatisticos(){
    //DADOS INSTANTANEOS
    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 6; j++){
            HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa = (int **)malloc(sizeof(int*)*numeroMaximoCaixasPossivel);
            for (int l = 0; l < numeroMaximoCaixasPossivel; l++){
                HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l] = (int*)calloc(2, sizeof(int));
                // Coluna 0: tempoEspera | Coluna 1: numeroClientesFila
            }
            HistoricoDados.dadosIntantaneosdiarios[i][j].numerosCaixasAbertas = 0;
            HistoricoDados.dadosIntantaneosdiarios[i][j].numeroClienteSupermercado = 0;
        }      
    }

    //INTS
        HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario = (int **)malloc(sizeof(int*)*n_funcionarios);
        for (int i = 0; i < n_funcionarios; i++)
            HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i] = (int *)calloc(3, sizeof(int));
        //coluna 0: ids funcionarios | coluna 1: n pessoas atendidas | coluna 2: n produtos vendidos


        HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa = (int**) malloc(sizeof(int*)*numeroMaximoCaixasPossivel);
        for (int i = 0; i < numeroMaximoCaixasPossivel; i++)
            HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i] = (int *)calloc(2, sizeof(int));
        //coluna 0: n pessoas atendidas por cada caixa | coluna 1: n produtos vendidos por cada caixa

        HistoricoDados.mediaDiaria.numeroProdutosOferecidos = 0;

    //CHARS
        HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMaisPessoas = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMaisPessoas, "Calculando");
        HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMenosPessoas = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMenosPessoas, "Calculando");
        HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMaisProdutos = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMaisProdutos, "Calculando");
        HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMenosProdutos = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMenosProdutos, "Calculando");
    

    //FLOATS    
        HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora = (float **)malloc(sizeof(float*)*24);
        HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora = (float **)malloc(sizeof(float*)*24);
        for (int i = 0; i < 24; i++){
            HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[i] = (float*)calloc(numeroMaximoCaixasPossivel, sizeof(float));
            HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[i] = (float*)calloc(numeroMaximoCaixasPossivel, sizeof(float));
        }
        HistoricoDados.mediaDiaria.tempoMedioEsperaTotal_CadaHora = (float*)calloc(24, sizeof(float));
        HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa = (float*)calloc(numeroMaximoCaixasPossivel, sizeof(float));
        HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaHora = (float*)calloc(24, sizeof(float));
        HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa = (float*)calloc(numeroMaximoCaixasPossivel, sizeof(float));
        HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_CadaHora = (float*)calloc(24, sizeof(float));
        HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_CadaHora = (float*)calloc(24, sizeof(float));

        HistoricoDados.mediaDiaria.tempoMedioEspera_Dia = 0.0;
        HistoricoDados.mediaDiaria.numeroMedioClienteFila_Dia = 0.0;
        HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_dia = 0.0;
        HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_Dia = 0.0;
}


void destruirHistoricoDadosEstatisticos(){
    // DADOS INSTANTANEOS
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 6; j++) {
                for (int l = 0; l < numeroMaximoCaixasPossivel; l++) {
                    free(HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l]);
                }
                free(HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa);
            }
        }
        
    // INTS
        for (int i = 0; i < n_funcionarios; i++) {
            free(HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i]);
        }
        free(HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario);

        for (int i = 0; i < numeroMaximoCaixasPossivel; i++) {
            free(HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i]);
        }
        free(HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa);

    // CHARS
        free(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMaisPessoas);
        free(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMenosPessoas);
        free(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMaisProdutos);
        free(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMenosProdutos);

    // FLOATS
        for (int i = 0; i < 24; i++) {
            free(HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[i]);
            free(HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[i]);
        }
        free(HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora);
        free(HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora);

        free(HistoricoDados.mediaDiaria.tempoMedioEsperaTotal_CadaHora);
        free(HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa);
        free(HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaHora);
        free(HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa);
        free(HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_CadaHora);
        free(HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_CadaHora);
}

void destruirHistoricoSubStructTransacao(void *transacaoArg){
    HistoricoSubStructTransacao* transacao = (HistoricoSubStructTransacao*)transacaoArg;
    destruirLista(transacao->listaProdutos, destruirProduto);
    free(transacao);
}

void destruirHistoricoSubStructCliente(void* clienteArg){
    HistoricoSubStructCliente* cliente = (HistoricoSubStructCliente*)clienteArg;
    for(int j = 0; j < numeroMaximoCaixasPossivel; j++){
        destruirLista(cliente->caixas[j], destruirHistoricoSubStructTransacao);
    }
    free(cliente->caixas);
}

void recolhaDadosEstatisticosHistoricoTransacoes(){
    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento *clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (clientesHistorico){
            HistoricoSubStructCliente *clientesHistoricoInfo = (HistoricoSubStructCliente *)clientesHistorico->Info;
            for (int j = 0; j < numeroMaximoCaixasPossivel; j++){
                Elemento *caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                if(caixasHistorico)
                    HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[j][0]++; //!numAtendimentos recolhido
                while (caixasHistorico){
                    int flag = 1;
                    HistoricoSubStructTransacao *caixasHistoricoInfo = (HistoricoSubStructTransacao *)caixasHistorico->Info;

                    HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[j][1] += caixasHistoricoInfo->listaProdutos->quantidadeElementos; //!numProdutos recolhido
                    if (caixasHistoricoInfo->valorProdutoOferecido > 0){
                        
                        HistoricoDados.mediaDiaria.numeroProdutosOferecidos++; //!numeroProdutosOferecidos recolhido
                        HistoricoDados.mediaDiaria.valorTotalProdutosOferecidos += caixasHistoricoInfo->valorProdutoOferecido; //!valorProdutosOferecidos recolhido
                    }
                    for (int l = 0; l < n_funcionarios; l++){
                        if(HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][0] == 0)
                            HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][0] = caixasHistoricoInfo->funcionario->id;
                        if(HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][0] == caixasHistoricoInfo->funcionario->id){
                            HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][1] += flag; //!numAtendimentos recolhido
                            flag = 0;
                            HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][2] += caixasHistoricoInfo->listaProdutos->quantidadeElementos; //!numProdutos recolhido
                            break;
                        }
                    }
                    caixasHistorico = caixasHistorico->next;
                }
            }
            clientesHistorico = clientesHistorico->next;
        }
    }
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
}
void recolhaDadosEstatisticosHistoricoPeriodica(int hora, int minuto){
    Elemento* caixa = Global.caixas->head;
    HistoricoDados.dadosIntantaneosdiarios[hora][minuto].numerosCaixasAbertas = Global.caixas->quantidadeElementos;
    HistoricoDados.dadosIntantaneosdiarios[hora][minuto].numeroClienteSupermercado = Global.n_pessoasEmLoja;
    
    int i = 0;
    while(caixa){
        CaixaStruct* caixaInfo = (CaixaStruct*)caixa->Info;
        HistoricoDados.dadosIntantaneosdiarios[hora][minuto].tempoEspera_numeroClienteFila_CadaCaixa[i][0] = caixaInfo->tempoTotalEspera;
        HistoricoDados.dadosIntantaneosdiarios[hora][minuto].tempoEspera_numeroClienteFila_CadaCaixa[i++][1] = caixaInfo->listaPessoas->quantidadeElementos;
        caixa = caixa->next;
    }
}

void calculosRecolhas(){
    int idFunc_maisAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][0],
    idFunc_menosAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][0],
    idFunc_maisProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][0],
    idFunc_menosProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][0],
    FuncionarioMaisAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][1],
    FuncionarioMenosAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][1],
    FuncionarioMaisProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][2],
    FuncionarioMenosProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][2];

    for (int i = 0; i < n_funcionarios; i++){
        if(FuncionarioMaisAtendimentos < HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1]){
            FuncionarioMaisAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1];
            idFunc_maisAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][0];
        }
        if(FuncionarioMenosAtendimentos > HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1]){
            FuncionarioMenosAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1];
            idFunc_menosAtendimentos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][0];
        }
        if(FuncionarioMaisProdutos < HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2]){
            FuncionarioMaisProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2];
            idFunc_maisProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][0];

        }
        if(FuncionarioMenosProdutos > HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2]){
            FuncionarioMenosProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2];
            idFunc_menosProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][0];
        }
    }

    /* pthread_mutex_lock(&FuncionariosLock); */
        int indexVetorFuncionarios;

        indexVetorFuncionarios = encontrarIdFuncionario(idFunc_maisAtendimentos);
        if(indexVetorFuncionarios != -1){
            free(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMaisPessoas);
            HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMaisPessoas = (char*)malloc(1+sizeof(char)*strlen(Funcionarios[indexVetorFuncionarios]->nome));
            strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMaisPessoas, Funcionarios[indexVetorFuncionarios]->nome);
        }

        indexVetorFuncionarios = encontrarIdFuncionario(idFunc_menosAtendimentos);
        if(indexVetorFuncionarios != -1){
            free(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMenosPessoas);
            HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMenosPessoas = (char*)malloc(1+sizeof(char)*strlen(Funcionarios[indexVetorFuncionarios]->nome));
            strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioAtendeuMenosPessoas, Funcionarios[indexVetorFuncionarios]->nome);
        }

        indexVetorFuncionarios = encontrarIdFuncionario(idFunc_maisProdutos);
        if(indexVetorFuncionarios != -1){
            free(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMaisProdutos);
            HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMaisProdutos = (char*)malloc(1+sizeof(char)*strlen(Funcionarios[indexVetorFuncionarios]->nome));
            strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMaisProdutos, Funcionarios[indexVetorFuncionarios]->nome);
        }

        indexVetorFuncionarios = encontrarIdFuncionario(idFunc_menosProdutos);
        if(indexVetorFuncionarios != -1){
            free(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMenosProdutos);
            HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMenosProdutos = (char*)malloc(1+sizeof(char)*strlen(Funcionarios[indexVetorFuncionarios]->nome));
            strcpy(HistoricoDados.mediaDiaria.nomeFuncionarioVendeuMenosProdutos, Funcionarios[indexVetorFuncionarios]->nome);
        }

    /* pthread_mutex_unlock(&FuncionariosLock); */

    int caixaAtendeuMaisPessoas = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][0],
    caixaAtendeuMenosPessoas = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][0],
    caixaVendeuMaisProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][1],
    caixaVendeuMenosProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][1];
    for (int i = 0; i < numeroMaximoCaixasPossivel; i++){
        if(caixaAtendeuMaisPessoas < HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][0]){
            caixaAtendeuMaisPessoas = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][0];
            HistoricoDados.mediaDiaria.caixaAtendeuMaisPessoas = i+1;
        }
        if(caixaAtendeuMenosPessoas > HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][0]){
            HistoricoDados.mediaDiaria.caixaAtendeuMenosPessoas = i+1;
            caixaAtendeuMenosPessoas = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][0];
        }
        if(caixaVendeuMaisProdutos < HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1]){
            HistoricoDados.mediaDiaria.caixaVendeuMaisProdutos = i+1;
            caixaVendeuMaisProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1];
        }
        if(caixaVendeuMenosProdutos > HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1]){
            HistoricoDados.mediaDiaria.caixaVendeuMenosProdutos = i+1;
            caixaVendeuMenosProdutos = HistoricoDados.mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1];
        }
    }    


    for (int i = 0; i < 24; i++){//Atualizar tempoMedioEspera_CadaCaixa_CadaHora e tempoMedioEsperaTotal_CadaHora, numeroMedioClienteFila_CadaCaixa_CadaHora e numeroMedioClienteFila_CadaHora
        for (int j = 0; j < 6; j++){
            for (int l = 0; l < numeroMaximoCaixasPossivel; l++){
                //Tempos de espera
                HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[i][l] = (float)((HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[i][l] + HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][0])/2);
                HistoricoDados.mediaDiaria.tempoMedioEsperaTotal_CadaHora[i] = (float)((HistoricoDados.mediaDiaria.tempoMedioEsperaTotal_CadaHora[i] + HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][0])/2);

                //Numero de clientes Fila
                HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[i][l] = (float)((HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[i][l] + HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][1])/2);
                HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaHora[i] = (float)((HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaHora[i] + HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][1])/2);

            }
            HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_CadaHora[i] = (float)((HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_CadaHora[i] + HistoricoDados.dadosIntantaneosdiarios[i][j].numerosCaixasAbertas)/2);
            HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_CadaHora[i] = (float)((HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_CadaHora[i] +  HistoricoDados.dadosIntantaneosdiarios[i][j].numeroClienteSupermercado)/2);
        }
    }

    for (int i = 0; i < numeroMaximoCaixasPossivel; i++){//Atualizar tempoMedioEspera_CadaCaixa e numeroMedioClienteFila_CadaCaixa
        for (int j = 0; j < 24; j++){
            HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa[i] = (float)((HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa[i] + HistoricoDados.mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[j][i])/2);
            HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa[i] = (float)((HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa[i] + HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[j][i])/2);
        }
    }
    
    for (int i = 0; i < 24; i++){
        HistoricoDados.mediaDiaria.tempoMedioEspera_Dia = (float)((HistoricoDados.mediaDiaria.tempoMedioEspera_Dia + HistoricoDados.mediaDiaria.tempoMedioEsperaTotal_CadaHora[i])/2);
        HistoricoDados.mediaDiaria.numeroMedioClienteFila_Dia = (float)((HistoricoDados.mediaDiaria.numeroMedioClienteFila_Dia + HistoricoDados.mediaDiaria.numeroMedioClienteFila_CadaHora[i])/2);
        HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_dia = (float)((HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_dia + HistoricoDados.mediaDiaria.numeroMedioCaixasAbertas_CadaHora[i])/2);
        HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_Dia = (float)((HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_Dia + HistoricoDados.mediaDiaria.numeroMedioClienteSupermercado_CadaHora[i])/2);
    }
}

int hashFunction(char *nome){
    if (!nome){
        printf("\n\t[red]Error![/red] Given name is NULL\n");
        return -1;
    }
    int sum = 0, p = 31;// Um número primo para gerar o hash

    for (int i = 0; nome[i] != '\0'; i++)
        sum = (sum * p) + nome[i];

    // Ajusta o tamanho do hash para o tamanho do vetor
    sum = (sum % HistoricoDados.tamanhoVetorHash + HistoricoDados.tamanhoVetorHash) % HistoricoDados.tamanhoVetorHash;
    return sum;
}

void *criarSubStructClienteHistorico(ClienteStruct *cliente)
{
    HistoricoSubStructCliente *elementoCliente = (HistoricoSubStructCliente *)malloc(sizeof(HistoricoSubStructCliente));
    elementoCliente->nome = (char *)malloc(strlen(cliente->nome) + 1);
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista **)malloc(sizeof(Lista *) * numeroMaximoCaixasPossivel);
    for (int i = 0; i < numeroMaximoCaixasPossivel; i++)
        elementoCliente->caixas[i] = criarLista();
    return elementoCliente;
}

void *criarInfoHistorico(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido)
{
    ClienteStruct *pessoa = (ClienteStruct *)caixa->listaPessoas->head->Info;
    HistoricoSubStructTransacao *infoHistorico = (HistoricoSubStructTransacao *)malloc(sizeof(HistoricoSubStructTransacao));
    infoHistorico->funcionario = caixa->funcionario;
    infoHistorico->listaProdutos = pessoa->listaProdutos;
    infoHistorico->tempoEstimadoCaixa = pessoa->tempoEstimadoCaixa;
    infoHistorico->tempoAtraso = pessoa->tempoAtraso;
    infoHistorico->movimentoCartaoCliente = movimentoSaldoCartao;
    infoHistorico->precoTotal = pessoa->precoTotalProdutos;
    infoHistorico->valorProdutoOferecido = valorProdutoOferecido;
    infoHistorico->dataTransacao = formatTimeStruct(getCurrentTimeMillisecounds());
    return infoHistorico;
}

void AddHistorico_Hash(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido){
    if (!caixa)
    {
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }
    if (!caixa->listaPessoas->head->Info)
    {
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");
        return;
    }
    /* printf("\n\n\n\t\t\t\tola1\n\n\n\n\n\n"); */

    ClienteStruct *pessoaAtendida = (ClienteStruct *)malloc(sizeof(ClienteStruct));
    memcpy(pessoaAtendida, caixa->listaPessoas->head->Info, sizeof(ClienteStruct));
    int hashIndex = hashFunction(pessoaAtendida->nome);

    FuncionarioStruct *funcionario = (FuncionarioStruct *)malloc(sizeof(FuncionarioStruct));
    memcpy(funcionario, caixa->funcionario, sizeof(FuncionarioStruct));

    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    Elemento *Aux = HistoricoDados.HistoricoTransacoes[hashIndex]->head;
    while (Aux){
        HistoricoSubStructCliente *guardado = (HistoricoSubStructCliente *)Aux->Info;
        if (pessoaAtendida->id == guardado->id)
        {   /* printc("\n\n\n\t\t\t\t[green]ola5 ADD INFO HISTORICO[/green]\n\n\n\n\n\n"); */
            AddElementoInicio(guardado->caixas[caixa->id - 1], criarElemento(criarInfoHistorico(caixa, movimentoSaldoCartao, valorProdutoOferecido)));
            pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
            return;
        }
        Aux = Aux->next;
    }
    AddElementoInicio(HistoricoDados.HistoricoTransacoes[hashIndex], criarElemento(criarSubStructClienteHistorico(pessoaAtendida)));
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
    /* printc("\n\n\n\t\t\t\t[green]RECURSIVEEEEEEEEEEEEE[/green]\n\n\n\n\n\n"); */
    AddHistorico_Hash(caixa, movimentoSaldoCartao, valorProdutoOferecido);
}

//* index Hash->|0|1|2|3|...          __HistoricoSubStructCliente
//*              |        ___________/      /
//*              V       V                 /
//*           |Nome, Id|  --> |1|2|3|4|5|... <--id caixas
//*                             |
//*                          |Info|  <--- HistoricoSubStructTransacao

void mostrarHistorico(){
    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento *clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (clientesHistorico){
            HistoricoSubStructCliente *clientesHistoricoInfo = (HistoricoSubStructCliente *)clientesHistorico->Info;
            for (int j = 0; j < numeroMaximoCaixasPossivel; j++){
                Elemento *caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                while (caixasHistorico){   
                    char horas[9];
                    HistoricoSubStructTransacao *caixasHistoricoInfo = (HistoricoSubStructTransacao *)caixasHistorico->Info;
                    formatTime(caixasHistoricoInfo->tempoEstimadoCaixa, horas);

                    printc("\n[blue]Nome cliente:[/blue] %s\t[blue]ID cliente:[/blue] %d\n[blue]ID caixa:[/blue] %d\t[blue]Nome funcionário:[/blue] %s\t[blue]ID funcionário:[/blue] %d\n[blue]Data de transação:[/blue] %d/%d/%d\t[blue]Hora:[/blue] %d:%d:%d\n[blue]Tempo de espera na fila:[/blue] %s\t", clientesHistoricoInfo->nome, clientesHistoricoInfo->id, j+1, caixasHistoricoInfo->funcionario->nome, caixasHistoricoInfo->funcionario->id, caixasHistoricoInfo->dataTransacao.dia, caixasHistoricoInfo->dataTransacao.mes, caixasHistoricoInfo->dataTransacao.ano, caixasHistoricoInfo->dataTransacao.hora, caixasHistoricoInfo->dataTransacao.minuto, caixasHistoricoInfo->dataTransacao.segundo, horas);

                    printc("[blue]Tempo de atraso:[/blue] ");
                    if (caixasHistoricoInfo->tempoAtraso < 0)
                        printc("[green]Adiantou-se:[/green] %.2f segundos\n", fabs((float)caixasHistoricoInfo->tempoAtraso / 1000.0));
                    else if (caixasHistoricoInfo->tempoAtraso > 0)
                        printc("[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso / 1000.0);

                    Elemento *produtos = caixasHistoricoInfo->listaProdutos->head;
                    while (produtos)
                    {
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }

                    printc("\t[blue]Preço total:[/blue] %.2f\n", caixasHistoricoInfo->precoTotal);

                    if (caixasHistoricoInfo->valorProdutoOferecido > 0)
                    {
                        printc("\t[yellow]Produto oferecido![/yellow] [blue]Preço:[/blue] %.2f", caixasHistoricoInfo->valorProdutoOferecido);
                    }
                    printc("\t[blue]Saldo cartão cliente:[/blue]\n");
                    if (caixasHistoricoInfo->movimentoCartaoCliente < 0)
                    {
                        printc("\t\t[blue]O cliente usou[/blue] %.2f euros", fabs(caixasHistoricoInfo->movimentoCartaoCliente));
                    }
                    else
                        printc("\t\t[blue]O cliente angariou[/blue] %.2f euros", caixasHistoricoInfo->movimentoCartaoCliente);

                    caixasHistorico = caixasHistorico->next;
                }
            }

            clientesHistorico = clientesHistorico->next;
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
}

void pesquisarClienteNoHistorico(){
    /* for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){ */
    int id, pos = -1, flag = 0;
    scanfs("%d", &id, "Qual o id de Cliente que pretende pesquisar? ", "Tem de inserir um numero inteiro!");
    pos =  encontrarIdCliente(id);
    if (pos == -1) return;
    char *nome = malloc(sizeof(char) * strlen(Clientes[pos]->nome));
    strcpy(nome, Clientes[pos]->nome);
    printf("Nome: %s\n", nome);
    Elemento* pessoasHistorico = HistoricoDados.HistoricoTransacoes[hashFunction(nome)]->head;
    while (pessoasHistorico != NULL){
        HistoricoSubStructCliente *ClienteInfo = (HistoricoSubStructCliente *) pessoasHistorico->Info;
        if ((id == ClienteInfo->id) /* && strcasecmp(nome, ClienteInfo->nome) */){
            flag = 1;
            printc("[blue]Cliente:[/blue] %s [blue]id:[/blue] %d \n", ClienteInfo->nome, ClienteInfo->id);
            for (int j = 0; j < numeroMaximoCaixasPossivel; j++){
                Elemento *caixasHistorico = ClienteInfo->caixas[j]->head;
                while (caixasHistorico){
                    HistoricoSubStructTransacao *caixaInfo = ((HistoricoSubStructTransacao *)((HistoricoSubStructCliente *) pessoasHistorico->Info)->caixas[j]->head->Info);

                    printc("\t[blue]Caixa:[/blue] %d [blue]Funcionario:[/blue] %s [blue]id:[/blue] %d\n", j+1, caixaInfo->funcionario->nome, caixaInfo->funcionario->id);
                    printc("\t[blue]Data:[/blue] %d/%d/%d [blue]Hora:[/blue] %d:%d:%d\n", caixaInfo->dataTransacao.dia, caixaInfo->dataTransacao.mes, caixaInfo->dataTransacao.ano, caixaInfo->dataTransacao.hora, caixaInfo->dataTransacao.minuto, caixaInfo->dataTransacao.segundo);
                    
                    printc("\t[blue]Tempo de espera na fila:[/blue] %d\n", caixaInfo->tempoEstimadoCaixa);

                    printc("\t[blue]Tempo de atraso:[/blue] ");
                    if (caixaInfo->tempoAtraso < 0)
                        printc("\t[green]Adiantou-se:[/green] %.2f segundos\n", fabs((float)caixaInfo->tempoAtraso / 1000.0));
                    else if (caixaInfo->tempoAtraso > 0)
                        printc("\t[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixaInfo->tempoAtraso / 1000.0);

                    printc("\t[blue]Preço total:[/blue] %.2f\n", caixaInfo->precoTotal);

                    printc("\t[blue]Saldo cartão cliente:[/blue] %.2f\n", caixaInfo->movimentoCartaoCliente);
                    
                    printc("\t[blue]Produtos:[/blue]\n");
                    Elemento *produtos = caixaInfo->listaProdutos->head;
                    while (produtos){
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }
                    caixasHistorico = caixasHistorico->next;
                }
            }
        }
        pessoasHistorico = pessoasHistorico->next;
    } 
    /* } */
    flag == 0 ? printc("[red]Cliente não encontrado![/red]\n") : (void)NULL;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarCaixaNoHistorico(){
    int id;
    scanfv("%d", &id, "Qual o id de caixa que pretende pesquisar? ", "Tem de inserir um numero inteiro!", validateRange, 1, numeroMaximoCaixasPossivel);
    printc("[yellow]Caixa:[/yellow] %d\n\n", id);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento* pessoasHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (pessoasHistorico){
            HistoricoSubStructCliente *ClienteInfo = (HistoricoSubStructCliente *) pessoasHistorico->Info;
            if (ClienteInfo->caixas[id - 1]->head){
                HistoricoSubStructTransacao *caixaInfo = ((HistoricoSubStructTransacao *)((HistoricoSubStructCliente *) pessoasHistorico->Info)->caixas[id - 1]->head->Info);
                Elemento *caixasHistorico = ClienteInfo->caixas[id - 1]->head;
                while (caixasHistorico){
                    printc("\t[blue]Funcionario:[/blue] %s [blue]id:[/blue] %d\n", caixaInfo->funcionario->nome, caixaInfo->funcionario->id);
                    printc("\t[blue]Cliente:[/blue] %s [blue]id:[/blue] %d \n", ClienteInfo->nome, ((HistoricoSubStructCliente *)pessoasHistorico->Info)->id);
                    printc("\t\t[blue]Data:[/blue] %d/%d/%d [blue]Hora:[/blue] %d:%d:%d\n", caixaInfo->dataTransacao.dia, caixaInfo->dataTransacao.mes, caixaInfo->dataTransacao.ano, caixaInfo->dataTransacao.hora,    caixaInfo->dataTransacao.minuto, caixaInfo->dataTransacao.segundo);

                    printc("\t\t[blue]Tempo de espera na fila:[/blue] %d\n", caixaInfo->tempoEstimadoCaixa);
                    printc("\t[blue]Tempo de atraso:[/blue] ");
                    if (caixaInfo->tempoAtraso < 0)
                        printc("\t[green]Adiantou-se:[/green] %.2f segundos\n", fabs((float)caixaInfo->tempoAtraso / 1000.0));
                    else if (caixaInfo->tempoAtraso > 0)
                        printc("\t[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixaInfo->tempoAtraso / 1000.0);

                    printc("\t[blue]Preço total:[/blue] %.2f\n", caixaInfo->precoTotal);

                printf("\t[blue]Saldo cartão cliente:[/blue] %.2f\n", caixaInfo->movimentoCartaoCliente);
                
                printf("\t[blue]Produtos:[/blue]\n");
                Elemento *produtos = caixaInfo->listaProdutos->head;
                while (produtos){
                    ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                    printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                    produtos = produtos->next;
                }
                caixasHistorico = caixasHistorico->next;
            }
            
            pessoasHistorico = pessoasHistorico->next;
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}
}