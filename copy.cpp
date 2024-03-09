#include <fcntl.h> // Para as chamadas open e close
#include <unistd.h> // Para as constantes de controle de arquivo:
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        _exit(EXIT_FAILURE);
    }

    const char *sourcefn = argv[1];
    const char *targetfn = argv[2];
    int source = open(sourcefn, O_RDONLY);
    int target = open(targetfn, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    char buf[1024];

    int s;

    while ((s = read(source, buf, 1024)) != 0){
        write(target, buf, s);
        close(target);
        close(source);
    }

    return 0;

}