# Operating-Systems-Project-2
Implementation of the Banker's Algorithm in a Linux environment.
# Description
This project implements the Banker’s Algorithm for deadlock avoidance using C++ on a Linux/Unix system. It reads in from input text files to create tables in this
format: 

<img width="583" height="320" alt="image" src="https://github.com/user-attachments/assets/04c23e33-2677-441d-8864-4c9b47862b46" />

Using this data, the program computes the Need matrix, representing how many additional resources each process requires to finish. It then goes through the safety
check phase of the Banker’s Algorithm by looping to search for a process whose needs can be satisfied. When a process is found, it releases its allocated resources
back into the system. If all processes can finish in this way, then the system is in a safe state. If not, then no safe sequence exists and the system is
unsafe.

# Installation/Execution
All required files are provided here.
The files used during execution are:
```
bank.cpp
bank.hpp
test.txt or test2.txt
```
# Dependencies
The following libraries are used in this program:
```
<iostream>
<fstream>
<string>
<csdtlib>
```
Hardware Versions used:  
Visual Studio Code v1.105.1  
OS: Linux x64 6.14.0-27-generic snap  
# Compilation
Guid for compilation:  
  1. Load Visual Studio Code in a Linux/UNIX environment (can be done natively, remotely, or through virtualization)
  2. Open the terminal
  3. Enter the datapath to the folder
  4. Run the following commands:
```
$ g++ -o bank bank.cpp
$ ./bank test.txt
```
# Examples
Below are screenshots of the program in execution:

Compilation:
