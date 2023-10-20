#include "tme3exo1.h"
#include <vector>
#include <iostream>
#include <string>

using namespace tme3;
using namespace std;

int main() {

    vector<string> vMots; 
    string tab[6]= {"hello", "world", "it's", "world", "world", "/0"};

    for(int i = 0; tab[i] != "/0"; i++){

        vMots.push_back( tab[i] );

    }

    size_t nbMotsBE = count(vMots.begin(), vMots.end());

    cout << " Nombre de mots du début à la fin : " << nbMotsBE << endl;

    size_t nbEqualW = count_if_equal( vMots.begin(), vMots.end(), "world");

    cout << " Nombre de mots égaux à world : " << nbEqualW<< endl;

    size_t nbEqualH = count_if_equal( vMots.begin(), vMots.end(), "hello");

    cout << " Nombre de mots égaux à hello : " << nbEqualH << endl;


}