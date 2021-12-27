#include "UNO.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
namespace MB
{
    UNO::UNO(GameDataRef data) : _data(data)
    {
        //ctor
    }
    bool UNO::fin_de_cartes()
    {
        if (vuno.size() == 0)
            return(true);
        else
            return(false);
    }
    carte& UNO::derniere_carte()
    {
        return(vjeter[vjeter.size() - 1]);
    }
    void UNO::nouvelle_partie()
    {
        carte c;
        if (vuno.size() != 0)
            vuno.clear();
        if (vjeter.size() != 0)
            vjeter.clear();
        string tcoul[4] = { "rouge","bleu","jaune","vert" };
        int icoul[4] = { ROUGE,BLEU,JAUNE,VERT };
        string tsym[4] = { "+2","block","inverse" };
        int isym[4] = { DEUX_PLUS,BLOQUE,INVERSE };
        for (int i = 0; i < 4; i++)
        {
            c = carte(_data, tcoul[i], 0, "0");
            c.modifier_figure(icoul[i], 9);
            vuno.push_back(c);
            for (int j = 1; j < 10; j++)
            {
                c = carte(_data, tcoul[i], j, to_string(j));
                c.modifier_figure(icoul[i], j - 1);
                vuno.push_back(c);
                vuno.push_back(c);
            }
            for (int k = 0; k < 3; k++)
            {
                c = carte(_data, tcoul[i], 20, tsym[k]);
                c.modifier_figure(icoul[i], isym[k]);
                vuno.push_back(c);
                vuno.push_back(c);
            }
        }
        for (int i = 0; i < 4; i++)
        {
            c = carte(_data, "noir", 50, "+4");
            c.modifier_figure(NOIR, QUATRE_PLUS);
            vuno.push_back(c);
            c = carte(_data, "noir", 50, "joker");
            c.modifier_figure(NOIR, MODIFIER_COULEUR);
            vuno.push_back(c);
        }
    }
    void UNO::nouvelle_tour()
    {
        carte c;
        c = vjeter[vjeter.size() - 1];
        vjeter.erase(vjeter.begin() + vjeter.size() - 1);
        vuno.swap(vjeter);
        for (int i = 0; i < vuno.size(); i++)
        {
            if ((vuno[i].donner_symbole() == "joker") || (vuno[i].donner_symbole() == "+4"))
                vuno[i].modifier_couleur("noir");
        }
        vjeter.push_back(c);
    }
    UNO::~UNO()
    {
        //dtor
    }
}
