#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include "Rotor.h"
#include "Enigma.h"

int main()
{
    int rotorSettings[3]  = {0, 0, 0};
    int rotors[3]  = {1, 0, 0};
    int reflector = 0;
    std::vector<std::pair<char, char>> plugs = {{'A', 'D'}, {'P', 'F'}, {'G', 'H'}};

    std::string message;
    std::cout << "Enter a message to encrypt: ";
    Enigma* enigma = new Enigma(rotors, reflector, rotorSettings, plugs);
    std::cout << enigma->encodeMessage("A");
    while(true){};
}
