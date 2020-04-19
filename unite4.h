// Sentinelle d'inclusion
#ifndef _unite4_h
#define _unite4_h

#include "unite3.h"

class Game
{
public:

    enum State {
        Reset,
        Pause,
        Play,
        StepByStep,
        GameOver
    };

    static constexpr int TAILLE_MATRICE = 200;

    Game();
    void init();

    [[nodiscard]] bool isSick();
    [[nodiscard]] bool isPregnant();

    [[nodiscard]] bool isVacant(int x, int y, int z) const;

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

    void clear(int p);

    int initialSheepCount() const;
    void setInitialSheepCount(int initialSheepCount);

    int initialWolfCount() const;
    void setInitialWolfCount(int initialWolfCount);

    void moveAll();

    float ratio() const;
    [[nodiscard]] Type winner() const noexcept;

    void setWinner(const Type &winner);

private:
    void moveSheep(int x, int y);
    void moveWolf(int x, int y);

    int m_initialSheepCount = 2000;
    int m_initialWolfCount = 2000;

    float gMortaliteLoup = 0.1;
    float gNataliteMouton = 0.1;

    Type m_winner = VIDE;
    State m_state = Pause;
};

extern Game *game;

#endif // unite4_h
