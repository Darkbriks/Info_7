#include "../Header/stockfish.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <array>

using namespace std;

// Fonction pour communiquer avec Stockfish
string communicate_with_stockfish(const string command)
{
    string fullCommand = "./../Stockfish/stockfish-windows.exe " + command + " 2>&1"; // 2>&1 pour rediriger les erreurs vers la sortie standard

    // Exécuter Stockfish en tant que processus externe
    ostringstream output;
    array<char, 128> buffer;
    FILE* pipe = _popen(fullCommand.c_str(), "r");
    if (!pipe)
    {
        // Gérer l'erreur d'exécution de Stockfish
        return "Erreur lors de l'exécution de Stockfish";
    }

    // Lire les données de sortie de Stockfish
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    {
        output << buffer.data();
    }

    _pclose(pipe);

    return output.str();
}