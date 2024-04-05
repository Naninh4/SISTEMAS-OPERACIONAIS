#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  pid = fork(); // dividiu um processo em dois
  std::cout << "Processo copiado: " << pid << "\n";
    
  if (pid != 0) { /* Processo pai */
    std::cout << "Sou o processo pai: "
              << getpid() << "\n";
    /* Processo pai espera processo filho terminar */
    wait(nullptr);
    std::cout << "Filho terminou!!!\n";
  }
  else { /* Processo filho */
    std::cout << "Sou o processo filho: "
              << getpid() << "\n";
    char *argv[3] = {"ls","-l", nullptr};
    execve("/bin/ls", argv, NULL);
  }
  return 0;
}
