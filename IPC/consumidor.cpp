#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

int main() {
    const char *name = "OS";
    const int SIZE = 27;

    int shm_fd;
    void *ptr;

    // Abre a memória compartilhada
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Mapeia a memória compartilhada para o espaço de endereço do processo
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Lê o conteúdo da memória compartilhada e escreve na tela
    char *s = static_cast<char *>(ptr);
    for (int i = 0; i < SIZE; i++) {
        if (s[i] == '\0') break;
        std::putchar(s[i]);
    }
    std::putchar('\n');

    // Desmapeia a memória compartilhada
    if (munmap(ptr, SIZE) == -1) {
        perror("munmap");
        return 1;
    }

    // Fecha o descritor de arquivo da memória compartilhada
    if (close(shm_fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
