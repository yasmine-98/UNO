#pragma once
#include <string>
#include <iostream>
using namespace std;
#include "Game.h"
#include "Definitions.h"
namespace MB
{
    class carte
    {
    public:
        carte();
        carte(GameDataRef data, string coul, int val, string sym);
        virtual ~carte();
        int donner_valeur();
        string donner_couleur();
        string donner_symbole();
        void modifier_couleur(string coul);
        void modifier_figure(int coul, int sym);
        sf::Sprite& donner_figure();
    protected:
        string couleur;
        string symbole;
        int valeur;
        sf::Sprite figure;
        GameDataRef _data;
        sf::Clock clock;
    };
}