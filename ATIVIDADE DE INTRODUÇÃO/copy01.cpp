#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *sourcefn = argv[1];
    const char *targetfn = argv[2];

    int source = open(sourcefn, O_RDONLY);
    if (source == -1) {
        perror("Erro ao abrir o arquivo de origem");
        exit(EXIT_FAILURE);
    }

    if (access(sourcefn, R_OK) == -1) {
        perror("Arquivo de origem não pode ser lido");
        close(source);
        exit(EXIT_FAILURE);
    }

    if (access(targetfn, F_OK) != -1) {
        fprintf(stderr, "O arquivo destino já existe\n");
        close(source);
        exit(EXIT_FAILURE);
    }

    int target = open(targetfn, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (target == -1) {
        perror("Erro ao abrir o arquivo de destino");
        close(source);
        exit(EXIT_FAILURE);
    }

    if (access(targetfn, W_OK) == -1) {
        perror("O arquivo destino não possui permissão de escrita");
        close(source);
        close(target);
        exit(EXIT_FAILURE);
    }

    char buf[1024];
    int s;

    while ((s = read(source, buf, 1024)) != 0) {
        if (s == -1) {
            perror("Erro ao ler o arquivo de origem");
            close(source);
            close(target);
            exit(EXIT_FAILURE);
        }

        if (write(target, buf, s) == -1) {
            perror("Erro ao escrever no arquivo de destino");
            close(source);
            close(target);
            exit(EXIT_FAILURE);
        }
    }

    close(source);
    close(target);

    return 0;
}
