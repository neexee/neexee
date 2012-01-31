#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{   pid_t t;
    t = fork();
    if(t == 0)
    { 
        close(0);
         int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
         printf("%d\n", fd);
    }
    else
    {   int status;
        char ko[20];
        scanf("%s", ko);

        printf("%s", ko);
        wait(&status);

    }
    return 0;
}
