#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <csignal>
#include <cstring>

using namespace std;

//-----------------------------------------------------------------------------------------------------

//Função para o handler
void handlersignal(int sinal) {

        if(sinal == SIGUSR1) {
            cout << "Sinal SIGUSR1 recebido." << endl;
        } else if(sinal == SIGUSR2) {
            cout << "Sinal SIGUSR2 recebido." << endl;
        } else if(sinal == SIGINT) {
            cout << "Sinal SIGINT recebido." << endl;
        } else if(sinal == SIGTERM) {
            cout << "Sinal SIGTERM recebido." << endl;
            cout << "Finalizando o programa..." << endl;
            cout << "-----------------------------------------" << endl;
            exit(sinal);
        }
}

//-----------------------------------------------------------------------------------------------------

int main() {

    int espera;

    //Informa PID do processo atual
    cout << "PID do 2º programa: " << getpid() << endl;

    cout << "Como deseja esperar pelo sinal no 1º programa?\n1 = busy wait\n2 = blocking wait" << endl;
    cin >> espera;

    //Registra sinais e signal handler
    signal(SIGUSR1, handlersignal);
    signal(SIGUSR2, handlersignal);
    signal(SIGINT, handlersignal);
    signal(SIGTERM, handlersignal);

    //Informa sobre erros no sinal inputado
    if(signal(SIGUSR1, handlersignal) == SIG_ERR) {
        cout << "SIGUSR1 não recebido." << endl;
    } else if(signal(SIGUSR2, handlersignal) == SIG_ERR) {
        cout << "SIGUSR2 não recebido." << endl;
    } else if(signal(SIGINT, handlersignal) == SIG_ERR) {
        cout << "SIGINT não recebido." << endl;
    } else if(signal(SIGTERM, handlersignal) == SIG_ERR) {
        cout << "SIGTERM não recebido." << endl;
    }

    //Método de espera:
    if (espera == 1) { //Busy Wait
        cout << "Esperando o sinal com busy wait..." << endl;
        while(1) {
            sleep(1);
        }
    } else if (espera == 2){ //Blocking Wait
        cout << "Esperando o sinal com blocking wait..." << endl;
        while(1){
            pause();
        }
    }

    return 0;

}