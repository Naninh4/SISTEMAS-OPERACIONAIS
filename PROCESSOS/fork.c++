// #include <iostream>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//   pid_t pid;
//   pid = fork(); // dividiu um processo em dois
//   std::cout << "Processo copiado: " << pid << "\n";
    
//   if (pid != 0) { /* Processo pai */
//     std::cout << "Sou o processo pai: "
//               << getpid() << "\n";
//     /* Processo pai espera processo filho terminar */
//     wait(nullptr);
//     std::cout << "Filho terminou!!!\n";
//   }
//   else { /* Processo filho */
//     std::cout << "Sou o processo filho: "
//               << getpid() << "\n";
//     char *argv[3] = {"ls","-l", nullptr};
//     execve("/bin/ls", argv, NULL);
//   }
//   return 0;
// }
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
sleep(15);
return 0;
}
}