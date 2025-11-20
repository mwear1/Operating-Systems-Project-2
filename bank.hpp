#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

const int NUMRESOURCES = 3;  // number of different resources
const int NUMPROCESSES = 5;  // number of processes

const char ENDLINE = ';';    // end of a record in the file
const char ENDLIST = ',';    // separator between values in the file

void createTable(const char* file, int allocated[][NUMRESOURCES], int max[][NUMRESOURCES], int* available);

#endif