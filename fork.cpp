#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX 20

/*
The  <sys/types.h>  header file include  definitions for system data types such as :
pid_t ( Used for process IDs ).
All the data types defined under sys types are preceded by _t
*/
int n;

// FUNCTION DEFINITION GOES HERE....

void accept_nos(int arr[MAX])
{
    int i;
    printf("\n\tEnter the number of elements:");
    scanf("%d", &n);

    printf("\n\t Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        printf("\n\t Element %d :", i + 1);
        scanf("%d", &arr[i]);
    } // end of for
} // end of accept_nos

void accept_str(char str[])
{
    printf("\nEnter the statement for calculating number of vowels and words :");
    fgets(str, 256, stdin);
}

void display(int arr[MAX], char str[])
{
    int i;
    printf("\n\t Array elements :\n");
    for (i = 0; i < n; i++)
    {
        printf("\t element [%d] : %d", i + 1, arr[i]);
        printf("\n");
    } // end of for
    printf("\n");

    printf("\n\t Entered String is :\n");
    printf("\t%s\n", str);
}

void sort_asc(int arr[MAX])
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (arr[i] < arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("\n\n\tThe Numbers In Ascending Order Are:\n\t ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}
void sort_desc(int arr[MAX])
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("\n\n\tThe Numbers In Descending Order Are:\n\t ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

void cnt_vowels(char str[])
{
    int i = 0, cnt = 0;

    while (str[i] != '\0')
    {

        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
        {
            cnt++;
        }
        i++;
    }
    printf(" \n\t Number of vowels in the given string is: %d\n", cnt);
}

void cnt_words(char str[])
{
    int cnt = 1, i = 0;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
        {
            cnt++;
        }
    }
    printf(" \n\t Number of words in the given string is: %d", cnt);
}

int main()
{
    char str[20];
    int arr[MAX], *status = NULL;
    pid_t cpid;

    fflush(stdout);

    // accept_str(str);
    accept_nos(arr);

    printf("\n\t Original numbers are : \n");
    display(arr, str);
    cpid = fork();

    if (cpid == 0)
    {
        printf("\n\t This is child process. ");
        printf("\n\t My process id is : %d", getpid());
        printf("\n\t My Parent process id is : %d", getppid());

        sort_desc(arr);
        // cnt_words(str);
    }
    else
    {
        /*Parent process waiting for child process, sorting array elements in descending order and
                                  calculating number of words in given statement.*/

        cpid = wait(status);

        printf("\n\n\t Parent process resumed after the execution of child process with PID %d", cpid);
        printf("\n\t My process id is : %d", getpid());
        printf("\n\t My Parent process id is : %d", getppid());

        sort_asc(arr);
        // cnt_vowels(str);
    } // end of if-else

    return 0;
} // end of main
