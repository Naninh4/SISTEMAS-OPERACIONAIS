## Sistemas operacionais
> *Exercício 01 - Introdução, Estrutra de um SO*
1. O que é um Sistema operacional?
        - **
2. Quais as funções de um Sistema operacional?
        - **
3. O que são e para que serve os modos de operação de um processador?
        - **
4. O que são e para que servem as interrupções em um processador?
        - **
5. Explique como a hierarquia de memórias melhora o desempenho de um computador.
Dica: Fale sobre a memória cache.
        - **



6. Como funciona um acesso direto a memória (DMA - Direct Memory access)?

        - **


7. O que é e para que serve uma chamada de sistema (system call)?
8. Considere o programa a seguir:
#include <fcntl.h> // Para as chamadas open e close
#include <unistd.h> // Para as constantes de controle de arquivo:


```cpp
    // O_RDONLY, O_WRONLY, O_CREAT, S_IRUSR e S_IWUSR

    int main(int argc, char ∗∗argv){
        const char ∗sourcefn = argv[1];
        const char ∗targetfn = argv[2];
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
```
Execute o programa e identifique todas as chamadas de sistema feitas durante a execução.
Use o programa strace1 para listar as chamadas de sistema. Escreva uma pequena explicação
do que faz faz cada chamada.

**OBS: Para diminuir a quantidade de chamadas de sistema compile com a opção -static:**
> ```gcc −Wall −O2 −static −o copy copy.c```

9. Na questão anterior, a opção do compilador -static diminui a quantidade de chamadas de
sistema. Explique por que isso acontece.
        - **

10. Complete o programa de cópia de arquivos para que ele faça todas as verificações para
funcionar corretamente: 
- Parâmetros do programa estão corretos? ✅
- arquivo origem existe? ✅
- posso ler? ✅
- arquivo destino não pode existir. ✅
- O nome do arquivo é válido? ✅
- Posso escrever no diretório do arquivo destino? ✅

Identifique todas as chamadas de sistema necessárias para o funcionamento correto do programa.


