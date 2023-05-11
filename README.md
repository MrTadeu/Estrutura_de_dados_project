<img src="Supermarket_Simulation.png" alt="">

<hr>

![GitHub commit activity](https://img.shields.io/github/commit-activity/y/MrTadeu/Estrutura_de_dados_project) ![GitHub last commit](https://img.shields.io/github/last-commit/MrTadeu/Estrutura_de_dados_project)



O projeto "Simulação de Supermercado" é uma implementação em C que tem como objetivo simular o funcionamento de um supermercado. O projeto permite que os usuários entendam a dinâmica de um supermercado, incluindo aspectos como fluxo de clientes e gerenciamento de tempo. A simulação é baseada em um conjunto de dados fictícios que foram criados para representar as características do supermercado. Com esse projeto, os usuários podem ter uma experiência prática e interativa, permitindo que eles aprendam e experimentem como funciona um supermercado.

# 1. Instruções de execução
## 1.1. Instrução de execução via comando
>&nbsp;
>```cmd
>> gcc -o3 -Wall .\src\main.c .\includes\TipoDados.h .\src\TipoDadosFuncoes.c .\src\Utils.c .\includes\ListaLigada.h .\src\ListaLigadaFuncoes.c .\src\Import_Export.c -o  run.exe
>```
>&nbsp;
## 1.2. Instruçoes de execução com `Makefile` no Windows (recomendado)
As instruções a seguir irão ajudá-lo a executar uma **compilação automática** do projeto. O Makefile é uma ferramenta útil que gerencia todo o processo e torna as coisas mais fáceis.\
Para executar uma **compilação automátomaticamente** no windows, é obrigatório instalar `Makefile`. Neste projeto, foi utilizado o _Chocolatey_, uma ferramenta de gerenciamento de pacotes para o Windows, que irá facilitar o processo de instalação.
>### 1.2.1. Instalando a ferramenta de gerenciamento de pacotes:
>* Através do site da [Chocolatey](https://chocolatey.orginstall#individual)\
>__**OU**__
>* Através de um comando no PowerShell no modo Administrativo
>```pwsh
>> Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
>```
>&nbsp;
>### 1.2.2. Verifique se o Chocolatey foi instalado corretamente executando o comando:
>```pwsh
>> choco -v
>```
>&nbsp;
>### 1.2.3. Depois que _Chocolatey_ foi instalado, use o comando a seguir:
>```pwsh
>> choco install make
>```
>&nbsp;
>### 1.2.4. Verifique se o Makefile foi instalado corretamente executando o comando:
>```pwsh
>> make -v
>```
>&nbsp;
>### 1.2.6. Caso haja algum erro:
>Reinicie o editor (IDE) e feche qualquer terminal que tenha aberto no processo, uma vez que possa dar alguns erros e possivelmente a não execução do comando `make`.\
>&nbsp;
>### 1.2.7. Uma vez já instalado:
>Uma vez que o Makefile tenha sido instalado com sucesso e você esteja na mesma pasta que o arquivo makefile, use o comando `make` ou `make -f makefile` para criar um arquivo executável chamado _"simulation.exe"_. Se você precisar recompilar ou excluir o arquivo, use o comando `make clean`, que irá remover o arquivo _"simulation.exe"_.\
>&nbsp;
>&nbsp;
## 1.3. Instruçoes de execução com `Makefile` no Linux (recomendado)
As instruções a seguir irão ajudá-lo a executar uma **compilação automática** do projeto. O Makefile é uma ferramenta útil que gerencia todo o processo e torna as coisas mais fáceis.\
Para executar uma **compilação automátomaticamente** no Linux, é obrigatório instalar `Makefile`. A maioria das distribuições Linux já vem com o makefile já pré instalado.

>### 1.2.1. Verificar se possui o makefile:
>```bash
>$ make -v
>```
>&nbsp;
>### 1.2.2. Se não tem o makefile instale com o seguinte comando:
>```bash
>$ sudo apt-get install make
>```
>&nbsp;
>### 1.2.3. Uma vez já instalado:
>Use para compilar e  para Deletar os ficheiros.
Uma vez que o Makefile tenha sido instalado com sucesso e você esteja na mesma pasta que o arquivo makefile, use o comando `make buildLinux` para criar um arquivo executável chamado "simulation". Se você precisar recompilar ou excluir o arquivo, use o comando `make cleanLinux`, que irá remover o arquivo "simulation".\
>&nbsp;

# 2. Como Usar

# Contribuição
* Este projeto foi desenvolvido por uma equipe composta por Benno Vasconcellos, João Falcão e Pedro Tavares. O objetivo do projeto foi desenvolver um sistema em C para gerenciamento de um supermercado. Cada membro da equipe contribuiu com suas habilidades e conhecimentos únicos para o projeto.