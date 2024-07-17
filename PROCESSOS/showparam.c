#include <stdlib.h>
#include <stdio.h>
int main(int argc, char ** argv){
if (argc!=2){
printf("Uso: showparam [PAR]\n");
exit(-1);
}
printf("%s\n",argv[1]);
exit(0);
}