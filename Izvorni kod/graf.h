#ifndef GRAF
#define GRAF
#include <vector>
#include <stack>
#include <queue>
#include <list>
using namespace std;

template <typename TipCvorova, typename TipIvica = bool>
class Graf
{
    int broj_cvorova;
    vector<TipCvorova> cvorovi;
    vector<bool> posjecen;
    vector<vector<TipIvica> > matrica;
    bool treba_li_dalje;

    void TestCvora(int cvor)
    {
        if(cvor < 1 || cvor > broj_cvorova) throw "Cvor izvan opsega!\n";
    }

    void Priprema();
    void DFS_pomocna(int pocetni_cvor);

    bool PosjetiCvor(int cvor)
    {
        if(!treba_li_dalje) return false;
        posjecen[cvor] = true;
        return treba_li_dalje = UlaznaObrada(cvor);
    }

    bool ZabiljeziIvicu(int pocetni, int zavrsni)
    {
        if(!treba_li_dalje) return false;
        return treba_li_dalje = IzlaznaObrada(pocetni, zavrsni);
    }

    public:

    Graf(int broj_cvorova);
    int VratiBrojCvorova() { return broj_cvorova; }
    int VratiBrojIvica();

    void foo();
    vector<TipCvorova>* topoloskoSortiranje();

    virtual bool UlaznaObrada(int cvor){}
    virtual bool IzlaznaObrada(int pocetni, int zavrsni){}

    void OznaciCvor(int cvor, TipCvorova oznaka)
    {
        TestCvora(cvor); cvorovi[cvor] = oznaka;
    }

    TipCvorova OznakaCvora(int cvor)
    {
        TestCvora(cvor); return cvorovi[cvor];
    }

    void DodajJednosmjernuIvicu(int pocetni, int zavrsni, TipIvica tezina = 1)
    {
        TestCvora(pocetni); TestCvora(zavrsni);
        matrica[pocetni][zavrsni] = tezina;
    }

    void DodajIvicu(int pocetni, int zavrsni, TipIvica tezina = 1)
    {
        TestCvora(pocetni); TestCvora(zavrsni);
        matrica[pocetni][zavrsni] = matrica[zavrsni][pocetni] = tezina;
    }

    bool Spojeni(int pocetni, int zavrsni)
    {
        TestCvora(pocetni); TestCvora(zavrsni);
        return matrica[pocetni][zavrsni] != 0;
    }

    TipIvica VratiTezinu(int pocetni, int zavrsni)
    {
        TestCvora(pocetni); TestCvora(zavrsni);
        return matrica[pocetni][zavrsni];
    }

    void DFS_klasicni(int pocetni_cvor);
    void BFS_klasicni(int pomocni_cvor);
    void DFS(int pocetni_cvor);
    void BFS(int pocetni_cvor);
};

template <typename TipCvorova, typename TipIvica>
Graf<TipCvorova,TipIvica>::Graf(int broj_cvorova) :
broj_cvorova(broj_cvorova), cvorovi(broj_cvorova+1), matrica(broj_cvorova+1), posjecen(broj_cvorova+1), treba_li_dalje(true)
{
    for(int i = 1; i <= broj_cvorova; i++) matrica[i].resize(broj_cvorova+1);
}

template <typename TipCvorova, typename TipIvica>
int Graf<TipCvorova,TipIvica>::VratiBrojIvica()
{
    int brojac(0);
    for(int i = 1; i <= broj_cvorova; i++)
        for(int j = 1; i <= broj_cvorova; i++)
            if(matrica[i][j] != 0) brojac++;
    return brojac;
}

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::Priprema()
{
    treba_li_dalje = true;
    for(int i = 1; i <= broj_cvorova; i++) posjecen[i] = false;
}

//Klasicni nerekurzivni DFS. Ova verzija DFS ne podrzava izlaznu obradu!

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::DFS_klasicni(int pocetni_cvor)
{
    stack<int> s;
    Priprema();
    s.push(pocetni_cvor);

    while(!s.empty())
    {
        int cvor=s.top(); s.pop();
        if(!posjecen[cvor])
        {
            if(!PosjetiCvor(cvor)) return;
            for(int i=1; i<=broj_cvorova; i++)
                if(matrica[cvor][i] != 0 && !posjecen[i]) s.push(i);
        }
    }
}

//Klasicni BFS. Ova verzija BFS ne podrzava izlaznu obradu!

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::BFS_klasicni(int pocetni_cvor)
{
    queue<int> q;
    Priprema();
    q.push(pocetni_cvor);

    while(!q.empty())
    {
        int cvor=q.front(); q.pop();
        if(!posjecen[cvor])
        {
            if(!PosjetiCvor(cvor)) return;
            for(int i=1; i<=broj_cvorova; i++)
            if(matrica[cvor][i] != 0 && !posjecen[i]) q.push(i);
        }
    }
}

//Klasicni rekurzivni DFS. Podrzava izlaznu obradu.

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::DFS(int pocetni_cvor)
{
    Priprema();
    DFS_pomocna(pocetni_cvor);
}

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::DFS_pomocna(int pocetni_cvor)
{
    if(!PosjetiCvor(pocetni_cvor)) return;

    for(int i=1; i<=broj_cvorova; i++)
    {
        if(matrica[pocetni_cvor][i] != 0 && !posjecen[i])
        {
            if(!ZabiljeziIvicu(pocetni_cvor, i)) return;
            DFS_pomocna(i);
        }
    }
}

// Poboljsani BFS. Podrzava izlaznu obradu.

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::BFS(int pocetni_cvor)
{
    queue<int> q;
    Priprema();
    q.push(pocetni_cvor);

    while(!q.empty())
    {
        int cvor=q.front(); q.pop();
        if(!PosjetiCvor(cvor)) return;

        for(int i=1; i<=broj_cvorova; i++)
            if(matrica[cvor][i] != 0 && !posjecen[i])
            {
                if(!ZabiljeziIvicu(cvor,i)) return;
                q.push(i);
                posjecen[i]=true;
            }
    }
}

template <typename TipCvorova, typename TipIvica>
void Graf<TipCvorova,TipIvica>::foo()
{
    for (int i=1; i<=broj_cvorova; i++)
    {
        cout << OznakaCvora(i) << ":    ";
        for (int j=1; j<=broj_cvorova; j++) cout << matrica[i][j] << " ";
        cout << endl;
    }
}


template <typename TipCvorova, typename TipIvica>
vector<TipCvorova>* Graf<TipCvorova,TipIvica>::topoloskoSortiranje()
{
    vector<TipCvorova>* rez=new vector<TipCvorova>; // L -> vektor za rezultat
    list<int> s;
    vector<int> incoming(broj_cvorova+1);

    Priprema();

    vector<vector<TipIvica> > mat (broj_cvorova+1);
    for (int i=1; i<=broj_cvorova; i++)
    {
        mat[i].resize(broj_cvorova+1);
        for (int j=1; j<=broj_cvorova; j++) mat[i][j]=matrica[i][j];
    }

    for (int i=1; i<=broj_cvorova; i++) // T1
    {
        incoming[i]=0;
        for (int j=1; j<=broj_cvorova; j++)
            if (matrica[j][i]!=0) incoming[i]++;

        if (incoming[i]==0) s.push_back(i);
    }

    while (!s.empty())
    {
        int cvor=s.front();
        s.pop_front();
        rez->push_back(OznakaCvora(cvor));

        for (int i=1; i<=broj_cvorova; i++)
            if (mat[cvor][i]!=0)
            {
                mat[cvor][i]=0;
                incoming[i]--;
                if (incoming[i]==0) s.push_back(i);
            }
    }

    for (int i=1; i<=broj_cvorova; i++)
        for (int j=1; j<=broj_cvorova; j++)
            if (mat[i][j]!=0)
                return 0;

    return rez;
}
#endif

