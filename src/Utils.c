#include "../includes/TipoDados.h"

int Aleatorio(int min, int max){
    int resultado = min + rand() % (max-min + 1);
    return resultado;
}

DataStruct gerarData(int anoMin, int anoMax){
    DataStruct data;
    data.ano = Aleatorio(anoMin, anoMax);
    data.mes = Aleatorio(1, 12);

    if((data.mes % 2 != 0 && data.mes < 8) || (data.mes >= 8 && data.mes % 2 == 0))
        data.dia = Aleatorio(1, 31);
    else if((data.mes % 2 == 0 && data.mes <= 8 && data.mes != 2) || (data.mes > 8 && data.mes % 2 != 0))
        data.dia = Aleatorio(1, 30);
    else if((data.mes == 2 && data.ano % 4 == 0))
        data.dia = Aleatorio(1, 29);
    else if((data.mes == 2 && data.ano % 4 != 0))
        data.dia = Aleatorio(1, 28);
    
    return data;
}

int DataAntesDepois(DataStruct d1, DataStruct d2){ // Se d1 for antes de d2 return 1
    if(d2.ano > d1.ano || 
        (d2.ano == d1.ano && 
        d2.mes > d1.mes) || 
        (d2.ano == d1.ano && 
        d2.mes == d1.mes && 
        d2.dia >=  d1.dia))
        return 1;
    return 0;
}



/* int fileExists(const char* path) {
  struct stat st;
  if (stat(path, &st) == 0) {
    return 1;
  }
  return 0;
}

int fileExistAll(){
  if(fileExists("data/bin/alunos.bin") && fileExists("data/bin/cursosdisciplina.bin") && fileExists("data/bin/disciplinas.bin") && fileExists("data/bin/permission.bin") && fileExists("data/bin/professores.bin") && fileExists("data/bin/regimes.bin") && fileExists("data/bin/salas.bin")){
    return 1;
  }
  else{
    return 0;
  }
} */


/* if (fileExistAll() == 0){
        printc("[red]Error[/red] Ficheiros não existem.\n\n");
        MenuFilesNovos();
    } */