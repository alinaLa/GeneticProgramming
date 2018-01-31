// NotacjaPolska.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Manager.h"
#include "CNode.h"
#include "CTree.h"
#include "Interface.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

const std::string PATH_TO_READ = "C:\\Users\\Ania\\Documents\\testDoOdczytu.txt";
const std::string PATH_TO_WRITE = "C:\\Users\\Ania\\Documents\\wynik.txt";
const std::string WRITE_ERROR = "Nie udalo sie otworzyc pliku do zapisu.";
const std::string READ_ERROR = "Nie udalo się otworzyc pliku do odczytu.";
const std::string BAT_DATA_ERROR = "Nieprawidlowe dane.";

const int SIZE_OF_POPULATION = 100;
const int NUMBER_OF_ITERATIONS = 100;
const int PROBABILITY_OF_CROSSING = 5;
const int PROBABILITY_OF_MUTATION = 5;

void test() {
	srand((int)time(NULL));
	Manager m;
	bool fileToReadIsOpen;
	bool onlyNumbers = true;
	m.readFile(PATH_TO_READ, &fileToReadIsOpen, &onlyNumbers);
	if (fileToReadIsOpen) {
		if (onlyNumbers) {
			m.gp(SIZE_OF_POPULATION, NUMBER_OF_ITERATIONS, PROBABILITY_OF_CROSSING, PROBABILITY_OF_MUTATION);
			m.printSolution();
			bool fileToWriteIsGood;
			m.writeToFile(PATH_TO_WRITE, &fileToWriteIsGood);
			if (!fileToWriteIsGood) {
				std::cout << WRITE_ERROR;
			}
			m.dealocateMemeory();
		}
		else {
			std::cout << BAT_DATA_ERROR;
		}
	}
	else {
		std::cout << READ_ERROR;
	}
}

int main()
{
	test();
	_getch();
	//_CrtDumpMemoryLeaks();
    return 0;
}



