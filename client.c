/* shm-client - client program to demonstrate shared memory. */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define SHMSZ  2
main() {
int shmid;
key_t key;
char *shm, *s;
/* We need to get the segment named "56 8", created by the server.
*/
key = 5678;
/* Locate the segment.
*/
if ((shmid = shmget(key, SHMSZ , 0666)) < 0) {
printf("shmget error");
exit(1);
}
/* Now we attach the segment to our data space.
*/
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
printf("shmat error");
exit(1);
}
/* Now read what the server put in the memory.
*/
for (s = shm; *s != NULL; s++)
putchar(*s);
putchar('\n');
/* Finally, change the frst character of the segment to '*', indicating we have read the segment.
*/
*shm = '*';
exit(0);
}
