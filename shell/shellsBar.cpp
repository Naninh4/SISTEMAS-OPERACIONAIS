#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <vector>
#include <filesystem>
#include <cstring> // Para strlen e strtok
#include <limits.h>
#include <string>


// Códigos ANSI para cores
const std::string BLUE = "\033[38;5;21m";      // Azul
const std::string PURPLE = "\033[38;5;93m";    // Roxo
const std::string PINK = "\033[38;5;200m";     // rosa
const std::string RESET = "\033[0m";    
const std::string YELLOW = "\033[33m";       // Amarelo
const std::string GREEN = "\033[32m";        // Verde


const char* user = std::getenv("USER");
const char* hostname = std::getenv("HOSTNAME");


std::string def = PINK + (user ? std::string(user) : "unknown-user") + RESET + "@" + PURPLE + (hostname ? std::string(hostname) : "unknown-host") + RESET + ":";
std::string PS1 = def;


std::string PATH = "./test/:/bin/";

std::vector<std::string> history;
pid_t pid_back = 0;

std::vector<pid_t> process;

void check_background_processes() {
    int status;
    for (auto it = process.begin(); it != process.end();) {
        pid_t result = waitpid(*it, &status, WNOHANG); // WNOHANG para não bloquear
        if (result == 0) {
            ++it;
        } else if (result == -1) {
            // Erro ao verificar o processo
            it = process.erase(it); // Remove o processo com erro
        } else {
            it = process.erase(it); // Remove o processo da lista
        }
    }
}


std::string pwd() {
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) != nullptr) {
        return BLUE + currentPath + RESET;
    } else {
        perror("Erro ao obter o diretório atual");
        return "";
    }
}

std::string cd(std::string newDir) {
    if (chdir(newDir.c_str()) == 0) {       
        PS1 = def + pwd();
        return pwd();
    } else {
        perror("Erro ao mudar o diretório");
        return "";
    }
}

std::string findABPATH(const std::string& command) {
    char* path = new char[PATH.size() + 1];
    std::strcpy(path, PATH.c_str());

    char* token = std::strtok(path, ":");
    while (token != nullptr) {
        std::string absolute_path = std::string(token) + "/" + command;
        if (access(absolute_path.c_str(), F_OK) == 0) {
            delete[] path;
            return absolute_path;
        }
        token = std::strtok(nullptr, ":");
    }

    delete[] path;
    return command;
}

// Função para dividir a string de comando em argumentos
std::vector<std::string> tokeriza(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> args;
    std::string token;

    while (iss >> token) {
        args.push_back(token);
    }

    return args;  // Retorna mesmo que o vetor esteja vazio
}

// Função para converter vetores de string em vetores de char* de forma segura
std::vector<char*> set_argv(const std::vector<std::string>& args) {
    std::vector<char*> argv;
    
    // Criando uma cópia persistente das strings
    for (const auto& arg : args) {
        char* arg_cstr = new char[arg.size() + 1];  // Alocando espaço para a string e o terminador nulo
        std::strcpy(arg_cstr, arg.c_str());  // Copiando o conteúdo da string
        argv.push_back(arg_cstr);
    }

    argv.push_back(nullptr);  // Terminador nulo para imitar o estilo de argv em C

    return argv;
}

// Função para liberar a memória alocada pelo set_argv
void free_argv(std::vector<char*>& argv) {
    for (auto& arg : argv) {
        delete[] arg;  // Liberar a memória alocada
    }
    argv.clear();  // Limpa o vetor
}

void process_command(std::string command) {
    bool background = false;

    if (command == "exit") {
        exit(0);
    }
    if(command == "echo $PATH"){
        std::cout << YELLOW << PATH << RESET << std::endl;
        history.push_back(command);
        return;
    }
    if(command == "jobs"){
        for(int x=0; x< process.size();x++)
        std::cout << process[x] << std::endl;
        history.push_back(command);
        return;
    }
    
    if (command.substr(command.size() - 2) == " &") {
        background = true;
        command.erase(command.size() - 2);
    }

    if (command == "pwd") {
        std::cout << pwd() << std::endl;
        history.push_back(command);
        return;
    }

    if (command.substr(0, 3) == "cd ") {
        std::string dir = command.substr(3);
        history.push_back(command);    
        cd(dir);
        return;
    }

    if (command.substr(0, 5) == "PATH=") {
        PATH = command.substr(5);
        history.push_back(command);        
        return;
    }

    




    std::vector<std::string> args = tokeriza(command);
    std::vector<char*> argv = set_argv(args);

    if (args.size() > 0 && args[0] == "history") {
        // Verifica se o segundo argumento está presente antes de acessá-lo
        if (args.size() > 1 && std::string(argv[1]) == "-c") {
            history.clear();
            free_argv(argv);
            return;
        }
        
        if (args.size() > 1) {
            int index;
            std::stringstream ss(args[1]);
            if (!(ss >> index) || index < 1 || index > static_cast<int>(history.size())) {
                std::cout << "O que você forneceu não é um índice inválido" << std::endl;
            } else {
                args = tokeriza(history[index - 1]);  // Ajuste para acessar o índice corretamente
                free_argv(argv);
                argv = set_argv(args);
                history.push_back(history[index - 1]);
            }
        } else {
            // Exibe todo o histórico se nenhum índice for fornecido
            for (int x = history.size() - 1; x >= 0; x--) {
                std::cout << YELLOW << x + 1 << RESET << GREEN << " " << history[x] << RESET << std::endl;
            }

            return;
        }
    }else{
        history.push_back(command);
    }

    std::string absolute_path = findABPATH(args[0]);

    if (access(absolute_path.c_str(), F_OK) == 0) {
        if (access(absolute_path.c_str(), X_OK) == 0) {
            pid_t pid = fork();
            if (pid < 0) {
                std::cout << "Erro de execução!" << std::endl;
                return;
            } else if (pid == 0) {
                if (background) {
                    pid_back = setsid();
                    std::cout << "Número do processo em background: " << pid_back << std::endl << std::flush;
                    if (pid_back == -1) {
                        std::cerr << "Erro ao criar um novo grupo de processos." << std::endl;
                        exit(1);
                    }
                       
                }
                execve(absolute_path.c_str(), argv.data(), nullptr);
                perror("execve"); 
                exit(1);
            } else {
               
                if (background) {
                    process.push_back(pid);
                } else {

                    waitpid(pid, nullptr, 0);
                }
               
            }
        } else {
            std::cout << "permission denied: " << command << std::endl;
        }
    } else {
        std::cout << "Command not found: " << command << std::endl;
    }
}





int main() {
   
       while (true) {

        std::cout  << PS1 << "$> ";
        std::string command;
        getline(std::cin, command);
        process_command(command);
    }
    return 0;
}
