#include "HashMap.h"
#include "tme3exo1.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <fstream>
#include <regex>
#include <forward_list>

using namespace pr;
using namespace std;
using namespace tme3;

void nbOccurence(const string &word, HashMap<string,int> &map){
    auto find = map.get(word); 

    if( find == nullptr ){ cout << word << " pas trouvé :( " << endl; }
    else{
        cout << "Nombre d'occurrences de " << word << " : " << *find << endl;

    }
}


int main(){



    HashMap<string,int> myMap(2500000);

    ifstream input = ifstream("WarAndPeace.txt");

    cout << " Parsing War and Peace " << endl;

    string word;

    regex re( R"([^a-zA-Z])");

    while(input >> word) {

        
        word = regex_replace( word, re, "");
        transform(word.begin(), word.end(), word.begin(), ::tolower);

//get nous renvoie un ptr sur l'adresse de la val associée a key

       auto  ptr = myMap.get(word) ; 
    
        if(ptr != nullptr){// si diff de nullptr donc que key dans table

            (*ptr)++; ; // on incrémente la val associée à la key

       } else {
             
             myMap.put(word,1); //sinon on a ajoute la clé à la map
       }

        

     }
     input.close();
     cout<<"Finish Parsing"<<endl;
    
// avant nbOcc
  //  cout << " Nombre d'occurences de war  :" << *(myMap.get("war"))  << endl;
  //  cout << " Nombre d'occurences de peace : " << *(myMap.get("peace"))  << endl;
// cout << " Nombre d'occurences de toto : " << *(myMap.get("toto") ) << endl;

nbOccurence("war", myMap);
nbOccurence("peace", myMap);
nbOccurence("the", myMap);

//TME3 copie dans un vecteur à l'aide des iterateurs crées
//ctor par copie de vector : vector(interator first, iterator last)

vector<pair<string,int>> v;


for(auto it = myMap.begin() ; it != myMap.end() ; ++it){
    v.push_back(make_pair((*it).key, (*it).val) );
}

sort(v.begin(), v.end(), [] (const auto & a, const auto & b) {return a.second > b.second ;});

int cpt = 0;

while(cpt < 10){

    cout << v[cpt].first << " " << v[cpt].second << endl;
    cpt++;
    
}

size_t nbCount = count(myMap.begin(), myMap.end());

cout << "nombre mots appel count : " << nbCount << endl;


    return 0;

}

