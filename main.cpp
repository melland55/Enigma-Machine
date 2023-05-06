#include <iostream>
#include <string>
#include "Rotor.h"

class Enigma {
private:
    Rotor* rotors[3];
    Rotor* reflector;
    char rotorSelection[3][26] = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
        {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'},
        {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'}};
    char steppers[3] = { 3, 3, 3};
    char reflectorSelection[3][26] = {
        {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'},
        {'Y', 'R', 'U', 'H', 'Q', 'S', 'L', 'D', 'P', 'X', 'N', 'G', 'O', 'K', 'M', 'I', 'E', 'B', 'F', 'Z', 'C', 'W', 'V', 'J', 'A', 'T'},
        {'F', 'V', 'P', 'J', 'I', 'A', 'O', 'Y', 'E', 'D', 'R', 'Z', 'X', 'W', 'G', 'C', 'T', 'K', 'U', 'Q', 'S', 'B', 'N', 'M', 'H', 'L'}};
public:
    Enigma(int* rot, int ref, int* rotorSettings) {
        reflector = new Rotor(reflectorSelection[ref], 0, 0);
        rotors[2] = new Rotor(rotorSelection[rot[2]], rotorSettings[2], steppers[rot[2]], reflector);
        rotors[1] = new Rotor(rotorSelection[rot[1]], rotorSettings[1], steppers[rot[1]], rotors[2]);
        rotors[0] = new Rotor(rotorSelection[rot[0]], rotorSettings[0], steppers[rot[0]], rotors[1]);
        reflector->setPrev(rotors[2]);
        rotors[2]->setPrev(rotors[1]);
        rotors[1]->setPrev(rotors[0]);
    }

    char encodeLetter(char letter){
        rotors[0]->rotate();
        return rotors[0]->encode(letter);
    }

    std::string encodeMessage(std::string message){
        std::string encodedMessage = "";
        for(int i = 0; i < message.length(); i++){
            encodedMessage += this->encodeLetter(message[i]);
        }
        return encodedMessage;
    }
};

int main()
{
    // Set the initial position of the rotors
    int rotorSettings[3]  = {0, 0, 0};
    int rotors[3]  = {1, 0, 0};
    int reflector = 0;

    std::string message;
    std::cout << "Enter a message to encrypt: ";
    Enigma* enigma = new Enigma(rotors, reflector, rotorSettings);
    std::cout << enigma->encodeMessage("XMQSHEOBHPUCZNGUQVNYHTFQJUXMQSHEOBHPUCZNGUQVNYHTFQJUXMQSHEOBHPUCZNGUQVNYHTFQJUXMQSHEOBHPUCZNGUQVNYHTFQJUXMQSHEOBHPUCZNGUQVNYHTFQJUXM");
    while(true){};
}
