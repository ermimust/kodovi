#include <list>

using namespace std;

class stanovnik {
    public:
        int x, y, maticniBroj;
        static list<stanovnik*> popis;
        stanovnik(int X, int Y, int matBr);
        stanovnik(int X, int Y);
        int xK();
        int yK();
        int mat_broj();
        int udaljenost(stanovnik &B);
        int udaljenost(int a, int b);
        stanovnik& najblizi();
        virtual stanovnik& fokusiraj(stanovnik& B)=0;
        int razmaknutost(int a, int b);
        virtual bool lokOptimiziraj()=0;
        static void lokOptSve();
        static list<stanovnik*> Svi();
};

class Gustav:public stanovnik {
    public:
        Gustav(int X, int Y, int matBr);
        Gustav(int X, int Y);
        stanovnik& fokusiraj(stanovnik& B);
        bool lokOptimiziraj();
};

class Ivar:public stanovnik {
    public:
        Ivar(int X, int Y, int matBr);
        Ivar(int X, int Y);
        stanovnik& fokusiraj(stanovnik& B);
        bool lokOptimiziraj();
};
