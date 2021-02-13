/*****************************************************************
//
//  NAME:        Jacob Gordon
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        Feb 16, 2020
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   This file contains the headers, includes, and prototypes for database
//     functionality in Project 1.
//
//
****************************************************************/

#ifndef HOMEWORK3B_DATABASE_H
#define HOMEWORK3B_DATABASE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "record.h"

extern int debugmode;

int addRecord (struct record **, int, char [ ],char [ ]);
int printRecord (struct record *, int);
void printAllRecords(struct record *);
int modifyRecord (struct record *, int, char [ ]);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
int writefile(struct record *, char []);
void cleanup(struct record **);

#endif
