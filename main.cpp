/**
Plik z funkcja main() do cwiczenia na laboratoriach z AISDI.

COPYRIGHT:
Copyright (c) 2015 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <iostream>
#include <chrono>

#ifndef AISDI_LOCAL
#include "ListMap.h"
#else
#include "ListMap.h"
#endif

int CCount::count = 0;

int Test2();

int main()
{
   std::cout << "AISDI struktury liniowe: wchodze do funkcji main." << std::endl;
   const auto start = std::chrono::high_resolution_clock::now();
   Test2();
   const auto duration = std::chrono::high_resolution_clock::now() - start;
   const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
   std::cout << "\nCzas wykonania Test2() : " << milliseconds.count() << " ms." << std::endl;
   return EXIT_SUCCESS;
}
