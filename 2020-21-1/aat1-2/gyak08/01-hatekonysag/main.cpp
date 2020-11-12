#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "bemenet.hpp"
#include "idomero.hpp"

using namespace std;

string egyszeru_cseres_rendezes(vector<int> &bemenet)
{
  Idomero idomero(bemenet.size(), "Egyszer� cser�s rendez�s");

  idomero.Kezd();
  for (int i = 0; i < bemenet.size() - 1; ++i)
  {
    for (int j = i + 1 ; j < bemenet.size(); ++j)
    {
      if (bemenet.at(j) < bemenet.at(i))
      {
        int temp = bemenet.at(i);
        bemenet.at(i) = bemenet.at(j);
        bemenet.at(j) = temp;

        idomero.UjMozgatas(3);
      }
      idomero.UjOsszehasonlitas(1);
    }
  }
  idomero.Befejez();
  idomero.SzovegesStatisztika();

  return idomero.CSVStatisztika();
}

string maximum_kivalasztasos_rendezes(vector<int> &bemenet)
{
  Idomero idomero(bemenet.size(), "Maximum kiv�laszt�sos rendez�s");

  idomero.Kezd();
  for (int i = 0; i < bemenet.size() - 1; ++i)
  {
    int minind = i;
    for (int j = i + 1; j < bemenet.size(); ++j)
    {
      if (bemenet.at(j) < bemenet.at(minind))
      {
        minind = j;
      }
      idomero.UjOsszehasonlitas(1);
    }

    // Ha nincs j� helyen a vizsg�lt elem
    if (i != minind)
    {
      int temp = bemenet.at(i);
      bemenet.at(i) = bemenet.at(minind);
      bemenet.at(minind) = temp;

      idomero.UjMozgatas(3);
    }
  }
  idomero.Befejez();
  idomero.SzovegesStatisztika();

  return idomero.CSVStatisztika();
}

string buborekos_rendezes(vector<int> &bemenet)
{
  Idomero idomero(bemenet.size(), "Bubor�kos rendez�s");

  idomero.Kezd();
  for (int i = bemenet.size(); i > 1; --i)
  {
    for (int j = 0; j < i - 1; ++j)
    {
      if (bemenet.at(j) > bemenet.at(j + 1))
      {
        int temp = bemenet.at(j + 1);
        bemenet.at(j + 1) = bemenet.at(j);
        bemenet.at(j) = temp;

        idomero.UjMozgatas(3);
      }
      idomero.UjOsszehasonlitas(1);
    }
  }
  idomero.Befejez();
  idomero.SzovegesStatisztika();

  return idomero.CSVStatisztika();
}

int main()
{
  // Nyelv be�ll�t�s
  setlocale(LC_ALL, "Hungarian");
  // V�letlensz�m gener�tor init
  srand(time(nullptr));

  vector<int> bemenet;

  ofstream file("stat.csv");
  // CSV fejl�c
  file << "N�v" << ';'
       << "Elemek sz�ma" << ';'
       << "Eltelt id�" << ';'
       << "�sszehasonl�t�sok sz�ma" << ';'
       << "Mozgat�sok sz�ma" << ';'
       << "Mozgat�sok ar�nya" << ';'
       << "Mozgat�sok n�gyzetes ar�nya" << endl;

  bemenet = VeletlenszeruBemenet(100);
  file << maximum_kivalasztasos_rendezes(bemenet);
  bemenet = VeletlenszeruBemenet(250);
  file << maximum_kivalasztasos_rendezes(bemenet);
  bemenet = VeletlenszeruBemenet(500);
  file << maximum_kivalasztasos_rendezes(bemenet);
  bemenet = VeletlenszeruBemenet(1000);
  file << maximum_kivalasztasos_rendezes(bemenet);
  bemenet = VeletlenszeruBemenet(2500);
  file << maximum_kivalasztasos_rendezes(bemenet);
  bemenet = VeletlenszeruBemenet(5000);
  file << maximum_kivalasztasos_rendezes(bemenet);
  bemenet = VeletlenszeruBemenet(10000);
  file << maximum_kivalasztasos_rendezes(bemenet);

  file.close();

  return 0;
}
