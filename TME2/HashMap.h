#ifndef HASHMAP_H
#define HASHMAP_H 
#include <iostream>
#include <vector>
#include <string>
#include <forward_list>

namespace pr{

    template<typename K, typename V>
    class HashMap {

    
        public : 

        class Entry {
            public : 
            const K key; 
            V val;
            Entry( const K &k, const V& v) : key(k), val(v){}
        };

private : 

        typedef std::vector< std::forward_list< Entry > > bucketsType ;
        bucketsType buckets;
        size_t size;


public : 
        //CTOR
        HashMap(size_t size): size(size){

            for( int i = 0; i< size ; i++){
                buckets.push_back(std::forward_list<Entry>());
            }
        }

        //méthodes d'accès

        V* get( const K & key ) {
            
            //note pour moi : on ne veut pas itérer toute le vecteur et chaque 
            // bucket pour trouver la bonne clé => but= petite complexité
            // h prend le int la valeur de k ( le hash de key supposée, 
            // car il peut y avoir des collisions selon les valeur de key
            // on regarde dans le bucket target si c'est bien cette key

            size_t h = std::hash<K>()(key); 
            size_t target = h % buckets.size() ;
            
            for( Entry &ent : buckets[target] ){

                if( ent.key == key){
                    return &ent.val;
                }
            }
            return nullptr;

        }

        bool put( const K & key, const V & value) {

            size_t h = std::hash<K>()(key);//pos supposée de key
            size_t target = h % buckets.size() ;

            for( Entry & ent : buckets[target]){
                if(ent.key == key){
                    ent.val = value;
                    return true;
                }
            }
            size++;
            buckets[target].emplace_front(key,value);
            return false;
        }

        size_t getSize() const { return size ;}

        void grow() {

                HashMap newHash = HashMap(2*buckets.size() );

                for(  auto &list : buckets) {
                    for( auto &entry : list){
                        newHash.put(entry.key, entry.value);
                    }
                }
            buckets = newHash.buckets;; 
        }

        class iterator {

            typename bucketsType::iterator bucketsEnd ;
            typename bucketsType::iterator vit;
            typename std::forward_list<Entry>::iterator lit;

            public:

            iterator(const typename bucketsType::iterator & bEnd
                    ,const typename bucketsType::iterator & vit
                    ,const typename std::forward_list<Entry>::iterator & lit ):
                    bucketsEnd(bEnd), vit(vit), lit(lit) {}

            iterator & operator++(){

                ++lit;// on incrémente d'abord lit

                if(lit == vit->end()){//si au bout de la liste
                    ++vit; //on se décale sur vit, buckets suivant 
                    while(vit != bucketsEnd && vit->empty()){//on cherche une case non vide 
                        ++vit;
                    }
                    //si on est sorti on a soit trouvé une case  non vide soit la fin du buckets
                    if( vit != bucketsEnd){
                        lit = vit->begin(); //lit devient la tête de cette liste
                    }
                }
                return *this;

            }

            bool operator!=(const iterator &other){

                return (vit != other.vit ) || ( lit != other.lit);

            }

            Entry & operator*(){
                return *lit;
            }
            };


            //comme vu en TD il ne faut pas oublier les begin et end de la map
            //c'est le conteneur qui fournit ces operateurs

            iterator begin(){//renvoi premiuer buckets non vide

                typename bucketsType::iterator i = buckets.begin();

                while(i != buckets.end() && i->empty()){
                    ++i;
                }
                //comme tout a l'heure on test s'il est nul 
                if( i != buckets.end()){
                    return iterator(buckets.end(), i, i->begin());
                }
            return end();

            }

            iterator end(){
                return iterator(buckets.end(), buckets.end(), buckets.front().end());
            }
        

    };

}

#endif