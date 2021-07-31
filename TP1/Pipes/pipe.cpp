#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#include "../FuncSup/suporte.cpp"

using namespace std;

#define READ 0
#define WRITE 1

//-------------------------------------------------------------------------------

// Funções e variáveis
void produtor(int fd[2], int qtde_numeros);
void consumidor(int fd[2]);
int maxn;
int n0=1;

//-------------------------------------------------------------------------------

int main (){
    int fd[2];
   
    printf("Selecione a quantidade de números a serem gerados: ");
    scanf("%d", &maxn);
   
    // Criando pipe
    pipe (fd);
   
    // Criando novo processo
    int pid = fork();
   
    if (pid == -1) {
        perror("Erro ao criar um novo processo!");
    } else if (pid > 0) {
        // O processo pai funciona como produtor
        produtor(fd, maxn);
    } else {
        // O processo filho funciona como consumidor
        consumidor(fd);
    }
   
    return 0;
    }
   
    // Programa produtor, recebe o pipe e quantidade de numeros
    void produtor(int fd[2], int qtde_numeros) {
        // Fechando a leitura do pipe
        close(fd[READ]);
       
        int i, bytesEscritos;
       
        // Loop onde o produtor vai ficar ate "produzir" todos os números
        // Sleep definindo um tempo aleatório entre os números produzidos
        // n0 vai incrementando
        // Quando i é igual a qtde_numeros o produtor envia 0 no pip
        for (i = 1 ; i <= qtde_numeros; i++) {
           
            sleep(1);
           
            n0 = n0 + ran();
           
            cria_num(n0);
           

            // Escreve no pipe
            bytesEscritos = write(fd[WRITE], &n0, sizeof(int));

            if (bytesEscritos == -1) {
               perror("Erro de escrita no pipe!");
            }
            if(i==qtde_numeros){
                int n0 = 0;
                bytesEscritos = write(fd[WRITE], &n0, sizeof(int));
            }
           
        }
        wait(NULL);
        close (fd[WRITE]);
    }
   
// Programa consumidor, recebe o pipe
// Quando o consumidor lê i igual a 0, ele finaliza

void consumidor(int fd[2]){
    // Fechando a escrita do pipe
    close (fd[WRITE]);
   
    int i, bytesLidos;
    while (true) {
        // Lê do pipe,colocando o valor da leitura em i
        bytesLidos = read (fd[READ], &i, sizeof(int));
        sleep(1);
   
        if(i==0){
            break;
        }
        
        if (e_primo(i)){
            printf("%d é primo.\n", i);
        } else {
            printf("%d não é primo.\n", i);
        }

        if (bytesLidos == -1) {
           perror("Erro de leitura no pipe!");
        }
    }
}