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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the structure for the record this project uses.
//
//
****************************************************************/


#ifndef HOMEWORK3B_RECORD_H
#define HOMEWORK3B_RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};

#endif
