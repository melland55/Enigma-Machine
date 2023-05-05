#include <iostream>
#include <vector>
#include <algorithm>
#include <String>
using namespace std;

class Rotor{
private:
    std::vector<char> wiring;
    int position;
    Rotor* next;
    int stepper;
public:
    Rotor(std::vector<char> rotor, int pos, int step) {
        wiring = rotor;
        position = pos;
        stepper = step;
        next = NULL;
        for(int i = pos; i < pos; i++){
            rotate();
        }
    }

    Rotor(std::vector<char> rotor, int pos, int step, Rotor* r) {
        wiring = rotor;
        position = pos;
        stepper = step;
        next = r;
        for(int i = pos; i < pos; i++){
            rotate();
        }
    }

    char encode(char letter) {
        return wiring[(letter - 65 + position)%26];
    }

    char decode(char letter){
        return find(wiring.begin(), wiring.end(),(char)((letter - 65 + position)%26 + 65)) - wiring.begin() + 65;
    }

    void rotate() {
        char lastChar = wiring.back();
        wiring.pop_back();
        wiring.insert(wiring.begin(), lastChar);
        if(stepper == position && next != NULL){
            next->rotate();
        }
        position = (position+1)%26;
    }
};


// Function to rotate the rotor
void rotateRotor(vector<char>& rotor)
{
    char lastChar = rotor.back();
    rotor.pop_back();
    rotor.insert(rotor.begin(), lastChar);
}

// Function to encrypt a letter
char encryptLetter(char letter, vector<vector<char>> rotors)
{
    // Pass the letter through each rotor in sequence
    for (int i = 0; i < rotors.size(); i++) {
        letter = rotors[(i+1) % rotors.size()][letter - 65];
    }
    return letter;
}

int main()
{
    // Create three rotors with different sets of characters
    vector<vector<char>> rotors = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
        {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'},
        {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'}
    };

    // Set the initial position of the rotors
    vector<int> rotorPositions = {0, 0, 0};

    // Input a message to encrypt
    string message;
    cout << "Enter a message to encrypt: ";
    getline(cin, message);
    Rotor* r = new Rotor(rotors[1], 0, 2);
    Rotor* r2 = new Rotor(rotors[1], 0, 2, r);
    Rotor* r3 = new Rotor(rotors[1], 0, 2, r2);\
    cout << r->encode(r2->encode(r3->encode('A')));

    // Encrypt each letter in the message
    // for (int i = 0; i < message.length(); i++) {
    //     // Ignore non-alphabetic characters
    //     if (!isalpha(message[i])) {
    //         continue;
    //     }

    //     // Convert the letter to uppercase
    //     char letter = toupper(message[i]);
    //     char newLetter = encryptLetter(letter, rotors);
    //     cout << newLetter;
    //     // Rotate the rotors
    //     for (int j = 0; j < rotors.size(); j++) {
    //         rotateRotor(rotors[j]);
    //         rotorPositions[j]++;
    //         rotorPositions[j] %= 26;

    //         // Shift the rotor positions of the adjacent rotors if needed
    //         if (j < rotors.size() - 1 && rotorPositions[j] == (rotors[j].size() - 1)) {
    //             rotateRotor(rotors[j+1]);
    //         }
    //     }
    // }
}
