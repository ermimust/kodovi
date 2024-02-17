#include <iostream>
#include "stanovnik.h"

using namespace std;

int main(void) {
    Ivar I1(3, 5, 5), I2(4, 7, 6), I3(20, 20);
    Gustav G1(4, 9), G2(11, 0), G3(30, 30), G(12, 12);
    list<stanovnik*>::iterator i;
    list<stanovnik*> S;
    
    cout<<G3.mat_broj()<<" na koord: "<<G3.xK()<<","<<G3.yK()<<endl;  // 4 na koord: 30,30

    cout<<G1.razmaknutost(4,9)<<","<<G3.razmaknutost(25,25)<<","<<G1.razmaknutost(3,5)<<endl;  // 65,107,-937
    
    cout<<G.mat_broj()<<" na koord: "<<G.xK()<<","<<G.yK()<<endl;  // 7 na koord: 12,12
    cout<<G.najblizi().mat_broj()<<" na koord: "<<G.najblizi().xK()<<","<<G.najblizi().yK()<<endl;  // 1 na koord: 20,20

    cout<<G3.lokOptimiziraj()<<", "<<I1.lokOptimiziraj()<<endl;
    cout<<G3.mat_broj()<<" na koord: "<<G3.xK()<<","<<G3.yK()<<endl;  // 4 na koord: 31,31
    cout<<I1.mat_broj()<<" na koord: "<<I1.xK()<<","<<I1.yK()<<endl;  // 5 na koord: 4,6

    G1.fokusiraj(G3).fokusiraj(G3);
    cout<<G1.mat_broj()<<" na koord: "<<G1.xK()<<","<<G1.yK()<<endl<<endl;  // 2 na koord: 2,7

    S=G1.Svi();
    stanovnik::lokOptSve();
    for(i=S.begin(); i!=S.end(); i++) cout<<(*i)->mat_broj()<<" na koord: "<<(*i)->xK()<<","<<(*i)->yK()<<endl;
    /*
    5 na koord: 4,7
    6 na koord: 4,7
    1 na koord: 19,19
    2 na koord: 1,6
    3 na koord: 12,0
    4 na koord: 32,32
    7 na koord: 13,11 */

    cout<<endl;

    return 0;
}
