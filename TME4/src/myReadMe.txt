1.2 - Transaction 

    1) commentaires dans le code 
     - fonction transaction : créer les int i,j et m random pour compte débiteur, créditeur et montant aléatoires
     - dans le main : création des threads avec boucle for comme en TD
     - dans banque.h / banque.cpp : fonction verifSolde() renvoie un int avec le solde totale ( somme de tout les comptes de la banque)
        Normalement on ne perdait rien puisque ce qui était prit d'un compte était reversé à un autre compte
        Ça marche, cool 
    - puis boucle for pour join tout les threads( concurrence max car on le fait après le for qui céer les threads )
    - puis test pour voir si pas de perte 

    2) Pas de data race puisque les blocs de codes sont protégés avec le mutex donc pas d'écrasement des débits/crédits

    3)4)5) On a un problème par contre, on veut une maj des comptes atomiques 
        -> si on regarde à un instant t : le compte débité et celui crédité sont mis à jour simultanément
        => du coup on lock les deux comptes, comme ça accès interdit tant que les opérations ne sont pas finies 
        mais on avoir un deadlock c'est sûr
            => ça se bloque direct
        => disons qu'on ait d à débiter et c à créditer de val
            alors on lock c et d et on fait d.debiter
            on lock d qui était déjà lock = deadlock 
    
    6) prof a parlé de recursive mutex => cppref
        -> can be used to protect shared data from being simultaneously  accessed 
        by multiple threads
        -> A calling threads owns a recursive mutex for a period of time starting when it calls *successfuly* lock or try lock
            ->  during this period : thread can call again lock or try lock 
                until matching calls to unlock
                => let's go pour un thread : ça marche pour un thread
                Go tester pour deux:  2 ça bloque des fois ahhh

                on a T0 et T1 
                scénario possible :
                - ils piochent des comptes différents : 
                    pas de pb 
                     
                - ils piochent les mêmes débiteurs : 
                    T0 pioche d et c, T1 pioche d et g
                    T0 lock d 
                    T1 lock d mais d est déjà locked, donc T1 se bloque 
                    T0 lock c
                    T0 finit et unlock d , T1 lock d et g et fait ses affaires
                    T1 unlock d et tout le monde est content
                - pareil pour même créditeurs
                - ils piochent les même paires : 
                    T0 pioche d et c, T1 pioche c et d
                    T0 lock d
                    T1 lock c
                    T0 lock d => bloqué 
                    T1 lock d => bloqué
                    Quand ça marche c'est que T0 ou T1 a bloqué ses deux comptes à la suite. 
                    Mais on peut avoir un interblocage comme ici
                    il faudrait ordonner la prise des lock => lock sur ce bloc d'instructions?
                        on va avoir 2 lock en tout c'est bof un peu

                    On peut lock plusieurs truc en même temps ? 
                    => cplusplus : lock multiple mutextes : locks all the objects passed as arg 
                    if the function cannot lock all the objects -> it first unlocks all objects it locked before failing
                    c'est ça qu'on veut un des objets de la paire est déjà locked alors on unlock tout et on attend
                    => okay ça marche 





    
            