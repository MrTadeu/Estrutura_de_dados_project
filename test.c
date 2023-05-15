#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long milliseconds = ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
    printf("Current time in milliseconds: %lld\n", milliseconds);

    time_t seconds = milliseconds / 1000;
    struct tm *tm_info = localtime(&seconds);
    char buffer[30];
    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Current date and time: %s\n", buffer);


    milliseconds += 1000*60*1440*656LL;
    printf("Current time in milliseconds: %lld\n", milliseconds);

    seconds = milliseconds / 1000;
    tm_info = localtime(&seconds);
    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Current date and time: %s\n", buffer);
    return 0;
}
