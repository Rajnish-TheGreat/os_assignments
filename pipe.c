#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pipefds1[2], pipefds2[2];
    char a[20], b[20], c[20];
    printf("\nEnter Message from Parent to Child(size < 20)\n");
    scanf(" %s", a);
    printf("\nEnter Message from Child to Parent(size < 20)\n");
    scanf(" %s", b);

    if (pipe(pipefds1) == -1)
    {
        printf("Unable to create Pipe 1 \n");
        return 1;
    }

    if (pipe(pipefds2) == -1)
    {
        printf("Unable to create Pipe 2 \n");
        return 1;
    }

    if (fork() != 0)
    {
        close(pipefds1[0]);
        close(pipefds2[1]);
        printf("\nIn Parent: Writing to Pipe 1 – Message is %s\n", a);
        write(pipefds1[1], a, sizeof(a));
        read(pipefds2[0], c, sizeof(c));
        printf("\nIn Parent: Reading from Pipe 2 – Message is %s\n", c);
    }

    else
    {
        close(pipefds1[1]);
        close(pipefds2[0]);
        read(pipefds1[0], c, sizeof(c));
        printf("\nIn Child: Reading from Pipe 1 – Message is %s\n", c);
        printf("\nIn Child: Writing to Pipe 2 – Message is %s\n", b);
        write(pipefds2[1], b, sizeof(b));
    }

    return 0;
}
