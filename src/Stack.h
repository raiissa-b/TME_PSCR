#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t sempop; 
	sem_t sempush;
	sem_t mutex;
public :
	Stack () : sz(0) {
		 memset(tab,0,sizeof tab);
		 sem_init(&sempop,1,0);//au debut c'est vide du coup 
		 sem_init(&sempush,1,STACKSIZE);//vide au debut du coup on peut push stacksize fois
		 sem_init(&mutex,1,1);
		 }
	~Stack(){
		sem_destroy(&sempop);
		sem_destroy(&mutex);
		sem_destroy(&sempush);
	}

	T pop () {
		// bloquer si vide
		sem_wait(&sempop);//si vide wait que someone fasse un push
		//prend mutex si il peut pop
		sem_wait(&mutex);
		
		T toret = tab[--sz];
		sem_post(&sempush);//quand on a pop on prévient push que c'est pas plein
		sem_post(&mutex);//qd on a fniit on rend le mutex
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&sempush);//prend mutex une fois qu'il est debloqué
		//prend mutex
		sem_wait(&mutex);
		tab[sz++] = elt;
		sem_post(&sempop);
		sem_post(&mutex); // on rend le mutex qd on a fini

	}
};

}
