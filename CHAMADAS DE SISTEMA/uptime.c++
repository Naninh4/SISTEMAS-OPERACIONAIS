#include <stdio.h>   // Fornece funcionalidades básicas de entrada e saída padrão.
#include <time.h>    // Fornece funções e tipos de dados relacionados ao tempo e data.
#include <unistd.h>  // Fornece acesso a funções e constantes para operações de sistema, como manipulação de arquivos.
#include <fcntl.h>   // Fornece constantes e declarações de funções para operações de controle de arquivo.
#include <sstream>   // Para o uso do std::istringstream e std::ostringstream

int err(const char* msg) { // Função para lidar com erros e retornar códigos de erro
    perror(msg); // Imprime uma mensagem de erro formatada
    return 1;    // Retorna 1 indicando erro
}

int main(int argc, char **argv) {

    char buff[256];        // Buffer para armazenar os dados lidos do arquivo

    int origem = open("/proc/uptime", O_RDONLY); // Abre o arquivo /proc/uptime para leitura
    if (origem == -1) return err("Erro ao abrir o arquivo"); // Verifica se houve erro na abertura do arquivo

    int destino = read(origem, buff, 256); // Lê os dados do arquivo e armazena em buff
    if (destino == -1) return err("Erro ao ler o arquivo"); // Verifica se houve erro na leitura do arquivo

    std::istringstream iss(buff); // Transforma o conteúdo de buff em uma std::istringstream para facilitar a extração de dados
    int segs;                     // Variável para armazenar os segundos lidos do arquivo
    iss >> segs;                  // Extrai os segundos do arquivo e armazena em segs

    // Calcula horas, minutos e segundos a partir dos segundos lidos
    int horas = segs / 3600;
    int minutos = (segs / 60) % 60;
    int segundos = segs % 60;

    std::ostringstream Mycout; // Cria um std::ostringstream para formatar a saída
    Mycout << horas << "h:" << minutos << "m:" << segundos << "s" << "\n"; // Formata a saída com horas, minutos e segundos
    std::string TempoFormatado = Mycout.str(); // Converte o conteúdo de cout em uma string
    write(STDOUT_FILENO, TempoFormatado.c_str(), TempoFormatado.size()); // Escreve o conteúdo formatado na saída padrão do sistema (terminal)

    close(origem); // Fecha o arquivo

    return 0; 
}
