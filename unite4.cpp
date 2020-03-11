#include "unite1.h"
#include "unite3.h"
#include "unite4.h"
#include <stdlib.h>
     // exit, rand





int isSick()                // Fonction de maladie d'un loup
{
    int a,b;
	a=rand()%100+1;                       // On choisit aléatoirement un entier entre 1 et 100
	if ( a<gMortaliteLoup*100 )           // Si le nombre est inférieur à la mortalité
	{
	    b=1;        //Le loup va y passer
	}
	else
	{
	    b=0;        //C'est reparti pour un tour
	}

return b;
}




int isPregnant()                    // De meme que pour isSick
{
    int a,b;
	a=rand()%100+1;
	if ( a<gNataliteMouton*100 )
	{
	    b=1;        //Un nouveau né est en vue
	}
	else
	{
	    b=0;        //Rien ne sera pondu
	}
return b;
}



int isVacant(int x,int y,int z)             //Fonction permettant de savoir si la case est vide, ou pas
{
    if(gTableauJeu[x][y][z] == VIDE)
        return 1;
    else
        return 0;

}



void setTab(int p)                     // Mise à zéro du tableau de jeu
{
    int i, j;

    for ( i=0 ; i<TAILLE_MATRICE+2 ; i++)
    {
            for ( j=0 ; j<TAILLE_MATRICE+2 ; j++ )
            {
                if ( i!=0 && j!=0 && i!=TAILLE_MATRICE+1 && j!=TAILLE_MATRICE+1 )
                {
                    gTableauJeu[i][j][p]=VIDE;          // Les cases centrales sont vides
                }
                else
                {
                    gTableauJeu[i][j][p]=BORD;          // Et les bords sont inaccessibles, pour des problèmes de déplacement
                }
            }
    }
}

void deplacerMouton (int x, int y){         // Procédure déplacant les moutons
      int a;
      int p=gTour%2;            // p = 0 ou 1 selon ma parité du nombre de tours joués
      int xfutur,yfutur;        // futur case du mouton
      int count=0;

      do            // le processeur cherche
      {
        count++;
        a=(rand()%8)+1;         //Variable aléatoire de 1 à 8
        switch (a)
        {
          case 1 :              // 1 -> bas/gauche
          xfutur=x-1;
          yfutur=y-1;
          break;

          case 2 :              // 2 -> bas/centre
          xfutur=x;
          yfutur=y-1;
          break;

          case 3 :              // 3 -> bas/droite
          xfutur=x+1;
          yfutur=y-1;
          break;

          case 4 :              // 4 -> gauche
          xfutur=x-1;
          yfutur=y;
          break;

          case 5 :              // 5 -> haut/droite
          xfutur=x+1;
          yfutur=y+1;
          break;

          case 6 :              // 6 -> doite
          xfutur=x+1;
          yfutur=y;
          break;

          case 7 :              // 7 -> haut/gauche
          xfutur=x-1;
          yfutur=y+1;
          break;

          case 8 :              // 8 -> haut/centre
          xfutur=x;
          yfutur=y+1;
          break;
        }
      } // tant que l'un des 2 tableaux est occupé, et que le compteur est inférieur à 10 (risque de boucle infine)
      while ( ( !isVacant(xfutur,yfutur,1-p) || !isVacant(xfutur,yfutur,p) ) && count<10);


    if(count<10)   {     // S'il trouve une solution lorsque le compteur est inférieur à 10
      gTableauJeu[xfutur][yfutur][1-p]=MOUTON;      // il déplace le mouton dans le nouveau tableau


      if (isPregnant())             // Si le mouton est "enceinte"
      {
          gTableauJeu[x][y][1-p]=MOUTON;        // Il laisse un mouton derrière lui (dans le nouveau tableau)

      }
      else
      {
          gTableauJeu[x][y][1-p]=VIDE;      // Sinon, il se déplace simplement
      }
    }
    else
        gTableauJeu[x][y][1-p]=MOUTON;   // Si le compteur est à 10, on laisse le mouton où il était, mais dans le nouveau tableau
 gTableauJeu[x][y][p]=VIDE;        // On efface le mouton joué du tableau précédent
  }

void deplacerLoup(int x,int y)          // Procédure de déplacement des loups
{
    int p=gTour%2;
    int moutonici=0;                // Indicateur de présence d'un mouton
    int moutonx,moutony;            // Coordonées d'un mouton
    for(int i=-1;i<=1 && !moutonici;i++)        // Balayage des cases tant que le loup n'a pas trouvé de mouton
    {
        for(int j=-1; j<=1 && !moutonici;j++)
        {               // S'il en trouve un
            if(gTableauJeu[x+i][y+j][1-p]==MOUTON||gTableauJeu[x+i][y+j][p]==MOUTON)
            {
                moutonici=1;
                moutonx=x+i;        //Définition des coordonées du mouton vu par le loup
                moutony=y+j;
            }
        }
    }
    if(moutonici)           // Consommation du mouton par le loup
    {
        gTableauJeu[x][y][1-p]=LOUP;                // Naissance d'un nouveau loup dans la case précédente
        gTableauJeu[moutonx][moutony][1-p]=LOUP;       //Déplacement du loup sur le mouton vu
        gTableauJeu[moutonx][moutony][p]=VIDE;          // "Nettoyage" du tableau précédent
    }
    else                // Sinon, le loup n'a trouvé aucun mouton
                        // Il se déplace aléatoirement, avec la probabilité de mourrir de faim à chaque tour
    {
        int count=0;
        int a,b;
        do
        {
            a=x+rand()%3-1;         // Choix aléatoire d'une case autour du loup
            b=y+rand()%3-1;
            count++;
        }
                        // Sortie si la case est trouvée, ou si le compteur atteint 10
        while((!isVacant(a,b,1-p) || !isVacant(a,b,p)) && count<10);

        if(!isSick()){ //Si le loup n'est pas malade
            if(count<10)           // Si le compteur est inférieur à 10
            {
                gTableauJeu[a][b][1-p]=LOUP;        // On le déplace

            }
            else
            {
                gTableauJeu[x][y][1-p]=LOUP;    // Il ne bouge pas, mais change de tableau
            }
        }
    }

    gTableauJeu[x][y][p]=VIDE;      // "Nettoyage" du tableau
    // rq : Si le loup est malade, il n'est pas placé dans le nouveau tableau, il est donc mort

}

void deplacement()      // Procédure globale
{
    int p=gTour%2;      // On balaie le tableau p
    for(int i=1;i<TAILLE_MATRICE+1;i++){
        for(int j=1;j<TAILLE_MATRICE+1;j++){
                if( gTableauJeu[i][j][p]==LOUP)     // S'il y a un loup
                    deplacerLoup(i,j);      // On le déplace
                else if(gTableauJeu[i][j][p] == MOUTON)     // Si c'est un mouton
                    deplacerMouton(i,j);       // On le déplace
        }
    }
    setTab(p);      // Et on nettoie le tableau p
}

float rapport() //calcul le rapport loup/mouton
{
    int p=gTour%2; //parité du tour
    float r;
    float nbLoup=0, nbMouton=0;

    //On compte
    for(int i=1;i<TAILLE_MATRICE+1;i++){
        for(int j=1;j<TAILLE_MATRICE+1;j++){
                if( gTableauJeu[i][j][p]==LOUP)
                    nbLoup=nbLoup+1;
                else if(gTableauJeu[i][j][p] == MOUTON)
                    nbMouton=nbMouton+1;
            }
        }
    //Si il n'y a plus de mouton
    if (nbMouton==0)
        return -1; //Valeur impssible
    else
        r=nbLoup/nbMouton; // Sinon on peut faire le ratio
    
    return r;
}

