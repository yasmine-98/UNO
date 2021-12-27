#include "joueur.h"
#include "UNO.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
namespace MB
{
    joueur::joueur(GameDataRef data) : _data(data)
    {
        score = 0;
    }
    carte& joueur::return_carte(int pos)
    {
        return(v[pos]);
    }
    void joueur::draw(UNO u, joueur j, int pcarte)
    {
        sf::Sprite carte;
        carte.setTexture(_data->assets.GetTexture("Carte Cachee"));
        float dx = 6.0 / (j.v.size() - 1);
        double x = 225;
        for (int i = 0; i < j.v.size(); i++)
        {
            carte.setPosition(x, 50);
            _data->window.draw(carte);
            x = x + dx * 50;
        }
        carte.setPosition(700, 250);
        _data->window.draw(carte);
        carte = u.vjeter[u.vjeter.size() - 1].donner_figure();
        carte.setPosition(375, 250);
        _data->window.draw(carte);
        dx = 6.0 / (v.size() - 1);
        x = 225;
        for (int i = 0; i < v.size(); i++)
        {
            if (i == pcarte)
            {
                v[i].donner_figure().setPosition(x, 470);
            }
            else
                v[i].donner_figure().setPosition(x, 500);
            _data->window.draw(v[i].donner_figure());
            x = x + dx * 50;
        }
    }
    bool joueur::bloque(UNO u)
    {
        if ((u.derniere_carte().donner_symbole() == "+4") || (u.derniere_carte().donner_symbole() == "+2") || (u.derniere_carte().donner_symbole() == "inverse") || (u.derniere_carte().donner_symbole() == "block"))
            return(true);
        else
            return(false);
    }
    int joueur::nbr_de_cartes()
    {
        return(v.size());
    }
    carte joueur::distribuer(UNO& u, joueur& j)
    {
        int r;
        carte c;
        if (v.size() != 0)
            v.clear();
        if (j.v.size() != 0)
            j.v.clear();
        j.piocher(u, 7);
        piocher(u, 7);
        srand(time(0));
        r = rand() % (u.vuno.size());
        u.vjeter.push_back(u.vuno[r]);
        c = u.vuno[r];
        u.vuno.erase(u.vuno.begin() + r);
        return c;
    }
    vector<carte> joueur::piocher(UNO& u, int nbr)
    {
        int r;
        vector<carte> vect;
        for (int i = 0; i < nbr; i++)
        {
            srand(time(0));
            r = rand() % (u.vuno.size());
            v.push_back(u.vuno[r]);
            vect.push_back(u.vuno[r]);
            u.vuno.erase(u.vuno.begin() + r);
        }
        return vect;
    }
    vector<int> joueur::chercher_couleur(string coul)
    {
        vector<int> vect;
        for (int i = 0; i < v.size(); i++)
            if (v[i].donner_couleur() == coul)
                vect.push_back(i + 1);
        return vect;
    }
    vector<int> joueur::chercher_symbole(string sym)
    {
        vector<int> vect;
        for (int i = 0; i < v.size(); i++)
            if (v[i].donner_symbole() == sym)
                vect.push_back(i + 1);
        return vect;
    }
    bool joueur::jeter(UNO& u, int indice, joueur& j)
    {
        bool test = false;
        int n = u.vjeter.size();
        if (v[indice - 1].donner_symbole() == "joker")
        {
            u.vjeter.push_back(v[indice - 1]);
            v.erase(v.begin() + indice - 1);
            test = true;
        }
        else if (v[indice - 1].donner_symbole() == "+4")
        {
            if (((chercher_couleur(u.vjeter[n - 1].donner_couleur()).size() == 0) && (chercher_symbole(u.vjeter[n - 1].donner_symbole()).size() == 0) && (chercher_symbole("joker").size() == 0)) || ((u.vjeter[n - 1].donner_symbole() == "+4") && (chercher_couleur(u.vjeter[n - 1].donner_couleur()).size() == 0) && (chercher_symbole("joker").size() == 0)))
            {
                u.vjeter.push_back(v[indice - 1]);
                v.erase(v.begin() + indice - 1);
                j.piocher(u, 4);
                test = true;
            }
        }
        else if ((u.vjeter[n - 1].donner_couleur() == v[indice - 1].donner_couleur()) || (u.vjeter[n - 1].donner_symbole() == v[indice - 1].donner_symbole()))
        {
            u.vjeter.push_back(v[indice - 1]);
            v.erase(v.begin() + indice - 1);
            test = true;
        }
        if ((u.vjeter[u.vjeter.size() - 1].donner_symbole() == "+2") && (test == true))
            j.piocher(u, 2);
        return test;
    }
    int joueur::calcule_score()
    {
        for (int i = 0; i < v.size(); i++)
            score = score + v[i].donner_valeur();
        return score;
    }
    bool joueur::joueur_automatique(UNO& u, joueur& j)
    {
        vector<int> vcoul = chercher_couleur(u.vjeter[u.vjeter.size() - 1].donner_couleur());
        vector<int> vsym = chercher_symbole(u.vjeter[u.vjeter.size() - 1].donner_symbole());
        bool test = false;
        int n = u.vjeter.size();
        if (vcoul.size() != 0)
            jeter(u, vcoul[rand() % (vcoul.size())], j);
        else if (vsym.size() != 0)
            jeter(u, vsym[rand() % (vsym.size())], j);
        else if (chercher_symbole("joker").size() != 0)
        {
            int indice = chercher_symbole("joker")[0];
            u.vjeter.push_back(v[indice - 1]);
            v.erase(v.begin() + indice - 1);
        }
        else if (chercher_symbole("+4").size() != 0)
        {
            int indice = chercher_symbole("+4")[0];
            u.vjeter.push_back(v[indice - 1]);
            v.erase(v.begin() + indice - 1);
        }
        else
        {
            piocher(u, 1);
            if ((v[v.size() - 1].donner_couleur() == u.vjeter[u.vjeter.size() - 1].donner_couleur()) || (v[v.size() - 1].donner_symbole() == u.vjeter[u.vjeter.size() - 1].donner_symbole()) || (v[v.size() - 1].donner_couleur() == "noir"))
            {
                u.vjeter.push_back(v[v.size() - 1]);
                v.erase(v.begin() + v.size() - 1);
                if (u.vjeter[u.vjeter.size() - 1].donner_symbole() == "+2")
                    j.piocher(u, 2);
            }
        }
        if (u.vjeter.size() == n + 1)
        {
            test = true;
            if ((u.vjeter[u.vjeter.size() - 1].donner_symbole() == "joker") || (u.vjeter[u.vjeter.size() - 1].donner_symbole() == "+4"))
            {
                int a = chercher_couleur("rouge").size();
                int b = chercher_couleur("bleu").size();
                int c = chercher_couleur("jaune").size();
                int d = chercher_couleur("vert").size();
                int liste[] = { a,b,c,d };
                if (*(max_element(liste, liste + 4)) == a)
                    u.vjeter[u.vjeter.size() - 1].modifier_couleur("rouge");
                if (*(max_element(liste, liste + 4)) == b)
                    u.vjeter[u.vjeter.size() - 1].modifier_couleur("bleu");
                if (*(max_element(liste, liste + 4)) == c)
                    u.vjeter[u.vjeter.size() - 1].modifier_couleur("jaune");
                if (*(max_element(liste, liste + 4)) == d)
                    u.vjeter[u.vjeter.size() - 1].modifier_couleur("vert");
            }
            if (u.vjeter[u.vjeter.size() - 1].donner_symbole() == "+4")
                j.piocher(u, 4);
        }
        return(test);
    }
    joueur::~joueur()
    {
        //dtor
    }
}
