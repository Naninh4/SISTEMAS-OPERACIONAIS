#include <stdio.h>   // Fornece funcionalidades básicas de entrada e saída padrão.
#include <time.h>    // Fornece funções e tipos de dados relacionados ao tempo e data.

int main(int argc, char **argv) {

    time_t tempo_atual;    // Variável para armazenar o tempo atual
    tempo_atual = time(NULL); // Obter o tempo atual em segundos desde o Epoch

    int segundos, minutos, horas;
    segundos = tempo_atual % 60; // Obter os segundos atuais
    tempo_atual /= 60; // Converter para minutos
    minutos = tempo_atual % 60; // Obter os minutos atuais
    tempo_atual /= 60; // Converter para horas
    horas = tempo_atual % 24; // Obter as horas atuais


    // Imprime a hora formatada
    printf("%02d:%02d:%02d\n", horas, minutos,segundos);

    return 0;
}

