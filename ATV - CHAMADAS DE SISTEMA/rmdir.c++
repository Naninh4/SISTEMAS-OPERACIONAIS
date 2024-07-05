#include <unistd.h>
#include <sys/stat.h> // verificar se o diretório existe
#include <iostream>

int main(int argc, char **argv){
    struct stat st; 
    if (argc != 2) {
        std::cerr << "Erro: Número incorreto de argumentos.\n";
        std::cerr << "Uso: " << argv[0] << " <caminho_do_diretorio>\n";
        return 1;
    }
    if (stat(argv[1], &st) == 0) {
        // Se o diretório existe
        if (rmdir(argv[1]) != 0) {
            std::cerr << "Erro: Não foi possível remover este diretório.\n";
            return 1;
        }

    } else {
        std::cerr << "Erro: Diretório não existe.\n";
        return 1;
    }

}