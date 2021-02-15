#include "taboulist.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include "stdlib.h"
 #include "math.h"
#include "conio.h"
#include "time.h"
#include  "stdlib.h"
#include  "string.h"
#include  "fstream"
#include  "string"
#include   "cstring"
#include <deque>


#define FILE_PATH  "Berlin52.tsp","r"
using namespace std;
#include <string>



Taboulist::Taboulist() {
    initTab2d();
    initialiser();
   //generer_une_solution_initiale();
    generer_aleratoire();
    inFname="bier127.tsp.txt";
}



void Taboulist::initTab2d(){
for(int i=0;i<taboulength;i++){
    for(int j=0;j<=nb_villes;i++){
            listTabou[i][j]=0;

    }
}
}

int Taboulist::initialiser(){


    int added = 0;
    int id_read = 0;
    double x_read = 0;
    double  y_read = 0;
    int i=0;
    int j=0;
    int d=0;
    nb_villes=0;

    ifstream read("burma14.tsp.txt");

    if (!read)
    {
        cout << "error";
        return 0; // file doesn't exist
    }

    while (read>>id_read>>x_read>>y_read) // go till end of file
    {
       // std::cout<<added<<"---"<<x_read<<"------"<<y_read<<endl;
        nb_villes++;

         villes[added][0]=x_read;
         villes[added][1]=y_read;
        ++added;
    }

    for(int i=0;i<nb_villes;i++) {   /*  init city_dis[] */
      for(int j=0;j<nb_villes;j++)
      { if(j>i)
        { int d=(villes[i][0]-villes[j][0])*(villes[i][0]-villes[j][0])*1.0+
            (villes[i][1]-villes[j][1])*(villes[i][1]-villes[j][1])*1.0;
          distances[i][j]=sqrt(d)-(int)sqrt(d)>=0.5?(int)sqrt(d)+1:(int)sqrt(d);
          continue;
        }
        if(j==i) {distances[i][j]=0;continue;}
        if(j<i)  distances[i][j]=distances[j][i];


      }

     }

      for(i=0;i<nb_villes;i++) {   /*  init city_dis[] */
       route[i]=-1;
      }


    read.close();


    return added;
}

void Taboulist::afficheroute(int *t){
     for(int i=0;i<=nb_villes;i++)
        std::cout<<"->"<<t[i]<<"";

 }

bool Taboulist::existe(int *t,int a){
    for(int i=0;i<nb_villes;i++){
        if(t[i]==a) return true;
    }
return false;
}

double Taboulist::fonctionobjective(int *t) {
    double cout=0;
    int i;
    for(i=0;i<nb_villes-1;i++){
        cout+=distances[t[i]][t[i+1]];
    }
    cout+=distances[t[i]][t[0]];
    return cout;
}

void Taboulist::generer_une_liste_voisnins(int *t) {

    int ran2;

    //affichematrice2(listvoisins);

    for (int i=0;i<this->nb_voisins;i++){
        int ran=rand()%(nb_villes);

        do{
            ran2=rand()%(nb_villes);
        } while (ran=ran2);

         copier_table_to_table(listvoisins[i],permuter(t,ran,ran2));
    }
    //return listvoisins;
}

int *Taboulist::permuter(int *t, int i, int j) {
    int temp=t[i];
    t[i]=t[j];
    t[j]=temp;
    return t;
}
int * Taboulist::get_min_voisins_from_voisins(int **t) {
    int min=fonctionobjective(t[0]);
    int indice=0;
    for (int i=0;i<nb_voisins;i++){
        if(fonctionobjective(t[i])<min){
         min=fonctionobjective(t[i]);
         indice=i;
        }
    }
    return t[indice];
}

void Taboulist::generer_aleratoire(){

      for (int x=0; x!=nb_villes;x++)
{
    int tmp = 1 + (rand() % nb_villes) ;
    while( x !=0 && existe_deja(tmp, x))
           tmp = (rand() % nb_villes) ;

    route[x] = tmp;

}

      route[nb_villes]=route[0];


}

bool Taboulist::existe_deja(int value, int index){
for( int i = 0; i < index; i ++)
          if( route[i] == value)
              return true;
     return false;

}



int* Taboulist::generer_une_solution_initiale() {
    int i;
    int minindice= 42;
    route[0]= minindice;

    for(i=1;i<nb_villes-1;i++){
        int minimum=100000;
        for(int j=0;j<nb_villes;j++){
             if( minindice!=j && existe(route,j)==false && distances[minindice][j]<minimum){
                minimum=distances[minindice][j];
                minindice=j;
             }
          }

        route[i]=minindice;

    }

      route[i+1]=route[0];

    cout<<"le cout initiale est "<<fonctionobjective(route)<<endl;
    return route;
}

void Taboulist::affichertableau(int *t){
     for(int i=0;i<10;i++)
        cout<<t[i];
}

void Taboulist::affichematrice2(int **t){
    for(int i=0;i<nb_voisins;i++){
        for(int j=0;j<nb_villes;j++){
            cout<<t[i][j];
        }
    }
}

void Taboulist::copier_table_to_table(int *t, int *v) {


    for (int i = 0; i <=nb_villes ; i++) {
        v[i]=t[i];
    }

}

bool Taboulist::istabou(int *t){
     bool istb;

    for(int i=0;i<=indiceTabou;i++) {
        istb=true;
        for(int j=0;j<=nb_villes;j++) {

           if (listTabou[i][j]!=t[i]){

                istb=false;

           }}
           if(istb==true) return true;

    }

 return false;
}

void Taboulist::miseajourlistTabou(int *t, int indice){
       if(indice>taboulength){
            copier_table_to_table(t,listTabou[0]);

       }
       else{
        copier_table_to_table(t,listTabou[indice]);

       }
indiceTabou++;

}

void Taboulist::solution(){
     clock_t  start, endtime;
     start=clock();
     indiceTabou=0;
     int  bestroute[nb_villes];

     double bestcout=fonctionobjective(route);


     double bestcoutvoisin=0;

     int bestIteration=0;

     int bestvoisin[nb_villes];
     int voisin[nb_villes];

     int i;

     for (int k = 0; k <nb_villes ; k++) {
        bestvoisin[k]=0;
        voisin[k]=0;
        bestroute[k]=0;

       }

     copier_table_to_table(route,bestroute);
     Taboulist::copier_table_to_table(bestroute,bestvoisin);
     Taboulist::copier_table_to_table(bestroute,voisin);

     for(i=0;i<nb_iteration;i++){

         //cout<<"iteration : "<<i;

          copier_table_to_table(bestvoisin,voisin);

           for(int j=0;j<nb_voisins;j++){

             int ran1 = rand()%nb_villes;
             int ran2 ;
             do{
                 ran2=rand()%nb_villes;
             }
             while(ran1==ran2);

             permuter(voisin,ran1,ran2);



             if(fonctionobjective(voisin)<fonctionobjective(bestvoisin) && istabou(voisin)==true){
                copier_table_to_table(voisin,bestvoisin);
                bestcoutvoisin=fonctionobjective(bestvoisin);
             }


           }



        if(fonctionobjective(bestvoisin)<fonctionobjective(bestroute)){

            copier_table_to_table(bestvoisin,bestroute);
            bestcout=bestcoutvoisin;
            bestIteration=i;

            }
            miseajourlistTabou(bestvoisin,indiceTabou);


     // cout<<"    --le cout est "<<bestcout<<endl;

            }



      endtime=clock();
      cout<<"---le meilleure cout finale  est :"<<bestcout<<endl;
       double time_taken = double(endtime - start) / double(CLOCKS_PER_SEC);

        cout << "---Temps d'excution de programme est : " << time_taken ;
        cout << " sec " << endl;

      cout<<"---le meilleure chemain finale  est :  ";
      afficheroute(bestroute);



}
