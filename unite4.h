// Sentinelle d'inclusion
#ifndef _unite4_h
#define _unite4_h



void deplacerMouton(int x, int y);
void deplacerLoup(int x, int y);
void deplacement();
void setTab(int p);
[[nodiscard]] bool isVacant(int x, int y, int z);
[[nodiscard]] bool isSick();
[[nodiscard]] bool isPregnant();
float rapport() ;
#endif // unite4_h
