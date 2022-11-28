#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>	

const char content[] = "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";
size_t contentLen  = sizeof(content)/sizeof(content[0]) ;
char fileName[] = "test.txt";
const char resultFile[] = "time_shared.txt";

int main()
{
	int shmid, status;
	int *a, *b;
	int i;

    // tao shared memory lai IPC_PRIVATE de truyen thong tin giua cha va con 
	shmid = shmget(IPC_PRIVATE, contentLen, 0777|IPC_CREAT);


	if (fork() == 0) {

		/* Child Process */

		/*  shmat() returns a char pointer which is typecast here
		    to int and the address is stored in the int pointer b. */
		b = (int *) shmat(shmid, 0, 0);

		for( i=0; i< 10; i++) {
			sleep(1);
			printf("\t\t\t Child reads: %d,%d\n",b[0],b[1]);
		}
		/* each process should "detach" itself from the 
		   shared memory after it is used */

		shmdt(b);

	}
	else {

		/* Parent Process */

		/*  shmat() returns a char pointer which is typecast here
		    to int and the address is stored in the int pointer a.
		    Thus the memory locations a[0] and a[1] of the parent
		    are the same as the memory locations b[0] and b[1] of
		    the parent, since the memory is shared.
		*/
		a = (int *) shmat(shmid, 0, 0);

		a[0] = 0; a[1] = 1;
		for( i=0; i< 10; i++) {
			sleep(1);
			a[0] = a[0] + a[1];
			a[1] = a[0] + a[1];
			printf("Parent writes: %d,%d\n",a[0],a[1]);
		}
		wait(&status);

		/* each process should "detach" itself from the 
		   shared memory after it is used */

		shmdt(a);

		/* Child has exited, so parent process should delete
		   the cretaed shared memory. Unlike attach and detach,
		   which is to be done for each process separately,
		   deleting the shared memory has to be done by only
		   one process after making sure that noone else
		   will be using it 
		 */

		shmctl(shmid, IPC_RMID, 0);
	}
}