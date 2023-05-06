#include "Enigma.h"

Enigma::Enigma(int* rot, int ref, int* rotorSettings) {
    reflector = new Rotor(reflectorSelection[ref], 0, 0);
    rotors[2] = new Rotor(rotorSelection[rot[2]], rotorSettings[2], steppers[rot[2]], reflector);
    rotors[1] = new Rotor(rotorSelection[rot[1]], rotorSettings[1], steppers[rot[1]], rotors[2]);
    rotors[0] = new Rotor(rotorSelection[rot[0]], rotorSettings[0], steppers[rot[0]], rotors[1]);
    reflector->setPrev(rotors[2]);
    rotors[2]->setPrev(rotors[1]);
    rotors[1]->setPrev(rotors[0]);
}

Enigma::Enigma(int* rot, int ref, int* rotorSettings, const std::vector<std::pair<char, char>>& plugboard) : plugs(plugboard) {
    reflector = new Rotor(reflectorSelection[ref], 0, 0);
    rotors[2] = new Rotor(rotorSelection[rot[2]], rotorSettings[2], steppers[rot[2]], reflector);
    rotors[1] = new Rotor(rotorSelection[rot[1]], rotorSettings[1], steppers[rot[1]], rotors[2]);
    rotors[0] = new Rotor(rotorSelection[rot[0]], rotorSettings[0], steppers[rot[0]], rotors[1]);
    reflector->setPrev(rotors[2]);
    rotors[2]->setPrev(rotors[1]);
    rotors[1]->setPrev(rotors[0]);
}

char Enigma::encodeLetter(char letter){
    rotors[0]->rotate();
    if(plugs.empty()){
        return rotors[0]->encode(letter);
    }else{
        auto plugIt = std::find_if(plugs.begin(), plugs.end(),[letter](const std::pair<char, char>& plug) {
            return plug.first == letter || plug.second == letter;
        });

        if (plugIt != plugs.end()) {
            if (plugIt->first == letter) {
                letter = plugIt->second;
            } else {
                letter = plugIt->first;
            }
        }
        char encodedLetter = rotors[0]->encode(letter);

        plugIt = std::find_if(plugs.begin(), plugs.end(),[encodedLetter](const std::pair<char, char>& plug) {
            return plug.first == encodedLetter || plug.second == encodedLetter;
        });

        if (plugIt != plugs.end()) {
            if (plugIt->first == encodedLetter) {
                encodedLetter = plugIt->second;
            } else {
                encodedLetter = plugIt->first;
            }
        }
        return encodedLetter;
    }
}

std::string Enigma::encodeMessage(std::string message){
    std::string encodedMessage = "";
    for(int i = 0; i < message.length(); i++){
        encodedMessage += this->encodeLetter(message[i]);
    }
    return encodedMessage;
}