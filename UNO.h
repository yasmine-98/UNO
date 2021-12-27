#pragma once
#include <vector>
#include "carte.h"
namespace MB
{
    class UNO
    {
    public:
        UNO(GameDataRef data);
        virtual ~UNO();
        void nouvelle_tour();
        void nouvelle_partie();
        carte& derniere_carte();
        bool fin_de_cartes();
        friend class joueur;
    protected:
        vector<carte> vjeter;
        vector<carte> vuno;
        GameDataRef _data;
    };
}