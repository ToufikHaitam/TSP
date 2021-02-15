#include "genetique.h"
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

Genetique::Genetique()
{
   initialiser();

}

Genetique::~Genetique()
{
    //dtor
}

int Genetique::initialiser(){
    int added = 0;
    int id_read = 0;
    float x_read = 0;
    float  y_read = 0;
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
        { float d=(villes[i][0]-villes[j][0])*(villes[i][0]-villes[j][0])*1.0+
            (villes[i][1]-villes[j][1])*(villes[i][1]-villes[j][1])*1.0;
          distances[i][j]=sqrt(d)-(float)sqrt(d)>=0.5?(float)sqrt(d)+1:(float)sqrt(d);
          cout<<distances[i][j]<<endl;
          continue;
        }
        if(j==i) {distances[i][j]=0;continue;}
        if(j<i)  distances[i][j]=distances[j][i];


      }

     }



    read.close();

    return added;
}

double Genetique::fonctionobjective(int* t) {
    double coutroute=0;
    int i;
    for(i=1;i<nb_villes;i++){
        coutroute+=distances[t[i-1]][t[i]];
    }
    coutroute+=distances[t[i]][t[0]];
    return coutroute;
}

void   Genetique::copier_table_to_table(int *t, int *v) {
    for (int i = 0; i <=nb_villes ; i++) {
        v[i]=t[i];
    }
}

bool  Genetique::existe_deja(int *table,int value , int index1,int index2){
       for(int i=0;i<=index1;i++){
        if(table[i]==value)
            return true ;
       }
       for(int i=index2;i<nb_villes;i++){
        if(table[i]==value)
            return true ;
       }
       return false;
}

void Genetique::trier_population(int pop[14][14]){
   int N=nbindividu;
   for(int i=0;i<N-1;i++)
  {
     int imin=i;

     double minn=fonctionobjective(pop[i]);
      for(int j=i+1;j<N;j++)
        if(fonctionobjective(pop[j])<minn){
           minn=fonctionobjective(pop[j]);
           imin=j;
        }
       int tmp[nb_villes];
       copier_table_to_table(pop[imin],tmp);
       copier_table_to_table(pop[imin],pop[i]);
       copier_table_to_table(pop[i],tmp);



  }
//return table;
}

int*  Genetique::generer_individu(){
    int i,j,k;
    int V[nb_villes];
    int List[nb_villes];
    int ListLength;
    for( i=0; i<nb_villes; i++)
        V[i] = 0;

    j =rand()%nb_villes/2;
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
    return route;
}

void Genetique::afficheIndividu(int* t){
for(int i=0;i<nb_villes;i++){
    cout<<t[i]<<"->";
}
cout<<endl;
}

void Genetique::generer_population(){
      for(int i=0;i<nbindividu;i++){
            copier_table_to_table(generer_individu(),population[i]);

      }
}

void Genetique::crossOver(int* pere,int* mere){

       int index1=(rand()%((int)(nb_villes/2)))+((int)(nb_villes/2))-1;
       int index2;
       do{
        index2 = rand()%(nb_villes);
       }while(index1>=index2);
        int tmp[index2-index1];
        int tmp2[index2-index1];


       for(int i=index1;i<=index2;i++){
                tmp[i-index1]=pere[i];
                tmp2[i-index1]=mere[i];
                pere[i]=mere[i];
                mere[i]=tmp[i-index1];

       }
       for(int j=0;j<nb_villes;j++){
           int cont=0;
           int cont2=0;

           for(int k=0;k<nb_villes;k++){
               if(pere[k]==j){
                cont++;
               }
              }

            if(cont==0){

                    int indice=veriferedandance(pere);

                    if(indice!=-1){
                    pere[indice]=j;
                    }

                }

           for(int k=0;k<nb_villes;k++){
               if(mere[k]==j){
                cont2++;
               }
           }

            if(cont2==0){
                    int indice=veriferedandance(mere);
                    if(indice!=-1){
                    mere[indice]=j;
                    }

                }




       }



}

int* Genetique::mutation(int * individu){
       int index1=rand()%nb_villes;
       int index2;
       int tmp;
       do{
        index2 =rand()%(nb_villes);
       }while(index1>=index2);
        tmp =individu[index1];
        individu[index1]=individu[index2];
        individu[index2]=tmp;
        return individu;
}

int Genetique::veriferedandance(int* t){
      for(int i=0;i<nb_villes;i++){
        int cont=0;
         for(int j=0;j<nb_villes;j++){
             if(t[i]==t[j]){
                cont++;
                if(cont>1){
                    return j;
                }

             }

         }

      }
      return -1;

}
void  Genetique::solution(){
     clock_t  start, endtime;
     start=clock();

    generer_population();
    afficheIndividu(population[0]);
    int global[14][14];


    //initialiser le global
    for(int i=0;i<nbindividu;i++){
            for(int j=0;j<nb_villes;j++){
                global[i][j]=population[i][j];
            }
        }
     // fin init
    int local[14][14];
    for(int i=0;i<nbindividu;i++){

           cout<<"iteration "<<i<<endl;
               //copier le globale dans local
                for(int k=0;k<nbindividu;k++){
                        for(int j=0;j<nb_villes;j++){
                            local[k][j]=global[k][j];
                        }
                    }
                //fin copier le globale dans local

       trier_population(local);

       for(int j=0;j<nbindividu;j++){
         int rand1=(rand()%(nbindividu/2));
         int rand2;
         do{
           rand2=rand()%nbindividu;
         }while(rand2<=rand1);


           crossOver(local[rand1],local[rand2]);



        }


        //copier le local dans globale
                for(int k=0;k<nbindividu;k++){
                        for(int j=0;j<nb_villes;j++){
                            global[k][j]=local[k][j];
                        }
                    }
        //fin copier le globale dans local

trier_population(local);

  cout<<fonctionobjective(local[0]);

    }
    cout<<"fin de programme"<<endl;


       endtime=clock();
       double time_taken = double(endtime - start) / double(CLOCKS_PER_SEC);

        cout << "---Temps d'excution de programme est : " << time_taken ;
        cout << " sec " << endl;

  trier_population(global);
  afficheIndividu(global[1]);
  cout<<veriferedandance(global[0])<<endl;
  cout<<fonctionobjective(global[0]);

}
