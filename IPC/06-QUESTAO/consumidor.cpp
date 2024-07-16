#include <iostream>
#include <fcntl.h>  // Para shm_open, O_RDONLY
#include <sys/mman.h>  // Para mmap, PROT_READ, MAP_SHARED
#include <unistd.h>  // Para close

int main(int argc, char **argv) {
    
    const char *name = argv[1];

    const char* S = argv[2];

    const int SIZE = int(S[0]);


    int shm_fd;

    void *ptr;

    // Abre a memória compartilhada
    shm_fd = shm_open(name, O_RDWR , 0666);


    // Mapeia a memória compartilhada para o espaço de endereço do processo
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


    // Abre o arquivo destino para escrita
    const char *arquivo = argv[3];

    int target = open(arquivo, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    char *s = static_cast<char *>(ptr);
    char buf[1];

    for (s = static_cast<char *>(ptr);  *s != static_cast<char>(NULL); s++) {
        std::putchar(*s);
        buf[0] = *s;
        write(target, buf, 1);
    }
    
    std::putchar('\n');
    s = static_cast<char *>(ptr);
    *s = '*';

    close(target);
    return 0;
}
