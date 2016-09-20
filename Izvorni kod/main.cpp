#include <iostream>
#include <cstdlib>
#include <cstring>
#include "graf.h"
using namespace std;

class MojGraf : public Graf<char>
{
    public:
    MojGraf(int broj_cvorova) : Graf<char>(broj_cvorova) {}

    bool UlaznaObrada(int cvor)
    {
        cout<<"Posjecen cvor: " << OznakaCvora(cvor) << "\n";
        return true;
    }

    bool IzlaznaObrada(int pocetni, int zavrsni)
    {
        cout << "Biljezim ivicu: (" << OznakaCvora(pocetni) << ","  << OznakaCvora(zavrsni) << ")" << endl;
        return true;
    }
};

void DefinirajGraf(MojGraf &g)
{
    struct Ivica
    {
        int x, y;
    };

    Ivica ivice[] = {{1, 2}, {1, 5}, {2, 3}, {2, 4}, {3, 4}, {4, 12}, {5, 6}, {5, 7}, {5, 8}, {6, 9}, {7, 9}, {7, 13}, {9, 10}, {9, 11}};
    //Ivica ivice[]= {{1, 2}, {2, 3}, {3,4}, {4,5}, {5,6}, {6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,1}};

    for(int i = 1; i <= g.VratiBrojCvorova(); i++)
        g.OznaciCvor(i, 'A' + i - 1);

    for(int i = 0; i < sizeof(ivice) / sizeof(Ivica); i++)
        g.DodajJednosmjernuIvicu(ivice[i].x, ivice[i].y);
}

void DefinirajGraf(Graf<string> &g)
{
    struct Ivica
    {
        int x, y;
    };

    //Ivica ivice[] = {{1, 2}, {1, 5}, {2, 3}, {2, 4}, {3, 4}, {4, 12}, {5, 6}, {5, 7}, {5, 8}, {6, 9}, {7, 9}, {7, 13}, {9, 10}, {9, 11}};
    Ivica ivice[]= {{1,2}, {2,3}, {3,4}, {4,5}, {5,6},  {7,8}, {8,1}};

    //for(int i = 1; i <= g.VratiBrojCvorova(); i++)
        //g.OznaciCvor(i, 'A' + i - 1);
    g.OznaciCvor(1,"1-Abc");
    g.OznaciCvor(2,"2-Def");
    g.OznaciCvor(3,"3-Ghi");
    g.OznaciCvor(4,"4-Jkl");
    g.OznaciCvor(5,"5-Mno");
    g.OznaciCvor(6,"6-Pqrs");
    g.OznaciCvor(7,"7-Tuv");
    g.OznaciCvor(8,"8-Wxyz");


    for(int i = 0; i < sizeof(ivice) / sizeof(Ivica); i++)
        g.DodajJednosmjernuIvicu(ivice[i].x, ivice[i].y);
}

int main()
{
    try
    {


    MojGraf g(14);
    DefinirajGraf(g);
    Graf<string> h(8);
    DefinirajGraf(h);

    cout << "Klasicni DFS, samo sa ulaznom obradom: " << endl;
    g.DFS_klasicni(1);

    cout << endl << "Klasicni BFS, samo sa ulaznom obradom: " << endl;
    g.BFS_klasicni(1);

    cout << endl << "Rekurzivni DFS, sa ulaznom i izlaznom obradom: " << endl;
    g.DFS(1);

    cout<< endl << "Poboljsani BFS, sa ulaznom i izlaznom obradom: " << endl;
    g.BFS(1);

    vector<string> *sortiraniCvorovi=h.topoloskoSortiranje();
    if (sortiraniCvorovi!=0)
    {
        cout << "Topoloski poredak: ";
        for (int i=0; i<sortiraniCvorovi->size(); i++)
            cout << (*sortiraniCvorovi)[i] << " ";
        cout << endl;
    }
    else cout << "Nemoguce topoloski sortirati!" << endl;


    }
    catch(const char poruka[])
    {
        cout << poruka << endl;
    }
    catch(...)
    {
        cout << "Problemi :(" << endl;
    }

    return 0;
}


