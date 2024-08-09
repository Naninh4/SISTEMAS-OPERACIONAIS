#include <iostream>
#include <fcntl.h>  // Para shm_open, O_RDONLY
#include <sys/mman.h>  // Para mmap, PROT_READ, MAP_SHARED
#include <unistd.h>  // Para close

int main() {
    const char *name = "OS";
    const char *name2 = "argv";
    const int SIZE = 27;

    int shm_fd;
    int arg_fd;

    void *ptr;
    void *oto;

    // Abre a memória compartilhada
    shm_fd = shm_open(name, O_RDWR , 0666);
    arg_fd = shm_open(name2, O_RDONLY, 0666);


    // Mapeia a memória compartilhada para o espaço de endereço do processo
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    oto = mmap(0, SIZE, PROT_READ, MAP_SHARED, arg_fd, 0);
    char *b = static_cast<char *>(oto);


    std::string arq;
    // Constrói o nome do arquivo a partir da memória compartilhada
    for (b = static_cast<char *>(oto);  *b != static_cast<char>(NULL); b++) {
        arq +=*b;
        std::putchar(*b);

    }
    std::putchar('\n');

    // Abre o arquivo destino para escrita
    const char *arquivo = arq.c_str();
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

    close(shm_fd);
    close(arg_fd);
    close(target);
}
