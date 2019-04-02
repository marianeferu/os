#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int main()
{
    int i,status;
    pid_t pid;
    char path[200] = "./";
    char auxPath[200];
    FILE* stats;

    int n;
    scanf("%d",&n);


    strcat(path,"root");

    printf("\n%s\n",path);

    mkdir(path,S_IRWXU);

    char comanda[200];

    sprintf(comanda, "cd  %s && ((ps |  grep %d) > stats.txt)", path, getpid());
    system(comanda);

    if(status == -1)
    {
        perror("Nu s-a creat fisierul root");
        return errno;
    }

    for(i=0; i<n; i++)
    {
        pid = fork();


        if(pid==0)
        {
            printf("Copil pid: %d, tata: %d\n", getpid(), getppid());
            char localPath[200];
            sprintf(localPath,"%s/%d", path, getpid());
            strcpy(path, localPath);

            mkdir(localPath, S_IRWXU);
            char comanda2[200];

            sprintf(comanda2, "cd %s && ((ps |  grep %d) > stats.txt)", localPath, getpid());
            system(comanda2);
        }


        else if(pid<0)
        {
            perror("eroare la crearea unui proces\n");
            return errno;
        }
    }

    for(i=0; i<n; i++)
    {
        wait(NULL);
    }
}
