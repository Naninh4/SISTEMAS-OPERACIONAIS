## Sistemas operacionais
> *Exercício 01 - Introdução, Estrutra de um SO*
1. **O que é um Sistema Operacional?**
   Um Sistema Operacional (SO) é um software que gerencia os recursos de hardware e fornece serviços para programas de aplicação. Ele atua como uma camada intermediária entre o hardware e os programas, facilitando a execução eficiente de tarefas do usuário.

2. **Quais as funções de um Sistema Operacional?**
   As funções principais de um Sistema Operacional incluem gerenciamento de recursos (CPU, memória, dispositivos de armazenamento), fornecimento de uma interface para interação com o usuário, execução de programas e garantia de segurança e proteção.

3. **O que são e para que serve os modos de operação de um processador?**
   Os modos de operação, como o modo usuário e o modo kernel, definem o nível de privilégio de execução de instruções. O modo kernel permite acesso total ao hardware, enquanto o modo usuário tem restrições. Isso ajuda a proteger o sistema operacional e os programas em execução.

4. **O que são e para que servem as interrupções em um processador?**
   Interrupções são sinais que o hardware ou software envia ao processador para indicar a necessidade de atenção imediata. Elas interrompem a execução normal do programa, permitindo lidar com eventos assíncronos, como entradas/saídas, erros ou solicitações de serviço.

5. **Explique como a hierarquia de memórias melhora o desempenho de um computador.**
   A hierarquia de memórias, incluindo a memória cache, RAM e armazenamento de longo prazo, permite um acesso mais rápido e eficiente aos dados. A memória cache, em particular, armazena dados frequentemente usados, reduzindo o tempo de acesso à RAM e melhorando o desempenho global do sistema.

6. **Como funciona um acesso direto a memória (DMA - Direct Memory Access)?**
   O DMA é um mecanismo que permite que dispositivos periféricos acessem diretamente a memória sem intervenção da CPU. Isso melhora a eficiência do sistema, pois os dados podem ser transferidos diretamente entre dispositivos e memória sem a necessidade de envolvimento constante da CPU.

7. **O que é e para que serve uma chamada de sistema (system call)?**
   Uma chamada de sistema é uma interface entre os programas de aplicação e o kernel do sistema operacional. Ela permite que os programas solicitem serviços específicos ao sistema operacional, como operações de leitura/gravação em disco, criação de processos, entre outras operações de baixo nível.

8. Considere o programa a seguir:

```cpp
        #include <fcntl.h> // Para as chamadas open e close
        #include <unistd.h> // Para as constantes de controle de arquivo:


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

**`mprotect`:**
   - **Função:** Altera as permissões de proteção de uma região de memória.
   - **Utilização Típica:** Pode ser usada para modificar as permissões de uma página de memória, como torná-la executável ou somente leitura.

**`openat`:**
   - **Função:** Abre ou cria um arquivo ou diretório.
   - **Utilização Típica:** É usada para abrir arquivos, e é semelhante à chamada de sistema `open`. A diferença principal é que `openat` permite especificar um diretório base para caminhos relativos.

**`access`:**
   - **Função:** Verifica se um processo tem permissão de acesso a um arquivo ou diretório.
   - **Utilização Típica:** Pode ser usada para verificar a existência de um arquivo, bem como as permissões de leitura, gravação e execução para o processo.

**`write`:**
   - **Função:** Escreve dados em um arquivo ou descritor de arquivo.
   - **Utilização Típica:** Usada para escrever informações em um arquivo aberto. Pode ser usado com arquivos regulares, pipes, sockets, entre outros.

**`read`:**
   - **Função:** Lê dados de um arquivo ou descritor de arquivo.
   - **Utilização Típica:** Usada para ler informações de um arquivo aberto. Pode ser usado com arquivos regulares, pipes, sockets, entre outros.



**OBS: Para diminuir a quantidade de chamadas de sistema compile com a opção -static:**
> ```gcc −Wall −O2 −static −o copy copy.c```

9. Na questão anterior, a opção do compilador -static diminui a quantidade de chamadas de
sistema. Explique por que isso acontece.

    - A opção do compilador -static diminui a quantidade de chamadas de sistema ao carregar os códigos diretamente, em vez de realizar a ligação dinâmica durante a execução. Quando a opção -static é utilizada, as bibliotecas necessárias para a execução do programa são incorporadas diretamente no binário compilado. Isso elimina a necessidade de procurar e carregar essas bibliotecas dinamicamente durante a execução do programa, resultando em uma redução das chamadas de sistema associadas à resolução dinâmica de símbolos e carregamento de bibliotecas compartilhadas. Essa abordagem estática pode melhorar o desempenho e a eficiência do programa, uma vez que as dependências são tratadas durante a fase de compilação.

10. Complete o programa de cópia de arquivos para que ele faça todas as verificações para
funcionar corretamente: 
- Parâmetros do programa estão corretos? ✅
- arquivo origem existe? ✅
- posso ler? ✅
- arquivo destino não pode existir. ✅
- O nome do arquivo é válido? ✅
- Posso escrever no diretório do arquivo destino? ✅

Identifique todas as chamadas de sistema necessárias para o funcionamento correto do programa:
- Principalmente o access e o open, o retorno deles vai determinar as tarefas que o código vai desempenhar de fato.


