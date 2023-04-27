#include "../includes/TipoDados.h"


void criarCaixaInit(){
    Global.caixas = criarLista();
    for (int i = 0; i < Opcoes.numCaixasTotal; i++){
        CaixaStruct *caixa = (CaixaStruct *) malloc(sizeof(CaixaStruct));
        caixa->id = i;
        caixa->aberta = 0;
        caixa->fecharUrgencia = 0;
        caixa->tempoTotalEspera = 0;
        caixa->funcionario = (FuncionarioStruct *) escolherFuncionarios();
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

    //Remover da fila
    return RemElementoInicio(caixa->listaPessoas);
}
/* ------------------------------#< ATUALIZAÇÃO DADOS CAIXA >#------------------------------*/

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

/* CaixaStruct gerarCaixa(){ // gerarCaixa na ordem
    
}*/

CaixaStruct *MelhorCaixa(){ // o melhor index que tem o menor tempo
    if (Global.caixas->head == NULL) return NULL;
    
    Elemento *caixaAux = Global.caixas->head;
    printc("\n\n\t[red]Entrou no1 AQUI[/red]\n");
    printc("\n\n\t[red]Entrou no AQUI2222[/red]\n");
    CaixaStruct *menor = (CaixaStruct *)caixaAux->Info;
    printc("\n\n\t[red]Entrou no AQUI2222[/red] funcionario: %s id: %d\n", ((CaixaStruct *)caixaAux->Info)->funcionario->nome, ((CaixaStruct *)caixaAux->Info)->id);
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
    printc("\n\n\t[blue]Entrou no while[/blue]\n");
    printc("\n\n\t[green]Menor[/green] funcionario: %s id: %d\n", menor->funcionario->nome, menor->id);
    printc("\n\n\t[green]Segundo menor[/green] funcionario: %s id: %d\n", menor->funcionario->nome, menor->id);
    printc("\n\n\t[green]Maior[/green] funcionario: %s id: %d\n", menor->funcionario->nome, menor->id);

    if (menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior){
        printc("\n\n\t[blue]menor->tempoTotalEspera > Opcoes.TempoLimiteSuperior[/blue]\n");
        Opcoes.numCaixasAbertas++;
        primeiraCaixaFechada->aberta = 1;
        return primeiraCaixaFechada;
    }
    if (maior->tempoTotalEspera < Opcoes.TempoLimiteInferior && menor != SegundaMenor && Opcoes.numCaixasAbertas > 1){ // SegundaMenor == menor == maior??????? não pode fechar se todas forem iguais por isso Opcoes.numCaixasAbertas > 1
        printc("\n\n\t[blue]maior->tempoTotalEspera < Opcoes.TempoLimiteInferior && menor != SegundaMenor && Opcoes.numCaixasAbertas > 1[/blue]\n");
        Opcoes.numCaixasAbertas--;
        menor->aberta = 0;
        return SegundaMenor;
    }
    if (menor->aberta == 0){
        printc("\n\n\t[blue]menor->aberta == 0[/blue]\n");
        Opcoes.numCaixasAbertas++;
        menor->aberta = 1;
    }
    
    printc("\n\n\t[blue]Retornou[/blue]\n");
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
    if (pessoaEnviar == NULL) return;

    CaixaStruct* melhorCaixa;
    printc("\n\n\t[green]OLa1[/green]\n");

    while(pessoaEnviar){

        melhorCaixa = MelhorCaixa();
        //Atualizar o tempo de atraso consoante a pessoa a ser atendida no momento
        printc("\n\n\t[green]TESTE[/green]\n");
        printc("\n\n\t[red]pessoaEnviar: %s tempoDecompra: %d [/red] funcionario: %s id: %d tempoCaixa: %d\n", ((ClienteStruct*)pessoaEnviar->Info)->nome, ((ClienteStruct*)pessoaEnviar->Info)->tempoEstimadoCaixa, melhorCaixa->funcionario->nome, melhorCaixa->id, melhorCaixa->tempoTotalEspera);
/*         ((ClienteStruct *)pessoaEnviar->Info)->tempoAtraso = melhorCaixa->tempoTotalEspera + ((ClienteStruct *)pessoaEnviar->Info)->tempoEstimadoCaixa; */
        /* ((ClienteStruct *)pessoaEnviar->Info)->tempoAtraso = ((ClienteStruct *)melhorCaixa->listaPessoas->head->Info)->tempoAtraso;  */ // O QUE ESTA MERDA ESTÁ A FAZER AQUI  ???????????????????????????????????? !!!!!!!!!!!!!!!!
        
        printc("\n\n\t[green]PESSSOA ADD Caixa[/green]\n");
        AddElementoFim(melhorCaixa->listaPessoas, criarElemento(pessoaEnviar->Info));
        melhorCaixa->tempoTotalEspera +=((ClienteStruct *)pessoaEnviar->Info)->tempoEstimadoCaixa;
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

