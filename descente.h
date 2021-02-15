#ifndef UNTITLED5_DESCENTE_H
#define UNTITLED5_DESCENTE_H
#include <string>
#include <cstring>
#include <cstdlib>
#include <string>

class Descente {
public: int    nb_iteration;
        int    nb_villes;
        double distances[1000][1000];
        double villes[1000][2];
        int    route[1000];
        int    nb_voisins;
        int    listvoisins[100][100];
        std::string inFname;




public:
    int      initialiser();
    int*     permuter(int *t,int i,int j);
    double   fonctionobjective(int *t);
    int*     generer_une_solution_initiale();
    void     generer_une_liste_voisnins(int *);
    int*     get_min_voisins_from_voisins(int **);
    void     copier_table_to_table(int *t,int *v);
    bool     existe(int *t, int val);
    int      affiche();
    void     afficheroute(int *t);
    void     affichematrice2(int **t);
    void     solution();
    void     affichertableau(int *t);
    void     generer_aleratoire();
    bool     existe_deja(int value, int index);

    virtual ~Descente()=default;

    Descente();







};


#endif //UNTITLED5_DESCENTE_H
