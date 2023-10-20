#include <iostream>
#include <forward_list>
#include <string>

using namespace std;

int main(){

    forward_list<int> lInt = {10,20,30} ;

    for(forward_list<int>::iterator i = lInt.begin(); i != lInt.end() ; i++ ){
        *i *= 2;
    }

    for(forward_list<int>::iterator i = lInt.begin(); i != lInt.end() ; i++ ){
        cout << *i << endl ;
    }

    forward_list<pair<string, int>> myPair;
    myPair.push_front(make_pair("hello", 1) );
    myPair.push_front(make_pair("world", 1) );
    myPair.push_front(make_pair("raissa", 2) );

    for(forward_list<pair<string, int>>::iterator i = myPair.begin(); i != myPair.end() ; i++ ){
        cout << i->first << " ";
        cout << i->second << endl;

    }



    return 0;


}

