//
// Created by Nathan ARMANET on 2019-02-25.
//

#include "Jeu.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

Jeu::Jeu() {
    this->g = new Grille;
    this->ia = new IA;
    this->tour = 1;
    this->J1 = "J1";
    this->J2 = "J2";

    Pion * p;
    bool tab[4];
    int k;
    std::string link;
    for (int i = 0; i < 16; i++) {
        k = i;
        link = "../images/";
        for (int j = 3; j >=0 ; --j) {
            if (k >= pow(2, j)) {
                tab[j] = true;
                k -= (int)pow(2, j);
                link += "1";
            } else {
                tab[j] = false;
                link += "0";
            }
        }
        link += ".png";
        p = new Pion(tab[3], tab[2], tab[1], tab[0], link);
        this->tabPion.push_back(*p);
    }
}

int Jeu::selectPion(int mousseX, int mousseY, std::vector<sf::RectangleShape> & og) {

    for (int i = 0; i < 16; ++i) {
        if ((20+155*(i%8) < mousseX)
            && (mousseX < (20+155*(i%8)+150))
            && ((700+155*(i/8)) < mousseY)
            && (mousseY < (700+155*(i/8)+150))
            && (og[i].getTexture() != nullptr)) {

            og[i].setOutlineColor(sf::Color::Red);

            return i;
        }
    }

    return -1;
}

void Jeu::selectCaseGrille(int mousseX, int mousseY, int & x, int & y) {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            if ((20+155*i < mousseX)
                && (mousseX < 150+20+155*i)
                && (20+155*j < mousseY)
                && (mousseY < 150+20+155*j)
                && (this->g->getCase(i, j).getPion() == nullptr)) {
                x = i;
                y = j;
                return;
            }
        }
    }
}

void Jeu::menu() {
    int largeur = 1350, hauteur = 1100;
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(largeur, hauteur), "Mode de Jeu | Quarto", sf::Style::Titlebar | sf::Style::Close);

    //Initialisation de la font
    sf::Font font_titre, font_mode;
    font_titre.loadFromFile("../fonts/PermanentMarker-regular.ttf");
    font_mode.loadFromFile("../fonts/Ubuntu-regular.ttf");

    //Création du texte
    sf::Text titre;
    titre.setFont(font_titre);
    titre.setString("Choix du mode de jeu");
    titre.setCharacterSize(100);
    titre.setPosition((largeur-titre.getLocalBounds().width)/2, 40);
    titre.setFillColor(sf::Color::Red);

    sf::Text pvp;
    pvp.setFont(font_mode);
    pvp.setString("Mode joueur contre joueur");
    pvp.setCharacterSize(75);
    pvp.setPosition((largeur-pvp.getLocalBounds().width)/2, 300);
    pvp.setFillColor(sf::Color::Blue);

    sf::Text ia1;
    ia1.setFont(font_mode);
    ia1.setString("Mode joueur contre IA (alpha-beta)");
    ia1.setCharacterSize(75);
    ia1.setPosition((largeur-ia1.getLocalBounds().width)/2, 500);
    ia1.setFillColor(sf::Color::Blue);

    sf::Event event;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (sf::Mouse::getPosition(window).x >= ((largeur-pvp.getLocalBounds().width)/2)
                            && sf::Mouse::getPosition(window).x <= ((largeur+pvp.getLocalBounds().width)/2)
                            && sf::Mouse::getPosition(window).y >= 300
                            && sf::Mouse::getPosition(window).y <= 375) {
                            /*
                             * Cas ou on choisit le mode 2 joueurs
                             */
                            window.close();
                            this->pvp();
                        }else if (sf::Mouse::getPosition(window).x >= ((largeur-ia1.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).x <= ((largeur+ia1.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).y >= 500
                                  && sf::Mouse::getPosition(window).y <= 575) {
                            /*
                             * cas joueur vs IA (Alpha-beta)
                             */
                            std::cout<<"IA alpha beta"<<std::endl;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // effacement de la fenêtre en blanc
        window.clear(sf::Color::White);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        window.draw(titre);
        window.draw(pvp);
        window.draw(ia1);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }
}

void Jeu::resultat(std::string gagnant) {
    unsigned int largeur = 1350, hauteur = 700;
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(largeur, hauteur), "Resultat | Quarto", sf::Style::Titlebar | sf::Style::Close);

    //Initialisation de la font
    sf::Font font_titre, font_mode;
    font_titre.loadFromFile("../fonts/PermanentMarker-regular.ttf");
    font_mode.loadFromFile("../fonts/Ubuntu-regular.ttf");

    //Création du texte
    sf::Text titre;
    titre.setFont(font_titre);
    if (gagnant == "match nul") {
        titre.setString("Match nul !");
    }else {
        titre.setString("Le gagnant de cette\npartie est :\n"+gagnant);
    }
    titre.setCharacterSize(100);
    titre.setPosition(40, 40);
    titre.setFillColor(sf::Color::Red);

    sf::Text retour;
    retour.setFont(font_mode);
    retour.setString("Retour aux modes de jeu");
    retour.setCharacterSize(75);
    retour.setPosition((largeur-retour.getLocalBounds().width)/2, 500);
    retour.setFillColor(sf::Color::Blue);

    sf::Text quitter;
    quitter.setFont(font_mode);
    quitter.setString("Quitter");
    quitter.setCharacterSize(75);
    quitter.setPosition((largeur-quitter.getLocalBounds().width)/2, 600);
    quitter.setFillColor(sf::Color::Blue);

    sf::Event event;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (sf::Mouse::getPosition(window).x >= ((largeur-retour.getLocalBounds().width)/2)
                            && sf::Mouse::getPosition(window).x <= ((largeur+retour.getLocalBounds().width)/2)
                            && sf::Mouse::getPosition(window).y >= retour.getPosition().y
                            && sf::Mouse::getPosition(window).y <= retour.getPosition().y+retour.getCharacterSize()) {

                            window.close();
                            this->menu();
                        }else if (sf::Mouse::getPosition(window).x >= ((largeur-quitter.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).x <= ((largeur+quitter.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).y >= quitter.getPosition().y
                                  && sf::Mouse::getPosition(window).y <= quitter.getPosition().y+quitter.getCharacterSize()) {

                            window.close();
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // effacement de la fenêtre en blanc
        window.clear(sf::Color::White);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        window.draw(titre);
        window.draw(retour);
        window.draw(quitter);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }
}

void Jeu::pvp() {
    std::string infoTourJ1, infoTourJ2;

    infoTourJ1 = J2+" choisit le pion et \n"+J1+" le place.";
    infoTourJ2 = J1+" choisit le pion et \n"+J2+" le place.";

    int ind_pion = -1, ind_x = -1, ind_y = -1;

    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1350, 1100), "Quarto", sf::Style::Titlebar | sf::Style::Close);

    // création texte explicatif
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../fonts/Ubuntu-Regular.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(50);
    text.setString(infoTourJ1);
    text.setPosition(700, 20);

    std::vector<sf::RectangleShape> grille;

    for (int i = 0; i < 16; ++i) {
        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%4), 20+155*(i/4));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Black);
        rect.setTexture(nullptr);
        grille.push_back(rect);
    }

    std::vector<sf::RectangleShape> openGrille;

    sf::Texture * texture;
    for (int i = 0; i < 16; ++i) {
        texture = new sf::Texture;

        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%8), 700+155*(i/8));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Transparent);

        texture->loadFromFile(this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400));

        texture->setSmooth(true);

        rect.setTexture(texture);

        openGrille.push_back(rect);
    }

    sf::Event event;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        std::string joueur;
        if (g->win(joueur)) {
            window.close();
            this->resultat(joueur);
        } else if (tour == 17) {
            window.close();
            this->resultat("match nul");
        }

        if (tour%2 == 1) {
            text.setString(infoTourJ1);
        }else {
            text.setString(infoTourJ2);
        }
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            switch (event.type) {
                case sf::Event::Closed: window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ind_pion == -1) {
                        ind_pion = this->selectPion(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, openGrille);
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        this->selectCaseGrille(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, ind_x, ind_y);

                        if (ind_pion != -1 && ind_y != -1) {
                            this->g->setCase(static_cast<unsigned int>(ind_x), static_cast<unsigned int>(ind_y), & this->tabPion[ind_pion]);
                            grille[ind_y*4+ind_x].setTexture(openGrille[ind_pion].getTexture());
                            openGrille[ind_pion].setTexture(nullptr);
                            openGrille[ind_pion].setOutlineColor(sf::Color::Transparent);

                            ind_pion = -1;
                            ind_x = -1;
                            ind_y = -1;
                            tour++;
                        }


                        //gestion des conditions de victoire (affichage console uniquement)
                        bool win = this->g->win(J1);
                        if(win) {
                            std::cout<<"--- J1/J2 Gagne ---"<<std::endl;
                            std::cout<<J1<<std::endl;
                            // on ferme si c'est gagné (juste du test)
                            //window.close();
                        } else if (this->g->full()) {
                            std::cout<<"pas de victoire"<<std::endl;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // effacement de la fenêtre en blanc
        window.clear(sf::Color::White);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        window.draw(text);

        for (sf::RectangleShape  & child : grille) {
            window.draw(child);
        }

        for (sf::RectangleShape & child : openGrille) {
            window.draw(child);
        }

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

}

void Jeu::IA_alpha_beta() {
    std::string infoTourJ1, infoTourIA;

    infoTourJ1 = "L'IA choisit le pion et \n"+J1+" le place.";
    infoTourIA = J1+" choisit le pion et \n L'IA le place.";

    int ind_pion = -1, ind_x = -1, ind_y = -1;

    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1350, 1100), "Quarto", sf::Style::Titlebar | sf::Style::Close);

    // création texte explicatif
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../fonts/Ubuntu-Regular.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(50);
    text.setString(infoTourJ1);
    text.setPosition(700, 20);

    std::vector<sf::RectangleShape> grille;

    for (int i = 0; i < 16; ++i) {
        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%4), 20+155*(i/4));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Black);
        rect.setTexture(nullptr);
        grille.push_back(rect);
    }

    std::vector<sf::RectangleShape> openGrille;

    sf::Texture * texture;
    for (int i = 0; i < 16; ++i) {
        texture = new sf::Texture;

        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%8), 700+155*(i/8));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Transparent);

        texture->loadFromFile(this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400));

        texture->setSmooth(true);

        rect.setTexture(texture);

        openGrille.push_back(rect);
    }

    sf::Event event;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        if (tour%2 == 1) {
            text.setString(infoTourJ1);
        }else {
            text.setString(infoTourIA);
        }
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            switch (event.type) {
                case sf::Event::Closed: window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ind_pion == -1) {
                        ind_pion = this->selectPion(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, openGrille);
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        this->selectCaseGrille(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, ind_x, ind_y);

                        if (ind_pion != -1 && ind_y != -1) {
                            this->g->setCase(static_cast<unsigned int>(ind_x), static_cast<unsigned int>(ind_y), & this->tabPion[ind_pion]);
                            grille[ind_y*4+ind_x].setTexture(openGrille[ind_pion].getTexture());
                            openGrille[ind_pion].setTexture(nullptr);
                            openGrille[ind_pion].setOutlineColor(sf::Color::Transparent);

                            ind_pion = -1;
                            ind_x = -1;
                            ind_y = -1;
                            tour++;
                        }


                        //gestion des conditions de victoire (affichage console uniquement)
                        bool win = this->g->win(J1);
                        if(win) {
                            std::cout<<"--- J1/J2 Gagne ---"<<std::endl;
                            std::cout<<J1<<std::endl;
                            // on ferme si c'est gagné (juste du test)
                            //window.close();
                        } else if (this->g->full()) {
                            std::cout<<"pas de victoire"<<std::endl;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // effacement de la fenêtre en blanc
        window.clear(sf::Color::White);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        window.draw(text);

        for (sf::RectangleShape  & child : grille) {
            window.draw(child);
        }

        for (sf::RectangleShape & child : openGrille) {
            window.draw(child);
        }

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }
}
