#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

void handler(){
	for(pid_t p : pidsC){
		kill(p, SIGINT);
	}

}

std::vector<pid_t> pidsC;
int main () {
	//quand ctrl C => termine ses fils?
	signal(SIGINT, handler);

	//créer segment shm
	int fd = shm_open("/myshm", O_RDWR|O_CREAT|O_EXCL,0600);
	//sorte de malloc
	ftruncate(fd, sizeof(Stack<char>));
	//map
	void * addr = mmap(nullptr, sizeof(Stack<char>), 
	PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);


	Stack<char> * s = new (addr)Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}


	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}else{
		pidsC.push_back(pc);

	}
	

	wait(0);
	wait(0);

	shm_unlink("/myshm");

	delete s;
	return 0;
}

