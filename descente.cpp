#include <math.h>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "Descente.h"
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



Descente::Descente() {

    initialiser();
    //generer_une_solution_initiale();
   generer_aleratoire();
   afficheroute(route);
    inFname="berlin52.tsp";
}

int Descente::initialiser(){


    int added = 0;
    int id_read = 0;
    double x_read = 0;
    double  y_read = 0;
    int i=0;
    int j=0;

    nb_villes=0;

    ifstream read("berlin52.tsp");

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


     for(i=0;i<nb_villes;i++) {
       route[i]=-1;
      }

    read.close();


    return added;
}

void Descente::afficheroute(int *t){
     for(int i=0;i<=nb_villes;i++)
        std::cout<<"->"<<t[i]<<"";

 }

bool Descente::existe(int *t,int a){
    for(int i=0;i<nb_villes;i++){
        if(t[i]==a) return true;
    }
return false;
}

double Descente::fonctionobjective(int *t) {
    double cout=0;
    int i;
    for(i=1;i<nb_villes;i++){
        cout+=distances[t[i-1]][t[i]];
    }
    cout+=distances[t[i]][t[0]];
    return cout;
}

void Descente::generer_une_liste_voisnins(int *t) {

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

int *Descente::permuter(int *t, int i, int j) {
    int temp=t[i];
    t[i]=t[j];
    t[j]=temp;
    return t;
}
int * Descente::get_min_voisins_from_voisins(int **t) {
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

bool Descente::existe_deja(int value, int index){
for( int i = 0; i < index; i ++)
          if( route[i] == value)
              return true;
     return false;

}
void Descente::generer_aleratoire(){
  for (int x=0; x!=nb_villes;x++)
   {
    int tmp =(rand() % nb_villes) ;
    while( x !=0 && existe_deja(tmp, x))
           tmp = (rand() % nb_villes) ;

    route[x] = tmp;

   }

      route[nb_villes]=route[0];


}


int* Descente::generer_une_solution_initiale() {
    int i,j,k;
    int V[nb_villes];
    int List[nb_villes];
    int ListLength;
    for( i=0; i<nb_villes; i++)
        V[i] = 0;

    j =rand()%nb_villes;
    route[0] = j;
     V[j] = 1;
    for( i=1; i<nb_villes; i++){
        double x=100000;
        for( j=0; j<nb_villes; j++){

            if( V[j]==0 ){
                if( x > distances[route[i-1]][j] ){
                    x = distances[ route[i-1]][j] ;
                    k = j;

                }
            }
        }
        for( j=0; j<nb_villes; j++)
            List[j] = 0;
        ListLength = 0;


        for( j=0; j<nb_villes; j++){


            if( V[j]==0 && distances[route[i-1]][j] < x * 1.05 ){



                List[ListLength] = j;
                ListLength++;

            }

        }
        k = rand()%ListLength;

        k = List[k];

        route[i] = k;
        V[k]=1;

    }
    route[nb_villes]=route[0];

    cout<<"le cout initiale est "<<fonctionobjective(route)<<endl;

     afficheroute(route);


    return route;

}

void affichertableau(int *t){
     for(int i=0;i<10;i++)
        cout<<t[i];
}

void Descente::affichematrice2(int **t){
    for(int i=0;i<nb_voisins;i++){
        for(int j=0;j<nb_villes;j++){
            cout<<t[i][j];
        }
    }
}

void Descente::copier_table_to_table(int *t, int *v) {


    for (int i = 0; i <=nb_villes ; i++) {
        v[i]=t[i];



    }

}


void Descente::solution(){
     clock_t  start, endtime;
     start=clock();

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
     Descente::copier_table_to_table(bestroute,bestvoisin);
     Descente::copier_table_to_table(bestroute,voisin);

     for(i=0;i<nb_iteration;i++){

       //cout<<"iteration : "<<i;

          copier_table_to_table(bestvoisin,voisin);

           for(int j=0;j<nb_voisins;j++){

             int ran1=(rand()%nb_villes);
             int ran2;
             do{
                 ran2=(rand()%nb_villes);
             }
             while(ran1==ran2);

             permuter(voisin,ran1,ran2);

             if(fonctionobjective(voisin)<fonctionobjective(bestvoisin)){
                copier_table_to_table(voisin,bestvoisin);
                bestcoutvoisin=fonctionobjective(bestvoisin);
             }

           }



        if(fonctionobjective(bestvoisin)<fonctionobjective(bestroute)){

            copier_table_to_table(bestvoisin,bestroute);
            bestcout=bestcoutvoisin;
            bestIteration=i;


        }

      //cout<<"    --le cout est "<<bestcout<<endl;

            }

      endtime=clock();
      cout<<endl<<"---le meilleure cout finale  est :"<<bestcout<<endl;
       double time_taken = double(endtime - start) / double(CLOCKS_PER_SEC);

        cout << "---Temps d'excution de programme est : " << time_taken ;
        cout << " sec " << endl;

      cout<<"---le meilleure chemain finale  est :  ";
      afficheroute(bestroute);
      copier_table_to_table(bestroute,route);



}
