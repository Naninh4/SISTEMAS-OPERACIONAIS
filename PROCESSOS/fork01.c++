#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid; // criou um processo
    pid  = fork(); // dividiu o processo
    // o fork retorna 0 no processo filho
    // o fork retorna o valor no processo filho no pid do pai

    if(pid==0){ // sou o filho
        sleep(1);
        std::cout << "I dont want to be your son: My pid= " << getpid() << std::endl;
        sleep(5);
    }else{ // sou o pai
        std::cout << "I your father Luke: My pid=" <<  getpid() << std::endl;
        sleep(2);
        std::cout << "I know your PID ahahahahahah " << pid << std::endl;
        sleep(4);
    }
   
    // std::cout << "My pid: " << getpid();
    // std::cout << " pid=" << pid << std::endl;
    // sleep(10);
    return 0;
}