#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <vector>
#include <string>



// Função para dividir a linha de comando em comando e argumentos
std::vector<std::string> split_command(const std::string &command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
//    std::cout << "Tokens: ";
//     for (const auto& t : tokens) {
//         std::cout << "[" << t << "] ";
//     }
//     std::cout << std::endl;
    return tokens;
}



void process_command(std::string command) {
    // Se for comando interno...
    if (command == "exit")
        exit(0);

    split_command(command);
    // Se for comando externo

    // * necessário verificar se é para ser executado em background
    /*  Se for caminho relativo, procurar o comando na lista de diretórios
        Se for absoluto verifica se comando existe
    */
    std::string absolute_path = "/bin/" + command; 
    
    if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório
        if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
            pid_t pid = fork();
            if (pid < 0){ // Erro
                std::cout << "Erro de execução!" << std::endl;
                return;
            } else if (pid == 0){ //processo filho



                char * argv[2] = {(char *)command.c_str(), nullptr};
                std::cout << argv[2];
                execve(absolute_path.c_str(), argv, NULL);
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
