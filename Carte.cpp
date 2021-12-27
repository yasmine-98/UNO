#include "carte.h"
namespace MB
{
    carte::carte()
    {

    }
    carte::carte(GameDataRef data, string coul, int val, string sym) :_data(data)
    {
        couleur = coul;
        valeur = val;
        symbole = sym;
    }
    void carte::modifier_figure(int coul, int sym)
    {
        figure.setTexture(_data->assets.GetTexture("UNO Cartes"));
        if (coul == ROUGE)
        {
            if (sym == BLOQUE)
                figure.setTextureRect(sf::IntRect(0, 4 * 78, 50, 78));
            else if (sym == INVERSE)
                figure.setTextureRect(sf::IntRect(50, 4 * 78, 50, 78));
            else if (sym == DEUX_PLUS)
                figure.setTextureRect(sf::IntRect(100, 4 * 78, 50, 78));
            else
                figure.setTextureRect(sf::IntRect(sym * 50, coul * 78, 50, 78));
        }
        else if (coul == JAUNE)
        {
            if (sym == BLOQUE)
                figure.setTextureRect(sf::IntRect(150, 4 * 78, 50, 78));
            else if (sym == INVERSE)
                figure.setTextureRect(sf::IntRect(200, 4 * 78, 50, 78));
            else if (sym == DEUX_PLUS)
                figure.setTextureRect(sf::IntRect(250, 4 * 78, 50, 78));
            else
                figure.setTextureRect(sf::IntRect(sym * 50, coul * 78, 50, 78));
        }
        else if (coul == VERT)
        {
            if (sym == BLOQUE)
                figure.setTextureRect(sf::IntRect(300, 4 * 78, 50, 78));
            else if (sym == INVERSE)
                figure.setTextureRect(sf::IntRect(350, 4 * 78, 50, 78));
            else if (sym == DEUX_PLUS)
                figure.setTextureRect(sf::IntRect(400, 4 * 78, 50, 78));
            else
                figure.setTextureRect(sf::IntRect(sym * 50, coul * 78, 50, 78));
        }
        else if (coul == BLEU)
        {
            if (sym == BLOQUE)
                figure.setTextureRect(sf::IntRect(450, 4 * 78, 50, 78));
            else if (sym == INVERSE)
                figure.setTextureRect(sf::IntRect(0, 5 * 78, 50, 78));
            else if (sym == DEUX_PLUS)
                figure.setTextureRect(sf::IntRect(50, 5 * 78, 50, 78));
            else
                figure.setTextureRect(sf::IntRect(sym * 50, coul * 78, 50, 78));
        }
        else if (coul == NOIR)
        {
            if (sym == MODIFIER_COULEUR)
                figure.setTextureRect(sf::IntRect(100, 5 * 78, 50, 78));
            else
                figure.setTextureRect(sf::IntRect(200, 5 * 78, 50, 78));
        }
    }
    sf::Sprite& carte::donner_figure()
    {
        return(figure);
    }
    int carte::donner_valeur()
    {
        return(valeur);
    }
    string carte::donner_couleur()
    {
        return(couleur);
    }
    string carte::donner_symbole()
    {
        return(symbole);
    }
    void carte::modifier_couleur(string coul)
    {
        couleur = coul;
    }
    carte::~carte()
    {
        //dtor
    }
}
