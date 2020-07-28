#include <stdio.h>          /* 输入输出标准库头文件 */
#include <stdlib.h>         /* C标准函数库的头文件 */
#include <unistd.h>         /* UNIX Standard */
#include <fcntl.h>          /* 文件描述符 */     
#include <sys/types.h>      /* 不同的数据类型 */
#include <sys/stat.h>       /* 文件信息(stat (Unix)等) */
#include <string.h>         /* 大小写不敏感字符串操作 */
#include <limits.h>

void open_operation(void);
void lseek_operation(int argc, char * argv[]);
void lseek_operation1(void);

int main(int argc, char* argv[])
{
    //open_operation();
    //lseek_operation(argc, argv);
    lseek_operation1();

    exit(EXIT_SUCCESS);
}

void lseek_operation1(void)
{
    int fd;
    const char buf1[] = "abcdefghij";
    const char buf2[] = "ABCDEFGHIJ";

    if ((fd = open("file.hole", O_CREAT | O_WRONLY | O_TRUNC , 0655)) < 0 )
    {
        printf("open error\n");
        exit(EXIT_FAILURE);
    }
    
    if (write(fd, buf1, sizeof(buf1)) != sizeof(buf1))
    {
        printf("write error\n");
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, sizeof(buf1) + sizeof(buf2), SEEK_END) == -1)
    {
        printf("lseek error");
        exit(EXIT_FAILURE);
    }
    
    if (write(fd, buf2, sizeof(buf2)) != sizeof(buf2))
    {
        printf("write error\n");
        exit(EXIT_FAILURE);
    }

    close(fd);

    exit(EXIT_SUCCESS);
}

void lseek_operation(int argc, char * argv[])
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    {
        printf("cannot seek \n");
    }
    else
        printf("seek OK");
}

void open_operation(void)
{
    int fd;
    int numbytes;
    char path[] = "file";
    char buf[256];

    fd = open(path, O_CREAT | O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }
    
    memset(buf, 0x00, 256);
    while ((numbytes = read(fd, buf, 255)) > 0)
    {
        printf("%d bytes read: %s", numbytes, buf);
        memset(buf, 0x00, 256);
    }

    FILE file;
    
    close(fd);

    exit(EXIT_SUCCESS);
}