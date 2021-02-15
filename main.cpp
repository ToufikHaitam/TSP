#include "Recuitsumuler.h"
#include <iostream>
#include "Descente.h"
#include"taboulist.h"
#include"local.h"
#include"math.h"
#include <cstdlib>
#include <ctime>
#include"genetique.h"

using namespace std;

int main()
{




//
//    cout<<"--------la methode descente-----------"<<endl;
  srand((unsigned int)time(NULL));
  srand(time(NULL));


//    Descente *p=new Descente();
//    p->nb_iteration=15000;
//    p->nb_voisins=5000;
//    p->solution();
//    delete p;
//    cout<<"--------fin de la methode descente----"<<endl;

//9604 15,26
//9347   16,4
//
//
//
//
//    cout<<endl;
//    cout<<endl;
//   cout<<endl<<"--------la methode Tabou-----------"<<endl;
//
//    Taboulist *t=new Taboulist();
//    t->taboulength=1500;
//    t->nb_iteration=15000;
//    t->nb_voisins=500;
//    t->miseajourlistTabou(t->route,0);
//    t->solution();
//    delete t;

//    Recuitsumuler *r=new Recuitsumuler();
//    r->nb_iteration=15000;
//    r->nb_voisins=5000000;
//    r->solution();
//    delete r;

Genetique *g=new Genetique();
g->nbindividu=14;
g->solution();
delete g;


//Local *l=new Local();
//
//l->solution();

////
//    cout<<"--------Fin de la methode Tabou----"<<endl;

    return 0;
}
