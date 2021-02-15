#ifndef GENETIQUE_H
#define GENETIQUE_H


class Genetique
{
public:
            int nb_villes;
            int population[100][100];
            float mutationRatio=0.015;
            int nbindividu;
            float villes[1000][2];
            float distances[1000][1000];
            int    route[100];


    public:
        Genetique();
        int      initialiser();
        double   fonctionobjective(int *t);
        void     crossOver(int*,int*);
        int*     generer_individu();
        int**    selection(int**); // selection les meilleures individus
        int*     mutation(int*);
        void     generer_population();
        void     copier_table_to_table(int *t,int *v);
        void     trier_population(int pop[14][14]);
        void     solution();
        bool     existe_deja(int *table,int value , int index1,int index2);
        void     afficheIndividu(int *);
        int      veriferedandance(int *);






        virtual ~Genetique();

    protected:

    private:
};

#endif // GENETIQUE_H
