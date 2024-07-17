#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int valor = 5;
int main(int argc, char ** argv){
pid_t pid;
valor+=1;
pid = fork();
valor+=1;
if (pid == 0) {
valor += 3;
return 0;
}
else if (pid > 0) {
valor += 5;
wait(NULL);
printf("Processo pai: valor = %d\n",valor); 
return 0;
}
}