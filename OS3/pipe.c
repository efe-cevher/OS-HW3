#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#define Read            0
#define Write           1
#define ParentRead      read_pipe[0]
#define ParentWrite     write_pipe[1]
#define ChildRead       write_pipe[0]
#define ChildWrite      read_pipe[1]


int main()
{
    int data_processed;

    /** Pipe for reading for subprocess */
    int read_pipe[2];
    /** Pipe for writing to subprocess */
    int write_pipe[2];

    char buffer[100];
    memset(buffer, '\0', 100);

    if (pipe(read_pipe) == 0 && pipe(write_pipe) == 0)
    {
        pid_t pid = fork();
        if (pid == (pid_t) -1)
        {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        else if (pid == (pid_t) 0) {  //Child process
            close(Read);
            close(Write);
            close(ParentRead);
            close(ParentWrite);
            dup2 (ChildRead, 0);
            dup2 (ChildWrite, 1);
            execlp("cat", "cat", (char*)NULL);
            exit(EXIT_FAILURE);
        }
        else { //Parent process
            close(ChildRead);
            close(ChildWrite);

            write(ParentWrite, "abc", 3);
            int r = read(ParentRead, buffer, 99);
            printf("%d %d", r, errno);
            puts(buffer);
        }
    }

    exit(EXIT_SUCCESS);
}

