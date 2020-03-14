// Sentinelle d'inclusion
#ifndef _unite4_h
#define _unite4_h

void deplacerMouton(int x, int y);
void deplacerLoup(int x, int y);
void deplacement();
void setTab(int p);
[[nodiscard]] bool isVacant(int x, int y, int z);

float rapport() ;

class Game
{
public:

    static constexpr int TAILLE_MATRICE = 200;

    [[nodiscard]] bool isSick();
    [[nodiscard]] bool isPregnant();

    [[nodiscard]] constexpr float  wolfDeathRate() const noexcept
    {
        return gMortaliteLoup;
    }

    [[nodiscard]] constexpr float  sheepBirthRate() const noexcept
    {
        return gNataliteMouton;
    }

    void setWolfDeathRate(float deathRate)
    {
        gMortaliteLoup = deathRate;
    }

    void setSheepBirthRate(float birthRate)
    {
        gNataliteMouton = birthRate;
    }


    int gTableauJeu[TAILLE_MATRICE + 2][TAILLE_MATRICE + 2][2];

private:
    float gMortaliteLoup = 0.1;
    float gNataliteMouton = 0.1;
};

extern Game *game;

#endif // unite4_h
