// Delée Alexis et Martina-Cahill Laureen

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "conio.c"

int random(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void setColors(int IValue)
{
    if(IValue == 'J'){
        textcolor(YELLOW);
    } else if(IValue == 'R'){
        textcolor(LIGHTRED);
    } else if(IValue == 'V'){
        textcolor(LIGHTGREEN);
    } else if(IValue == 'B'){
        textcolor(LIGHTCYAN);
    } else if(IValue == '#'){
        textcolor(BROWN);
    }
}

void init(int **IGraph, int ISize, int IAlea, int *IConfigBonus, int INBPlayer)
{
    int ICounterI, ICounterJ, IWall, IDistance;

    srand(time(NULL));
    for(ICounterI = 0; ICounterI <= ISize; ICounterI++){
        for(ICounterJ = 0; ICounterJ <= ISize; ICounterJ++){
            if(ICounterI == 0 && ICounterJ == 0){
                IGraph[ICounterI][ICounterJ] = ' ';
            } else if(ICounterI == 0 || ICounterJ == 0){
                if(ICounterI == 0){
                    IGraph[ICounterI][ICounterJ] = 'A' - 1 + ICounterJ;
                } else {
                    IGraph[ICounterI][ICounterJ] = ICounterI - 1;
                }
            } else {
                if(IAlea == 1){
                    IDistance = ICounterI + ICounterJ - 2; // se base sur la distance avec le coin haut gauche

                    switch(INBPlayer){
                        case 4:
                            if(IDistance > ICounterI + abs(ICounterJ - ISize - 1)  - 2){
                                IDistance = ICounterI + abs(ICounterJ - ISize - 1)  - 2;
                            }
                        case 3:
                            if(IDistance > abs(ICounterI - ISize - 1) + ICounterJ - 2){
                                IDistance = abs(ICounterI - ISize - 1) + ICounterJ - 2;
                            }
                        case 2:
                            if(IDistance > abs(ICounterI - ISize - 1) + abs(ICounterJ - ISize - 1)  - 2){
                                IDistance = abs(ICounterI - ISize - 1) + abs(ICounterJ - ISize - 1) - 2;
                            }
                    }

                    IGraph[ICounterI][ICounterJ] = IDistance;
                } else {
                    IGraph[ICounterI][ICounterJ] = random(0, 9);;
                }
            }
        }
    }

    if(IConfigBonus[0] == 1){
        for(ICounterI = 1; ICounterI <= ISize; ICounterI++){
            IWall = random(1, 100);

            if(IWall <= 60){
                IWall = random(1, ISize);
                IGraph[ICounterI][IWall] = '#';
            }
        }
    }
}

void configCPlayers(int **IGraph, int ISize, int INBPlayer, char *CPlayers)
{
    switch(INBPlayer){
        case 4: IGraph[1][ISize] = CPlayers[3];
        case 3: IGraph[ISize][1] = CPlayers[2];
        case 2: IGraph[1][1] = CPlayers[0]; IGraph[ISize][ISize] = CPlayers[1];
    }
}

int checkMove(int **IGraph, int ISize, char CChoiceCol, int IChoiceLine, char CTurn, int IMode, int ILastMoveLine, int ILastMoveCol)
{
    int ILeft, IRight, ITop, IBottom;
    int ITopRight, ITopLeft, IBottomRight, IBottomLeft;

    if(IGraph[IChoiceLine + 1][(int)CChoiceCol - 64] >= 25){
        return 0;
    }

    /* A gauche */

    if((int)CChoiceCol - 65 >= 1){
        ILeft = IGraph[IChoiceLine + 1][(int)CChoiceCol - 65];
        if(IMode == 1){
            if(IChoiceLine + 1 == ILastMoveLine && (int)CChoiceCol - 65 == ILastMoveCol){
                return 1;
            }
        } else {
            if(ILeft == CTurn){
                return 1;
            }
        }
    }

    /* A droite */

    if((int)CChoiceCol - 63 <= ISize){
        IRight = IGraph[IChoiceLine + 1][(int)CChoiceCol - 63];
        if(IMode == 1){
            if(IChoiceLine + 1 == ILastMoveLine && (int)CChoiceCol - 63 == ILastMoveCol){
                return 1;
            }
        } else {
            if(IRight == CTurn){
                return 1;
            }
        }
    }

    /* En haut */

    if(IChoiceLine >= 1){
        ITop = IGraph[IChoiceLine][(int)CChoiceCol - 64];
        if(IMode == 1){
            if(IChoiceLine == ILastMoveLine && (int)CChoiceCol - 64 == ILastMoveCol){
                return 1;
            }
        } else {
            if(ITop == CTurn){
                return 1;
            }
        }
    }

    /* En bas */

    if(IChoiceLine + 2 <= ISize){
        IBottom = IGraph[IChoiceLine + 2][(int)CChoiceCol - 64];
        if(IMode == 1){
            if(IChoiceLine + 2 == ILastMoveLine && (int)CChoiceCol - 64 == ILastMoveCol){
                return 1;
            }
        } else {
            if(IBottom == CTurn){
                return 1;
            }
        }
    }

    /* En haut à gauche */

    if((int)CChoiceCol - 65 >= 1 && IChoiceLine >= 1){
        ITopLeft = IGraph[IChoiceLine][(int)CChoiceCol - 65];
        if(IMode == 2){
            if(ITopLeft == CTurn){
                return 1;
            }
        }
    }

    /* En haut à droite */

    if((int)CChoiceCol - 63 <= ISize && IChoiceLine >= 1){
        ITopRight = IGraph[IChoiceLine][(int)CChoiceCol - 63];
        if(IMode == 2){
            if(ITopRight == CTurn){
                return 1;
            }
        }
    }

    /* En bas à gauche */

    if((int)CChoiceCol - 65 >= 1 && IChoiceLine + 2 <= ISize){
        IBottomLeft = IGraph[IChoiceLine + 2][(int)CChoiceCol - 65];
        if(IMode == 2){
            if(IBottomLeft == CTurn){
                return 1;
            }
        }
    }

    /* En haut à droite */

    if((int)CChoiceCol - 63 <= ISize && IChoiceLine + 2 <= ISize){
        IBottomRight = IGraph[IChoiceLine + 2][(int)CChoiceCol - 63];
        if(IMode == 2){
            if(IBottomRight == CTurn){
                return 1;
            }
        }
    }

    return 0;
}

int playORnext(int **IGraph, int ISize, char CTurn, int IMode, int ILastMoveLine, int ILastMoveCol)
{
    int ICounterI, ICounterJ, ILeft, IRight, IBottom, ITop;
    int ITopLeft, ITopRight, IBottomLeft, IBottomRight;

    if(IMode == 1){
        if(ILastMoveCol - 1 >= 1){
            if(IGraph[ILastMoveLine][ILastMoveCol - 1] <= 25){
                return 1;
            }
        }

        if(ILastMoveCol + 1 <= ISize){
            if(IGraph[ILastMoveLine][ILastMoveCol + 1] <= 25){
                return 1;
            }
        }

        if(ILastMoveLine - 1 >= 1){
            if(IGraph[ILastMoveLine - 1][ILastMoveCol] <= 25){
                return 1;
            }
        }

        if(ILastMoveLine + 1 <= ISize){
            if(IGraph[ILastMoveLine + 1][ILastMoveCol] <= 25){
                return 1;
            }
        }
    } else if(IMode == 2){
        for(ICounterI = 1; ICounterI <= ISize; ICounterI++){
            for(ICounterJ = 1; ICounterJ <= ISize; ICounterJ++){
                if(IGraph[ICounterI][ICounterJ] == CTurn){
                    if(ICounterJ - 1 >= 1){
                        ILeft = IGraph[ICounterI][ICounterJ - 1];
                        if(ILeft <= 25){
                            return 1;
                        }
                    }

                    if(ICounterJ + 1 <= ISize){
                        IRight = IGraph[ICounterI][ICounterJ + 1];
                        if(IRight <= 25){
                            return 1;
                        }
                    }

                    if(ICounterI - 1 >= 1){
                        ITop = IGraph[ICounterI - 1][ICounterJ];
                        if(ITop <= 25){
                            return 1;
                        }
                    }

                    if(ICounterI + 1 <= ISize){
                        IBottom = IGraph[ICounterI + 1][ICounterJ];
                        if(IBottom <= 25){
                            return 1;
                        }
                    }

                    if(ICounterJ - 1 >= 1 && ICounterI - 1 >= 1){
                        ITopLeft = IGraph[ICounterI - 1][ICounterJ - 1];
                        if(ITopLeft <= 25){
                            return 1;
                        }
                    }

                    if(ICounterJ + 1 <= ISize && ICounterI - 1 >= 1){
                        ITopRight = IGraph[ICounterI - 1][ICounterJ + 1];
                        if(ITopRight <= 25){
                            return 1;
                        }
                    }

                    if(ICounterJ - 1 >= 1 && ICounterI + 1 <= ISize){
                        IBottomLeft = IGraph[ICounterI + 1][ICounterJ - 1];
                        if(IBottomLeft <= 25){
                            return 1;
                        }
                    }

                    if(ICounterJ + 1 <= ISize && ICounterI + 1 <= ISize){
                        IBottomRight = IGraph[ICounterI + 1][ICounterJ + 1];
                        if(IBottomRight <= 25){
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

void draw(int **IGraph, int ISize, char *CPlayers)
{
    int ICounterI, ICounterJ;

    printf("\n");

    for(ICounterI = 0; ICounterI <= ISize; ICounterI++){
        for(ICounterJ = 0; ICounterJ <= ISize; ICounterJ++){
            if(ISize > 10){
                if(IGraph[ICounterI][ICounterJ] > 25){
                    if(ICounterI != 0){
                        setColors(IGraph[ICounterI][ICounterJ]);
                    }
                    printf("%c ", IGraph[ICounterI][ICounterJ]);
                } else if(IGraph[ICounterI][ICounterJ] < 10){
                    printf("%d ", IGraph[ICounterI][ICounterJ]);
                } else {
                    printf("%d", IGraph[ICounterI][ICounterJ]);
                }
            } else {
                if(IGraph[ICounterI][ICounterJ] <= 25){
                    printf("%d", IGraph[ICounterI][ICounterJ]);
                } else {
                    if(ICounterI != 0){
                        setColors(IGraph[ICounterI][ICounterJ]);
                    }
                    printf("%c", IGraph[ICounterI][ICounterJ]);
                }
            }
            textcolor(LIGHTGRAY);
            printf("|");
        }
        printf("\n");
    }
}

int maxScore(int *IScoreTab, int INBPlayer, int strict)
{
    int ICounterI, IMax = IScoreTab[0], IMultiple = 0, IIndex = 0;

    for(ICounterI = 1; ICounterI < INBPlayer; ICounterI++){
        if(IScoreTab[ICounterI] == IMax){
            IMultiple = 1;
        }

        if(IScoreTab[ICounterI] > IMax){
            IMultiple = 0;
            IMax = IScoreTab[ICounterI];
            IIndex = ICounterI;
        }
    }

    if(strict == 1 && IMultiple == 1){
        return -1;
    } else {
        return IIndex;
    }
}

void swap(int *IScoreTab, char *CPlayers, int *INBArea, int ICounterI, int ICounterJ)
{
    int ITmp = IScoreTab[ICounterI], ITempI = CPlayers[ICounterI], IScoreI = INBArea[ICounterI];

    INBArea[ICounterI] = INBArea[ICounterJ];
    CPlayers[ICounterI] = CPlayers[ICounterJ];
    IScoreTab[ICounterI] = IScoreTab[ICounterJ];

    INBArea[ICounterJ] = IScoreI;
    CPlayers[ICounterJ] = ITempI;
    IScoreTab[ICounterJ] = ITmp;
}


int main(int argc, char **argv)
{
    int ISize = 5, **IGraph = NULL, INBPlayer = 2, ICounterTurn = 0, IConfigBonus[2] = {0, 0}, ILastMove[8], INBArea[4] = {1, 1, 1, 1}, INext, IPercent, ICounterJ;
    int ICounterI, IMode = 1, IChoiceLine, IEnd = 0, IScore, IScoreTab[4] = {0, 0, 0, 0}, ISkip = 0, IChoice, IAlea = 1, IBonus = 0, IChoiceBonus, IWall = 0, IConquete = 0;
    char CPlayers[4] = {'J', 'R', 'V', 'B'}, CTurn = CPlayers[ICounterTurn], CChoiceCol;

    // Menu

    do {
        system("cls");

        printf("\n| Configuration par defaut");
        printf("\n-------------------------------------------------------------------------\n");
        printf("\n1 - Taille de la map : %dx%d", ISize, ISize);
        printf(IMode == 1 ? "\n2 - Mode : serpent" : "\n2 - Mode : pieuvre");
        printf("\n3 - Nombre de joueurs : %d", INBPlayer);
        printf(IAlea == 1 ? "\n4 - Generateur de valeurs : distance entre les joueurs" : "\n4 - Generateur de valeurs : aleatoire");
        printf(IBonus == 0 ? "\n5 - Bonus : desactive" : "\n5 - Bonus : active");
        printf("\n6 - Commencer la partie");
        printf("\nTapez entre 1 et 5 pour changer les configurations, ou sur 6 pour commencer une partie : ");
        scanf("%d", &IChoice);

        if(IChoice == 1){
            printf("\nCombien de lignes/colonnes souhaitez-vous generer ? ");
            scanf("%d", &ISize);
            while(ISize < 5 || ISize > 26){
                printf("Vous ne pouvez generer qu'entre 5 et 26 lignes/colonnes : ");
                scanf("%d", &ISize);
            }
        } else if(IChoice == 2){
            do {
                printf("\n1) Mode serpent");
                printf("\n2) Mode pieuvre");
                printf("\nQuel mode souhaitez-vous jouer ? ");
                scanf("%d", &IMode);
            } while(IMode < 1 || IMode > 2);
        } else if(IChoice == 3){
            printf("\nA combien de joueurs comptez-vous jouer ? ");
            scanf("%d", &INBPlayer);
            while(INBPlayer < 2 || INBPlayer > 4){
                printf("Vous ne pouvez generer qu'entre 2 et 4 joueurs : ");
                scanf("%d", &INBPlayer);
            }
        } else if(IChoice == 4){
            do {
                printf("\n1) Distance entre les joueurs");
                printf("\n2) Aleatoire");
                printf("\nDe quelle facon souhaitez-vous generer les valeurs ? ");
                scanf("%d", &IAlea);
            } while(IAlea < 1 || IAlea > 2);
        } else if(IChoice == 5){
            do {
                system("cls");

                printf("\n| Configuration bonus");
                printf("\n-------------------------------------------------------------------------\n");
                printf(IWall == 0 ? "\n1 - Ajout de murs" : "\n1 - Murs ajoutes (#)");
                printf(IConquete == 0 ? "\n2 - Ajout du mode conquete" : "\n2 - Mode conquete active");
                printf("\n3 - Revenir au menu precedent");
                printf("\n4 - Commencer la partie");
                printf("\nTapez entre 1 et 2 pour changer les configurations, ou sur 4 pour les valider : ");
                scanf("%d", &IChoiceBonus);

                if(IChoiceBonus == 1){
                    IBonus = 1;
                    IConfigBonus[0] = 1;
                    IWall = 1;
                } else if(IChoiceBonus == 2){
                    IBonus = 1;
                    IConfigBonus[1] = 2;
                    IConquete = 1;
                } else if(IChoiceBonus == 3){
                    break;
                } else if(IChoiceBonus == 4){
                    IChoice = 6;
                    break;
                }
            } while(1);
        }
    } while(IChoice != 6);

    /* Création tableau à deux dimensions */

    IGraph = malloc((ISize + 1) * sizeof(int*));

    for(ICounterI = 0; ICounterI <= ISize; ICounterI++){
        IGraph[ICounterI] = malloc((ISize + 1) * sizeof(int));
    }

    ILastMove[0] = 1;
    ILastMove[1] = 1;
    ILastMove[2] = ISize;
    ILastMove[3] = ISize;
    ILastMove[4] = 1;
    ILastMove[5] = ISize;
    ILastMove[6] = ISize;
    ILastMove[7] = 1;

    /* Initialisation tableau */

    if(IGraph != NULL){
        init(IGraph, ISize, IAlea, IConfigBonus, INBPlayer);
    } else {
        printf("Erreur d'allocation !");
        exit(-1);
    }

    configCPlayers(IGraph, ISize, INBPlayer, CPlayers);

    /* Traitement */

    while(1){
        system("cls");

        /* Affichage des scores en cours de partie */

        for(ICounterI = 0; ICounterI < INBPlayer; ICounterI++){
            if(CTurn == CPlayers[ICounterI]){
                setColors(CTurn);
            }
            printf("-|%c : %d|-", CPlayers[ICounterI], IScoreTab[ICounterI]);
            textcolor(LIGHTGRAY);
        }

        printf("\n");

        printf("\n--------------------");
        printf("\n| Tour au joueur ");
        setColors(CTurn);
        printf("%c", CTurn);
        textcolor(LIGHTGRAY);
        printf(" |");
        printf("\n--------------------\n");

        draw(IGraph, ISize, CPlayers);

        IScore = 0;
        IEnd = 0;

        if(playORnext(IGraph, ISize, CTurn, IMode, ILastMove[ICounterTurn * 2 + 1], ILastMove[ICounterTurn * 2]) == 0){
            IEnd = 1;
            ISkip++;

            // Fin prématurée

            if(IConquete == 0 && ISkip == INBPlayer - 1){
                if(maxScore(IScoreTab, INBPlayer, 1) >= 0){
                    if((ICounterTurn + 1 >= INBPlayer ? 0 : ICounterTurn + 1) == maxScore(IScoreTab, INBPlayer, 1)){
                        printf("\nFin de la partie");
                        break;
                    }
                }
            }
        } else {
            ISkip = 0;
        }

        if(ISkip == INBPlayer){
            printf("\nFin de la partie");
            break;
        }

        while(IEnd == 0){
            printf("\nSaisir une colonne : ");
            scanf(" %c", &CChoiceCol);
            while(CChoiceCol < 'A' || CChoiceCol > ISize + 64){
                printf("Saisir une colonne entre A et %c : ", ISize + 64);
                scanf(" %c", &CChoiceCol);
            }

            while(IEnd == 0){
                printf("Saisir une ligne : ");
                scanf("%d", &IChoiceLine);
                while(IChoiceLine < 0 || IChoiceLine >= ISize){
                    printf("Saisir une ligne comprise entre 0 et %d : ", ISize - 1);
                    scanf("%d", &IChoiceLine);
                }

                if(checkMove(IGraph, ISize, CChoiceCol, IChoiceLine, CTurn, IMode, ILastMove[ICounterTurn * 2 + 1], ILastMove[ICounterTurn * 2]) == 0){
                    printf("\nMouvement impossible !\n");
                    break;
                } else {
                    IEnd = 1;
                    IScore = IGraph[IChoiceLine + 1][(int)CChoiceCol - 64];
                    IGraph[IChoiceLine + 1][(int)CChoiceCol - 64] = (int)CTurn;
                    ILastMove[ICounterTurn * 2] = (int)CChoiceCol - 64;
                    ILastMove[ICounterTurn * 2 + 1] = IChoiceLine + 1;
                    INBArea[ICounterTurn] += 1;
                }
            }
        }

        /* Comptabilisation des points */

        IScoreTab[ICounterTurn] += IScore;

        /* Changer de joueur */

        ICounterTurn++;
        if(ICounterTurn >= INBPlayer){
            ICounterTurn = 0;
        }
        CTurn = CPlayers[ICounterTurn];
    }

    /* Affichage des scores finaux */

    system("cls");
    printf("Classement :\n");

    if(IConquete == 1){
        for(ICounterI = 0; ICounterI < INBPlayer; ICounterI++){
            IScoreTab[ICounterI] = (IScoreTab[ICounterI] * 3.5 + INBArea[ICounterI] * 6.4) / 10;
        }
    }

    for(ICounterI = 1; ICounterI < INBPlayer; ICounterI++){
        if(IScoreTab[ICounterI - 1] > IScoreTab[ICounterI]){
            for(ICounterJ = ICounterI; ICounterJ >= 1; ICounterJ--){
                if(IScoreTab[ICounterJ] < IScoreTab[ICounterJ - 1]){
                    swap(IScoreTab, CPlayers, INBArea, ICounterJ, ICounterJ - 1);
                }
            }
        }
    }

    for(ICounterI = INBPlayer - 1; ICounterI >= 0; ICounterI--){
        printf("[%d] %c ", INBPlayer - ICounterI, CPlayers[ICounterI]);
        for(ICounterJ = 1; ICounterJ <= IScoreTab[ICounterI]; ICounterJ++){
            printf("|");
        }
        printf(" (%d)\n", IScoreTab[ICounterI]);
    }

    printf("\nTerritoire capture : ");
    for(ICounterI = 0; ICounterI < INBPlayer; ICounterI++){
        IPercent = INBArea[ICounterI] * 100 / pow(ISize, 2);
        printf("\n[%c : %d%%]", CPlayers[ICounterI], IPercent);
    }

    printf("\n\n#");

    INext = 0;
    ICounterTurn = 0;
    IPercent = INBArea[INext] * 100 / pow(ISize, 2);

    for(ICounterI = 0; ICounterI < 100; ICounterI++){
        if(INext < INBPlayer){
            if(ICounterTurn < IPercent){
                setColors(CPlayers[INext]);
                printf("#");
                ICounterTurn++;
            } else {
                ICounterTurn = 0;
                INext++;
                IPercent = INBArea[INext] * 100 / pow(ISize, 2);
            }
        } else {
            textcolor(LIGHTGRAY);
            printf("-");
        }
    }

    textcolor(LIGHTGRAY);
    printf("#\n");

    if(IGraph != NULL){ free(IGraph); }
    return 0;
}
