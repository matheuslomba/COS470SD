#include <iostream>
#include <unistd.h>
#include <csignal>
#include <cstring>

using namespace std;

//Variável Global
int pidprocesso;

//-----------------------------------------------------------------------------------------------------

//Função para o handler
void handlersignal(int sinal) {

        if(sinal == SIGUSR1) {
            cout << "Enviando sinal SIGUSR1 para o processo " << pidprocesso << endl;
            kill(pidprocesso, SIGUSR1);
        } else if(sinal == SIGUSR2) {
            cout << "Enviando sinal SIGUSR2 para o processo " << pidprocesso << endl;
            kill(pidprocesso, SIGUSR2);
        } else if(sinal == SIGINT) {
            cout << "Enviando sinal SIGINT para o processo " << pidprocesso << endl;
            kill(pidprocesso, SIGINT);
        } else if(sinal == SIGTERM) {
            cout << "Finalizando o programa..." << endl;
            cout << "-----------------------------------------" << endl; 
            kill(pidprocesso, SIGTERM);
            exit(sinal);
        }
}

//-----------------------------------------------------------------------------------------------------

int main() {

    //Informa PID do processo atual
    cout << "PID do 1º programa: " << getpid() << endl;

    //Pega o PID do processo e o sinal
    cout << "Digite o número do processo destino: ";
    cin >> pidprocesso;

    cout << "-----------------------------------------" << endl;

    //Verifica se o processo indicado existe
    if (0 == kill(pidprocesso, 0)) { //Processo existe
        //Envia o sinal ao programa
        cout << "Processo válido." << endl;
    } else { //Processo não existe
        cout << "O processo indicado não existe. Favor rodar o programa novamente e inserir um pid válido." << endl;
        exit(1);
    }

    //-----------------------------------------------------------------------------------------------------

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

    //Aguarda sinal do usuário
    cout << "Sinais que podem ser usados:" << endl;
    cout << "SIGUSR1\nSIGUSR2\nSIGINT\nSIGTERM - finaliza os programas" << endl;
    cout << "Insira o sinal que deve ser enviado ao processo destino. " << endl;
    while(1) {
        sleep(1);
    }

    return 0;

}