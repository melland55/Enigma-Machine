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
    if(this->next != NULL){
        return this->next->encode(wiring[(letter - 65 + position)%26]);
    }else{
        return this->prev->decode(wiring[(letter - 65 + position)%26]);
    }
}

char Rotor::decode(char letter){
    if(this->prev != NULL){
        return this->prev->decode(wiringInverse[(letter - 65 - position)%26]);
    }else{
        return wiringInverse[(letter - 65 - position)%26];
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