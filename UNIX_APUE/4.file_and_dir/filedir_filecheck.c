#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHECK_FILE "/dev/fd/1"

static void check(const char * filename)
{
    struct stat st;
    //if (stat(filename, &st) == 0)
    if (fstatat(AT_FDCWD, filename, &st, AT_SYMLINK_NOFOLLOW) == 0)
    {
        printf("st.st_rdev      [%d]        \n", st.st_rdev);
        printf("st.st_dev       [%d]        \n", st.st_dev);
        printf("st.st_no        [%lld]      \n", st.st_ino);
        printf("st.st_nlink     [%d]        \n", st.st_nlink);
        printf("st.st_size      [%lld]      \n", st.st_size);
        printf("st.st_blksize   [%d]        \n", st.st_blksize);
        printf("st.st_blocks    [%lld]      \n", st.st_blocks);
        printf("st.st_gen       [%d]        \n", st.st_gen);
        printf("st.st_atimespec [%ld,%ld]   \n", st.st_atimespec.tv_nsec, st.st_atimespec.tv_sec);
        printf("st.st_ctimespec [%ld,%ld]   \n", st.st_ctimespec.tv_nsec, st.st_ctimespec.tv_sec);
        printf("st.st_mtimespec [%ld,%ld]   \n", st.st_mtimespec.tv_nsec, st.st_mtimespec.tv_sec);

        mode_t mode = st.st_mode;
        if (S_ISREG(mode))
        {
            printf("[%s] is regular file \n", filename);
        }
        else if (S_ISLNK(mode)) 
        {
            printf("[%s] is link file\n", filename);
        }
        else if (S_ISCHR(mode)) 
        {
            printf("[%s] is char special file\n", filename);
        }
        else if (S_ISBLK(mode)) 
        {
            printf("[%s] is block special file\n", filename);
        }
        else if (S_ISFIFO(mode)) 
        {
            printf("[%s] is fifo file\n", filename);
        }
        else if (S_ISSOCK(mode)) 
        {
            printf("[%s] is socket file\n", filename);
        }
        else if (S_ISDIR(mode)) 
        {
            printf("[%s] is dir file\n", filename);
        }
    }
    else 
    {
        perror("stat ");
    }
}

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        printf("Usage:\n");
        printf("      %s <file>\n", argv[0]);
        return -1;
    }

    check(argv[1]);
    return 0;
}