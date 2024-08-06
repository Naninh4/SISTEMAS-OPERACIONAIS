
!(shellsBar.jpg)


# shellsBar

Este é um shell simples em C++ que suporta execução de comandos básicos, manipulação de diretórios, e execução de processos em segundo plano.

## Funcionalidades

O shell oferece as seguintes funcionalidades:

1. **Execução de Comandos**: Você pode executar comandos do sistema operacional como `ls`, `pwd`, `cd`, etc.
2. **Histórico de Comandos**: Armazena comandos executados em uma sessão para que você possa visualizar ou repetir comandos anteriores.
3. **Processos em Segundo Plano**: Executa comandos em segundo plano usando o operador `&`.
4. **Manipulação do PATH**: Permite alterar a variável PATH para determinar onde procurar binários executáveis.
5. **Listagem de Processos em Segundo Plano**: Lista os processos que estão rodando em segundo plano.(Apesar de que não consegui verificar quando ele acaba para tirar ele da lista :()

## Uso

Para compilar e executar o shell:

```bash
g++ -o shellsBar shellsBar.cpp
./shellsBar
```

### Comandos internos Suportados

- `cd <diretório>`: Muda o diretório atual para `<diretório>`.
- `pwd`: Exibe o diretório de trabalho atual.
- `history`: Mostra o histórico de comandos. Use `history -c` para limpar o histórico ou `history <número>` para executar um comando anterior.
- `exit`: Fecha o shell.
- `echo $PATH`: Exibe o caminho atual dos diretórios de busca de comandos.
- `PATH=<novo_path>`: Define uma nova variável de ambiente PATH.
- `<comando> &`: Executa `<comando>` em segundo plano.
- `jobs`: Lista os processos que estão rodando em segundo plano.

### Exemplo

```shell
$> pwd
/home/usuario

$> cd /var/log
$> pwd
/var/log

$> ls &
Número do processo em background: 12345

$> jobs
12345

$> history
3 cd /var/log
2 pwd
1 pwd
```

## Vulnerabilidades

Existem algumas vulnerabilidades de segurança conhecidas neste shell que devem ser consideradas:

### 1. **Injeção de Comandos**

Este shell não verifica a entrada do usuário para caracteres especiais ou sequências de comando perigosas, permitindo potencialmente que comandos arbitrários sejam executados.

**Solução Potencial:** Implementar um parser que saneie a entrada do usuário antes de executar comandos. Verificar especificamente por injeções de comandos comuns, como `&&`, `||`, `;`, etc.

### 2. **Permissões de Acesso**

O shell não verifica adequadamente as permissões de execução antes de tentar executar um comando. Se um arquivo não é executável, ele simplesmente falha ao tentar executá-lo, mas não oferece feedback claro.

**Solução Potencial:** Antes de tentar executar um comando, verificar explicitamente as permissões de arquivo com `access` para garantir que o arquivo é de fato executável e fornecer mensagens de erro detalhadas.

### 3. **Caminhos Relativos e Variáveis de Ambiente**

Atualmente, o shell não gerencia variáveis de ambiente além de PATH, e o PATH é alterado de maneira que pode não persistir entre as execuções.

**Solução Potencial:** Implementar suporte para mais variáveis de ambiente e gerenciar caminhos relativos com mais precisão, garantindo que as mudanças no PATH sejam refletidas adequadamente em cada execução.

## Melhorias Futuras

- **Adicionar Suporte a Pipes**: Implementar a capacidade de encadear comandos usando pipes (`|`).
- **Gerenciamento Avançado de Sinais**: Melhorar o manuseio de sinais para processos em segundo plano, permitindo que eles sejam terminados ou suspensos de forma limpa (Não consegui implementar :( ).
- **Interface de Configuração**: Adicionar opções de configuração para personalizar o shell, como cores, prompt, etc.


## Contribuições

Contribuições são bem-vindas! Se você encontrar bugs, tiver sugestões de melhorias ou novas funcionalidades, sinta-se à vontade para sugerir.

## Licença

Todos os direitos reservados a mim e aos anjos do stackoverflow

