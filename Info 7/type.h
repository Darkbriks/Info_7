#ifndef TYPE
#define TYPE

#include <string>

struct type_board
{
    // Cette structure contient toutes les informations relatives à la position des pièces sur l'échiquier et à l'état de la partie.
    // Elle contient également des méthodes pour convertir la position des pièces en FEN et vice-versa.
    // Le plateau est représenté par un tableau 1D de 64 cases, chaque case contenant une pièce.
    // Les pièces sont représentées par un caractère, selon la notation FEN.
    // Les pièces blanches sont représentées par des caractères en majuscule, les pièces noires par des caractères en minuscule.
    // On considère que i = 0 correspond à la colonne a et j = 0 correspond à la ligne 1. On a ainsi par exemple i = 4 et j = 2 pour la case e3.
    // Pour passer d'un tableau 1D à un tableau 2D, on utilise la formule index = i + 8*j.
    // Pour passer d'un tableau 2D à un tableau 1D, on utilise les formules i = index % 8 et j = index / 8.
    
    // Attributes
    char *board = new char[64]; // Tableau de 64 cases qui contiennent les pièces
    std::string fen_other; // Chaîne de caractères qui contient les informations relatives à l'état de la partie.
    // L'etat est sous la forme suivante : "turn castle_short_white castle_long_white castle_short_black castle_long_black en_passant_i en_passant_j halfmove_dizaine halfmove_unite fullmove_dizaine fullmove_unite"

    // Constructor
    type_board(); // Initialise le plateau avec la position de départ des pièces.

    // Getters
    char get_piece(int i, int j) const; // Renvoie la pièce à la position i, j. Si i ou j est en dehors du tableau, renvoie '!'. Si la case est vide, renvoie ' '.
    char get_turn() const; // Renvoie le tour. Si le tour est aux blancs, renvoie 'w'. Si le tour est aux noirs, renvoie 'b'.
    std::string get_castling() const; // Renvoie les roques possibles. Si aucun roque n'est possible, renvoie '-'. Sinon, renvoie les roques possibles sous la forme "KQkq".
    std::string get_castling(char color) const; // Renvoie les roques possibles pour la couleur color. Si aucun roque n'est possible, renvoie '-'. Sinon, renvoie les roques possibles sous la forme "KQ" ou "kq".
    std::string get_en_passant() const; // Renvoie la case en passant. Si aucune case en passant n'est possible, renvoie '-'. Sinon, renvoie la case en passant sous la forme "e3".
    int get_halfmove() const; // Renvoie le nombre de coups joués depuis le dernier coup de pion ou de capture. Si aucun coup n'a été joué depuis le dernier coup de pion ou de capture, renvoie 0.
    int get_fullmove() const; // Renvoie le nombre de coups joués depuis le début de la partie. Si aucun coup n'a été joué depuis le début de la partie, renvoie 1.
    std::string get_fen() const; // Renvoie la position des pièces sous la forme d'une chaîne de caractères FEN.

    // Setters
    void set_piece(int i, int j, char piece); // Place la pièce piece à la position i, j. Si i ou j est en dehors du tableau, ne fait rien.
    void set_turn(char turn); // Définit le tour. Si turn est 'w', le tour est aux blancs. Si turn est 'b', le tour est aux noirs. Si turn est autre chose, ne fait rien.
    void set_castling(char castling, bool value); // Définit si le roque castling est possible. Si value est true, le roque est possible. Si value est false, le roque n'est pas possible. Si castling n'est pas 'K', 'Q', 'k' ou 'q', ne fait rien.
    void set_en_passant(std::string en_passant); // Définit la case en passant. Si en_passant est '-', aucune case en passant n'est possible. Sinon, en_passant doit être une case valide. Si en_passant n'est pas une case valide, ne fait rien.
    void set_halfmove(int halfmove); // Définit le nombre de coups joués depuis le dernier coup de pion ou de capture.
    void set_fullmove(int fullmove); // Définit le nombre de coups joués depuis le début de la partie.
    void set_board_with_fen(std::string fen); // Définit la position des pièces à partir d'une chaîne de caractères FEN.
    void set_board_with_array(char array[64]); // Définit la position des pièces à partir d'un tableau 1D de 64 cases.
};

struct type_mask
{
    // Attributes
    int *mask = new int[64];

    // Constructor
    type_mask();

    // Getters
    int get_mask(int i, int j) const;

    // Setters
    void set_mask(int i, int j, int value) const;
};

#endif