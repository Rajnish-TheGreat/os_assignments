#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	key_t key = 1234;
	int shmid = shmget(key, 1024, 0666|IPC_CREAT);
	char *str = (char*)shmat(shmid, NULL, 0);
	printf("\nWrite updated Data: ");
	fgets(str, 50, stdin);
	printf("Server Writes Data written in memory: %s\n", str);
	shmdt(str);
	return 0;
}
