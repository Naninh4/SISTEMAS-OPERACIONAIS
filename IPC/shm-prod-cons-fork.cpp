/* produtor/consumidor: Programa exemplo de memória compartilhada */
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
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

    /***************************PRODUTOR*********************************** */
    if (pid) { /* processo pai: produtor */
        /* Escreve na área os caracteres de 'a' a 'z' */
        for (char c = 'a'; c <= 'z'; c++)
            *s++ = c;
        *s = (char)NULL;
        s = static_cast<char *>(ptr);
        while (*s != '*')
            sleep(1);

        /* Remove memória compartilhada */
        shm_unlink(name);

        /***************************consumidor********************************* */
    } else { /* processo filho: consumidor */
        for (s = static_cast<char *>(ptr); *s != static_cast<char>(NULL); s++)
            std::putchar(*s);
        std::putchar('\n');
        s = static_cast<char *>(ptr);
        *s = '*';
    }
    std::exit(0);
}
