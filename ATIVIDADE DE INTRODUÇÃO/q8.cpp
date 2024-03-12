 #include <fcntl.h> // Para as chamadas open e close
#include <unistd.h> // Para as constantes de controle de arquivo:


    // O_RDONLY, O_WRONLY, O_CREAT, S_IRUSR e S_IWUSR

int main(int argc, char ∗∗argv){
        const char *sourcefn = argv[1];
        const char *targetfn = argv[2];
        int source = open(sourcefn, O_RDONLY);
        int target = open(targetfn, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        char buf[1024];
        int s;
        while ((s = read(source, buf, 1024)) != 0)
            write(target, buf, s);
            close(target);
            close(source);
return 0;
}