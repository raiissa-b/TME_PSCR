#include "Banque.h"
#include <iostream>
#include <ctime> //pour time de rand
#include <cstdlib>//pour rand et srand
#include <thread>
#include <chrono>

using namespace std;
using namespace pr;

const int NB_THREAD = 50;
const int NB_COMPTES = 500; 
const unsigned int SOLDE_INI = 100;

void transaction(Banque &b){

	for(int k = 0; k<1000 ; k++){// a chaque tour de boucle on a de nvx i,j,m

		int m = rand() %  100 + 1; //montant aléatoire
		int i = rand() %  NB_COMPTES;  //debiteur
		int j = rand() % NB_COMPTES ; // 100 rediteur 

		b.transfert(i, j, m);//appel transfert 

		//auto r = rand() % 2; //rand de 0 à 20sec
		//this_thread::sleep_for(chrono::milliseconds(r));

	}
}

int main () {
	
	vector<thread> threads;

	//creation banque contenant nbCompte de soldeIni solde
	Banque b(NB_COMPTES, SOLDE_INI);

	srand( time( nullptr )); //seed pour le rand

	//creation threads
	for(int i = 0 ; i < NB_THREAD; i++ ){

		threads.push_back(thread(transaction,ref(b)));
	} 

	for (auto & t : threads) {
		t.join();
	}
	
	cout << "ok pas de pb jusque la:) "<< endl;
	cout << "Vérif du solde total de la banque : "<< endl;

	if( (NB_COMPTES * SOLDE_INI ) == b.verifSolde() ){
		cout << "yayyyyy :) on a bien : "<< NB_COMPTES * SOLDE_INI << endl; 
	}else {
		cout << "boooouuh loser :( il manque : "<<  (NB_COMPTES * SOLDE_INI) - b.verifSolde() << endl;
	}


	
	return 0;
}
