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
    const char *name2 = "argv";

    /* fd (File Descriptor) da memória compartilhada */
    int shm_fd;
    int arg_fd;
    
    /* Ponteiro para a área compartilhada */
    void *ptr;
    void *oto;

    /* Cria a área de memória */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    arg_fd = shm_open(name2, O_CREAT | O_RDWR, 0666);

    /* Configura o tamanho da área */
    ftruncate(shm_fd, SIZE);
    ftruncate(arg_fd, SIZE);

    /* Mapeia a área para acesso via ponteiro */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char *s = static_cast<char *>(ptr);

    oto = mmap(0, 32, PROT_WRITE, MAP_SHARED, arg_fd, 0);
    char *b = static_cast<char *>(oto);

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *sourcefn = argv[1];
    const char *targetfn = argv[2];

    int source = open(sourcefn, O_RDONLY);


     // Copiando o conteúdo da variável para a memória compartilhada
    std::strcpy(b, targetfn);

    // Referenciando oto em b e escrevendo o conteúdo na saída padrão
    for (b = static_cast<char *>(oto); *b != static_cast<char>(NULL); b++) {
        std::putchar(*b);
    }

    // Inicializar o buffer e variáveis
    char buf[1];
    int c;

    for (s = static_cast<char *>(ptr); *s != static_cast<char>(NULL); s++)
            std::putchar(*s);

    while ((c = read(source, buf, sizeof(buf))) > 0) {
        *s++ = buf[0];
        std::cout << buf[0];
    }
    int i =0;


    *s = (char)NULL;
    s = static_cast<char *>(ptr); // não estava funcionando por conta disso AQUI. Estava faltando reposicionar o ponteiro para o inicio da área de memória
    // pois o processo consumidor  

    // Espera até que o valor '*' seja encontrado na memória compartilhada
    while (*s != '*') {
        sleep(1);
    }

    /* Remove memória compartilhada */
    shm_unlink(name);
    shm_unlink(name2);
    munmap(ptr, SIZE);
    munmap(oto, SIZE);
    close(shm_fd);
    close(arg_fd);
    close(source);
    return 0;
}
