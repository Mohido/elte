#ifndef PONT_HPP_INCLUDED
#define PONT_HPP_INCLUDED

#include <iostream>

using namespace std;

// Oszt�ly
class Pont
{
  public:
    Pont(); // Konstruktor
    Pont(float new_x, float new_y);
    Pont(const Pont &p); // Copy konstruktor
    float GetX();
    void SetX(float new_x);
    float GetY();
    void SetY(float new_y);
    void Nagyit(float arany); // Met�dus
    float Tavolsag(const Pont &p);
    friend Pont operator+(const Pont &p1, const Pont &p2); // Friend f�ggv�ny
    friend ostream& operator<<(ostream &os, const Pont &p);
  private:
    float x; // Mez�, attrib�tum, field, property, attribute
    float y;
};

// L�that�s�g: private, public, (protected)
// Getter-Setter
// Konstruktor - inicializ�l�s (kezd��rt�kek be�ll�t�sa)

#endif // PONT_HPP_INCLUDED
