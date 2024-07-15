#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
// -------------- CRIANDO MEMÓRIA COMPARTILHADA ---------------
/* Tamanho (em bytes) da memória compartilhada */
    const int SIZE = 27;
    /* Nome da área de memória compartilhada */
    const char *name = "OS";
    /* fd (File Descriptor) da memória compartilhda */
    int shm_fd;
    /* Ponteiro para a área compartilhada */
    void *ptr;

    /* Cria a área de memória */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    /* Confifura o tamanho da área */
    ftruncate(shm_fd, SIZE);
    /* Mapeia a área para acesso via ponteiro */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char *s = static_cast<char *>(ptr);
    pid_t pid = fork();


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

    char buf[27];
    int c;
    while ((c = read(source, buf, 27)) != 0) {
        for (int i=0 ; i<c ; ++i){
            *s++ = buf[i];
        }
    }
   
    *s = (char)NULL;
    s = static_cast<char *>(ptr);
    while (*s != '*')
        sleep(1);

    /* Remove memória compartilhada */
    shm_unlink(name);

}
