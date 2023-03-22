#include <iostream>
#include <exception>
#include <vector>
#include <string>

using namespace std;

class Produs
{
public:
    int ID;
    string nume_produs;
    double pret;
    Produs(int x, string name, double p);
    static Produs citire()
    {
        int ID;
        string nume_produs;
        double pret;

        cout << "Introdu ID-ul:";
        cin >> ID;
        cout << "Introdu numele:";
        cin.sync();
        getline(cin, nume_produs);
        cout << "Introdu pretul:";
        cin >> pret;
        Produs p = Produs(ID, nume_produs, pret);
        return p;
    }

    virtual void afisare();

    int GetID()
    {
        return ID;
    }
    string GetNameProd()
    {
        return nume_produs;
    }
    double GetPrice()
    {
        return pret;
    }

    void setID(int x)
    {
        ID = x;
    }
    void setNameProd(string name)
    {
        nume_produs = name;
    }
    void setPrice(double p)
    {
        pret = p;
    }
};

Produs::Produs(int id, string nume, double pret)
{
    this->ID = id;
    this->nume_produs = nume;
    this->pret = pret;
}

void Produs::afisare()
{
    cout << "ID produs: " << ID << endl;
    cout << "Numele produsului: " << nume_produs << endl;
    cout << "Pretul produsului: " << pret << endl;
}

class Frigider : public Produs
{
public:
    int volum;
    bool areCongelator;

    Frigider(int id, string nume, double pret, int volum, bool areCongelator) : Produs(id, nume, pret)
    {
        this->volum = volum;
        this->areCongelator = areCongelator;
    }

    static Produs* citire()
    {
        int ID;
        string nume_produs;
        double pret;
        int volum;
        bool areCongelator;
        cout << "Introdu ID-ul frigiderului: " << endl;
        cin >> ID;
        cout << "Introdu numele frigiderului: " << endl;
        cin >> nume_produs;
        cout << "Introdu pretul frigiderului: " << endl;
        cin >> pret;
        cout << "Introdu volumul frigiderului: " << endl;
        cin >> volum;
        cout << "Vrei sa aiba congelator?" << endl;
        cout << "1 -> da, 0 -> nu" << endl;
        cin >> areCongelator;
        Frigider* frg;
        frg = new Frigider(ID, nume_produs, pret, volum, areCongelator);
        return (Produs*)frg;
    }
    virtual void afisare();

};


void Frigider::afisare()
{
    cout << "ID produs: " << GetID() << endl;
    cout << "Numele produsului: " << GetNameProd() << endl;
    cout << "Pretul produsului: " << GetPrice() << endl;
    cout << "Volumul frigiderului: " << volum << endl;
    if (areCongelator == 1) {
        cout << "Are congelator" << endl;
    }
    else {
        cout << "Nu are congelator" << endl;
    }

}

class MasinaDeSpalat : public Produs
{
public:
    int RPM;
    string clasaEnergetica;
    MasinaDeSpalat(int id, string nume, double pret, int RPM, string clasaEnergetica) :Produs(id, nume, pret)
    {
        this->RPM = RPM;
        this->clasaEnergetica = clasaEnergetica;
    }
    static Produs* citire()
    {
        int ID;
        string nume_produs;
        double pret;
        int RPM;
        string clasaEnergetica;
        cout << "Introduceti id-ul masinii de spalat: " << endl;
        cin >> ID;
        cout << "Introduceti numele masinii de spalat: " << endl;
        cin >> nume_produs;
        cout << "Introduceti pretul masinii de spalat: " << endl;
        cin >> pret;
        cout << "Introduceti numarul de rotatii per minut a masinii de spalat: " << endl;
        cin >> RPM;
        cout << "Introduceti clasa energetica a masinii de spalat: " << endl;
        cin >> clasaEnergetica;
        MasinaDeSpalat* ms;
        ms = new MasinaDeSpalat(ID, nume_produs, pret, RPM, clasaEnergetica);
        return (Produs*)ms;
    }
    virtual void afisare();
};

void MasinaDeSpalat::afisare()
{
    cout << "ID produs: " << GetID() << endl;
    cout << "Numele produsului: " << GetNameProd() << endl;
    cout << "Pretul produsului: " << GetPrice() << endl;
    cout << "Numarul rotatiilor per minut: " << RPM << endl;
    cout << "Clasa energetica: " << clasaEnergetica << endl;
}

class Magazin {
public:
    int nrProduse;
    vector<Produs*> p;
    Magazin() {}
    Magazin(int nrProduse)
    {
        cout << "Numarul de produse suportate:";
        this->nrProduse = nrProduse;
    }

    void adaugaProdus()
    {
        int x;

        cout << "Ce produs vrei sa alegi dintre frigider si masina de spalat?" << endl << "Frigider=0, Masina de spalat=1" << endl;
        cin >> x;
        if (x == 0)
        {
            p.push_back((Produs*)Frigider::citire());
        }
        else if (x == 1)
        {
            p.push_back((Produs*)MasinaDeSpalat::citire());
        }
    }

    void eliminaProdus(int idProdus)
    {
        for (int i = 0; i < p.size(); i++)
        {
            if (i = idProdus)
            {
                p.erase(p.begin() + (idProdus - 1));
            }
        }
    }

    Produs* cautaProdus(int idProdus)
    {

        for (int i = 0; i < p.size(); i++)
        {
            if (p[i]->GetID() == idProdus)
            {
                return p[i];
            }
        }
        return nullptr;
    }

    int numaraMasiniDeSpalat()
    {
        int cnt = 0;
        for (int i = 0; i < p.size(); i++)
        {
            if (typeid(*p[i]) == typeid(MasinaDeSpalat))
            {
                cnt++;
            }
        }
        return cnt;
    }

    void scrieProduse()
    {
        for (int i = 0; i < p.size(); i++)
        {
            if (typeid(*p[i]) == typeid(MasinaDeSpalat))
            {
                cout << "[ " << i + 1 << " ]" << ":" << endl;
                p[i]->afisare();
                cout << endl;
            }
            if (typeid(*p[i]) == typeid(Frigider))
            {
                cout << "[ " << i + 1 << " ]" << ":" << endl;
                p[i]->afisare();
                cout << endl;
            }
        }
    }

};

int main() {
    char caz;
    int idProd, nrProduse = 0;
    int cnt = 0;
    Magazin mgz;
    mgz = Magazin(nrProduse);
    cin >> nrProduse;
    cout << "Bine ai venit la magazinul nostru!" << endl << endl;
    do {
        cout << "Alege o comanda din urmatoarele:" << endl << "A -> Adauga produs" << endl << "E -> Elimina produs" << endl << "C -> Cauta produs" << endl << "N -> Numara masinile de spalat" << endl << "L -> Scrie produse" << endl << "Q -> Inchide magazinul" << endl << endl;
        cin >> caz;
        switch (caz) {
        case 'A': try {
            cnt++;
            if (cnt > nrProduse)
            {
                throw string("MagazinPlinException");
            }
            mgz.adaugaProdus();


        }
                catch (string exc) {
                    cout << endl;
                    cout << exc << endl;
                }
                break;
        case 'E':
            try {
                cout << "Introdu ID-ul produsului pe care vrei sa il elimini:";
                cin >> idProd;
                if (mgz.cautaProdus(idProd) != NULL) {
                    mgz.eliminaProdus(idProd);
                    cout << "Produs eliminat cu succes!" << endl;
                }
                else {
                    cout << "Acest produs nu exista!" << endl;
                    throw string("ProdusInexistentException");
                }
            }
            catch (string exc)
            {
                cout << endl;
                cout << exc << endl;
            }
            break;
        case 'C':try {
            cout << "Introdu ID-ul produsului pe care vrei sa il cauti:";
            cin >> idProd;
            if (mgz.cautaProdus(idProd) != NULL) {
                mgz.cautaProdus(idProd)->afisare();
            }
            else {
                cout << "Produsul nu exista!" << endl;
                throw string("ProdusInexistentException");
            }
        }
                catch (string exc) {
                    cout << endl;
                    cout << exc << endl;
                }
                break;
        case 'N':cout << "Numarul de masini de spalat:" << mgz.numaraMasiniDeSpalat() << endl;
            break;
        case 'L':cout << "Lista produselor:" << endl;
            mgz.scrieProduse();
            break;
        }
    } while (caz != 'Q');

    return 0;
}
