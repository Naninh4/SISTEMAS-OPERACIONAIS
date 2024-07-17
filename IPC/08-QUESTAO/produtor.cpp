#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

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
    char *s = static_cast<char *>(ptr);


    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Abre o arquivo destino para escrita
    const char *sourcefn = argv[3];

    int source = open(sourcefn, O_RDONLY);

 
    // Inicializar o buffer e variáveis
    char buf[1];
    int c;

    while ((c = read(source, buf, sizeof(buf))) > 0) {
        *s++ = buf[0];
        std::cout << buf[0];
    }


    *s = (char)NULL;
    s = static_cast<char *>(ptr); // não estava funcionando por conta disso AQUI. Estava faltando reposicionar o ponteiro para o inicio da área de memória
    // pois o processo consumidor  


    close(source);
    return 0;
}
