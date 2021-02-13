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
//  FILE:        list.h
//
//  DESCRIPTION:
//   This file contains the header for the implementation "llist.cpp" which is a
//   singly-linked-list with a struct record from "record.h" as its data.
//
//
****************************************************************/

#include "record.h"
#include <iostream>

#ifndef PROJECT2_LLIST_H
#define PROJECT2_LLIST_H

#ifndef PROJECT2_DEBUG_MODE
#define PROJECT2_DEBUG_MODE 0
#endif
class llist
{
private:
    record * start;
    char filename[16];
    int readfile();
    int writefile();
    record * reverse(record *);
    void cleanup();

public:
    llist();
    llist(char [ ]);
    llist(const llist&);
    ~llist();
    int addRecord(int, char [ ], char [ ]);
    int printRecord(int);
    int modifyRecord(int, char [ ]);
    int deleteRecord(int);
    void reverse();
    llist& operator = (const llist &);
    friend std::ostream & operator << (std::ostream &, const llist &);
};
#endif
