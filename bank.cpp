// Matthew Wear
// Operating Systems Project 2

#include "bank.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Too few arguments" << std::endl;
        return 1;
    }

    char* resourceTable = argv[1];

    int allocated[NUMPROCESSES][NUMRESOURCES];
    int max[NUMPROCESSES][NUMRESOURCES];
    int available[NUMRESOURCES];

    // Creates the tables from the input file selected
    createTable(resourceTable, allocated, max, available);

    int finished[NUMPROCESSES] = {0};
    int answer[NUMPROCESSES];
    int index = 0;

    int need[NUMPROCESSES][NUMRESOURCES];

    // Compute Need = Max - Allocation
    for (int i = 0; i < NUMPROCESSES; ++i) {
        for (int j = 0; j < NUMRESOURCES; ++j) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    // Banker's safety check
    for (int k = 0; k < NUMPROCESSES; ++k) {
        for (int currProcess = 0; currProcess < NUMPROCESSES; ++currProcess) {
            if (finished[currProcess] == 0) { // only consider unfinished
                bool canFinish = true;

                for (int currResource = 0; currResource < NUMRESOURCES; ++currResource) {
                    if (need[currProcess][currResource] > available[currResource]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    // This process can finish: add to sequence and release its resources
                    answer[index++] = currProcess;

                    for (int r = 0; r < NUMRESOURCES; ++r) {
                        available[r] += allocated[currProcess][r];
                    }

                    finished[currProcess] = 1;
                }
            }
        }
    }

    bool safe = true;

    for(int currProcess = 0; currProcess < NUMPROCESSES; ++currProcess) {
        if (finished[currProcess] == 0) {
            safe = false;
            break;
        }
    }

    if(!safe){
        std::cout << "System is NOT in a safe state. No safe sequence exists." << std::endl;
    } 
    
    else{
        std::cout << "System is in a SAFE state." << std::endl;
        std::cout << "Safe sequence: ";
        for (int i = 0; i < NUMPROCESSES; ++i) {
            std::cout << "P" << answer[i];
            if (i != NUMPROCESSES - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

// Reads the table file and fills Allocation, Max, and Available
void createTable(const char* file, int allocated[][NUMRESOURCES], int max[][NUMRESOURCES], int* available) {
    int currProcess = 0;
    int currResPosition = 0;
    std::string currentLine;
    std::ifstream resourceTable(file, std::ifstream::in);

    if (!resourceTable.is_open()) {
        std::cerr << "Error: could not open file " << file << std::endl;
        std::exit(1);
    }

    // Each segment is read up to ';'
    while (std::getline(resourceTable, currentLine, ENDLINE)) {
        if (currentLine.empty()) {
            continue; // skip empty segments
        }

        int id = std::stoi(currentLine);

        // Available resources line: process id is negative (e.g., -1)
        if (id < 0) {
            for (int i = 0; i < NUMRESOURCES; ++i) {
                if (i == NUMRESOURCES - 1) {
                    // Last value ends at ';'
                    if (!std::getline(resourceTable, currentLine, ENDLINE)) break;
                } else {
                    if (!std::getline(resourceTable, currentLine, ENDLIST)) break;
                }
                available[i] = std::stoi(currentLine);
            }
            break; // Done with file
        }

        // Normal process line: id is the process number
        currProcess = id;

        // Allocated resources
        for (currResPosition = 0; currResPosition < NUMRESOURCES; ++currResPosition) {
            if (currResPosition == NUMRESOURCES - 1) {
                std::getline(resourceTable, currentLine, ENDLINE); // ends at ';'
            } else {
                std::getline(resourceTable, currentLine, ENDLIST); // ends at ','
            }
            allocated[currProcess][currResPosition] = std::stoi(currentLine);
        }

        // Max resources
        for (currResPosition = 0; currResPosition < NUMRESOURCES; ++currResPosition) {
            if (currResPosition == NUMRESOURCES - 1) {
                std::getline(resourceTable, currentLine, ENDLINE); // ends at ';'
            } else {
                std::getline(resourceTable, currentLine, ENDLIST); // ends at ','
            }
            max[currProcess][currResPosition] = std::stoi(currentLine);
        }
    }
}