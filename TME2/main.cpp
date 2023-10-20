#include <iostream>
#include <string>

using namespace std ;

int main ()
{
    /*hello world + jouer avec chaines et entrées 
    cout << "Hello world !"  << " C'est Raiissa ";

    int age(22); 

    cout << "J'ai " << age << " ans" << endl;

    string nom("Bouri");

    cout << "Mon nom est : " << nom << endl;

    cout << "Comment s'appelle ta soeur ?" << endl ;

    string nomSoeur;

    cin >> nomSoeur; 

    cout << nomSoeur <<"! C'est un joli prénom :)" << endl;
    */

   int a, b, res ; 

   cout << " Choisir nombre a " << endl;
   cin >> a ;
   cout << " Choisir nombre b " << endl;
   cin >> b ;
 
   res = a + b ;
   cout << " Le résulat est " << res << endl;

    return 0 ;

}