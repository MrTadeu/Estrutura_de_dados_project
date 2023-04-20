#ifdef _WIN32
#include <windows.h>
    void dormir(){
        Sleep(1000);
    }   
#endif


#ifdef __linux__
#include <linux.h>
    void dormir(){
        usleep(1000);
    }
#endif

  