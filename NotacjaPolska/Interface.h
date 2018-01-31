#pragma once

#include <iostream>
#include <iomanip>
#include "Manager.h"

std::string const COMMAND_ENTER = "enter";
std::string const COMMAND_VARS = "vars";
std::string const COMMAND_PRINT = "print";
std::string const COMMAND_COMP = "comp";
std::string const COMMAND_JOIN = "join";
std::string const COMMAND_EXIT = "exit";

std::string const INFO_WRONG_COMMAND = "Bledne polecenie.";
std::string const INFO_WRONG_FORMULA = "Wprowadzona formula jest bledna.";
std::string const INFO_WRONG_PARAMETERS = "Bledne parametry.";
std::string const INFO1 = "Bedzie przetwarzana formula: ";
std::string const INFO2 = "Liczba podanych wartosci nie odpowiada liczbie zmiennych w drzewie.";
std::string const VALUE = "Wartosc = ";

const std::string INFO_THE_BEST_SOLUTION = "Najlepsze rozwiazanie: ";
const std::string INFO_VALUE_OF_THE_FUNCTION = "Wartosc funkcji przystosowania: ";

char const C_SPACE = ' ';

int const PRECISION = 2;
