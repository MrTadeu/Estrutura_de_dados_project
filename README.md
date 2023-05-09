<img src="Supermarket_Simulation.png" alt="">

<hr>

![GitHub commit activity](https://img.shields.io/github/commit-activity/y/MrTadeu/Estrutura_de_dados_project) ![GitHub last commit](https://img.shields.io/github/last-commit/MrTadeu/Estrutura_de_dados_project)



O projeto "Simulação de Supermercado" é uma implementação em C que tem como objetivo simular o funcionamento de um supermercado. Desenvolvido por Benno, João Falcão e Pedro Tavares, o projeto permite que os usuários entendam a dinâmica de um supermercado, incluindo aspectos como fluxo de clientes e gerenciamento de tempo. A simulação é baseada em um conjunto de dados fictícios que foram criados para representar as características do supermercado. Com esse projeto, os usuários podem ter uma experiência prática e interativa, permitindo que eles aprendam e experimentem como funciona um supermercado.

# 1. Instruções de execução
## 1.1. Instrução de execução via comando
>&nbsp;
>```cmd
>> gcc -o3 -Wall .\src\main.c .\includes\TipoDados.h .\src\TipoDadosFuncoes.c .\src\Utils.c .\includes\ListaLigada.h .\src\ListaLigadaFuncoes.c .\src\Import_Export.c -o  run.exe
>```
>&nbsp;
## 1.2. Instruçoes de execução com `MakeFile` no Windows (recomendado)
As instruções a seguir irão ajudá-lo a executar uma **compilação automática** do projeto. O Makefile é uma ferramenta útil que gerencia todo o processo e torna as coisas mais fáceis.\
Para executar uma **compilação automátomaticamente** no windows, é obrigatório instalar `MakeFile`. Neste projeto, foi utilizado o _Chocolatey_, uma ferramenta de gerenciamento de pacotes para o Windows, que irá facilitar o processo de instalação.
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
>### 1.2.2. Uma vez que o Makefile tenha sido instalado com sucesso e você esteja na mesma pasta que o arquivo makefile, use o comando `make` ou `make -f makefile` para criar um arquivo executável chamado _"run.exe"_. Se você precisar recompilar ou excluir o arquivo, use o comando `make clean`, que irá remover o arquivo _"run.exe"_.
>&nbsp;
>### 1.2.6. Reinicie o editor (IDE) e feche qualquer terminal que tenha aberto no processo, uma vez que possa dar alguns erros e possivelmente a não execução do comando `make`.
>&nbsp;
## 1.3. Instruçoes de execução com `MakeFile` no Linux (recomendado)
As instruções a seguir irão ajudá-lo a executar uma **compilação automática** do projeto. O Makefile é uma ferramenta útil que gerencia todo o processo e torna as coisas mais fáceis.\
Para executar uma **compilação automátomaticamente** no Linux, é obrigatório instalar `MakeFile`. Neste projeto, foi utilizado o _Chocolatey_, uma ferramenta de gerenciamento de pacotes para o Linux, que irá facilitar o processo de instalação.

# Contribuição
* Este projeto foi desenvolvido por uma equipe composta por Benno, João Falcão e Pedro Tavares. O objetivo do projeto foi desenvolver um sistema em C para gerenciamento de um supermercado. Cada membro da equipe contribuiu com suas habilidades e conhecimentos únicos para o projeto.