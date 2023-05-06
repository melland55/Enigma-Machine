#ifndef ROTOR_H
#define ROTOR_H

class Rotor {
private:
    char wiring[26];
    char wiringInverse[26];
    int position;
    int stepper;
    Rotor* next;
    Rotor* prev;
public:
    Rotor(char arr[], int pos, int step);
    Rotor(char arr[], int pos, int step, Rotor* r);
    char encode(char letter);
    char decode(char letter);
    void rotate();
    void setPrev(Rotor* r);
};

#endif // ROTOR_H