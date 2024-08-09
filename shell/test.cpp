#include <iostream>
#include <cstdlib>  // Para EXIT_FAILURE
#include <unistd.h> // Para fork() e execl()
#include <sys/types.h>
#include <sys/wait.h> // Para waitpid()
#include <fcntl.h>    // Para open()
#include <csignal>    // Para signals

void printando() {
    pid_t pid = fork(); // Cria um novo processo filho

    if (pid == -1) {
        // Erro no fork
        perror("fork falhou");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Este é o processo filho

        // Cria uma nova sessão para o processo filho
        if (setsid() == -1) {
            perror("setsid falhou");
            exit(EXIT_FAILURE);
        }     
        const char *programa = "print"; // Caminho absoluto para o programa

        // Executa o programa
        if (execl(programa, programa, NULL) == -1) {
            perror("execl falhou");
            exit(EXIT_FAILURE);
        }
    } else {
        // Este é o processo pai
      
        std::cout << "Processo filho em segundo plano com PID: " << pid << std::endl;

        // Não espera pelo processo filho, o pai continua sua execução
    }
}

int main() {
    // Inicia a operação em segundo plano
    printando();

    // O programa principal pode continuar fazendo outras coisas
    std::cout << "Programa principal continua executando..." << std::endl;

    // Simula alguma operação do programa principal
    for (int i = 0; i < 5; ++i) {
        std::cout << "Trabalhando... " << i << std::endl;
        sleep(1);
    }

    return 0;
}
