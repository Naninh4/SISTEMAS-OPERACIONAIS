#include <unistd.h>
#include <fcntl.h>

int main(int agrc, char **argv){

    if (argc != 2) {
        std::cerr << "Erro: Número incorreto de argumentos.\n";
        std::cerr << "Uso: " << argv[0] << " <caminho_do_arquivo>\n";
        return 1;
    }

    char buff[16];

    int saida, file; // declarando arquivos de entrada e saída
    if( file =  open(argv[1], O_RDONLY)){ // Verificando se o arquivo foi aberto
        while((saida = read(file, buff, 16)) !=0){ // lendo o arquivo de 16 em 16 bits até que não tenha mais texto
            write(1, buff, 16); // Se conseguiu ler 16 bits ele escreve o conteudo na saída padrão (1);
        }
    }else{
        write(1, "Não foi possível abrir o arquivo", 29);// informa que não foi possível abrir o arquivo
    }


}