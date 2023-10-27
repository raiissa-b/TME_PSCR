#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << "main ppid : " << getppid()
	 << std::endl;

	//pour le wait
	int nbFils =0;


	//for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		for (int i=1, j=N; i<=N && j==N ; i++ ) {
			if( fork() != 0){
				nbFils++; break;
				
			}else { nbFils=0;
		
				std::cout << "pid : " << getpid() << " ppid :" << getppid() 
				<< " i:j " << i << ":" << j << std::endl;
				for (int k=1; k<=i && j==N ; k++) {
					if ( fork() == 0) {
					nbFils = 0;
					j=0;
					std::cout << "pid : " << getpid()
					<< " pere : " << getppid() 
					<<" k:j " << k << ":" << j << std::endl;
				}
				else{ nbFils++;}
				}
		
			}
			
		}
	

	for( int cpt = 0 ; cpt < nbFils ; cpt ++){

		if( wait(NULL) == -1){
			std::cout << " erreur trop de wait loser " << std::endl;
		}
	
	}
	if( wait(NULL) != -1){
		std::cout << "erreur il en reste lsoer " << std::endl;
	}


	return 0;
}
