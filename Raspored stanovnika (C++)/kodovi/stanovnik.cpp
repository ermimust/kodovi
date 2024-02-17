#include <cmath>
#include "stanovnik.h"

list<stanovnik*> stanovnik::popis;

stanovnik::stanovnik(int X, int Y, int matBr) {
    x=X;
    y=Y;
    maticniBroj=matBr;
    popis.push_back(this);
}

stanovnik::stanovnik(int X, int Y) {
    list<stanovnik*>::iterator li;
    int dodijeljeni=1, istinitost=0;
    x=X;
    y=Y;
    while(1) {
        for(li=popis.begin(); li!=popis.end(); li++) {
            if((*li)->maticniBroj==dodijeljeni) {
                istinitost=1;
                break;
            }
        }
        if(istinitost==0) {
            maticniBroj=dodijeljeni;
            popis.push_back(this);
            break;
        }
        else {
            ++dodijeljeni;
            istinitost=0;
        }
    }
}

Gustav::Gustav(int X, int Y, int matBr):stanovnik(X, Y, matBr) {}

Gustav::Gustav(int X, int Y):stanovnik(X, Y) {}

Ivar::Ivar(int X, int Y, int matBr):stanovnik(X, Y, matBr) {}

Ivar::Ivar(int X, int Y):stanovnik(X, Y) {}

int stanovnik::xK() {
    return x;
}

int stanovnik::yK() {
    return y;
}

int stanovnik::mat_broj() {
    return maticniBroj;
}

int stanovnik::udaljenost(stanovnik &B) {
    if(x==B.x) return abs(y-B.y);
    else if(y==B.y) return abs(x-B.x);
    else if(abs(x-B.x)==abs(y-B.y)) return abs(x-B.x);
    else if(abs(x-B.x)<=abs(y-B.y)) return abs(y-B.y);
    else return abs(x-B.x);
}

int stanovnik::udaljenost(int a, int b) {
    if(x==a) return abs(y-b);
    else if(y==b) return abs(x-a);
    else if(abs(x-a)==abs(y-b)) return abs(x-a);
    else if(abs(x-a)<=abs(y-b)) return abs(y-b);
    else return abs(x-a);
}

stanovnik& stanovnik::najblizi() {
    list<stanovnik*>::iterator li;
    int min=1000, minMatBr=maticniBroj, najbliziMatBr;
    for(li=popis.begin(); li!=popis.end(); li++)
        if(((*li)->maticniBroj!=maticniBroj && this->udaljenost((*li)->x, (*li)->y)<min) || ((*li)->maticniBroj!=maticniBroj && this->udaljenost((*li)->x, (*li)->y)==min && (*li)->maticniBroj<minMatBr)) {
            min=this->udaljenost((*li)->x, (*li)->y);
            najbliziMatBr=(*li)->maticniBroj;
            minMatBr=(*li)->maticniBroj;
        }
    for(li=popis.begin(); li!=popis.end(); li++)
        if((*li)->maticniBroj==najbliziMatBr) return *(*li);
}

stanovnik& Gustav::fokusiraj(stanovnik& B) {
    int maksx, maksy;
    double euklid=0.0;
    if((x-1<0 && y+1>99) || (x+1>99 && y+1>99) || (x+1>99 && y-1<0) || (x-1<0 && y-1<0)) return *this;
    else {
        int maks=this->udaljenost(B), i, j;
        for(i=x-1; i<=x+1; i++)
            for(j=y-1; j<=y+1; j++) {
                if(i==x && j==y) continue;
                else if(i>=0 && i<=99 && j>=0 && j<=99 && B.udaljenost(i, j)>maks) {
                    maks=B.udaljenost(i, j);
                    maksx=i;
                    maksy=j;
                    euklid=sqrt((B.x-i)*(B.x-i)+(B.y-j)*(B.y-j));
                }
                else if(i>=0 && i<=99 && j>=0 && j<=99 && B.udaljenost(i, j)==maks && sqrt((B.x-i)*(B.x-i)+(B.y-j)*(B.y-j))>euklid) {
                    maks=B.udaljenost(i, j);
                    maksx=i;
                    maksy=j;
                    euklid=sqrt((B.x-i)*(B.x-i)+(B.y-j)*(B.y-j));
                }
                else continue;
            }
    }
    this->x=maksx;
    this->y=maksy;
    return *this;
}

stanovnik& Ivar::fokusiraj(stanovnik& B) {
    int minx, miny;
    double euklid=0.0;
    if(this->udaljenost(B)==0) return *this;
    else {
        int min=this->udaljenost(B), i, j;
        for(i=x-1; i<=x+1; i++)
            for(j=y-1; j<=y+1; j++) {
                if(i==x && j==y) continue;
                else if(i>=0 && i<=99 && j>=0 && j<=99 && B.udaljenost(i, j)<min) {
                    min=B.udaljenost(i, j);
                    minx=i;
                    miny=j;
                    euklid=sqrt((B.x-i)*(B.x-i)+(B.y-j)*(B.y-j));
                }
                else if(i>=0 && i<=99 && j>=0 && j<=99 && B.udaljenost(i, j)==min && sqrt((B.x-i)*(B.x-i)+(B.y-j)*(B.y-j))<euklid) {
                    min=B.udaljenost(i, j);
                    minx=i;
                    miny=j;
                    euklid=sqrt((B.x-i)*(B.x-i)+(B.y-j)*(B.y-j));
                }
                else continue;
            }
    }
    this->x=minx;
    this->y=miny;
    return *this;
}

int stanovnik::razmaknutost(int a, int b) {
    int zbrojUdaljenostiOdSvih=0, brStanNaSusjednimPoljima=0, brStanNaab=0, i, j;
    list<stanovnik*>::iterator li;
    for(li=popis.begin(); li!=popis.end(); li++) {
        if((*li)->maticniBroj==maticniBroj) continue;
        zbrojUdaljenostiOdSvih+=(*li)->udaljenost(a, b);
    }
    for(i=a-1; i<=a+1; i++)
        for(j=b-1; j<=b+1; j++) {
            if(i==a && j==b) continue;
            else for(li=popis.begin(); li!=popis.end(); li++)
                if((*li)->x==i && (*li)->y==j && (*li)->maticniBroj!=maticniBroj) ++brStanNaSusjednimPoljima;
        }
    for(li=popis.begin(); li!=popis.end(); li++) {
        if((*li)->maticniBroj==maticniBroj) continue;
        else if((*li)->x==a && (*li)->y==b) ++brStanNaab;
    }
    return zbrojUdaljenostiOdSvih-50*brStanNaSusjednimPoljima-1000*brStanNaab;
}

bool Gustav::lokOptimiziraj() {
    int razm=this->razmaknutost(x, y), maks=this->razmaknutost(x, y), maksx=x, maksy=y, i, j;
    for(i=x-1; i<=x+1; i++)
        for(j=y-1; j<=y+1; j++) {
            if(i>=0 && i<=99 && j>=0 && j<=99 && this->razmaknutost(i, j)>maks) {
                maks=this->razmaknutost(i, j);
                maksx=i;
                maksy=j;
            }
            else continue;
        }
    if(maks>razm) {
        x=maksx;
        y=maksy;
        return true;
    }
    else return false;
}

/*
bool Gustav::lokOptimiziraj() {
    int razm=this->razmaknutost(x, y), maks, maksx=x, maksy=y, i, j;
    maks=razm;
    for(i=x-1; i<=x+1; i++)
        for(j=y-1; j<=y+1; j++) {
            if(i>=0 && i<=99 && j>=0 && j<=99 && this->razmaknutost(i, j)>maks) {
                maks=this->razmaknutost(i, j);
                maksx=i;
                maksy=j;
            }
            else continue;
        }
    if(maks>razm) {
        x=maksx;
        y=maksy;
        return true;
    }
    else return false;
} */

bool Ivar::lokOptimiziraj() {
    int razm=this->razmaknutost(x, y), min, minx=x, miny=y, i, j;
    min=razm;
    for(i=x-1; i<=x+1; i++)
        for(j=y-1; j<=y+1; j++) {
            if(i>=0 && i<=99 && j>=0 && j<=99 && this->razmaknutost(i, j)<min) {
                min=this->razmaknutost(i, j);
                minx=i;
                miny=j;
            }
            else continue;
        }
    if(min<razm) {
        x=minx;
        y=miny;
        return true;
    }
    else return false;
}

void stanovnik::lokOptSve() {
    list<stanovnik*>::iterator li;
    for(li=popis.begin(); li!=popis.end(); li++) (*li)->lokOptimiziraj();
    return;
}

list<stanovnik*> stanovnik::Svi() {
    return popis;
}
