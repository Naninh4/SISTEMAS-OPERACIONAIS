#include <iostream>
#include <unistd.h> 

using namespace std;

int main() {
    // Desativa o buffer de stdout
    setvbuf(stdout, NULL, _IONBF, 0); 

    for(int x = 0; x < 10; x++) {
        cout << x << endl;  // Uso de flush para garantir a saída imediata
        sleep(1);
    }

    return 0;
}
