#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define LOG_FILE "log_redirect.log"

void redirect_stdio(const char* filename)
{
    printf("filename [%s] \n", filename);

    freopen(filename, "a", stdout); setbuf(stdout, NULL);
    freopen(filename, "a", stderr); setbuf(stderr, NULL);
}

int main(int argc, char **argv)
{
    redirect_stdio(LOG_FILE);
    int size = arc4random()%1000;
    for (int i = 0; i < size; i++)
    {
        printf("[ %s %d ] index[%d]\n", __func__, __LINE__, i);
    }
    return 0;
}