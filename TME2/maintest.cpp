#include "HashMap.h"
#include <iostream>
#include <vector>
#include <string>
#include <forward_list>
#include <cstddef>
#include <algorithm>

using namespace std; 
using namespace pr;

int main(){

    HashMap<string,int> myMap(1);
    myMap.put("hello",1);
    myMap.put("world",6);
    myMap.put("raissa",10);
    myMap.put("hello",5);
    myMap.put("rania",4);
    myMap.put("link", 20);
    myMap.put("maman", 50);
    

    vector<pair<string,int>> v;

    for( auto it = myMap.begin(); it != myMap.end() ; ++it){
        v.push_back(make_pair((*it).key, (*it).val));
    }

    
    for( int i = 0; i < v.size() ; i++){
        cout << v[i].first << " " << v[i].second  << endl;
    }

    sort(v.begin(), v.end(), [] (const auto & a, const auto & b) {return a.second > b.second ;});
    cout << "sort "<< endl;
    for( int i = 0; i < v.size() ; i++){
        cout << v[i].first << " " << v[i].second  << endl;
    }


    

    return 0;

}

