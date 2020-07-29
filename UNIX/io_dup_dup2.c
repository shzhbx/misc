#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

void function_stdout_redirect_file(void)
{
    int fd = open("log.txt", O_RDWR | O_CREAT);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    //close(STDOUT_FILENO);
    //int new_fd = dup(fd);
    int new_fd = dup2(fd, STDOUT_FILENO);
    if (new_fd != 1)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }

    int count = 100;
    for (size_t i = 0; i < count; i++)
    {
        printf("out to log file1\n");
        fsync(new_fd);
    }

    exit(EXIT_SUCCESS);
}

int main(void)
{
    function_stdout_redirect_file();
}