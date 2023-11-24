#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <stdio.h>
#include <sys/waitwc.h>

using namespace std;
int main(int argc,  char ** argv){

     char *arg1[argc];
     char *arg2[argc];

    int i;
    for( i=1; i<argc; i++){
        if(!strcmp(argv[i],"|")){
            i++;//on recup position du i la ou on a le "|"
            break;
        }//qd on y est pas
        arg1[i-1]= argv[i];//on recopie prmeiere partie de la com
    }

    for(int j = 0; j < i ; j++){
        arg2[j]=argv[i];
        i++;
    }//ici on recopie le reste de la com après le"|"

//du coup ici j'ai premiere comm dans arg1 et 2e comm dans arg2
//maintenant on veut sortie arg1=entrée arg2

    int tube[2];
    if(pipe(tube) == -1){
        perror("pipe");
        exit(1);
    }

    if(fork()==0){//ici fils 1 et sa sortie = tube1
        dup2(tube[1],STDOUT_FILENO);//redirige sortie sur tube[1]
        close(tube[0]);
        close(tube[1]);
        //ici entrée redirigée ok 
        //du coup on execute dans fils arg1
        if(execv(arg1[0],arg1)==-1){
            perror("execv"); exit(3);
        }
    }

    //et ensuite fils2 prend en entrée tub0
    if(fork()==0){
        //pareil que fils1 on redirige entrée
        dup2(tube[0],STDIN_FILENO);
        close(tube[0]);
        close(tube[1]);
        if(execv(arg2[0],arg2)){//execute ce qui est dans arg
            perror("execv"); exit(3);
        }
    }

        //on sort cleaan
        close(tube[0]);
        close(tube[1]);
        wait(NULL);
        wait(NULL);

        return 0;
    
}