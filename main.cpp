#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;



class Exceptie : public exception {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "Factorul f este negativ!";
    }
};



class Produs{
   string denumire;
   string marime;
   string material;
   string brand;
   string culoare;
   float pret;
public:
   explicit Produs(string s1 = "", string s2 = "", string s3 = "", string s4 = "", string s5 = "", float p = 0): denumire(std::move(s1)), marime(std::move(s2))
   ,material(std::move(s3)), brand(std::move(s4)), culoare(std::move(s5)), pret(p){}

   virtual ~Produs()= default;

   Produs (const Produs& p){this->denumire = p.denumire; this->marime = p.marime; this->material = p.material; this->brand = p.brand; this->culoare = p.culoare; this->pret = p.pret;}

   Produs& operator=(const Produs& p){
        if(this == &p){return *this;}
        this->denumire = p.denumire; this->marime = p.marime; this->material = p.material; this->brand = p.brand; this->culoare = p.culoare; this->pret = p.pret;
        return *this;
    }

    [[nodiscard]] float get_pret() const{
    return pret;
   }

   friend ostream& operator<<(ostream &out, Produs& p){
       out << "Denumire: " << p.denumire;
       out << endl;
       out << "Marime: " << p.marime;
       out << endl;
       out << "Marterial: " << p.material;
       out << endl;
       out << "Brand: " << p.brand;
       out << endl;
       out << "Culoare: " << p.culoare;
       out << endl;
       out << "Pret: " << p.pret;
       out << endl;
       return out;
   }

   [[nodiscard]] virtual bool egal(const Produs& p) const {
        return denumire == p.denumire && marime == p.marime && material == p.material &&
               brand == p.brand && culoare == p.culoare && pret == p.pret;
   }

};


class Produs_femeie: virtual public Produs{
protected:int nivel_elasticitate_material;//1, 2 sau 3
protected:    const bool ventilatie;//0 sau 1
public:
    explicit Produs_femeie(bool v = false, [[maybe_unused]] string s1 = "", [[maybe_unused]] string s2 = "",
                           [[maybe_unused]] string s3 = "", [[maybe_unused]] string s4 = "", [[maybe_unused]] string s5 = "", float p = 0, int n_e = 1):
            Produs(std::move(s1),std::move(s2), std::move(s3), std::move(s4), std::move(s5), p), nivel_elasticitate_material(n_e), ventilatie(v){};

    ~Produs_femeie() override= default;

    Produs_femeie (const Produs_femeie& p): Produs(p), ventilatie(p.ventilatie) {this->nivel_elasticitate_material = p.nivel_elasticitate_material;}
    Produs_femeie& operator=(const Produs_femeie& p){
        if(this==&p){return *this;}
        Produs::operator=(p);
        this->nivel_elasticitate_material = p.nivel_elasticitate_material;
        return *this;

    }

    [[nodiscard]] bool egal(const Produs& p) const override {
        const auto* pf = dynamic_cast<const Produs_femeie*>(&p);
        return pf && Produs::egal(p) && nivel_elasticitate_material == pf->nivel_elasticitate_material &&
               ventilatie == pf->ventilatie;
    }

    friend ostream& operator<<(ostream& out, Produs_femeie& pf ){
        out << static_cast<Produs&>(pf);
        out << "Nivel_elasticitate_material: " << pf.nivel_elasticitate_material << endl;
        out << "Ventilatie: " << pf.ventilatie << endl;
        return out;
    }
};


class Produs_barbat: virtual public Produs{
protected:   int rezistenta_umiditate;//1, 2 sau 3
protected:const bool intaritura;//0 sau 1 (=marire_duritate_material-->genunchi+glezna etc)
public:
    explicit Produs_barbat(bool i, [[maybe_unused]] string s1 = "", [[maybe_unused]] string s2 = "",
                           [[maybe_unused]] string s3 = "", [[maybe_unused]] string s4 = "", [[maybe_unused]] string s5 = "", float p = 0, int r_u = 1):
            Produs(std::move(s1),std::move(s2), std::move(s3), std::move(s4), std::move(s5), p), rezistenta_umiditate(r_u), intaritura(i){};

    ~Produs_barbat() override= default;

    Produs_barbat (const Produs_barbat& p): Produs(p), intaritura(p.intaritura) {this->rezistenta_umiditate = p.rezistenta_umiditate;};

    Produs_barbat& operator=(const Produs_barbat& p){
        if(this == &p){return *this;}
        Produs::operator=(p);
        this->rezistenta_umiditate = p.rezistenta_umiditate;
        return *this;
    }

    [[nodiscard]] bool egal(const Produs& p) const override {
        const auto* pb = dynamic_cast<const Produs_barbat*>(&p);
        return pb && Produs::egal(p) && rezistenta_umiditate == pb->rezistenta_umiditate &&
               intaritura == pb->intaritura;
    }

    friend ostream& operator<<(ostream& out, Produs_barbat& pb ){
        out << static_cast<Produs&>(pb);
        out << "Rezistenta_umiditate: " << pb.rezistenta_umiditate << endl;
        out << "Intaritura: " << pb.intaritura << endl;
        return out;
    }
};


class Produs_copil: public Produs_femeie, public Produs_barbat{
    const bool elemente_reflectorizante;//0 sau 1
    const bool imprimeuri_tipice;//0 sau 1 (desene sau nu)
public:
    Produs_copil(bool v, bool i, bool e_r, bool i_t, const string& s1="", const string& s2="", const string& s3="", const string& s4="", const string& s5="", float p=0, int n_e=1, int r_u=1):
            Produs(s1,s2, s3, s4, s5, p), Produs_femeie(v,s1,s2, s3, s4, s5, p, n_e), Produs_barbat(i,s1,s2, s3, s4, s5, p, r_u), elemente_reflectorizante(e_r), imprimeuri_tipice(i_t){};

    ~Produs_copil() override= default;

    Produs_copil (const Produs_copil& p): Produs_femeie(p), Produs_barbat(p), elemente_reflectorizante(p.elemente_reflectorizante), imprimeuri_tipice(p.imprimeuri_tipice) {}

    Produs_copil& operator=(const Produs_copil& p){
        if(this == &p){return *this;}
        Produs_femeie::operator=(p);
        Produs_barbat::operator=(p);
        return *this;
    }

    [[nodiscard]] bool egal(const Produs& p) const override {
        const auto* pc = dynamic_cast<const Produs_copil*>(&p);
        return pc && Produs_femeie::egal(p) && Produs_barbat::egal(p) &&
               elemente_reflectorizante == pc->elemente_reflectorizante &&
               imprimeuri_tipice == pc->imprimeuri_tipice;
    }

    friend ostream& operator<<(ostream& out, Produs_copil& pc ){
        out << static_cast<Produs&>(pc);
        out << "Nivel_elasticitate_material: " << pc.nivel_elasticitate_material << endl;
        out << "Ventilatie: " << pc.ventilatie << endl;
        out << "Rezistenta_umiditate: " << pc.rezistenta_umiditate << endl;
        out << "Intaritura: " << pc.intaritura << endl;
        out << "Elemente_reflectorizante: " << pc.elemente_reflectorizante << endl;
        out << "Imprimeuri_tipice: " << pc.imprimeuri_tipice << endl;
        return out;
    }
};





class Persoana{
    string nume;
    string prenume;
protected:
    int id;
public:
    explicit Persoana(string s1 = "", string s2 = "",int i = 0): nume(std::move(s1)), prenume(std::move(s2)), id(i){}

    virtual ~Persoana()= default;

    Persoana(const Persoana& p){this->nume=p.nume; this->prenume = p.prenume; this->id = p.id;}

    Persoana& operator= (const Persoana& p){
        if(this == &p) return *this;
        this->nume = p.nume; this->prenume = p.prenume; this->id = p.id;
        return *this;
    }

    friend ostream& operator<<(ostream& out, Persoana& p);

    friend istream& operator>>(istream& in, Persoana& p);

    [[nodiscard]] int get_id() const{return id;}

    virtual void prezentare() = 0;
};
ostream& operator<<(ostream &out, Persoana& p){
    out << "Nume: ";
    out << p.nume << endl;
    out << "Prenume: ";
    out << p.prenume << endl;
    return out;
}

istream& operator>>(istream& in, Persoana& p){
    cout << "Nume: ";
    in >> p.nume;  cout << endl;
    cout << "Prenume: ";
    in >> p.prenume; cout << endl;
    return in;
}


class Client: public Persoana{
    float buget;
    vector<Produs*>cos_produse;
public:
    explicit Client([[maybe_unused]] string s1 = "", [[maybe_unused]] string s2 = "", int i = 0, float b = 0, vector<Produs*>c_p = {}): Persoana(std::move(s1), std::move(s2), i), buget(b), cos_produse(std::move(c_p)){}

    ~Client() override= default;

    Client (const Client& c): Persoana(c) {this->buget = c.buget; this->cos_produse = c.cos_produse;}

    Client& operator= (const Client c){
        if(this == &c) return *this;
        Persoana::operator=(c);
        this->buget = c.buget; this->cos_produse = c.cos_produse;
        return *this;
    }

    friend ostream& operator<<(ostream &out, Client& c);

    friend istream& operator>>(istream &in, Client& c);

    int cumparare_produs(Produs* p){
        if(buget<p->get_pret()){
            return 0;
        }
        buget-=p->get_pret();
        cos_produse.push_back(p);
        return 1;
    }

    void prezentare() override{
        cout <<"CLIENT|||" << "Id: " << id <<"; " << "Buget: "<< buget << ".   ";
    }
};
ostream& operator<<(ostream &out, Client& c){
    out << static_cast<Persoana&>(c);
    out << "Buget: ";
    out << c.buget << endl;
    out << "Cos_produse: " << endl <<endl;
    for(auto& p: c.cos_produse)
    out << *p << endl;
    return out;
}

istream& operator>>(istream &in, Client& c){
    in >> static_cast<Persoana&>(c);
    cout << "Buget: ";
    in >> c.buget; cout << endl;
    c.cos_produse={};
    return in;
}



class Angajat: public Persoana{
    string statut;
    float salariu;
public:
    explicit Angajat([[maybe_unused]] string s1 = "", [[maybe_unused]] string s2 = "", int i = 0, string s = "", float sal = 0): Persoana(std::move(s1), std::move(s2), i), statut(std::move(s)), salariu(sal){}
    Angajat():statut("casier"), salariu(2500){}

    ~Angajat() override = default;

    Angajat (const Angajat& a): Persoana(a) {this->salariu = a.salariu; this->statut = a.statut;}

    Angajat& operator= (const Angajat a){
        if(this==&a) return *this;
        Persoana::operator=(a);
        this->salariu = a.salariu; this->statut = a.statut;
        return *this;
    }

    friend ostream& operator<<(ostream &out, Angajat& a);

    friend istream& operator>>(istream &in, Angajat& a);

    friend Angajat& operator+(Angajat& a, float s);

    void prezentare() override{
        cout <<"ANGAJAT|||" << "Id: " << id <<"; " << "Salariu: "<< salariu << ".   ";
    }
};
ostream& operator<<(ostream &out, Angajat& a){
    out << static_cast<Persoana&>(a);
    out << "Statut: ";
    out << a.statut << endl;
    out << "Salariu: ";
    out << a.salariu << endl;
    return out;
}

istream& operator>>(istream &in, Angajat& a){
    in >> static_cast<Persoana&>(a);
    cout << "Statut: ";
    in >> a.statut; cout << endl;
    cout << "Salariu: ";
    in >> a.salariu; cout << endl;
    return in;
}

Angajat& operator+(Angajat& a, float s){
    a.salariu+=s;
    return a;
}


bool compararePersoanedupaId(const Persoana* , const Persoana* );
class Magazin{
    vector<Produs*>produse;
    vector<Angajat>angajati;
    vector<Client>clienti;
    static float buget;//Orice alt magazin deschis va imparti acelasi buget cu toate celelalte
public:
    explicit Magazin(vector<Produs*>pr={}, vector<Angajat>ag={}, vector<Client>cl={}):produse(std::move(pr)), angajati(std::move(ag)), clienti(std::move(cl)){}

    ~Magazin()= default;

    void afiseaza_angajat(int id){
        for(auto & a: angajati)
            if (a.get_id() == id) {
                cout << a <<endl;
                return;
            }
        cout << "Nu exista un angajat cu acest id!" << endl;
    }

    int get_cel_mai_mare_id(){
     int id = 0;
     for(auto& p: angajati)
         if (p.get_id()>id)id=p.get_id();
     return id;
    }

    void angajare(){
        Angajat a("", "", int(get_cel_mai_mare_id()+1), "", 0);
        cin>>a;
        angajati.push_back(a);
    }

    void concediere(int id){
        for(int i=0; i < int(angajati.size()); i++)
            if (angajati[i].get_id() == id && id!=0) {
                angajati.erase(angajati.begin()+i);
                return;
            }
        cout << "Nu exista un angajat cu acest id sau nu se poate concedia acest angajat!" << endl;
    }

    void mareste_salariu(int id, float s){
        for(auto & a: angajati)
            if (a.get_id() == id) {
                a=a+s;
                return;
            }
        cout << "Nu exista un angajat cu acest id!" << endl;
    }

    void aduga_produs(Produs* p){
        produse.push_back(p);
        Magazin::operator-=(*p);
        if (dynamic_cast<Produs_copil*>(p)){
            cout << "A fost adaugat un produs de copil!" << endl;
            return;
        }
        if (dynamic_cast<Produs_femeie*>(p)){
            cout << "A fost adaugat un produs de femeie!" << endl;
            return;
        }
        if (dynamic_cast<Produs_barbat*>(p)){
            cout << "A fost adaugat un produs de barbat!" << endl;
            return;
        }

    }

    void operator-=(const Produs& p){
      buget -= p.get_pret();
      if(buget <= 0) cout << "FALIMENT!!!!!!!!" <<endl;
    }

    void afiseaza_client(int id){
        for(auto & c: clienti)
            if (c.get_id() == id) {
                cout << c <<endl;
                return;
            }
        cout << "Nu exista un client cu acest id!" << endl;
    }

    void inregistrare(){
        Client c("", "", int(clienti.size()), 0, {});
        cin>>c;
        clienti.push_back(c);
    }

    void vinde_produs(Produs* p){
        for(int i=0; i<int(produse.size()); i++)
           if (produse[i]->egal(*p)) {
               Magazin::operator+=(*p);
               produse.erase(produse.begin()+i);
               return;
           }
    }

    void operator+=(const Produs& p){
        buget += p.get_pret();
    }

    int cumpara_produs(int id, Produs* p){
        for(auto & i : produse)
            if (i->egal(*p)) {
                        for(auto & c: clienti)
                            if (c.get_id() == id) {
                                if(c.cumparare_produs(p))
                                    return 1;
                                else{cout << "Buget insuficient!" << endl; return 0;}
                            }
                        cout << "Nu exista un client cu acest id!" << endl;
                        return 0;
            }
        cout << "Nu exista pe stocul magazinului un astfel de produs!" << endl;
        return 0;
    }

    void prezentare(){
        vector<Persoana*>P;
        for(auto& c: clienti)
            P.push_back(&c);
        for(auto& a: angajati)
            P.push_back(&a);
        std::sort(P.begin(), P.end(), compararePersoanedupaId);
        for(auto& p: P)
            p->prezentare();
    }

    static void marire_buget(float f){
        buget = buget*(1+f);
    }

    static float get_buget(){
        return buget;
    }

    void pune_client_m(Client& c){
        clienti.push_back(c);
    }

    void pune_angajat_m(Angajat& a){
        angajati.push_back(a);
    }

    void pune_produs_m(Produs* p){
        produse.push_back(p);
    }

    void afisare_produse(){
        for(auto& p:produse){
            if(dynamic_cast<Produs_copil*>(p)){ cout << *(dynamic_cast<Produs_copil*>(p)) << endl; continue;}
            if(dynamic_cast<Produs_femeie*>(p)){ cout << *(dynamic_cast<Produs_femeie*>(p)) << endl; continue;}
            if(dynamic_cast<Produs_barbat*>(p)){ cout << *(dynamic_cast<Produs_barbat*>(p)) << endl; continue;}
        }
    }
};
float Magazin::buget=1000000;//Toate sumele sunt in lei



bool compararePersoanedupaId(const Persoana* a, const Persoana* b) {
    return a->get_id() < b->get_id();
}



void Meniu() {
    vector<string> mesaje = {
            "LOGARE_ANGAJAT",
            "LOGARE_CUMPARATOR",
            "PERSOANELE_ASOCIATE_CU_MAGAZINUL",
            "AFISARE_PRODUSE",
            "IESIRE"

    };
    cout << "MENIUL MAGAZINULUI X " << endl << endl;
    for (int i = 0; i < int(mesaje.size()); i++) {
        cout << i + 1 << ". " << mesaje[i] << endl;
    }
    cout << "Optiune = " << endl;
}


void Meniu1() {
    vector<string> mesaje = {
            "ANGAJARE",
            "CONCEDIERE",
            "MARIRE_SALARIU",
            "ADAUGARE_PRODUS",
            "MARIRE_BUGET_MAGAZIN (cu un factor f)",
            "IESIRE"

    };

    for (int i = 0; i < int(mesaje.size()); i++) {
        cout << i + 1 << ". " << mesaje[i] << endl;
    }
    cout << "Optiune = " << endl;
}


void Meniu2() {
    vector<string> mesaje = {
            "PRODUS_FEMEIE",
            "PRODUS_BARBAT",
            "PRODUS_COPIL",
            "IESI"

    };
    for (int i = 0; i < int(mesaje.size()); i++) {
        cout << i + 1 << ". " << mesaje[i] << endl;
    }
    cout << "Optiune = " << endl;
}


void Meniu3() {
    vector<string> mesaje = {
            "CONECTEAZA-TE",
            "INREGISTREAZA-TE",
            "CUMPARA",
            "IESIRE"
    };
    for (int i = 0; i < int(mesaje.size()); i++) {
        cout << i + 1 << ". " << mesaje[i] << endl;
    }
    cout << "Optiune = " << endl;
}








int main() {
    Magazin X;
    vector <Produs*> Reziduri;



    auto* f1=new Produs_femeie(true,"tricou","S", "bumbac", "Puma", "negru", 200, 2 );
    auto* f2=new Produs_femeie(false,"tricou","XL", "lana", "Adidas", "alb", 150, 1 );
    auto* f3=new Produs_femeie(true,"pantalon","L", "catifea", "Nike", "albastru", 400, 3 );
    auto* f4=new Produs_femeie(true,"adidasi","38", "panza", "Puma", "galben", 370, 1 );
    auto* f5=new Produs_femeie(false,"ciorapi","35", "bumbac", "", "negru", 27, 3 );
    auto* b1=new Produs_barbat(false,"tricou","M", "bumbac", "Kipsta", "rosu", 130, 2 );
    auto* b2=new Produs_barbat(true,"adidasi","40", "piele", "Puma", "negru", 570, 3 );
    auto* b3=new Produs_barbat(true,"pantaloni","L", "bumbac", "Puma", "gri", 350,1 );
    auto* b4=new Produs_barbat(true,"pantaloni","M", "piele", "Nike", "galben", 800, 3 );
    auto* b5=new Produs_barbat(false,"ciorapi","42", "bumbac", "Nike", "gri", 46, 1 );
    auto* c1=new Produs_copil(true, true, true, true, "pantaloni","L", "bumbac", "Puma", "gri", 1100, 3, 3 );
    auto* c2=new Produs_copil(true, false, true, false, "tricou","M", "lana", "Adidas", "mov", 300, 2 );
    auto* c3=new Produs_copil(false, false, false, false, "adidasi","25", "piele", "Puma", "albastru", 842 );
    auto* c4=new Produs_copil(true, true, true, true, "ciorapi","37", "lana", "Kipsta", "gri", 60, 1, 2 );
    Reziduri.push_back(f1);
    Reziduri.push_back(f2);
    Reziduri.push_back(f3);
    Reziduri.push_back(f4);
    Reziduri.push_back(f5);
    Reziduri.push_back(b1);
    Reziduri.push_back(b2);
    Reziduri.push_back(b3);
    Reziduri.push_back(b4);
    Reziduri.push_back(b5);
    Reziduri.push_back(c1);
    Reziduri.push_back(c2);
    Reziduri.push_back(c3);
    Reziduri.push_back(c4);
    X.pune_produs_m(f1);
    X.pune_produs_m(f1);
    X.pune_produs_m(f2);
    X.pune_produs_m(f5);
    X.pune_produs_m(f4);
    X.pune_produs_m(b2);
    X.pune_produs_m(b4);
    X.pune_produs_m(b4);
    X.pune_produs_m(b3);
    X.pune_produs_m(b1);
    X.pune_produs_m(c1);
    X.pune_produs_m(c2);
    X.pune_produs_m(c3);
    X.pune_produs_m(c4);
    X.pune_produs_m(c1);
    X.pune_produs_m(c2);
    X.pune_produs_m(c3);
    X.pune_produs_m(c4);





    Angajat a1("Popa", "Ionel", 0, "manager", 6000);
    Angajat a2("Nitu", "Daniel", 1, "casier", 2700);
    X.pune_angajat_m(a1); X.pune_angajat_m(a2);





    vector<Produs*>cos_cump1={f3,c3};
    vector<Produs*>cos_cump2={b5,b1,b4};
    Client cl1("Popescu", "Simina", 0, 2000, cos_cump1);
    Client cl2("Stan", "Antonio", 1, 1300, cos_cump1);
    Client cl3("Irimia", "Alina", 2, 300);
    X.pune_client_m(cl1);
    X.pune_client_m(cl2);
    X.pune_client_m(cl3);



    bool continua = true;
    
    while(continua){
        Meniu();
        int n;
        cin >> n;
        switch (n) {
            case 1:{
               cout << "Id: ";
               int id;
               cin >> id;
               cout << endl;
               X.afiseaza_angajat(id);
               if(id == 0) {
                   bool continua1 = true;

                   while (continua1) {
                       Meniu1();
                       int n1;
                       cin >> n1;
                       switch (n1) {
                           case 1:{
                               X.angajare();
                               cout << endl;
                               break;
                           }



                           case 2:{
                               cout<<"Id: ";
                               int i;
                               cin >> i;
                               cout << endl;
                               X.concediere(i);
                               break;
                           }



                           case 3:{
                               cout<<"Id: ";
                               int i;
                               cin >> i;
                               cout << endl;
                               cout << "Suma_cu_care_se_mareste_slariul: ";
                               float s;
                               cin >> s;
                               cout << endl;
                               X.mareste_salariu(i, s);
                               break;
                           }



                           case 4:{
                               string denumire, marime, material, brand, culoare;
                               float pret;
                               bool continua2 = true;

                               while(continua2){
                                   Meniu2();
                                   int n2;
                                   cin >> n2;
                                   switch (n2) {
                                       case 1:{
                                       int nivel_elasticitate_material;
                                       bool ventilatie;
                                       cout << "Denumire: ";
                                       cin >> denumire;
                                       cout << endl;
                                       cout << "Marime: ";
                                       cin >> marime;
                                       cout << endl;
                                       cout << "Material: ";
                                       cin >> material;
                                       cout << endl;
                                       cout << "Brand: ";
                                       cin>>brand;
                                       cout << endl;
                                       cout << "Culoare: ";
                                       cin >> culoare;
                                       cout << endl;
                                       cout << "Pret: ";
                                       cin >> pret;
                                       cout << endl;
                                       cout << "Nivel_elasticitate_material (1, 2 sau 3): ";
                                       cin >> nivel_elasticitate_material;
                                       cout << endl;
                                       cout << "Ventilatie (0-Nu, 1-Da) : ";
                                       cin >> ventilatie;
                                       cout << endl;
                                       auto* p= new Produs_femeie(ventilatie, denumire, marime, material, brand, culoare, pret, nivel_elasticitate_material);
                                       Reziduri.push_back(p);
                                       X.aduga_produs(p);
                                       break;
                                       }

                                       case 2:{
                                           int rezistenta_umiditate;
                                           bool intaritura;
                                           cout << "Denumire: ";
                                           cin >> denumire;
                                           cout << endl;
                                           cout << "Marime: ";
                                           cin >> marime;
                                           cout << endl;
                                           cout << "Material: ";
                                           cin >> material;
                                           cout << endl;
                                           cout << "Brand: ";
                                           cin>>brand;
                                           cout << endl;
                                           cout << "Culoare: ";
                                           cin >> culoare;
                                           cout << endl;
                                           cout << "Pret: ";
                                           cin >> pret;
                                           cout << endl;
                                           cout << "Rezistenta_umiditate (1, 2 sau 3): ";
                                           cin >> rezistenta_umiditate;
                                           cout << endl;
                                           cout << "Intaritura (0-Nu, 1-Da) : ";
                                           cin >> intaritura;
                                           cout << endl;
                                           auto* p= new Produs_barbat(intaritura, denumire, marime, material, brand, culoare, pret, rezistenta_umiditate);
                                           Reziduri.push_back(p);
                                           X.aduga_produs(p);
                                           break;
                                       }

                                       case 3:{
                                           int nivel_elasticitate_material;
                                           bool ventilatie;
                                           int rezistenta_umiditate;
                                           bool intaritura;
                                           bool elemente_reflectorizante;
                                           bool imprimeuri_tipice;
                                           cout << "Denumire: ";
                                           cin >> denumire;
                                           cout << endl;
                                           cout << "Marime: ";
                                           cin >> marime;
                                           cout << endl;
                                           cout << "Material: ";
                                           cin >> material;
                                           cout << endl;
                                           cout << "Brand: ";
                                           cin>>brand;
                                           cout << endl;
                                           cout << "Culoare: ";
                                           cin >> culoare;
                                           cout << endl;
                                           cout << "Pret: ";
                                           cin >> pret;
                                           cout << endl;
                                           cout << "Nivel_elasticitate_material (1, 2 sau 3): ";
                                           cin >> nivel_elasticitate_material;
                                           cout << endl;
                                           cout << "Ventilatie (0-Nu, 1-Da) : ";
                                           cin >> ventilatie;
                                           cout << endl;
                                           cout << "Rezistenta_umiditate (1, 2 sau 3): ";
                                           cin >> rezistenta_umiditate;
                                           cout << endl;
                                           cout << "Intaritura (0-Nu, 1-Da) : ";
                                           cin >> intaritura;
                                           cout << endl;
                                           cout << "Elemente_reflectorizante (0-Nu, 1-Da) : ";
                                           cin >> elemente_reflectorizante;
                                           cout << endl;
                                           cout << "Imprimeuri_tipice (0-Nu, 1-Da) : ";
                                           cin >> imprimeuri_tipice;
                                           cout << endl;
                                           auto* p= new Produs_copil(ventilatie, intaritura, elemente_reflectorizante, imprimeuri_tipice, denumire, marime, material, brand, culoare, pret,nivel_elasticitate_material, rezistenta_umiditate);
                                           Reziduri.push_back(p);
                                           X.aduga_produs(p);
                                           break;
                                       }

                                       case 4:{
                                           continua2=false;
                                           break;
                                       }

                                       default:{
                                           break;
                                       }
                                   }
                                   cout << endl;
                               }
                               break;
                           }



                           case 5:{
                            cout << "Factorul f de marire: ";
                            float f;
                            cin >> f;
                            cout << endl;
                            try {
                                   if (f < 0) {
                                       throw Exceptie();
                                   } else {
                                       Magazin::marire_buget(f);
                                       cout << "Noul buget al magazinului X este: " << Magazin::get_buget() << endl;
                                   }
                            } catch (Exceptie& e) {
                                   cout<<"Eroare: "<< e.what() <<endl;
                            }
                            break;
                           }



                           case 6:{
                             continua1 = false;
                             break;
                           }



                           default:{
                               break;
                           }
                       }
                       cout << endl << endl;
                   }
               }
                break;
            }








            case 2:{
                cout << "Bine ai venit la magazinul X! Sa vedem daca ne cunoastem:))" << endl;
                bool continua3 = true;

                while (continua3){
                    Meniu3();
                    int n3;
                    cin >> n3;
                    switch(n3)
                    {
                    case 1:{
                        cout<<"Id: ";
                        int id;
                        cin>>id;
                        cout << endl;
                        X.afiseaza_client(id);
                        break;
                    }



                    case 2:{
                        X.inregistrare();
                        cout << endl;
                        break;
                    }



                    case 3:{
                        string denumire, marime, material, brand, culoare;
                        float pret;
                        bool continua2 = true;

                        while(continua2){
                            Meniu2();
                            int n2;
                            cin>>n2;
                            switch (n2) {
                                case 1:{
                                    int nivel_elasticitate_material;
                                    bool ventilatie;
                                    cout << "Denumire: ";
                                    cin >> denumire;
                                    cout << endl;
                                    cout << "Marime: ";
                                    cin >> marime;
                                    cout << endl;
                                    cout << "Material: ";
                                    cin >> material;
                                    cout << endl;
                                    cout << "Brand: ";
                                    cin>>brand;
                                    cout << endl;
                                    cout << "Culoare: ";
                                    cin >> culoare;
                                    cout << endl;
                                    cout << "Pret: ";
                                    cin >> pret;
                                    cout << endl;
                                    cout << "Nivel_elasticitate_material (1, 2 sau 3): ";
                                    cin >> nivel_elasticitate_material;
                                    cout << endl;
                                    cout << "Ventilatie (0/false-Nu, 1/true-Da) : ";
                                    cin >> ventilatie;
                                    cout << endl;
                                    auto* p= new Produs_femeie(ventilatie, denumire, marime, material, brand, culoare, pret, nivel_elasticitate_material);
                                    Reziduri.push_back(p);
                                    cout << "-------------" << endl;
                                    cout << "Id: ";
                                    int id;
                                    cin>>id;
                                    cout << endl;
                                    if(X.cumpara_produs(id, p)){
                                    X.vinde_produs(p);}
                                    else cout << "Nu se poate realiza achizitia!" <<endl;
                                    break;
                                }

                                case 2:{
                                    int rezistenta_umiditate;
                                    bool intaritura;
                                    cout << "Denumire: ";
                                    cin >> denumire;
                                    cout << endl;
                                    cout << "Marime: ";
                                    cin >> marime;
                                    cout << endl;
                                    cout << "Material: ";
                                    cin >> material;
                                    cout << endl;
                                    cout << "Brand: ";
                                    cin>>brand;
                                    cout << endl;
                                    cout << "Culoare: ";
                                    cin >> culoare;
                                    cout << endl;
                                    cout << "Pret: ";
                                    cin >> pret;
                                    cout << endl;
                                    cout << "Rezistenta_umiditate (1, 2 sau 3): ";
                                    cin >> rezistenta_umiditate;
                                    cout << endl;
                                    cout << "Intaritura (0/false-Nu, 1/true-Da) : ";
                                    cin >> intaritura;
                                    cout << endl;
                                    auto* p= new Produs_barbat(intaritura, denumire, marime, material, brand, culoare, pret, rezistenta_umiditate);
                                    Reziduri.push_back(p);
                                    cout << "-------------" << endl;
                                    cout << "Id: ";
                                    int id;
                                    cin>>id;
                                    if(X.cumpara_produs(id, p)){
                                        X.vinde_produs(p);}
                                    else cout << "Nu se poate realiza achizitia!" <<endl;
                                    break;
                                }

                                case 3:{
                                    int nivel_elasticitate_material;
                                    bool ventilatie;
                                    int rezistenta_umiditate;
                                    bool intaritura;
                                    bool elemente_reflectorizante;
                                    bool imprimeuri_tipice;
                                    cout << "Denumire: ";
                                    cin >> denumire;
                                    cout << endl;
                                    cout << "Marime: ";
                                    cin >> marime;
                                    cout << endl;
                                    cout << "Material: ";
                                    cin >> material;
                                    cout << endl;
                                    cout << "Brand: ";
                                    cin>>brand;
                                    cout << endl;
                                    cout << "Culoare: ";
                                    cin >> culoare;
                                    cout << endl;
                                    cout << "Pret: ";
                                    cin >> pret;
                                    cout << endl;
                                    cout << "Nivel_elasticitate_material (1, 2 sau 3): ";
                                    cin >> nivel_elasticitate_material;
                                    cout << endl;
                                    cout << "Ventilatie (0-Nu, 1-Da) : ";
                                    cin >> ventilatie;
                                    cout << endl;
                                    cout << "Rezistenta_umiditate (1, 2 sau 3): ";
                                    cin >> rezistenta_umiditate;
                                    cout << endl;
                                    cout << "Intaritura (0-Nu, 1-Da) : ";
                                    cin >> intaritura;
                                    cout << endl;
                                    cout << "Elemente_reflectorizante (0-Nu, 1-Da) : ";
                                    cin >> elemente_reflectorizante;
                                    cout << endl;
                                    cout << "Imprimeuri_tipice (0-Nu, 1-Da) : ";
                                    cin >> imprimeuri_tipice;
                                    cout << endl;
                                    auto* p= new Produs_copil(ventilatie, intaritura, elemente_reflectorizante, imprimeuri_tipice, denumire, marime, material, brand, culoare, pret,nivel_elasticitate_material, rezistenta_umiditate);
                                    Reziduri.push_back(p);
                                    cout << "-------------" << endl;
                                    cout << "Id: ";
                                    int id;
                                    cin>>id;
                                    if(X.cumpara_produs(id, p)){
                                        X.vinde_produs(p);}
                                    else cout << "Nu se poate realiza achizitia!" <<endl;
                                    break;
                                }

                                case 4:{
                                    continua2 = false;
                                    break;
                                }

                                default:{
                                    break;
                                }
                            }
                            cout << endl;
                        }
                        break;
                    }



                    case 4:{
                        continua3 = false;
                        break;
                    }



                    default:{
                        break;
                    }
                    }
                    cout << endl << endl;
                }
                break;
            }







            case 3:{
               X.prezentare();
                break;
            }






            case 4:{
                X.afisare_produse();
                break;
            }










            case 5:{
                continua = false;
                break;
            }








            default:{
                break;
            }

        }
        cout << endl << endl << endl;
    }

    for(auto& r: Reziduri)
        delete r;

}
