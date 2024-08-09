/* produtor/consumidor: Programa exemplo de memória compartilhada */
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h> // Necessário para a função wait
#include <cstring>    // Necessário para std::to_string

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <arquivo de origem> <arquivo de destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Tamanho (em bytes) da memória compartilhada */
    const int SIZE = 27;
    /* Nome da área de memória compartilhada */
    const char *name = "OS";
    /* fd (File Descriptor) da memória compartilhada */
    int shm_fd;
    /* Ponteiro para a área compartilhada */
    void *ptr;

    /* Cria a área de memória */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open falhou");
        exit(EXIT_FAILURE);
    }

    /* Configura o tamanho da área */
    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate falhou");
        exit(EXIT_FAILURE);
    }

    /* Mapeia a área para acesso via ponteiro */
    ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap falhou");
        exit(EXIT_FAILURE);
    }

    char *s = static_cast<char *>(ptr);
    const char *size = "27";

    pid_t pid = fork();

    const char *arquivoOrigem = argv[1];
    const char *arquivoDestino = argv[2];

    /***************************PRODUTOR***********************************/
    if (pid > 0) { /* processo pai: produtor */
        pid = fork();
        if (pid == 0) {
            const char *programa = "produtor";
            if (execl(programa, programa, name, size, arquivoOrigem, NULL) == -1) {
                perror("execl falhou");
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
            s = static_cast<char *>(ptr);
            while (*s != '*') {
                sleep(1);
            }
            /* Remove memória compartilhada */
            shm_unlink(name);
        }

    /***************************CONSUMIDOR*********************************/
    } else { /* processo filho: consumidor */
        const char *programa = "consumidor";
        if (execl(programa, programa, name, size, arquivoDestino, NULL) == -1) {
            perror("execl falhou");
            exit(EXIT_FAILURE);
        }
        s = static_cast<char *>(ptr);

    }

    return 0;
}
