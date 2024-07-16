#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <vector>

void process_command(std::string command) {
        // Se for comando interno...
    if (command == "exit")
        exit(0);

    std::istringstream iss(command);
    std::vector<std::string> args;
    std::string token;
    
    // Tokeniza a linha de comando
    while (iss >> token) {
        args.push_back(token);
    }
    
    // Verifica se há comandos e argumentos
    if (args.empty()) {
        return; // Comando vazio
    }

    // Converte argumentos para o formato necessário pelo execve
    std::vector<char*> argv;
    for (auto &arg : args) {
        argv.push_back(&arg[0]);
    }
    argv.push_back(NULL); // Termina a lista de argumentos com NULL

    std::string absolute_path = "/bin/" + args[0]; 
    if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório
        if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
            pid_t pid = fork();
            if (pid < 0){ // Erro
                std::cout << "Erro de execução!" << std::endl;
                return;
            } else if (pid == 0){ //processo filho
             
                execve(absolute_path.c_str(), argv.data(), NULL);
                
            } else { // Processo pai
                /* Deve adicionar processo filho na lista (std::vector) 
                   de processos em execução para gerenciar background. */
                /* Processo pai espera processo filho terminar. */
                waitpid(pid, nullptr, 0); 
            }
        } else { // Arquivo não é executável
            std::cout << "permission denied: " << command << std::endl;
        }
    } else { // Arquivo não existe
        std::cout << "Command not found: " << command << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "$> ";
        std::string command;
        getline(std::cin, command);
        process_command(command);
    }
    return 0;
}
