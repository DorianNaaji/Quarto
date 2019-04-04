//
// Created by Nathan ARMANET on 2019-02-25.
//

#include "Jeu.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "IA.h"

Jeu::Jeu() = default;

void Jeu::init() {
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
        link = "";
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
    unsigned int largeur = 1350, hauteur = 800;
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(largeur, hauteur), "Mode de Jeu | Quarto", sf::Style::Titlebar | sf::Style::Close);

    //Initialisation de la font
    sf::Font font_titre, font_mode;
    if (!font_titre.loadFromFile("./fonts/PermanentMarker-regular.ttf"))
        font_titre.loadFromFile("../fonts/PermanentMarker-regular.ttf");
    if (!font_mode.loadFromFile("./fonts/Ubuntu-regular.ttf"))
        font_mode.loadFromFile("../fonts/Ubuntu-regular.ttf");

    //Création du texte
    sf::Text name;
    name.setFont(font_titre);
    name.setString("PolyQuarto");
    name.setCharacterSize(150);
    name.setPosition((largeur-name.getLocalBounds().width)/2, 10);
    name.setFillColor(sf::Color(0, 204, 102));

    sf::Text titre;
    titre.setFont(font_titre);
    titre.setString("Choix du mode de jeu");
    titre.setCharacterSize(100);
    titre.setPosition((largeur-titre.getLocalBounds().width)/2, 200);
    titre.setFillColor(sf::Color::Red);


    sf::Text pvp;
    pvp.setFont(font_mode);
    pvp.setString("Mode joueur contre joueur");
    pvp.setCharacterSize(75);
    pvp.setPosition((largeur-pvp.getLocalBounds().width)/2, 400);
    pvp.setFillColor(sf::Color::White);

    sf::Text ia1;
    ia1.setFont(font_mode);
    ia1.setString("Mode joueur contre IA (alpha-beta)");
    ia1.setCharacterSize(75);
    ia1.setPosition((largeur-ia1.getLocalBounds().width)/2, 510);
    ia1.setFillColor(sf::Color::White);

    sf::Text quit;
    quit.setFont(font_titre);
    quit.setString("Quitter");
    quit.setCharacterSize(75);
    quit.setPosition((largeur-quit.getLocalBounds().width)/2, 710);
    quit.setFillColor(sf::Color::Red);

    sf::Event event{};

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
                        /*
                         * Fermeture fenètre
                         */



                        if (sf::Mouse::getPosition(window).x >= ((largeur-pvp.getLocalBounds().width)/2)
                            && sf::Mouse::getPosition(window).x <= ((largeur+pvp.getLocalBounds().width)/2)
                            && sf::Mouse::getPosition(window).y >= pvp.getPosition().y
                            && sf::Mouse::getPosition(window).y <= pvp.getPosition().y+pvp.getCharacterSize()) {
                            /*
                             * Cas ou on choisit le mode 2 joueurs
                             */
                            window.close();
                            this->init();
                            this->pvp();
                        }else if (sf::Mouse::getPosition(window).x >= ((largeur-ia1.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).x <= ((largeur+ia1.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).y >= ia1.getPosition().y
                                  && sf::Mouse::getPosition(window).y <= ia1.getPosition().y+ia1.getCharacterSize()) {
                            /*
                             * cas joueur vs IA (Alpha-beta)
                             */
                            window.close();
                            this->init();
                            this->IA_alpha_beta();
                        }else if (sf::Mouse::getPosition(window).x >= ((largeur-quit.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).x <= ((largeur+quit.getLocalBounds().width)/2)
                                  && sf::Mouse::getPosition(window).y >= quit.getPosition().y
                                  && sf::Mouse::getPosition(window).y <= quit.getPosition().y+quit.getCharacterSize()) {
                            /*
                             * quitter
                             */
                            window.close();
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // effacement de la fenêtre en blanc
        window.clear(sf::Color(100, 100, 120));

        // c'est ici qu'on dessine tout
        // window.draw(...);

        window.draw(name);
        window.draw(titre);
        window.draw(pvp);
        window.draw(ia1);
        window.draw(quit);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }
}

void Jeu::resultat(const std::string & message) {
    unsigned int largeur = 1350, hauteur = 600;
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(largeur, hauteur), "Resultat | Quarto", sf::Style::Titlebar | sf::Style::Close);

    //Initialisation de la font
    sf::Font font_titre, font_mode;
    if (!font_titre.loadFromFile("./fonts/PermanentMarker-regular.ttf"))
        font_titre.loadFromFile("../fonts/PermanentMarker-regular.ttf");
    if (!font_mode.loadFromFile("./fonts/Ubuntu-regular.ttf"))
        font_mode.loadFromFile("../fonts/Ubuntu-regular.ttf");

    //Création du texte
    sf::Text titre;
    titre.setFont(font_titre);
    if (message == "match nul") {
        titre.setString("Match nul !");
    }else {
        titre.setString("Le gagnant de cette\npartie est : "+message);
    }
    titre.setCharacterSize(100);
    titre.setPosition(40, 40);
    titre.setFillColor(sf::Color::Red);

    sf::Text retour;
    retour.setFont(font_mode);
    retour.setString("Retour aux modes de jeu ");
    retour.setCharacterSize(75);
    retour.setPosition(largeur-retour.getLocalBounds().width, 400);
    retour.setFillColor(sf::Color::White);

    sf::Text quitter;
    quitter.setFont(font_mode);
    quitter.setString("Quitter ");
    quitter.setCharacterSize(75);
    quitter.setPosition(largeur-quitter.getLocalBounds().width, 500);
    quitter.setFillColor(sf::Color::White);

    sf::Event event{};

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
                        if (sf::Mouse::getPosition(window).x >= (largeur-retour.getLocalBounds().width)
                            && sf::Mouse::getPosition(window).x <= largeur
                            && sf::Mouse::getPosition(window).y >= retour.getPosition().y
                            && sf::Mouse::getPosition(window).y <= retour.getPosition().y+retour.getCharacterSize()) {

                            window.close();
                            this->menu();
                        }else if (sf::Mouse::getPosition(window).x >= (largeur-quitter.getLocalBounds().width)
                                  && sf::Mouse::getPosition(window).x <= largeur
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
        window.clear(sf::Color(100, 100, 120));

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
    std::string infoTourJ1, infoTourJ2, joueur;

    infoTourJ1 = J2+" choisit le pion et \n"+J1+" le place.";
    infoTourJ2 = J1+" choisit le pion et \n"+J2+" le place.";

    int ind_pion = -1, ind_x = -1, ind_y = -1;

    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1350, 1100), "Quarto", sf::Style::Titlebar | sf::Style::Close);

    // création texte explicatif
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("../fonts/Ubuntu-Regular.ttf"))
        font.loadFromFile("./fonts/Ubuntu-Regular.ttf");
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

        if (!texture->loadFromFile("../images/"+this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400)))
            texture->loadFromFile("./images/"+this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400));

        texture->setSmooth(true);

        rect.setTexture(texture);

        openGrille.push_back(rect);
    }

    sf::Event event{};

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        if (tour%2 == 1) {
            text.setString(infoTourJ1);
            joueur = J1;
        }else {
            text.setString(infoTourJ2);
            joueur = J2;
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


                        //gestion des conditions de victoire

                        if(this->g->win()) {
                            window.close();
                            this->resultat(joueur);
                        } else if (this->g->full()) {
                            window.close();
                            this->resultat("match nul");
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
    std::string infoTourJ1, infoTourIA, joueur;

    int ind_pion = -1, ind_x = -1, ind_y = -1;

    infoTourJ1 = "L'IA choisit le pion et\n"+J1+" le place.";
    infoTourIA = J1+" choisit le pion et\nL'IA le place.";


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

        if (!texture->loadFromFile("../images/"+this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400)))
            texture->loadFromFile("./images/"+this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400));

        texture->setSmooth(true);

        rect.setTexture(texture);

        openGrille.push_back(rect);
    }

    sf::Event event{};

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen()) {

        if (tour%2 == 1) {
            text.setString(infoTourIA);
            joueur = "IA";
        }else {
            text.setString(infoTourJ1);
            joueur = "J1";
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
                        ind_pion = this->selectPion(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y,
                                openGrille);

                        if (tour%2 == 1) {
                            std::cout<<"Creation arbre..."<<std::endl;
                            ia->remplirArbre(*g, 0, 2, tabPion, &tabPion[ind_pion]);
                            std::cout<<"Creation arbre... ok!"<<std::endl;
                            std::cout<<"Selection case..."<<std::endl;
                            ia->alphaBeta(ind_x, ind_y, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), tour, true);
                            std::cout<<"Selection case... ok!"<<std::endl;
                            std::cout<<ind_x<<" | "<<ind_y<<std::endl;

                            std::cout<<"Placement Pion..."<<std::endl;
                            grille[ind_y*4+ind_x].setTexture(openGrille[ind_pion].getTexture());
                            std::cout<<"Placement Texture... ok!"<<std::endl;
                            openGrille[ind_pion].setTexture(nullptr);
                            std::cout<<"Suppresion Texture... ok!"<<std::endl;
                            openGrille[ind_pion].setOutlineColor(sf::Color::Transparent);
                            std::cout<<"Suppresion Bordure... ok!"<<std::endl;
                            std::cout<<"Placement Pion... ok!"<<std::endl;

                            /*
                             * Select pion
                             */

                            ia->selectPion(ind_pion, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), tour, false);

                            openGrille[ind_pion].setOutlineColor(sf::Color::Red);

                            ind_x = -1;
                            ind_y = -1;
                            tour++;

                            //gestion des conditions de victoire
                            if(this->g->win()) {
                                //window.close();
                                //this->resultat(joueur);
                            } else if (this->g->full()) {
                                window.close();
                                this->resultat("match nul");
                            }
                        }
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        this->selectCaseGrille(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y,
                                ind_x, ind_y);

                        if (ind_pion != -1 && ind_x != -1 && ind_y != -1) {
                            this->g->setCase(static_cast<unsigned int>(ind_x), static_cast<unsigned int>(ind_y),
                                    & this->tabPion[ind_pion]);

                            grille[ind_y*4+ind_x].setTexture(openGrille[ind_pion].getTexture());
                            openGrille[ind_pion].setTexture(nullptr);
                            openGrille[ind_pion].setOutlineColor(sf::Color::Transparent);

                            ind_pion = -1;
                            ind_x = -1;
                            ind_y = -1;
                            tour++;
                        }


                        //gestion des conditions de victoire
                        bool win = this->g->win();
                        if(win) {
                            //window.close();
                            //this->resultat(joueur);
                        } else if (this->g->full()) {
                            window.close();
                            this->resultat("match nul");
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
