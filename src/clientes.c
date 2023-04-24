#include "../includes/TipoDados.h"

void verClientes(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    for(int i = 0; i < n_clientes; i++){
        printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i].id, Clientes[i].nome, Clientes[i].saldoCartaoCliente, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}