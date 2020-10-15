#ifndef HALMAZ_HPP
#define HALMAZ_HPP

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Halmaz
{
  public:
    Halmaz();
    virtual ~Halmaz();
    bool TartalmazE(const T elem);
    void Halmazba(const T elem);
    void Halmazbol(const T elem);
    bool UresE();
    void Ures();
    Halmaz Metszet(Halmaz &masik);
    Halmaz Unio(Halmaz &masik);
    Halmaz Kulonbseg(Halmaz &masik);
    bool ReszhalmazaE(Halmaz &masik);

    // Megadjuk, hogy a SABLON operator<< legyen bar�t.
    // Az�rt U, mert a T m�r foglalt az oszt�ly �ltal
    template<typename U>
    friend ostream& operator<<(ostream &os, const Halmaz<U> &h);
  private:
    vector<T> elemek;
};

// Megadjuk, hogy konkr�tan milyen t�pusokra m�k�dj�n
template class Halmaz<int>;
template class Halmaz<char>;

#endif // HALMAZ_HPP
