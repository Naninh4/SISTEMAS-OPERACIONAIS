Claro! Aqui está o texto em Markdown:

---

### Passos para Criar e Usar uma Área de Memória Compartilhada entre Dois Processos Usando a API POSIX

1. **Criar e Abrir a Memória Compartilhada:**
   ```c
   int shm_fd = shm_open("nome_memoria", O_CREAT | O_RDWR, 0666);
   ```

2. **Configurar o Tamanho da Memória Compartilhada:**
   ```c
   ftruncate(shm_fd, tamanho);
   ```

3. **Mapear a Memória Compartilhada:**
   ```c
   void *ptr = mmap(0, tamanho, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
   ```

4. **Usar a Memória Compartilhada:**
   ```c
   sprintf(ptr, "dados");
   printf("%s\n", (char *)ptr);
   ```

5. **Desmapear a Memória:**
   ```c
   munmap(ptr, tamanho);
   ```

6. **Fechar o Descritor de Arquivo:**
   ```c
   close(shm_fd);
   ```

7. **Remover o Objeto de Memória Compartilhada:**
   ```c
   shm_unlink("nome_memoria");
   ```

---

Esses passos permitem que dois processos compartilhem uma área de memória, facilitando a comunicação entre eles.