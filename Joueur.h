#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;
#include "carte.h"
#include "UNO.h"
namespace MB
{
    class joueur
    {
    public:
        joueur(GameDataRef data);
        virtual ~joueur();
        vector<carte> piocher(UNO& u, int nbr);
        bool jeter(UNO& u, int indice, joueur& j);
        int calcule_score();
        int nbr_de_cartes();
        bool joueur_automatique(UNO& u, joueur& j);
        carte distribuer(UNO& u, joueur& j);
        bool bloque(UNO u);
        void draw(UNO u, joueur j, int pcarte);
        carte& return_carte(int pos);
        vector<int> chercher_couleur(string coul);
        vector<int> chercher_symbole(string sym);
    protected:
        int score;
        vector<carte> v;
        GameDataRef _data;
        sf::Sprite changement_de_couleur;
    };
}