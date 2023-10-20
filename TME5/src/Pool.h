#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

	void poolWorker(Queue<Job>& queue){
		while(true){
			Job *j = queue.pop();//on recup tache à faire dans queue
			if(j == nullptr) break; //si ==nullptr alors on a fini, plus de taff
			j->run(); // sinon on taff
			delete j; // et on supp j
		}
	}

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) : queue(qsize){}//on appelle ctor de queue avec qsize donné en arg

	void start (int nbthread){

		threads.reserve(nbthread);

		//on créer nbthread threads
		for(int i = 0; i < nbthread ; i++){

			threads.emplace_back(poolWorker,std::ref(queue));
			//chaque thread va dans pool worker
		}
	}

	void submit (Job * job) {
		queue.push(job); // on ajotue du taff dans la queue
	}
	void stop() {

		queue.setBlocking(false); // on arrete donc on bloque tout 

		//on attend tout les threads
		for( auto &t : threads ){
			t.join();
		}
	}
	~Pool() {}
};

}
