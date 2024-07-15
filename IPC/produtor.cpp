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
    int arg;
    /* Ponteiro para a área compartilhada */
    void *ptr;
    void *oto;

    /* Cria a área de memória */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    arg = shm_open(name2, O_CREAT | O_RDWR, 0666);

    /* Configura o tamanho da área */
    ftruncate(shm_fd, SIZE);
    ftruncate(arg, SIZE);

    /* Mapeia a área para acesso via ponteiro */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char *s = static_cast<char *>(ptr);

    oto = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, arg, 0);
    char *b = static_cast<char *>(oto);

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *sourcefn = argv[1];
    std::string targetfn = argv[2];
 
    int source = open(sourcefn, O_RDONLY);

    if (source < 0) {
        perror("Erro ao abrir o arquivo de origem");
        exit(EXIT_FAILURE);
    }

 

    // Inicializar o buffer e variáveis
    char buf[1];
    int c;

    while ((c = read(source, buf, sizeof(buf))) > 0) {
        *s++ = buf[0];
        std::cout << buf[0];
    }
    int i =0;
    while(targetfn[i] != NULL){
        buf[0] = targetfn[i];
        *b = buf[0];
        i++;
    }


    // Escreve os argumentos de linha de comando em *b
 

    *s = (char)NULL;
 // Finaliza a string com o caractere nulo

    // Espera até que o valor '*' seja encontrado na memória compartilhada
    while (*s != '*') {
        sleep(1);
    }

    /* Remove memória compartilhada */
    shm_unlink(name);
    shm_unlink(name2);

    return 0;
}
