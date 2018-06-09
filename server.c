#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define SHMSZ  2
main() {
char c;
int shmid;
key_t key;
char *shm, *s;
/* We'll name our shared memory segment "56 8".
*/
key = 5678;
/*
* Create the segment.
*/
if ((shmid = shmget(key, SHMSZ , IPC_CREAT | 0666)) < 0) {

printf("shmget err");
exit(1);
}
/*
* Now we attach the segment to our data space.
*/
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
printf("shmat error");
exit(1);
}
// Now put some things into the memory for the other process to read.
s = shm;
for (c = 'a'; c <= 'z'; c++)
  *s++ = c;
  *s = '\0';
/* Finally, we wait until the other process changes the frst character of our memory to '*', indicating that it has read
what we put there.
*/
while (*shm != '*')
  sleep(1);
for (s = shm; *s != '\0'; s++)
   putchar(*s);
   putchar('\n');
exit(0);
}
