#include "local.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "Local.h"
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



Local::Local() {

    initialiser();
    generer_une_solution_initiale();

   afficheroute(route);
    inFname="berlin52.tsp";
}

int Local::initialiser(){


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

void Local::afficheroute(int *t){
     for(int i=0;i<=nb_villes;i++)
        std::cout<<"->"<<t[i]<<"";

 }

bool Local::existe(int *t,int a){
    for(int i=0;i<nb_villes;i++){
        if(t[i]==a) return true;
    }
return false;
}

double Local::fonctionobjective(int *t) {
    double cout=0;
    int i;
    for(i=1;i<nb_villes;i++){
        cout+=distances[t[i-1]][t[i]];
    }
    cout+=distances[t[i]][t[0]];
    return cout;
}

int* Local::generer_une_solution_initiale() {
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

int *Local::permuter(int *t, int i, int j) {
    int temp=t[i];
    t[i]=t[j];
    t[j]=temp;
    return t;
}




void Local::copier_table_to_table(int *t, int *v) {


    for (int i = 0; i <=nb_villes ; i++) {
        v[i]=t[i];



    }

}


void Local::solution(){
     clock_t  start, endtime;
     start=clock();

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


      endtime=clock();
      cout<<endl<<"---le meilleure cout finale  est :"<<fonctionobjective(route)<<endl;
       double time_taken = double(endtime - start) / double(CLOCKS_PER_SEC);

        cout << "---Temps d'excution de programme est : " << time_taken ;
        cout << " sec " << endl;

      cout<<"---le meilleure chemain finale  est :  ";




}



Local::~Local()
{
    //dtor
}
