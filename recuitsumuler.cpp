#include "Recuitsumuler.h"
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



Recuitsumuler::Recuitsumuler(){

    initialiser();
    cout<<nb_villes;
    //generer_une_solution_initiale();

   generer_aleratoire();

     cout<<"le cout initiale est "<<fonctionobjective(route)<<endl;

   inFname="bier127.tsp.txt";
}

int Recuitsumuler::initialiser(){


    int added = 0;
    int id_read = 0;
    double x_read = 0;
    double  y_read = 0;
    int i=0;
    int j=0;

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


     for(i=0;i<=nb_villes;i++) {
       route[i]=-1;
      }

    read.close();

    return added;
}

void Recuitsumuler::afficheroute(int *t){
     for(int i=0;i<=nb_villes;i++)
        std::cout<<""<<t[i]<<"->";

 }

double Recuitsumuler::fonctionobjective(int *t) {
    double cout=0;
    int i;
    for(i=1;i<nb_villes;i++){
        cout+=distances[t[i-1]][t[i]];
    }
    //cout+=distances[t[i]][t[0]];
    return cout;
}

int *Recuitsumuler::permuter(int *t, int i, int j) {
    int temp=t[i];
    t[i]=t[j];
    t[j]=temp;
    return t;
}

bool Recuitsumuler::existe_deja(int value, int index){
for( int i = 0; i < index; i ++)
          if( route[i] == value)
              return true;
     return false;
}

void Recuitsumuler::generer_aleratoire(){
for (int x=0; x<nb_villes;x++)
{
    int tmp =  (rand() % nb_villes) ;
    while( x !=0 && existe_deja(tmp, x))
           tmp = (rand() % nb_villes) ;

    route[x] = tmp;

}
route[nb_villes]=route[0];
cout<<"1::"<<route[0]<<endl;

}


int* Recuitsumuler::generer_une_solution_initiale() {
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

double Recuitsumuler::getRandomNumber(double i,double j) {
   // cout<<((double)rand() / RAND_MAX) * (j - i) + i<<endl;
   return ((double)rand() / (RAND_MAX *9));
}


void Recuitsumuler::affichematrice2(int **t){
    for(int i=0;i<nb_voisins;i++){
        for(int j=0;j<nb_villes;j++){
            cout<<t[i][j];
        }
    }
}

void Recuitsumuler::copier_table_to_table(int *t, int *v) {


    for (int i = 0; i <=nb_villes ; i++) {
        v[i]=t[i];



    }

}


void Recuitsumuler::solution(){
     clock_t  start, endtime;
     start=clock();

     int  bestroute[nb_villes];

    this->temperature=590;
    this->fac_refroi=0.99;
    this->epsilon=0.9;
    double bestcout=fonctionobjective(route);

    int bestIteration=0;

     int bestvoisin[nb_villes];
     int voisin[nb_villes];

     int i;



     copier_table_to_table(route,bestroute);
     Recuitsumuler::copier_table_to_table(bestroute,voisin);

     while(temperature > epsilon){


           for(int j=0;j<nb_villes*1000000;j++){

             int ran1=( rand()% nb_villes);
             int ran2;
             do{
                 ran2=(rand()%nb_villes);
             }
             while(ran1==ran2);
             copier_table_to_table(bestroute,voisin);

             permuter(voisin,ran1,ran2);

             double voisincout=fonctionobjective(voisin);
                    bestcout=fonctionobjective(bestroute);
             double deff= bestcout-voisincout;

             if((deff >0)){

               copier_table_to_table(voisin,bestroute);

             }

             else {

               if( (double)exp((double)deff/temperature*2500)>(rand()/((double)RAND_MAX)) ){
                 copier_table_to_table(voisin,bestroute);

             }

             }


                 }
             if(fonctionobjective(bestroute)<7600) afficheroute(bestroute);

             temperature*=fac_refroi;
             cout<<"temperature  "<<temperature<<endl;
             cout<<fonctionobjective(bestroute)<<endl;
              endtime=clock();
       double time_taken = double(endtime - start) / double(CLOCKS_PER_SEC);

        cout << "---Temps d'excution de programme est : " << time_taken ;
        cout << " sec " << endl;

            }

      bestcout=fonctionobjective(bestroute);
      endtime=clock();
      cout<<endl<<"---le meilleure cout finale  est :"<<bestcout<<endl;
       double time_taken = double(endtime - start) / double(CLOCKS_PER_SEC);

        cout << "---Temps d'excution de programme est : " << time_taken ;
        cout << " sec " << endl;

      cout<<"---le meilleure chemain finale  est :  ";
      afficheroute(bestroute);



}

