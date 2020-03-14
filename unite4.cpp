#include "unite4.h"

#include <cstdlib>

#include "unite1.h"
#include "unite3.h"


Game *game = nullptr;

/*!
 * \brief Random draw.
 * \param rate Rate at which this function will return true. Must be between
 * 0.0 and 1.0.
 * \return Returns true with a probability of \a rate.
 */
static bool helper_random(float rate)
{
    const int random = std::rand() % 100 + 1;                       // On choisit aléatoirement un entier entre 1 et 100
    const bool isSick = random < rate * 100;           // Si le nombre est inférieur à rate
    return isSick;
}

Game::Game()
{
    clear(0);
    clear(1);
    init();
}

void Game::init()
{
    //On place les moutons aléatoirement dans le tableau de jeu
    int x, y;
    int n = 0;

    do {
        x = rand() % Game::TAILLE_MATRICE + 1;
        y = rand() % Game::TAILLE_MATRICE + 1;

        if (isVacant(x, y, 0)) {
            gTableauJeu[x][y][0] = MOUTON;
            n++;
        }
    } while (n < m_initialSheepCount);

    //On place les loups aléatoirment dans le tableau de jeu
    n = 0;

    do {
        x = rand() % Game::TAILLE_MATRICE + 1;
        y = rand() % Game::TAILLE_MATRICE + 1;

        if (isVacant(x, y, 0)) {
            gTableauJeu[x][y][0] = LOUP;
            n++;
        }
    } while (n < m_initialWolfCount);
}

bool Game::isSick()                // Fonction de maladie d'un loup
{
    return helper_random(gMortaliteLoup);
}

bool Game::isPregnant()                    // De meme que pour isSick
{
    return helper_random(gNataliteMouton);
}

void Game::clear(int p)
{
    for (int i = 0 ; i < TAILLE_MATRICE + 2 ; i++) {
        for (int j = 0 ; j < TAILLE_MATRICE + 2 ; ++j) {
            if (i != 0 && j != 0 && i != TAILLE_MATRICE + 1 && j != TAILLE_MATRICE + 1) {
                gTableauJeu[i][j][p] = VIDE;          // Les cases centrales sont vides
            } else {
                gTableauJeu[i][j][p] = BORD;          // Et les bords sont inaccessibles, pour des problèmes de déplacement
            }
        }
    }
}

int Game::initialSheepCount() const
{
    return m_initialSheepCount;
}

void Game::setInitialSheepCount(int initialSheepCount)
{
    m_initialSheepCount = initialSheepCount;
}

int Game::initialWolfCount() const
{
    return m_initialWolfCount;
}

void Game::setInitialWolfCount(int initialWolfCount)
{
    m_initialWolfCount = initialWolfCount;
}



bool Game::isVacant(int x, int y, int z) const           //Fonction permettant de savoir si la case est vide, ou pas
{
    return gTableauJeu[x][y][z] == VIDE;
}




void Game::moveSheep(int x, int y)           // Procédure déplacant les moutons
{
    int p = gTour % 2;        // p = 0 ou 1 selon ma parité du nombre de tours joués
    int xfutur, yfutur;       // futur case du mouton
    int count = 0;

    do {          // le processeur cherche
        count++;
        int a = (std::rand() % 8) + 1;         //Variable aléatoire de 1 à 8

        switch (a) {
        case 1 :              // 1 -> bas/gauche
            xfutur = x - 1;
            yfutur = y - 1;
            break;

        case 2 :              // 2 -> bas/centre
            xfutur = x;
            yfutur = y - 1;
            break;

        case 3 :              // 3 -> bas/droite
            xfutur = x + 1;
            yfutur = y - 1;
            break;

        case 4 :              // 4 -> gauche
            xfutur = x - 1;
            yfutur = y;
            break;

        case 5 :              // 5 -> haut/droite
            xfutur = x + 1;
            yfutur = y + 1;
            break;

        case 6 :              // 6 -> doite
            xfutur = x + 1;
            yfutur = y;
            break;

        case 7 :              // 7 -> haut/gauche
            xfutur = x - 1;
            yfutur = y + 1;
            break;

        case 8 :              // 8 -> haut/centre
            xfutur = x;
            yfutur = y + 1;
            break;
        }
    } // tant que l'un des 2 tableaux est occupé, et que le compteur est inférieur à 10 (risque de boucle infine)

    while ((!game->isVacant(xfutur, yfutur, 1 - p) || !game->isVacant(xfutur, yfutur, p)) && count < 10);


    if (count < 10)   {  // S'il trouve une solution lorsque le compteur est inférieur à 10
        game->gTableauJeu[xfutur][yfutur][1 - p] = MOUTON;  // il déplace le mouton dans le nouveau tableau


        if (game->isPregnant()) {           // Si le mouton est "enceinte"
            game->gTableauJeu[x][y][1 - p] = MOUTON;    // Il laisse un mouton derrière lui (dans le nouveau tableau)

        } else {
            game->gTableauJeu[x][y][1 - p] = VIDE;  // Sinon, il se déplace simplement
        }
    } else
        game->gTableauJeu[x][y][1 - p] = MOUTON; // Si le compteur est à 10, on laisse le mouton où il était, mais dans le nouveau tableau

    game->gTableauJeu[x][y][p] = VIDE;      // On efface le mouton joué du tableau précédent
}

void Game::moveWolf(int x, int y)         // Procédure de déplacement des loups
{
    int p = gTour % 2;
    bool moutonici = false;              // Indicateur de présence d'un mouton
    int moutonx, moutony;           // Coordonées d'un mouton

    for (int i = -1; i <= 1 && !moutonici; i++) { // Balayage des cases tant que le loup n'a pas trouvé de mouton
        for (int j = -1; j <= 1 && !moutonici; j++) {
            // S'il en trouve un
            if (game->gTableauJeu[x + i][y + j][1 - p] == MOUTON || game->gTableauJeu[x + i][y + j][p] == MOUTON) {
                moutonici = true;
                moutonx = x + i;    //Définition des coordonées du mouton vu par le loup
                moutony = y + j;
            }
        }
    }

    if (moutonici) {        // Consommation du mouton par le loup
        game->gTableauJeu[x][y][1 - p] = LOUP;            // Naissance d'un nouveau loup dans la case précédente
        game->gTableauJeu[moutonx][moutony][1 - p] = LOUP;   //Déplacement du loup sur le mouton vu
        game->gTableauJeu[moutonx][moutony][p] = VIDE;        // "Nettoyage" du tableau précédent
    } else              // Sinon, le loup n'a trouvé aucun mouton
        // Il se déplace aléatoirement, avec la probabilité de mourrir de faim à chaque tour
    {
        int count = 0;
        int a, b;

        do {
            a = x + rand() % 3 - 1; // Choix aléatoire d'une case autour du loup
            b = y + rand() % 3 - 1;
            count++;
        }

        // Sortie si la case est trouvée, ou si le compteur atteint 10
        while ((!game->isVacant(a, b, 1 - p) || !game->isVacant(a, b, p)) && count < 10);

        if (!game->isSick()) { //Si le loup n'est pas malade
            if (count < 10) {      // Si le compteur est inférieur à 10
                game->gTableauJeu[a][b][1 - p] = LOUP;    // On le déplace

            } else {
                game->gTableauJeu[x][y][1 - p] = LOUP; // Il ne bouge pas, mais change de tableau
            }
        }
    }

    game->gTableauJeu[x][y][p] = VIDE;    // "Nettoyage" du tableau
    // rq : Si le loup est malade, il n'est pas placé dans le nouveau tableau, il est donc mort

}

void Game::moveAll()      // Procédure globale
{
    int p = gTour % 2;  // On balaie le tableau p

    for (int i = 1; i < Game::TAILLE_MATRICE + 1; i++) {
        for (int j = 1; j < Game::TAILLE_MATRICE + 1; j++) {
            if (game->gTableauJeu[i][j][p] == LOUP)   // S'il y a un loup
                moveWolf(i, j);     // On le déplace
            else if (game->gTableauJeu[i][j][p] == MOUTON)    // Si c'est un mouton
                moveSheep(i, j);      // On le déplace
        }
    }

    game->clear(p);      // Et on nettoie le tableau p
}

float rapport() //calcul le rapport loup/mouton
{
    int p = gTour % 2; //parité du tour
    float r;
    float nbLoup = 0, nbMouton = 0;

    //On compte
    for (int i = 1; i < Game::TAILLE_MATRICE + 1; i++) {
        for (int j = 1; j < Game::TAILLE_MATRICE + 1; j++) {
            if (game->gTableauJeu[i][j][p] == LOUP)
                nbLoup = nbLoup + 1;
            else if (game->gTableauJeu[i][j][p] == MOUTON)
                nbMouton = nbMouton + 1;
        }
    }

    //Si il n'y a plus de mouton
    if (nbMouton == 0)
        return -1; //Valeur impssible
    else
        r = nbLoup / nbMouton; // Sinon on peut faire le ratio

    return r;
}

