#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
pid_t p1,p2;
printf("Oi!\n");
p1 = fork();
printf("Bom dia!!!\n");
if (p1==0){
char *a[3] = {"showparam",'Olha eu aqui!',NULL};
execve("showparam",a,NULL);
printf("Ate a proxima!\n");
} else {
wait(NULL);
printf("Ate mais ver!\n");
p2=fork();
printf("Fui...!\n");
}
return 0;
}