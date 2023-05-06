#include "Rotor.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

Rotor::Rotor(char arr[], int pos, int step) {
    position = pos;
    stepper = step;
    next = nullptr;
    prev = nullptr;
    for(int i = 0; i < 26; i++){
        wiring[i] = arr[i];
        wiringInverse[arr[i]-65] = i + 65;
    }
}

Rotor::Rotor(char arr[], int pos, int step, Rotor* r) {
    position = pos;
    stepper = step;
    next = r;
    prev = nullptr;
    for(int i = 0; i < 26; i++){
        wiring[i] = arr[i];
        wiringInverse[arr[i]-65] = i + 65;
    }
}

char Rotor::encode(char letter) {
    int c = wiring[(letter - 65 + position)%26] - 65 - position;
    if(this->next != NULL){
        return this->next->encode((c + (c < 0 ? 26 : 0)) + 65);
    }else{
        return this->prev->decode((c + (c < 0 ? 26 : 0)) + 65);
    }
}

char Rotor::decode(char letter){
    int c = wiringInverse[(letter - 65 + position)%26] - 65 - position;
    if(this->prev != NULL){
        return this->prev->decode((c + (c < 0 ? 26 : 0)) + 65);
    }else{
        return ((c + (c < 0 ? 26 : 0)) + 65);
    }
}

void Rotor::rotate() {
    if(this->next != NULL){
        if(position == stepper){
            this->next->rotate();
        }
        position = (position + 1) % 26;
    }
}

void Rotor::setPrev(Rotor* r) {
    prev = r;
}