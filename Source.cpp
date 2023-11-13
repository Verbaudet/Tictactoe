#include <iostream>
using namespace std;

// Enum pour représenter les positions sur le tableau
enum BoardPositions {
    TopLeft = 1, TopCenter, TopRight,
    MiddleLeft, MiddleCenter, MiddleRight,
    BottomLeft, BottomCenter, BottomRight
};

// Création du tableau de morpion
char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };

// Création des variables
int choice;
int row, column;
char turn = 'X';
bool draw = false;
int scoreX = 0, scoreO = 0; // Variables bonus pour garder en tete les scores 

// Fonction pour display l'etat du tableau en fonction du nombre de tours
void displayBoard() {
    system("cls"); // pour clear chaque fois que le joueur écrit une case
    cout << "Joueur - 1 [X] | Joueur - 2 [O]\n";
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << " \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << " \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << " \n";
    cout << "     |     |     \n";
}

// Fonction pour lancer un tour
void playerTurn() {
    int input;
    do {
        cout << "A toi, joueur " << turn << " (choisis une position entre 1 et 9): ";
        cin >> input;

        // Convertis le chiffre du joueur
        row = (input - 1) / 3;
        column = (input - 1) % 3;

        // Check si la position donnée est la bonne, sinon relance
        if (input < 1 || input > 9 || board[row][column] == 'X' || board[row][column] == 'O') {
            cout << "T'as mal compris je crois. Choisis entre 1 et 9.\n";
        }
        else {
            break;
        }
    } while (true);

    // Permet d'update le tour, et de lancer l'autre joueur
    board[row][column] = turn;
    turn = (turn == 'X') ? 'O' : 'X';
}

// Fonction pour voir si le match est terminé
bool gameOver() {
    // Check pour les win conditions dans les rows et columns
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] ||
            board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return false;
        }

    // Check pour les win conditions dans les diagonales
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] ||
        board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return false;
    }

    // Check pour voir si le jeu est toujours en cours, et si il reste de la place)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return true;
            }

    // Check pour du draw
    draw = true;
    return false;
}

// Fonction pour faire un rematch
void resetGame() {
    turn = 'X';
    draw = false;
    // Reset
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = (char)('1' + i * 3 + j);
}

// Fonction pour augmenter le score du gagnant
void updateScores() {
    if (!draw) {
        if (turn == 'X') {
            scoreX++;
        }
        else {
            scoreO++;
        }
    }
}

// Main
int main() {
    char playAgain;

    do {
        // Main game loop
        resetGame();  // Reset le jeu pour le rematch
        while (gameOver()) {
            displayBoard();
            playerTurn();
        }

        // Determine le gagnant
        displayBoard();  // Display le tableau final
        if (!draw) {
            char winner = (turn == 'X') ? 'O' : 'X';
            cout << "GG! Le joueur " << winner << " a gagne!\n";
        }
        else {
            cout << "Draw. Faites une revanche.\n";
        }

        // Lance la fonction updatescore
        updateScores();

        // Display les scores
        cout << "Scores - Player X: " << scoreO << " | Player O: " << scoreX << "\n"; // oui j'ai eu un probleme la mais bon j'ai reglé comme ca et ca fonctionne :/

        // Propose une revanche
        cout << "allez, une ptite revanche ? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}