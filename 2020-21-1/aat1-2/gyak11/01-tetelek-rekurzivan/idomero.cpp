#include "idomero.hpp"
#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>

using namespace std;

Idomero::Idomero(int elemek_szama, string nev)
{
  ElemekSzama = elemek_szama;
  Nev = nev;
  KezdesIdo = 0;
  BefejezesIdo = 0;
  OsszehasonlitasokSzama = 0;
  MozgatasokSzama = 0;
  AktualisMelyseg = 0;
  RekurzioMelysege = 0;
}

void Idomero::Kezd()
{
  KezdesIdo = clock();
}

void Idomero::Befejez()
{
  BefejezesIdo = clock();
}

void Idomero::UjOsszehasonlitas(int db)
{
  OsszehasonlitasokSzama += db;
}

void Idomero::UjMozgatas(int db)
{
  MozgatasokSzama += db;
}

void Idomero::UjRekurzio()
{
  AktualisMelyseg += 1;
  if (AktualisMelyseg > RekurzioMelysege)
  {
    RekurzioMelysege = AktualisMelyseg;
  }
}

void Idomero::RekurzioVege()
{
  AktualisMelyseg -= 1;
}

int Idomero::GetOsszehasonlitasokSzama()
{
  return OsszehasonlitasokSzama;
}

int Idomero::GetMozgatasokSzama()
{
  return MozgatasokSzama;
}

int Idomero::GetRekurzioMelysege()
{
  return RekurzioMelysege;
}

float Idomero::GetElteltIdo()
{
  return (float)(BefejezesIdo - KezdesIdo) / CLOCKS_PER_SEC;
}

float Idomero::GetMozgatasokAranya()
{
  return (float)MozgatasokSzama / ElemekSzama;
}

float Idomero::GetMozgatasokNegyzetesAranya()
{
  return (float)MozgatasokSzama / (ElemekSzama * ElemekSzama);
}

void Idomero::SzovegesStatisztika()
{
  cout << Nev << endl;
  cout << "Bemenet elemsz�ma            " << ElemekSzama << endl;
  cout << "Eltelt id�:                  " << GetElteltIdo() << "s" << endl;
  cout << "�sszehasonl�t�sok sz�ma:     " << OsszehasonlitasokSzama << endl;
  cout << "Mozgat�sok sz�ma:            " << MozgatasokSzama << endl;
  cout << "Mozgat�sok ar�nya:           " << GetMozgatasokAranya() << endl;
  cout << "Mozgat�sok n�gyzetes ar�nya: " << GetMozgatasokNegyzetesAranya() << endl;
  cout << "Rekurzi� maxim�lis m�lys�ge: " << RekurzioMelysege << endl;
  cout << endl;
}

string Idomero::CSVStatisztika()
{
  ostringstream oss;
  oss << Nev << ';'
      << ElemekSzama << ';'
      << GetElteltIdo() << ';'
      << OsszehasonlitasokSzama << ';'
      << MozgatasokSzama << ';'
      << GetMozgatasokAranya() << ';'
      << GetMozgatasokNegyzetesAranya() << ';'
      << RekurzioMelysege << endl;
  return oss.str();
}

