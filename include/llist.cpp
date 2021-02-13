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
//  FILE:        list.cpp
//
//  DESCRIPTION:
//   This file contains the implementation of "llist.h" which is a
//   singly-linked-list with a struct record from "record.h" as its data.
//
//
****************************************************************/

#include <algorithm>
#include "llist.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

//
// FUNCTION NAME:   Constructor

// PARAMETERS:  none

// DESCRIPTION:
//  Initiates the start variable to NULL and the filename to a constant, and
//  invokes readfile().
//
llist::llist()
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func_name: llist()" << std::endl;
    }
    char * fn = (char *) "../data.txt";
    start = NULL;
    strcpy(filename, fn);
    readfile();
}

//
// FUNCTION NAME:   Constructor

// PARAMETERS:  filename

// DESCRIPTION:
//  Initiates the start variable to NULL and the filename to the parameter, and
//  invokes readfile().
//
llist::llist(char * filename)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func_name: llist(char *)" << std::endl;
    }
    start = NULL;
    strcpy(this->filename, filename);
    readfile();
}

//
// FUNCTION NAME:   Constructor

// PARAMETERS:  const ref to list

// DESCRIPTION:
//  Initiates the start variable to the given list's start, and
//  invokes readfile().
//

llist::llist(const llist & list)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func_name: llist(const llist &)" << std::endl;
    }
    record * temp = list.start;
    while (temp != NULL)
    {
        addRecord(temp->accountno, temp->name, temp->address);
        temp = temp->next;
    }
    strcpy(filename, list.filename);
}

//
// FUNCTION NAME:  Deconstructor

// PARAMETERS:  N/A

// DESCRIPTION:
//  Writes the list as is and invokes cleanup to free memory.
//
llist::~llist()
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func_name: ~llist()" << std::endl;
    }
    cleanup();
}

//
// FUNCTION NAME:   addRecord

// PARAMETERS:  int accountno, char * name, char * address

// DESCRIPTION:
//  Adds a record to the list given its accountno to be unique, with the given
//  accountno, name and address from the parameters.
//  Record 0 if failure or 1 if added record.
//
int llist::addRecord(int accountno, char * name, char * address)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\taddRecord" << "int accountno:\t" << accountno << "char * name:\t" << name << "char * address:\t" << address << std::endl;
    }
    struct record * temp;
    int r;
    temp = this->start;
    r = 0;
    if (start == NULL)
    {
        start = new struct record();
        start->accountno = accountno;
        strcpy(start->name, name);
        strcpy(start->address, address);
        start->next = NULL;
        r = 1;
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                temp->next = new struct record();
                temp = temp->next;
                temp->accountno = accountno;
                strcpy(temp->name, name);
                strcpy(temp->address, address);
                temp->next = NULL;
                r = 1;
            }
            temp = temp->next;
        }
    }
    return r;
}

//
// FUNCTION NAME:   printRecord

// PARAMETERS:  int accountno

// DESCRIPTION:
//  Prints a record the standard output stream given its accountno exists.
//  Returns 0 if no record is found and 1 if the record is printed.
//
int llist::printRecord(int accountno)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tprintRecord" << "int accountno:\t" << accountno << std::endl;
    }
    record * temp = start;
    int r;
    r = 0;
    while (temp != NULL)
    {
        if (temp->accountno == accountno)
        {
            std::cout << "accountno:\t" << temp->accountno << std::endl << "name:\t" << temp->name << std::endl << "address:\t" << temp->address << std::endl;
            r = 1;
        }
        temp = temp->next;
    }
    return r;
}

//
// FUNCTION NAME:   modifyRecord

// PARAMETERS:  int accountno, char * address

// DESCRIPTION:
//
//  Modifies a record's address to the address in the parameter given the accountno exists.
//  Returns 0 if failed and 1 if modified the record.
//
int llist::modifyRecord(int accountno, char * address)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tmodifyRecord" << "int accountno:\t" << accountno << "char * address:\t" << address << std::endl;
    }
    int r;
    record * temp;
    r = 0;
    temp = start;
    while (temp != NULL)
    {
        if (temp->accountno == accountno)
        {
            r = 1;
            strcpy(temp->address, address);
        }
        temp = temp->next;
    }
    return r;
}

//
// FUNCTION NAME:   deleteRecord

// PARAMETERS:  int accountno, char * address

// DESCRIPTION:
//
//  Deletes a record from the list given its accountno.
//  Returns 1 if successfully deleted record and 0 if otherwise.
//
int llist::deleteRecord(int accountno)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tdeleteRecord" << "int accountno:\t" << accountno << std::endl;
    }
    record* temp, *prev;
    int r;
    temp = start;
    r = 0;
    if (temp != NULL && temp->accountno == accountno)
    {
        start = temp->next;
        delete temp;
        r = 1;
    }
    else
    {
        while (temp != NULL && temp->accountno != accountno)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL)
        {
            prev->next = temp->next;
            delete temp;
            r = 1;
        }
    }
    return r;
}

//
// FUNCTION NAME:   reverse

// PARAMETERS:  none

// DESCRIPTION:
//
//  Reverses the singly linked list if possible by invoking a helper function.
//
void llist::reverse()
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\treverse()" << std::endl;
    }
    reverse(this->start);
}

//
// FUNCTION NAME:   reverse

// PARAMETERS:  record * r

// DESCRIPTION:
//
//  Reverses the singly linked list through recursion given
//  a current node (or record in this case).
//  Returns an existing node, a new node, or NULL.
//
record * llist::reverse(record * r)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func_name: reverse(record *)" << std::endl;
    }
    if (r == NULL) return r;
    if (r->next == NULL)
    {
        start = r;
        return r;
    }
    record * r1 = reverse(r->next);
    r1->next = r;
    r->next = NULL;
    return r;
}


//
// FUNCTION NAME:   readfile

// PARAMETERS:  none

// DESCRIPTION:
//
//  Reads the file from the stored filename into the list, if possible.
//  The address is considered finished upon its final character being a '$'
//  Returns 0 if failure and 1 if succesfully read file.
//
int llist::readfile()
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\treadfile" << std::endl;
    }
    std::ifstream fp;
    int r, stage, accountno;
    char name[25], address[80];
    r = 0;
    stage = 0;
    fp.open(filename);
    if (!fp.fail()) {
        r = 1;
        while (!fp.eof()) {
            std::string str;
            const char * tstr = str.c_str();
            name[0] = '\0';
            address[0] = '\0';
            getline(fp, str);

            if (stage == 0) {
                accountno = atoi(tstr);
                name[0] = '\0';
                address[0] = '\0';
                stage += 1;
            } else if (stage == 1) {
                strcpy(name, tstr);
                stage += 1;
            } else {
                strcat(address, tstr);
                if (address[strlen(address) - 2] == '$') {
                    address[strlen(address) - 2] = '\0';
                    addRecord(accountno, name, address);
                    stage = 0;
                }
            }
        }
    }
}

//
// FUNCTION NAME:   writefile

// PARAMETERS:  none

// DESCRIPTION:
//
//  Writes the singly linked list in memory to a file stored at filename.
//  Returns 1 if wrote file and 0 if otherwise.
//
int llist::writefile()
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\twritefile" << std::endl;
    }
    int r;
    record * temp;
    r = 0;
    temp = start;
    std::ofstream fp(filename);
    while (temp != NULL)
    {
        fp << temp->accountno << std::endl;
        fp << temp->name << std::endl;
        fp << temp->address << "$" << std::endl;
        temp = temp->next;
        r = 1;
    }
    fp.close();
    return r;
}

//
// FUNCTION NAME:   cleanup

// PARAMETERS:  none

// DESCRIPTION:
//
//  Iterates through and clears all memory in the heap created by the linked list.
//
void llist::cleanup()
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\tcleanup" << std::endl;
    }
    struct record * temp = start;
    while (temp != NULL)
    {
        struct record * ttemp = temp->next;
        delete temp;
        temp = ttemp;
    }
}


//
// FUNCTION NAME:   ostream Operator

// PARAMETERS:  ref ostream, const ref list

// DESCRIPTION:
//
//  Prints the given list to the given output stream field by field.
//  Returns the output stream given as a parameter.
//
std::ostream & operator << (std::ostream & os, const llist &list)
{
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\t<<" << std::endl;
    }
    record * temp = list.start;
    while (temp != NULL)
    {
        os << "accountno:\t" << temp->accountno << std::endl << "name:\t" << temp->name << std::endl << "address:\t" << temp->address << std::endl;
        temp = temp->next;
    }
    return os;
}

//
// FUNCTION NAME:   equals operator

// PARAMETERS:  const list

// DESCRIPTION:
//
//  Assigns this list to the given list by transfering its filename and
//  all of its data.
//
llist &llist::operator = (const llist & list) {
    if (PROJECT2_DEBUG_MODE)
    {
        std::cout << "func name:\t=" << std::endl;
    }
    record * temp = list.start;
    while (temp != NULL)
    {
        addRecord(temp->accountno, temp->name, temp->address);
        temp = temp->next;
    }
    strcpy(filename, list.filename);
    return *this;
}





