#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
    void clear_screen() {
        system("cls");
        system("make");
    }
    void run_simulation() {
        system(".\\simulation.exe");
    }
    void criadorLinker(){
        FILE *fp = fopen("GeradorClicavel.bat", "w");
        fprintf(fp, "mklink /h simulation.exe simulation.lnk");
        fclose(fp);
    }
#else
    void clear_screen() {
        system("clear");
        system("make buildLinux");
    }
    void run_simulation() {
        system("./simulation");
    }
#endif

int main() {
    // Chama a função para limpar a tela do terminal
    clear_screen();
    criadorLinker();
    run_simulation();
    printf("acabouuuuuuuuuuuuuuuuuuuuu\n");
    return 0;
}