#include <stdio.h> // Fornece funcionalidades de entrada e saida de dados write e read
#include <unistd.h>  // Fornece acesso a funções e constantes para operações de sistema, como manipulação de arquivos.
#include <cstdlib>
#include <string>


int main(int argc, char **argv){
    if(argc !=3){
        fprintf(stderr, "Uso: rm <arquivo_para_remover> \n");
        return 1;
    }
    std::string file = argv[2];
    
    if (access(file.c_str(), F_OK) != 0) {
        fprintf(stderr, "O arquivo não existe neste diretório\n");
        return 1;
    }
    if(access(file.c_str(), W_OK) != 0){ // verificando se o usuário tem a permissão de escrever no arquivo (Consequêntemente se ele tem permissão de apagar ele).
        fprintf(stderr, "Você não possui permissão para remover este arquivo\n");
        return 1;
    }
    if (std::remove(file.c_str()) == 0) fprintf(stdout, "Arquivo <%s> removido com sucesso!\n", file.c_str());
    else{
          fprintf(stderr, "Erro ao remover o arquivo <%s>\n", file.c_str());
          return 1;
    }
    return 0;

}