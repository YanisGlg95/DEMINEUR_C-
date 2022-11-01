#include <iostream>
#include <stdlib.h>
#include <random>
#include <assert.h>
//#include "demineur.h"

using namespace std;


enum Etat_case { M = 'm', Vide = ' ', Cacher = '.', Marque = 'x' };   //état d'une case
enum action { Marquer = 'M', Demasquer = 'D' };

typedef char Item;
enum { SIZE = 100 };

typedef struct {

    unsigned int mine; // nombre de mines
    unsigned int colonne; //nombre de colonne 
    unsigned int ligne; // nombre de ligne 
    unsigned int coup;
    int pos_Mine[SIZE];
    int pos_Coup[SIZE];
    char HCoup[SIZE];
}Grille; //Structure d'une grille 



// 1) fonction permettant de créer un problème avec des valeurs aléatoire et des les afficher.

void InitPB(unsigned int ligne, unsigned int colonne, unsigned int mine) {

    
    srand(time(NULL));

    int* position = new int[mine];
    int* temp = new int[ligne * colonne];

    cout << ligne << " " << colonne << " " << mine;

    for (unsigned int i = 0; i < mine; i++) {
        unsigned int postionmine = rand() % (ligne * colonne);

        while (temp[postionmine] == -1) {
            postionmine = rand() % (ligne * colonne);
        }

        position[i] = postionmine;
        temp[postionmine] = -1;
        cout << " " << position[i];
    }
    cout << endl;

    delete[] position;
    delete[] temp;

}



//2) Initalise une grille à partir d'un nombre x de ligne, de colonne et de mine

// Initialiser une grille 

void InitJ(Grille& a, unsigned int ligne, unsigned colonne, unsigned int mine) {

    a.ligne = ligne;
    a.colonne = colonne;
    a.mine = mine;
    //Stockage des données dans la structure Grille pour les fonctions suivantes

    for (unsigned int i = 0; i < mine; ++i) {  //Choix et placement des mines stockées dans le tableau positionMines
        cin >> a.pos_Mine[i];

    }
    cin >> a.coup;
    assert(a.coup < (ligne* colonne) - a.mine);

    for (unsigned int i = 0; i < a.coup; ++i) {  //Historique de coups
        cin >> a.HCoup[i];
        cin >> a.pos_Coup[i];
    }
}
void triM(Grille& a) {
        //Tri position mine dans l'ordre croissant
        unsigned int t1 = 0;

        for (unsigned int i = 0; i < a.mine; i++) {
            for (unsigned int j = 0; j < a.mine; j++) {
                if (a.pos_Mine[i] < a.pos_Mine[j]) {

                    t1 = a.pos_Mine[i];
                    a.pos_Mine[i] = a.pos_Mine[j];
                    a.pos_Mine[j] = t1;

                }
            }
        }
    }
void triH(Grille& a) {
    //Tri  mines dans l'ordre croissant dans l'historique

    unsigned int t2 = 0, tl = 0;
  
    for (unsigned int i = 0; i < a.coup; ++i) {
        for (unsigned int j = 0; j < a.coup; ++j) {
            if (a.pos_Coup[i] < a.pos_Coup[j]) {

                //Permet de Triez les nombres
                t2 = a.pos_Coup[i];
                a.pos_Coup[i] = a.pos_Coup[j];
                a.pos_Coup[j] = t2;

                //Permet de Triez les caractères en fonction des nombres

                tl = a.HCoup[i];
                a.HCoup[i] = a.HCoup[j];
                a.HCoup[j] = tl;

            }
        }
    }
}

void InitGr(Item*** a, Grille& gr) {

    // Initialise la grille

    *a = new Item * [gr.ligne];

    for (unsigned int i = 0; i < gr.colonne; ++i) {

        (*a)[i] = new Item[gr.colonne];
    }

    for (unsigned int l = 0; l < gr.ligne; l++) {

        for (unsigned int c = 0; c < gr.colonne; c++) {

            (*a)[l][c] = '.';
        }
    }
}

void PoseMine(Grille& gr, Item** a) {
    unsigned int p = 0;
    unsigned int cpt = 0;

    for (unsigned int l = 0; l < gr.ligne; ++l) {
        for (unsigned int c = 0; c < gr.colonne; ++c) {
            if (gr.pos_Mine[cpt] == p) {
                a[l][c] = M;
                cpt++;
                p++;
            }
            else {
                p++;
            }
        }
    }
}
void MarqueOuDemasque(Grille& gr, Item** a) {
    int cpt = 0;
    int p = 0;
    for (unsigned int l = 0; l < gr.ligne; l++) {
        for (unsigned int c = 0; c < gr.colonne; c++) {
            if (gr.HCoup[cpt] == Marquer && gr.pos_Coup[cpt] == p) {
                a[l][c] = Marque;
                p++;
                cpt++;
            }
            else if (gr.HCoup[cpt] == Demasquer && gr.HCoup[cpt] == p) {
                if (a[l][c] == Cacher) {
                    a[l][c] = Vide;
                    p++;
                    cpt++;
                }
            }
            else {
                a[l][c] = Cacher;
                p++;
            }
        }
    }
}
    void caseadj(Grille & gr, Item * *a) {
        unsigned int ASC0 = 48; // 0 en ASCII = 48 --> sera une chaine de caractère

        for (unsigned int l = 0; l < gr.ligne; ++l) {         //On met les cases adjacentes à 0
            for (unsigned int c = 0; c < gr.colonne; ++c) {
                if (a[l][c] == M) {
                    a[l][c] = M;
                    if (l >= 1 && l < gr.ligne && c >= 1 && c < gr.colonne) {
                        if (a[l - 1][c + 1] != M) {
                            a[l - 1][c + 1] = ASC0;
                        }
                        if (a[l - 1][c - 1] != M) {
                            a[l - 1][c - 1] = ASC0;
                        }
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] = ASC0;
                        }
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] = ASC0;
                        }
                        if (a[l][c + 1] != M) {
                            a[l][c + 1] = ASC0;
                        }
                        if (a[l + 1][c - 1] != M) {
                            a[l + 1][c - 1] = ASC0;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] = ASC0;
                        }
                        if (a[l + 1][c + 1] != M) {
                            a[l + 1][c + 1] = ASC0;
                        }
                    }

                    if (l == 0 && c == 0) {
                        if (a[l + 1][c + 1] != M) {
                            a[l + 1][c + 1] = ASC0;
                        }
                        if (a[l][c + 1] != M) {
                            a[l][c + 1] = ASC0;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] = ASC0;
                        }
                    }

                    if (l == 0 && c > 0 && c < gr.colonne) {
                        if (a[l + 1][c + 1] != M) {
                            a[l + 1][c + 1] = ASC0;
                        }
                        if (a[l][c + 1] != M) {
                            a[l][c + 1] = ASC0;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] = ASC0;
                        }
                        if (a[l + 1][c - 1] != M) {
                            a[l + 1][c - 1] = ASC0;
                        }
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] = ASC0;
                        }
                    }

                    if (l == 0 && c == gr.colonne) {
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] = ASC0;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] = ASC0;
                        }
                        if (a[l - 1][c + 1] != M) {
                            a[l][c + 1] = ASC0;
                        }
                    }

                    if (l > 0 && l < gr.ligne && c == 0) {
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] = ASC0;
                        }
                        if (a[l - 1][c + 1] != M) {
                            a[l - 1][c + 1] = ASC0;
                        }
                        if (a[l][c + 1] != M) {
                            a[l][c + 1] = ASC0;
                        }
                        if (a[l + 1][c + 1] != M) {
                            a[l + 1][c + 1] = ASC0;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] = ASC0;
                        }
                    }

                    if (l == gr.ligne && c == 0) {
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] = ASC0;
                        }
                        if (a[l - 1][c + 1] != M) {
                            a[l - 1][c + 1] = ASC0;
                        }
                        if (a[l][c + 1] != M) {
                            a[l][c + 1] = ASC0;
                        }
                    }

                    if (l == gr.ligne && c > 0 && c < gr.colonne) {
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] = ASC0;
                        }
                        if (a[l - 1][c - 1] != M) {
                            a[l - 1][c - 1] = ASC0;
                        }
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] = ASC0;
                        }
                        if (a[l - 1][c + 1] != M) {
                            a[l - 1][c + 1] = ASC0;
                        }
                        if (a[l + 1][c + 1] != M) {
                            a[l + 1][c + 1] = ASC0;
                        }
                    }

                    if (l == gr.ligne && c == gr.colonne) {
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] = ASC0;
                        }
                        if (a[l - 1][c - 1] != M) {
                            a[l - 1][c - 1] = ASC0;
                        }
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] = ASC0;
                        }
                    }

                    if (c == gr.colonne && l > 0 && l < gr.ligne) {
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] = ASC0;
                        }
                        if (a[l - 1][c - 1] != M) {
                            a[l - 1][c - 1] = ASC0;
                        }
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] = ASC0;
                        }
                        if (a[l + 1][c - 1] != M) {
                            a[l + 1][c - 1] = ASC0;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] = ASC0;
                        }
                    }
                }
            }
        }

        for (unsigned int l = 0; l < gr.ligne; ++l) {      //Incrémentation des cases qui ont une mine autour d'elle. On ajoute un + aux cases adjacentes.

            for (unsigned int c = 0; c < gr.colonne; ++c) {
                if (a[l][c] == M) {
                    a[l][c] = M;
                    if (l >= 1 && l < gr.ligne && c >= 1 && c < gr.colonne) {
                        if (a[l - 1][c + 1] != M) {
                            a[l - 1][c + 1] += 1;
                        }
                        if (a[l - 1][c - 1] != M) {
                            a[l - 1][c - 1] += 1;
                        }
                        if (a[l - 1][c] != M) {
                            a[l - 1][c] += 1;
                        }
                        if (a[l][c - 1] != M) {
                            a[l][c - 1] += 1;
                        }
                        if (a[l][c + 1] != M) {
                            a[l][c + 1] += 1;
                        }
                        if (a[l + 1][c - 1] != M) {
                            a[l + 1][c - 1] += 1;
                        }
                        if (a[l + 1][c] != M) {
                            a[l + 1][c] += 1;
                        }
                        if (a[l + 1][c + 1] != M)
                            a[l + 1][c + 1] += 1;

                    }
                }

                if (l == 0 && c == 0) {
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                }

                if (l == 0 && c > 0 && c < gr.colonne) {
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] += 1;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                }

                if (l == 0 && c == gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                }

                if (l > 0 && l < gr.ligne && c == 0) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                }

                if (l == gr.ligne && c == 0) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                }

                if (l == gr.ligne && c > 0 && c < gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                }

                if (l == gr.ligne && c == gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                }

                if (c == gr.colonne && l > 0 && l < gr.ligne) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                }

            }
        }
    }


    void AfficherGr(Grille& gr, Item** a) {

        cout << gr.ligne << " " << gr.colonne << endl;

        for (unsigned int i = 1; i <= gr.colonne; ++i) {
            cout << " ---";
        }
        cout << endl;

        for (unsigned int l = 0; l < gr.ligne; ++l) {
            for (unsigned int c = 0; c < gr.colonne; ++c) {
                cout << "| " << a[l][c] << " ";
            }
            cout << "|" << endl;
            for (unsigned int i = 1; i <= gr.colonne; ++i) {
                cout << " ---";
            }
            cout << endl;
        }
    }
    void gagner(Grille& gr) {

        unsigned int resultat = 0;

        if (gr.coup != (gr.ligne * gr.colonne) - gr.mine) {
            resultat = 0; //game not won
        }
        else {
            for (unsigned int i = 0; i < gr.mine; ++i) {
                for (unsigned int j = 0; j < gr.mine; ++j) {
                    if (gr.HCoup[i] == Demasquer && gr.pos_Coup[i] != gr.pos_Mine[j]) {
                        resultat = 1; //game won
                    }
                    else {
                        resultat = 0; //game not won
                    }
                }
            }
        }

        if (resultat == 1) {
            cout << "GAME WON" << endl;
        }
        else {
            cout << "GAME NOT WON" << endl;
        }
    }


    void perdu(Grille& gr) {

        unsigned int resultat = 0;

        for (unsigned int i = 0; i < gr.mine; i++) {
            if (gr.HCoup[gr.coup - 1] == Marquer && gr.pos_Coup[gr.coup - 1] != gr.pos_Mine[i]) {
                resultat = 0; //game lost
            }
            if (gr.HCoup[gr.coup - 1] == Demasquer && gr.pos_Coup[gr.coup - 1] == gr.pos_Mine[i]) {
                resultat = 0; //game lost
            }
            if (gr.HCoup[gr.coup - 1] == Demasquer && gr.pos_Coup[gr.coup - 1] != gr.pos_Mine[i]) {
                resultat = 1; //game not lost
            }
            if (gr.HCoup[gr.coup - 1] == Marquer && gr.pos_Coup[gr.coup - 1] == gr.pos_Mine[i]) {
                resultat = 1; //game not lost 
            }
        }

        if (resultat == 0) {
            cout << "GAME LOST" << endl;
        }
        else {
            cout << "GAME NOT LOST" << endl;
        }
    }
    

int main() {

    int cdo;
    unsigned int l , c, m;
    cin >> cdo;
    assert(cdo >= 1);
    assert(cdo <= 5);

    Grille grille;
    Item** g;
    cin >> l >> c >> m; //Entrez utilisateur

    if (cdo == 1) {
        InitPB(l, c, m);
    }

    else if (cdo == 2) {

        InitJ(grille, l, c, m);
        triM(grille);
        triH(grille);
        InitGr(&g, grille);
        PoseMine(grille, g);
        MarqueOuDemasque(grille, g);
        caseadj(grille, g);
        AfficherGr(grille, g);
        

    }

    else if (cdo == 3) {
        InitJ(grille, l, c, m);
        gagner(grille);

    }
    else if (cdo == 4) {
        InitJ(grille, l, c, m);
        perdu(grille);

    }
    else if (cdo == 5) {
        //Pas encore trouver

    }



}