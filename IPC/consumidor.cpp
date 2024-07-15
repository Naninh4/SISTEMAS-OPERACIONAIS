#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

int main() {
    const char *name = "OS";
    const char *name2 = "argv";
    const int SIZE = 27;

    int shm_fd;
    int arg_fd;

    void *ptr;
    void *oto;

    // Abre a memória compartilhada
    shm_fd = shm_open(name, O_RDONLY, 0666);
    arg_fd = shm_open(name2, O_RDONLY, 0666);


    // Mapeia a memória compartilhada para o espaço de endereço do processo
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    oto = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, arg_fd, 0);
    char *b = static_cast<char *>(oto);

    // Constrói o nome do arquivo a partir da memória compartilhada
    std::string arquivo = "arquivo.txt";
    
    for (char *b = static_cast<char *>(oto);  *b != static_cast<char>(NULL); b++) {
        std::putchar(*b);
    }
    // Abre o arquivo destino para escrita
    int target = open(arquivo.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (target == -1) {
        perror("open");
        return 1;
    }


    char *s = static_cast<char *>(ptr);
    char buf[1];

     for (char *s = static_cast<char *>(ptr);  *s != static_cast<char>(NULL); s++) {
        std::putchar(*s);
        buf[0] = *s;
        write(target, buf, 1);
    }
        std::putchar('\n');
        s = static_cast<char *>(ptr);
        *s = '*';
    

    close(target);
    munmap(ptr, SIZE);
    munmap(oto, SIZE);
    close(shm_fd);
    close(arg_fd);
    return 0;
}
