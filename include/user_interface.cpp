/*****************************************************************
//
//  NAME:        Jacob Gordon
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 12, 2019
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This file contains the user-interface for Project2.
//
//
****************************************************************/

#include <iostream>
#include "llist.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void get_address(char *, int);
void get_name(char *, int);
void get_pos_int(int &, int);

//
// FUNCTION NAME:   main

// PARAMETERS:  int argc, char** argv

// DESCRIPTION:
//
//  Main function invoked when the program is ran.
//  Creates a llist object.
//  Print help messages and waits for user input to invoke various list commands.
//  Returns 0.
//
int main(int argc, char ** argv)
{
    llist list;
    bool running = true;
    int choice;
    std::cout << "------ Project 2 C++ Program ------" << std::endl;
    std::cout << "To chose a menu option, enter the index of the chosen option" << std::endl;
    while (running)
    {
        std::cout << "-----------------------------------" << std::endl;
        std::cout <<
                  "[1] = ADD RECORD\n"
                  "\t**Adds a new record to the system given some parameters**\n"
                  "\taccountno: an integer > 0\n"
                  "\ttname: a string, 100 chars max, with spaces and no special chars.\n"
                  "\taddress: a multiline string, 100 chars max each line, with special chars allowed.\n";
        std::cout <<
                  "[2] = PRINT RECORD\n"
                  "\t**Prints a record with the given accountnumber**\n"
                  "\taccountno: an integer > 0.\n";
        std::cout <<
                  "[3] = PRINT ALL RECORDS\n"
                  "\t**Prints all records in the system.**\n";
        std::cout <<
                  "[4] = MODIFY RECORD\n"
                  "\t**Modify a record's address given its account number**\n"
                  "\taccountno: an integer > 0.\n"
                  "\taddress: multi-line address for the record.\n";
        std::cout <<
                  "[5] = DELETE RECORD\n"
                  "\t**Delete a record given its account number**\n"
                  "\taccountno: an integer > 0.\n";
        std::cout << "[6] = REVERSE" << std::endl << "\t**reverses the linked list**" << std::endl;
        std::cout <<
                  "[7 or >= 7] = EXIT" << std::endl <<
                  "\t**Quits the program.**" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        get_pos_int(choice, 12);
        if (choice == 1)
        {
            int accountno;
            char name [25];
            char address[80];
            get_pos_int(accountno, 12);
            get_name(name, 25);
            get_address(address, 80);
            std::cout << (list.addRecord(accountno, name, address) ? "" : "ERROR! Cannot add record!") << std::endl;
        }
        else if (choice == 2)
        {
            int accountno;
            get_pos_int(accountno, 12);
            std::cout << (list.printRecord(accountno) ? "" : "ERROR! Cannot print record!") << std::endl;
        }
        else if (choice == 3)
        {
            std::cout << list << std::endl;
        }
        else if (choice == 4)
        {
            int accountno;
            char address[80];
            get_pos_int(accountno, 12);
            get_address(address, 80);
            std::cout << (list.modifyRecord(accountno, address) ? "" : "ERROR! Cannot modify record!") << std::endl;
        }
        else if (choice == 5)
        {
            int accountno;
            get_pos_int(accountno, 12);
            std::cout << (list.deleteRecord(accountno) ? "" : "ERROR! Cannot delete record!") << std::endl;
        }
        else if (choice == 6)
        {
            list.reverse();
        } else
        {
            running = false;
        }
    }
}

//
// FUNCTION NAME:   get_name

// PARAMETERS:  char * src, int lim

// DESCRIPTION:
//
//  Reads a line of input into src and upto lim characters. Only letters are valid and invalid
//  input will automatically wait for valid input by calling getlines.
//
void get_name(char * src, int lim)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tget_name" << std::endl << "char * src:\t" << src << std::endl << "int lim:\t" << lim << std::endl;
    }
    std::cout << "Enter a string without special characters (excluding white-space):" << std::endl;
    bool valid;
    char * str;
    str = new char[lim];
    do {
        int i;
        str[0] = '\0';
        std::cin.getline(str, lim);
        valid = true;
        i = 0;
        while (str[i] != '\0' && valid && i < lim)
        {
            if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' ' || str[i] == '\n' || str[i] == '\0')) {
                valid = false;
            }
            i++;
        }
    } while (!valid);
    strcpy(src, str);
    delete str;
}

//
// FUNCTION NAME:   get_address

// PARAMETERS:  char * src, int lim

// DESCRIPTION:
//
//  Reads line(s) of input into src upto lim digits per line.
//  Strings can contain any characters and can be multiline.
//  Reading exits upon any line having its last character be a '$' symbol.
//
void get_address(char * src, int lim)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tget_address" << std::endl << "char * src:\t" << src << std::endl << "int lim:\t" << lim << std::endl;
    }
    std::cout << "Enter a string(s) that can have special characters, including new-line" << std::endl <<
              "To end the address, append a '$' character to the end of the line:" << std::endl;
    int i, x;
    char * str;
    i = 0;
    x = 0;
    str = new char[lim];
    src[0] = '\0';
    do {
        str[0] = '\0';
        std::cin.getline(str, lim);
        if (x++ > 0)
        {
            int t;
            src[t = strlen(src)] = '\n';
            src[t + 1] = '\0';
        }
        strcat(src, str);
    } while(str[strlen(str) - 1] != '$');
    delete str;
}

//
// FUNCTION NAME:   get_pos_int

// PARAMETERS:  int ref accountno, int lim

// DESCRIPTION:
//
//  Reads a line of input upto lim characters a replaces accountno with an inputted
//  number greater than 0.
//
void get_pos_int(int &accountno, int lim)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tget_pos_int" << std::endl << "int &accountno:\t" << accountno << std::endl << "int lim:\t" << lim << std::endl;
    }
    char * str;
    bool valid;
    int i;
    str = new char[lim];
    std::cout << "Enter a positive integer:" << std::endl;
    i = 0;
    do
    {
        std::cin.getline(str, lim);
        valid = true;
        while (str[i] != '\0' && i < lim)
        {
            if (str[i] < '0' || str[i] > '9') valid = false;
        }
        if (atoi(str) <= 0) valid = false;
        if (valid)
        {
            accountno = atoi(str);
        }
    } while (!valid);
    delete str;
}

