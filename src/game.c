#include "game.h"

int countMinesAround(int x, int y, Plateau* plateau)
{
    int number = 0;

    // Coin superieur gauche
    if ((x - 1) >= 0 && (y - 1) >= 0 && plateau->grid[y - 1][x - 1].state == MINE)
    {
        number++;
    }
    
    // Haut
    if ((y - 1) >= 0 && plateau->grid[y - 1][x].state == MINE)
    {
        number++;
    }

    // Coin superieur droit
    if ((x + 1) < plateau->width && (y - 1) >= 0 && plateau->grid[y - 1][x + 1].state == MINE)
    {
        number++;
    }
    
    // Droite
    if ((x - 1) >= 0 && plateau->grid[y][x - 1].state == MINE)
    {
        number++;
    }
    
    // Gauche
    if ((x + 1) < plateau->width && plateau->grid[y][x + 1].state == MINE)
    {
        number++;
    }

    // Coin inferieur gauche
    if ((x - 1) >= 0 && (y + 1) < plateau->height && plateau->grid[y + 1][x - 1].state == MINE)
    {
        number++;
    }

    // Bas
    if ((y + 1) < plateau->height && plateau->grid[y + 1][x].state == MINE)
    {
        number++;
    }

    // Coin inferieur droit
    if ((x + 1) < plateau->width && (y + 1) < plateau->height && plateau->grid[y + 1][x + 1].state == MINE)
    {
        number++;
    }

    return number;
}

Plateau* revealSquare(int x, int y, Plateau *plateau)
{

    if (plateau->grid[y][x].state == MINE)
    {
        printf("Perdu");
        plateau->state = LOSE;
        return plateau;
    }

    int count = countMinesAround(x, y, plateau);

    if (count > 0)
    {
        plateau->grid[y][x].state = '0' + count;
    }

    return plateau;
}

int checkCoord(int x, int y, Plateau* board)
{
    if (x < 0 || x >= board->width || y < 0 || y >= board->height)
        return 0;
    return 1;
}

Plateau* placeFlag(int x, int y, Plateau* board)
{
    board->grid[y][x].flag = board->grid[y][x].flag ? 0 : 1;
    return board;
}

Plateau* makeAction(Plateau* board)
{
    char action[5];

    printf("Entrez une action (x y action) et Q pour retourner au menu\n");

    fgets(action, 5, stdin);

    printf("action = %s\n", action);

    if (!checkCoord(action[1] - 'A', action[2] - '0', board) && action[0] != 'Q')
    {
        coordError();
        return board;
    }

    switch (action[0])
    {
        case 'R':
            board = revealSquare(action[1] - 'A', action[2] - '0', board);
            break;
        
        case 'F':
            board = placeFlag(action[1] - 'A', action[2] - '0', board);
            break;

        case 'Q':
            board->state = ENDBYUSER;
            break;

        default:
            break;
    }

    return board;

}

void startGame()
{
    Plateau *board = createPlateau(9, 9);
    int endOfGame = 0;

    board = fillPlateauWithMine(board);

    getchar();
    while (endOfGame == 0)
    {
        displayPlateau(board);

        board = makeAction(board);

        if (board->state == LOSE || board->state == ENDBYUSER || board->state == WIN)
        {
            endOfGame = 1;
        }        
    }

    destroyPlateau(board);
}
