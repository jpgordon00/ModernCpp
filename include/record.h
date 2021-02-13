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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the struct for record, the data type used in
//   this project by our singly linked list.
//
//
****************************************************************/

#ifndef PROJECT2_RECORD_H
#define PROJECT2_RECORD_H
struct record
{
    int accountno;
    char name[25];
    char address[80];
    struct record * next;
};
#endif
