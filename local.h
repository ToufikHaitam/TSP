#ifndef LOCAL_H
#define LOCAL_H
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

class Local
{
    public:
        public: int    nb_iteration;
        int    nb_villes;
        double distances[1000][1000];
        double villes[1000][2];
        int    route[1000];
        int    nb_voisins;
        int    listvoisins[100][100];
        std::string inFname;
        Local();

        int      initialiser();
        int*     permuter(int *t,int i,int j);
        double   fonctionobjective(int *t);
        int*     generer_une_solution_initiale();
        void     copier_table_to_table(int *t,int *v);
        bool     existe(int *t, int val);
        void     afficheroute(int *t);
        void     solution();
        virtual ~Local();

    protected:

    private:
};

#endif // LOCAL_H
