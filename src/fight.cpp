#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"


//point de vie chaque processus en aura 3
int xp = 3; 

void handler(int sig){
    //pdt attaque si on reçoit un sigint on --xp
    if( sig == SIGINT){

        if(xp == 0){
            std::cout<< "piou piou " << getpid() <<" est dead bye " << std::endl;
        }
        else{

    
        xp--;
        std::cout << " piou piou il reste " << xp 
        << " point de vie pour " << getpid() << std::endl;
        }
    }

}


void attaque( pid_t adversaire){
    struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);


    //envoi sigint à adversaire
    if(kill(adversaire, SIGINT) == -1){
        //si kill return -1 adversaire a perdu 
        exit(0);
    }

    //dodo aléatoire
    randsleep();

}

void defense(){
    // se protege 
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT,&sa,NULL); 

    //dodo
    randsleep();
}

void combat( pid_t adversaire ){
    while(true){

        defense();
        attaque(adversaire);

    }
}






