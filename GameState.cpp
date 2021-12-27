#include <sstream>
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Definitions.h"
#include <iostream>
using namespace std;
namespace MB
{
    GameState::GameState(GameDataRef data) : _data(data)
    {
        u = new UNO(data);
        j1 = new joueur(data);
        j2 = new joueur(data);
        changement_de_couleur.setTexture(_data->assets.GetTexture("Couleur De Couleur"));
        verif_uno.setTexture(_data->assets.GetTexture("UNO Button"));
        verif_uno.setPosition(700, 500);
        changement_de_couleur.setPosition(280.5, 175);
        u->nouvelle_partie();
        j1->distribuer(*u, *j2);
        if (u->derniere_carte().donner_symbole() == "joker")
        {
            u->derniere_carte().modifier_couleur(coul);
            coul = "noir";
        }
        else if (u->derniere_carte().donner_symbole() == "+4")
        {
            u->derniere_carte().modifier_couleur(coul);
            coul = "noir";
            j2->piocher(*u, 4);
        }
        else if (u->derniere_carte().donner_symbole() == "+2")
            j2->piocher(*u, 2);
    }
    void GameState::init()
    {
        _background.setTexture(_data->assets.GetTexture("Game Background"));
    }
    void GameState::HandleInput()
    {
        sf::Event e;
        while (_data->window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _data->window.close();
            }
            else if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousepos = _data->input.MousePosition(_data->window);
                    if (u->derniere_carte().donner_couleur() == "noir")
                    {
                        if ((mousepos.x > 280.5) && (mousepos.x < 400) && (mousepos.y > 175) && (mousepos.y < 300))
                            coul = "jaune";
                        else if ((mousepos.x > 400) && (mousepos.x < 519.5) && (mousepos.y > 175) && (mousepos.y < 300))
                            coul = "bleu";
                        else if ((mousepos.x > 280.5) && (mousepos.x < 400) && (mousepos.y > 300) && (mousepos.y < 425))
                            coul = "rouge";
                        else if ((mousepos.x > 400) && (mousepos.x < 519.5) && (mousepos.y > 300) && (mousepos.y < 425))
                            coul = "vert";
                    }
                    else if ((mousepos.x > 225) && (mousepos.x < 575) && (mousepos.y < 578) && (mousepos.y > 500))
                    {
                        jeter = true;
                        int i = 1;
                        float dx = (6.0 / (j1->nbr_de_cartes() - 1)) * 50;
                        float x = 225;
                        while (i <= j1->nbr_de_cartes())
                        {
                            if ((mousepos.x - x > 0) && (mousepos.x - x < dx) && (mousepos.y < 578) && (mousepos.y > 500))
                                pos = i;
                            i++;
                            if (i == j1->nbr_de_cartes())
                                x = x + 50;
                            else
                                x = x + dx;
                        }
                    }
                    else if ((mousepos.x > 700) && (mousepos.x < 750) && (mousepos.y < 329) && (mousepos.y > 251))
                    {
                        piocher = true;
                    }
                    else if ((mousepos.x > 700) && (mousepos.x < 800) && (mousepos.y < 600) && (mousepos.y > 500))
                    {
                        if (j1->nbr_de_cartes())
                            uno = true;
                    }
                }

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                _data->machine.AddState(StateRef(new PauseState(_data)), false);
            }
        }
    }
    void GameState::Update(float dt)
    {
        sf::Vector2i p = _data->input.MousePosition(_data->window);
        int i = 1;
        float dx = (6.0 / (j1->nbr_de_cartes() - 1)) * 50;
        float x = 225;
        while (i <= j1->nbr_de_cartes())
        {
            if ((p.x - x > 0) && (p.x - x < dx) && (p.y < 578) && (p.y > 500))
                break;
            i++;
            if (i == j1->nbr_de_cartes())
                x = x + 50;
            else
                x = x + dx;
        }
        pcarte = i - 1;
        if (animation == false)
        {
            if ((j1->nbr_de_cartes() != 0) && (j2->nbr_de_cartes() != 0))
            {
                int n;
                string ch;
                vector<carte> v1, v2;
                if (((t1 == true) || (t == true) || (bloquee == true)) && (u->derniere_carte().donner_couleur() != "noir"))
                {
                    if (((u->derniere_carte().donner_symbole() != "+4") && (u->derniere_carte().donner_symbole() != "+2") && (u->derniere_carte().donner_symbole() != "inverse") && (u->derniere_carte().donner_symbole() != "block")) || (debut == false))
                    {
                        bloquee = false;
                        if ((((j1->bloque(*u) == false) && (t == true)) || ((j1->bloque(*u) == true) && (t == false)) || ((j1->bloque(*u) == false) && (t == false))) && (j1->nbr_de_cartes() != 0))
                        {
                            t2 = j2->joueur_automatique(*u, *j1);
                            if (t2 == true)
                            {
                                bloquee = j2->bloque(*u);
                            }
                            animation = true;
                            clock.restart();
                            if (u->fin_de_cartes() == true)
                                u->nouvelle_tour();
                        }
                    }
                }
                debut = false;
                if (u->derniere_carte().donner_couleur() != "noir")
                {
                    t = false;
                    t1 = false;
                }
                if ((debut == false) && (bloquee == false))
                {
                    if (((j2->bloque(*u) == false) && (t2 == true)) || ((j2->bloque(*u) == true) && (t2 == false)) || ((j2->bloque(*u) == false) && (t2 == false)))
                    {
                        {
                            if (jeter == true)
                            {
                                t = j1->jeter(*u, pos, *j2);
                                animation = true;
                                clock.restart();
                                jeter = false;
                            }
                            else if (piocher == true)
                            {
                                v2 = j1->piocher(*u, 1);
                                t1 = true;
                                t = j1->jeter(*u, j1->nbr_de_cartes(), *j2);
                                pos = j1->nbr_de_cartes();
                                animation = true;
                                clock.restart();
                                piocher = false;
                            }
                        }
                        if ((j1->nbr_de_cartes() == 1) && (t == true))
                        {
                            uno = false;
                            clockuno.restart();
                        }
                        if (u->fin_de_cartes() == true)
                            u->nouvelle_tour();
                    }
                }
                t2 = false;
            }
        }
        else if ((j1->nbr_de_cartes() != 0) && (j2->nbr_de_cartes() != 0))
        {
            if (clock.getElapsedTime().asSeconds() > 0.75)
            {
                animation = false;
            }
        }
        else
            _data->machine.AddState(StateRef(new GameOverState(_data, *j1, *j2)));
        if (j1->nbr_de_cartes() == 1)
            if ((clockuno.getElapsedTime().asSeconds() > 3.0) && (uno == false))
            {
                j1->piocher(*u, 2);
            }
    }
    void GameState::Draw(float dt)
    {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(verif_uno);
        j1->draw(*u, *j2, pcarte);
        if (((u->derniere_carte().donner_symbole() == "joker") && (u->derniere_carte().donner_couleur() == "noir")) || (((u->derniere_carte().donner_symbole() == "+4")) && (u->derniere_carte().donner_couleur() == "noir")))
        {
            sf::Text text;
            sf::Font font;
            font.loadFromFile("rsc/arial.ttf");
            text.setFont(font);
            text.setFillColor(sf::Color::White);
            text.setString("Selectionnez un couleur");
            text.setCharacterSize(50);
            text.setPosition(130, 115);
            _data->window.draw(text);
            _data->window.draw(changement_de_couleur);
            u->derniere_carte().modifier_couleur(coul);
            coul = "noir";
        }
        if (u->derniere_carte().donner_symbole() == "joker")
        {
            if (u->derniere_carte().donner_couleur() == "vert")
            {
                vert.setTexture(_data->assets.GetTexture("Carte Vert"));
                vert.setPosition(375, 251);
                _data->window.draw(vert);
            }
            else if (u->derniere_carte().donner_couleur() == "jaune")
            {
                jaune.setTexture(_data->assets.GetTexture("Carte Jaune"));
                jaune.setPosition(375, 251);
                _data->window.draw(jaune);
            }
            else if (u->derniere_carte().donner_couleur() == "bleu")
            {
                bleu.setTexture(_data->assets.GetTexture("Carte Bleu"));
                bleu.setPosition(375, 251);
                _data->window.draw(bleu);
            }
            else if (u->derniere_carte().donner_couleur() == "rouge")
            {
                rouge.setTexture(_data->assets.GetTexture("Carte Rouge"));
                rouge.setPosition(375, 251);
                _data->window.draw(rouge);
            }
        }
        if (u->derniere_carte().donner_symbole() == "+4")
        {
            if (u->derniere_carte().donner_couleur() == "vert")
            {
                vert.setTexture(_data->assets.GetTexture("Carte +4Vert"));
                vert.setPosition(375, 251);
                _data->window.draw(vert);
            }
            else if (u->derniere_carte().donner_couleur() == "jaune")
            {
                jaune.setTexture(_data->assets.GetTexture("Carte +4Jaune"));
                jaune.setPosition(375, 251);
                _data->window.draw(jaune);
            }
            else if (u->derniere_carte().donner_couleur() == "bleu")
            {
                bleu.setTexture(_data->assets.GetTexture("Carte +4Bleu"));
                bleu.setPosition(375, 251);
                _data->window.draw(bleu);
            }
            else if (u->derniere_carte().donner_couleur() == "rouge")
            {
                rouge.setTexture(_data->assets.GetTexture("Carte +4Rouge"));
                rouge.setPosition(375, 251);
                _data->window.draw(rouge);
            }
        }
        _data->window.display();
    }
}