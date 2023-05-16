#include "../Header/type.h"
#include <iostream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

/**
 * @brief Return a random number between a and b
 * @param a the minimum number
 * @param b the maximum number
 * @return int, a random number between a and b
 */
int random(const int a, const int b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

#pragma region Type_board
#pragma region Getters
/**
 * \brief return the piece at the position (i, j) with the following convention :
 * \n i = 0 corresponds to the column a
 * \n j = 0 corresponds to the row 1 \n
 * \n If the position is invalid, return '!'
 * \n If the position is empty, return ' '
 * \param i the column
 * \param j the row
 * \return char, the piece at the position (i, j)
 */
char type_board::get_piece(const int i, const int j) const
{
    if (i < 0 || i > 7 || j < 0 || j > 7) {return '!';} // If the position is invalid, return '!'
    return board[8*j + i];
}

/**
 * \brief Return the turn with the following convention :
 * \n 'w' for white
 * \n 'b' for black
 * \return char, the turn
 */
char type_board::get_turn() const {return fen_other[0];}

/**
 * \brief Return the castling rights with the following convention :
 * \n 'K' if white can castle short
 * \n 'Q' if white can castle long
 * \n 'k' if black can castle short
 * \n 'q' if black can castle long
 * \n '-' if no castling rights
 * \return string, the castling rights 
 */
string type_board::get_castling() const
{
    stringstream castling;
    if (fen_other[1] == 'K') {castling << "K";}
    if (fen_other[2] == 'Q') {castling << "Q";}
    if (fen_other[3] == 'k') {castling << "k";}
    if (fen_other[4] == 'q') {castling << "q";}
    if (castling.str() == "") {castling << "-";} // If no castling rights, add a dash
    return castling.str();
}

/**
 * \brief Return the castling rights for the specified color with the following convention :
 * \n 'K' if the color can castle short
 * \n 'Q' if the color can castle long
 * \n '-' if the color can't castle
 * \n If the color is invalid, return an empty string
 * \param color 'w' or 'b', in minuscule
 * \return string, the castling rights for the specified color
 */
string type_board::get_castling(const char color) const
{
    if (color != 'w' && color != 'b') {return "";}
    stringstream castling;
    castling << fen_other[1 + (color == 'b')*2] << fen_other[2 + (color == 'b')*2]; // Add the castling rights to the string stream (0 = false, 1 = true)
    return castling.str();
}

/**
 * \brief Return the en passant square with the following convention :
 * \n The first character is the column
 * \n The second character is the row
 * \n If there is no en passant, return a dash
 * \return string, the en passant square
 */
string type_board::get_en_passant() const
{
    stringstream en_passant;
    en_passant << fen_other[5] << fen_other[6];
    if (en_passant.str() == "--") {return "-";} // If no en passant, return a dash
    return en_passant.str();
}

/**
 * \brief Return the halfmove clock.
 * \n The halfmove clock is the number since the last capture or pawn move.
 * \return int, the halfmove clock
 */
int type_board::get_halfmove() const
{
    stringstream halfmove;
    halfmove << fen_other[7] << fen_other[8];
    int halfmove_int; halfmove >> halfmove_int;
    return halfmove_int;
}

/**
 * \brief Return the fullmove number.
 * \n The fullmove number is the number of the move, starting at 1, and incremented after black's move.
 * \return int, the fullmove number
 */
int type_board::get_fullmove() const
{
    stringstream fullmove;
    fullmove << fen_other[9] << fen_other[10];
    int fullmove_int; fullmove >> fullmove_int;
    return fullmove_int;
}

/**
 * \brief Return the FEN string.
 * \n The FEN string is the board, the turn, the castling rights, the en passant square, the halfmove clock and the fullmove number.
 * \n An example of FEN string is : "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 * \return string, the FEN string
 */
string type_board::get_fen() const
{
    stringstream fen_board;
    for (int i = 0; i < 8; i++)
    {
        int empty = 0; // Create an int to store the number of empty squares
        for (int j = 0; j < 8; j++)
        {
            if (board[8*i + j] == ' ') {empty++;} // If the square is empty, increment the number of empty squares
            else
            {
                if (empty > 0) {fen_board << empty; empty = 0;} // If there are empty squares before, add the number of empty squares to the string stream and reset the number of empty squares
                fen_board << board[8*i + j];
            }
        }
        if (empty > 0) {fen_board << empty;}  // If there are empty squares at the end of the row, add the number of empty squares to the string stream
        if (i < 7) {fen_board << '/';} // If it's not the last row, add a slash to the string stream
    }
    
    stringstream fen;
    fen << fen_board.str() << ' ' << get_turn() << ' ' << get_castling() << ' ' << get_en_passant() << ' ' << to_string(get_halfmove()) << ' ' << to_string(get_fullmove());
    return fen.str();
}
#pragma endregion

#pragma region Setters
/**
 * \brief Set a piece on the board at the specified position.
 * \n If the position is invalid, do nothing.
 * \n WARNING : the piece is not checked, so it must be valid.
 * \param i the column
 * \param j the row
 * \param piece 
 */
void type_board::set_piece(const int i, const int j, const char piece)
{
    if (i < 0 || i > 7 || j < 0 || j > 7) {return;}
    board[8*j + i] = piece;
}

/**
 * \brief Set the turn.
 * \n WARNING : the turn is not checked, so it must be valid.
 * \param turn 'w' or 'b'
 */
void type_board::set_turn(const char turn) {fen_other[0] = turn;}

/**
 * \brief Set the castling rights for the specified color.
 * \param color 'w' or 'b' for set the castle short, and 'W' or 'B' for set the castle long
 * \param castling true if the player can castle, false otherwise
 */
void type_board::set_castling(const char color, const bool castling)
{
    if (color == 'w') {castling ? fen_other[1] = 'K' : fen_other[1] = '-';} // true = 'K', false = '-'
    else if (color == 'b') {castling ? fen_other[3] = 'k' : fen_other[3] = '-';}
    else if (color == 'W') {castling ? fen_other[2] = 'Q' : fen_other[2] = '-';}
    else if (color == 'B') {castling ? fen_other[4] = 'q' : fen_other[4] = '-';}
}

/**
 * \brief Set the en passant square.
 * \n WARNING : the en passant square is not checked, so it must be valid.
 * \param en_passant the en passant square with the following convention :
 * \n The first character is the column
 * \n The second character is the row
 * \n If there is no en passant, set a dash
 */
void type_board::set_en_passant(const string en_passant) {fen_other[5] = en_passant[0]; fen_other[6] = en_passant[1];}

/**
 * \brief Set the halfmove clock.
 * \n WARNING : the halfmove clock is not checked, so it must be valid.
 * \param halfmove the halfmove clock
 */
void type_board::set_halfmove(const int halfmove) {fen_other[7] = to_string(halfmove)[0]; fen_other[8] = to_string(halfmove)[1];}

/**
 * \brief Set the fullmove number.
 * \n WARNING : the fullmove number is not checked, so it must be valid.
 * \param fullmove the fullmove number
 */
void type_board::set_fullmove(const int fullmove) {fen_other[9] = to_string(fullmove)[0]; fen_other[10] = to_string(fullmove)[1];}

/**
 * \brief Set the board with a FEN string.
 * \n The FEN string is the board, the turn, the castling rights, the en passant square, the halfmove clock and the fullmove number.
 * \n An example of FEN string is : "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 * \n WARNING : the FEN string is not checked, so it must be valid.
 * \param fen the FEN string
 */
void type_board::set_board_with_fen(const string fen)
{
    // Set the board
    int i = 0; int j = 7; string fen_board = fen.substr(0, fen.find(' '));
    // Inversion du plateau, car le FEN est donné de la ligne 8 à la ligne 1
    //reverse(fen_board.begin(), fen_board.end());

    // Set the board. The FEN board is given from the 8th rank to the 1st rank, so we assign the board from the last cell to the first cell
    for (int k = 0; k < fen_board.length(); k++)
    {
        if (fen_board[k] == ' ') {break;}
        if (fen_board[k] == '/') {i = 0; j--;}
        else if (fen_board[k] >= '1' && fen_board[k] <= '8') {for (int l = 0; l < fen_board[k] - '0'; l++) {set_piece(i, j, ' '); i++;}}
        else {set_piece(i, j, fen_board[k]); i++;}
    }
    
    // Set the other FEN parameters
    string fen_other_pure = fen.substr(fen.find(' ') + 1); // = w KQkq - 0 1
    fen_other = "wKQkq--0001";
    set_turn(fen_other_pure[0]);
    
    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = KQkq - 0 1
    set_castling('w', fen_other_pure[0] == 'K');
    set_castling('W', fen_other_pure[0] == 'Q' || fen_other_pure[1] == 'Q');
    set_castling('b', fen_other_pure[0] == 'k' || fen_other_pure[1] == 'k' || fen_other_pure[2] == 'k');
    set_castling('B', fen_other_pure[0] == 'q' || fen_other_pure[1] == 'q' || fen_other_pure[2] == 'q' || fen_other_pure[3] == 'q');

    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = - 0 1
    if (fen_other_pure[0] != '-') {set_en_passant(fen_other_pure.substr(0, 2));} else {set_en_passant("--");}

    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = 0 1
    set_halfmove(stoi(fen_other_pure.substr(0, fen_other_pure.find(' '))));

    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = 1
    set_fullmove(stoi(fen_other_pure));
}

/**
 * \brief Set the board with an array.
 * \n The array is the board.
 * \n The array must be a 64 characters array.
 * \n An example of array is : "RNBQKBNRPPPPPPPP--/28/--pppppppprnbqkbnr"
 * \n WARNING : the array is not checked, so it must be valid.
 * \param array the array
 */
void type_board::set_board_with_array(char array[64]) {for (int i = 0; i < 64; i++) {board[i] = array[i];}}
#pragma endregion

#pragma region Constructors
/**
 * \brief Default constructor.
 * \n Initialize the board to the starting position.
 */
type_board::type_board()
{
    board = new char[64];
    fen_other = "wKQkq--0001";
    cout << "Board initialized" << endl;
}
#pragma endregion
#pragma endregion

#pragma region Type_mask
/**
 * \brief Get the mask at the given position.
 * \n If the position is out of bounds, return -1.
 * \param i the column
 * \param j the row
 * \return the mask at the given position
 */
int type_mask::get_mask(const int i, const int j) const {return (i >= 0 && i < 8 && j >= 0 && j < 8) ? mask[8*j + i] : -1;}

/**
 * \brief Set the mask at the given position.
 * \n If the position is out of bounds, do nothing.
 * \n WARNING : the mask is not checked, so it must be valid.
 * \param i the column
 * \param j the row
 * \param value the value to set
 */
void type_mask::set_mask(const int i, const int j, const int value) const {if (i >= 0 && i < 8 && j >= 0 && j < 8) {mask[8*j + i] = value;}}

/**
 * \brief Default constructor.
 * \n Initialize the mask to 0.
 */
type_mask::type_mask() {mask = new int[64]; for (int i = 0; i < 64; i++) {mask[i] = 0;}}
#pragma endregion

#pragma region Type_maillon
/**
 * \brief Get the value of the maillon.
 * \return the value of the maillon
 */
string type_maillon::get_val() const {return val;}

/**
 * \brief Get the value of the i-th maillon.
 * \n If the i-th maillon does not exist, return "".
 * \param i the index of the maillon
 * \return the value of the i-th maillon
 */
string type_maillon::get_val(const int i) const
{
    if (i == 0) {return val;}
    else if (next == NULL) {return "";}
    else {return next->get_val(i - 1);}
}

/**
 * \brief Get the next maillon.
 * \return the next maillon
 */
type_maillon* type_maillon::get_next() const {return next;}

/**
 * \brief Set the value of the maillon.
 * \param value the value to set
 */
void type_maillon::set_val(const string value) {val = value;}

/**
 * \brief Set the next maillon.
 * \param next the next maillon
 */
void type_maillon::set_next(type_maillon* next) {this->next = next;}

/**
 * \brief Default constructor.
 * \n Initialize the value to "" and the next maillon to NULL.
 */
type_maillon::type_maillon() {val = ""; next = NULL;}

/**
 * \brief Constructor with a value.
 * \n Initialize the value to the given value and the next maillon to NULL.
 * \param value the value
 */
type_maillon::type_maillon(const string value) {val = value; next = NULL;}

/**
 * \brief Constructor with a value and a next maillon.
 * \n Initialize the value to the given value and the next maillon to the given next maillon.
 * \param value the value
 * \param next the next maillon
 */
type_maillon::type_maillon(const string value, type_maillon* next) {val = value; this->next = next;}

/**
 * \brief Destructor.
 * \n Delete this maillon and all the next maillons.
 */
type_maillon::~type_maillon() {delete next;}

/**
 * \brief Add a maillon at the end of the list.
 * \param val the value of the maillon to add
 */
void type_maillon::add(std::string val)
{
    if (next == NULL) {next = new type_maillon(val);} // If the next maillon is NULL, we add the maillon at the end
    else {next->add(val);} // Else, we call the function on the next maillon
}

/**
 * \brief Remove the last maillon of the list.
 */
void type_maillon::remove() {if (next != NULL) {if (next->next == NULL) {delete next; next = NULL;} else {next->remove();}}}

/**
 * \brief Get the value of the last maillon of the list.
 * \return the value of the last maillon of the list
 */
string type_maillon::last() const {return next == NULL ? val : next->last();}

/**
 * \brief Remove the last maillon of the list and return its value.
 * \return the value of the last maillon of the list
 */
string type_maillon::pop() {string res = last(); remove(); return res;}

/**
 * \brief Print the list.
 */
void type_maillon::print() const {cout << get_val() << " "; if (next != NULL) {next->print();}}


/**
 * \brief Get the size of the list.
 * \return the size of the list
 */
int type_maillon::size() const {return next == nullptr ? 1 : 1 + next->size();}
#pragma endregion

type_history::type_history()
{
    board_history = new type_maillon("rnbqkbnr/pppppppp/K7/8/8/8/PPPPPPPP/RNBQ1BNR w KQkq - 0 1");
    move_history = new type_maillon();
}

type_history::~type_history()
{
    delete(board_history); delete(move_history);
}


/**
 * \brief Get the chained list that contains the history of the moves.
 * \return the chained list that contains the history of the moves
 */
type_maillon* type_history::get_board_historique() const {return board_history;}

string type_history::get_board_historique(int i) const {return board_history->get_val(i);}


/**
 * \brief Get the chained list that contains the history of the moves.
 * \return the chained list that contains the history of the moves
 */
type_maillon* type_history::get_moves_historique() const {return move_history;}

string type_history::get_moves_historique(int i) const {return move_history->get_val(i);}

#pragma region Type_history

/**
 * \brief Set the chained list that contains the history of the board.
 * \param H the chained list that contains the history of the board
 */
void type_history::set_board_historique(type_maillon* H) {move_history = H;}
/**
 * \brief Set the chained list that contains the history of the board.
 * \param H the chained list that contains the history of the board
 */
void type_history::set_moves_historique(type_maillon* H) {move_history = H;}


void type_history::add_board_history(string val) {board_history->add(val);}
void type_history::add_moves_history(string val) {move_history->add(val);}



#pragma endregion

#pragma region Type_game
/**
 * \brief Get the board.
 * \return the board
 */
type_board type_game::get_board() const {return board;}

/**
 * \brief Get the mask.
 * \return the mask
 */
type_mask type_game::get_mask() const {return mask;}

/**
 * \brief Get the chained list that contains the history of the moves.
 * \return the chained list that contains the history of the moves
 */
type_maillon type_game::get_pile_historique() const {return pile_historique;}

/**
 * \brief Set the board.
 * \param board the board
 */
void type_game::set_board(const type_board board) {this->board = board;}

/**
 * \brief Set the mask.
 * \param mask the mask
 */
void type_game::set_mask(const type_mask mask) {this->mask = mask;}

/**
 * \brief Set the chained list that contains the history of the moves.
 * \param pile_historique the chained list that contains the history of the moves
 */
void type_game::set_pile_historique(const type_maillon pile_historique) {this->pile_historique = pile_historique;}

/**
 * \brief Default constructor.
 * \n Initialize the board to the default board, the mask to 0 and the chained list to NULL.
 */
type_game::type_game() {board = type_board(); mask = type_mask(); pile_historique = type_maillon();}

/**
 * \brief Constructor with a board.
 * \n Initialize the board to the given board, the mask to 0 and the chained list to NULL.
 * \param board the board
 */
type_game::type_game(const type_board board) {this->board = board; mask = type_mask(); pile_historique = type_maillon();}

/**
 * \brief Constructor with a board and a mask.
 * \n Initialize the board to the given board, the mask to the given mask and the chained list to NULL.
 * \param board the board
 * \param mask the mask
 */
type_game::type_game(const type_board board, const type_mask mask) {this->board = board; this->mask = mask; pile_historique = type_maillon();}

/**
 * \brief Constructor with a board, and a chained list that contains the history of the moves.
 * \n Initialize the board to the given board, the mask to 0 and the chained list to the given chained list.
 * \param board the board
 * \param pile_historique the chained list that contains the history of the moves
 */
type_game::type_game(const type_board board, const type_maillon pile_historique) {this->board = board; mask = type_mask(); this->pile_historique = pile_historique;}

/**
 * \brief Constructor with a board, a mask and a chained list that contains the history of the moves.
 * \n Initialize the board to the given board, the mask to the given mask and the chained list to the given chained list.
 * \param board the board
 * \param mask the mask
 * \param pile_historique the chained list that contains the history of the moves
 */
type_game::type_game(const type_board board, const type_mask mask, const type_maillon pile_historique) {this->board = board; this->mask = mask; this->pile_historique = pile_historique;}
#pragma endregion

#pragma region A garder ? (depend de type_maillon)
void createListeChaine( type_maillon** Tete,int N) {
    type_maillon* ptr;
    //cas spécial pour le premier élément
    if (N <= 0) { 
        *Tete = NULL;
    }
    else {
        ptr = new type_maillon; 
        *Tete = ptr; 
        ptr->val= "";
        N=N-1; //on a 1 élément de moins à créer
        while (N > 0) {
            ptr->next = new type_maillon; //on crée un nouvel élément
            ptr = ptr->next; //ptr pointe le nouvel élément
            ptr->val = "";
            N = N - 1; //on a 1 élément de moins à créer
        }
        ptr->next = NULL; //on fait pointer le dernier élément vers NULL
    }
}
void afficherListeChaine(type_maillon* LT) {
    cout << "FONCTION affiche :" << endl;
    while (LT->next != NULL) {
        cout << LT->val;
        if (LT->next->next != NULL) {
            cout << " -> ";
        }
        LT = LT->next;
    }
    cout << endl;
}

bool inserePositionChaine(type_maillon** LT, int P, string valeur) {
    if (P < 0) {
        return false;
    }
    type_maillon* N = new type_maillon;
    N->val = valeur;
    N->next = NULL;
    if(P==0){
        N->next = *LT;
        *LT = N;
        return true;
    }
    type_maillon* Np = NULL;
    type_maillon* Nc = *LT;
    for (int i = 0; P > i; i++) {
        if (Nc == NULL) {
            return false;
        }
        Np = Nc;
        Nc = Nc->next;
    }
    N->next = Nc;
    Np->next = N;
    return true;
}
void recopieListeChaine(type_maillon* LT, type_maillon** LTc) {
    *LTc = NULL;
    while (LT != NULL) {
        type_maillon* N = new type_maillon;
        N->val = LT->val;
        N->next = NULL;
        if (*LTc == NULL) {
            *LTc = N;
        }
        else {
            type_maillon* E = *LTc;
            while (E->next != NULL) {
                E = E->next;
            }
            E->next = N;
        }
        LT = LT->next;
    }
}
#pragma endregion
