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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file contains the user-interface to Project 1. This interface
//      allows interaction between the user and the databases.
//
//
****************************************************************/

#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "../records.txt"


int get_accountno();
void get_name(char str[ ], int max_length);
void get_address(char str[ ], int max_length);

int debugmode;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Main function for this program that displays a menu
//                 and prompts positive integer input from the user.
//
//  Parameters:    int argc | number of arguments, 1 or 2 are expected.
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/

int main(int argc, char ** argv)
{
    struct record * start;
    int result, s;
    char input[10];
    s = 1;

    if (argc == 2)
    {
        if (strcmp(argv[1], "debug") == 0)
        {
            debugmode = 1;
        }
        else
        {
            printf("EXPECTED USAGES:\t'./homework3b'\t'./homework3b debug'\n");
            debugmode = -1;
        }
    }
    else
    {
        debugmode = argc > 2 ? -1 : 0;
        if (argc > 2) printf("EXPECTED USAGES:\t'./homework3b'\t'./homework3b debug'\n");
    }
    if (debugmode >= 0)
    {
        start = NULL;
        readfile(&start, FILE_NAME);
        do
        {
            int accountno;
            char name[25];
            char address[80];

            printf("------------------\n");
            printf("[0 or n <= 0] = N/A\n");
            printf("[1] = ADD RECORD\n");
            printf("\t**Adds a new record to the system given some parameters**\n");
            printf("\taccountno: an integer > 0.\n");
            printf("\tname: a string, 25 chars max, with spaces and no special chars.\n");
            printf("\taddress: a multiline string, 80 chars max each line, with special chars allowed.\n");
            printf("[2] = PRINT RECORD\n");
            printf("\t**Prints a record with the given accountnumber**\n");
            printf("\taccountno: an integer > 0.\n");
            printf("[3] = PRINT ALL RECORDS\n");
            printf("\t**Prints all records in the system.**\n");
            printf("[4] = MODIFY RECORD\n");
            printf("\t**Modify a record's address given its account number**\n");
            printf("\taccountno: an integer > 0.\n");
            printf("\taddress: a multiline string, 80 chars max each line, with special chars allowed.\n");
            printf("[5] = DELETE RECORD\n");
            printf("\t**Delete a record given its account number**\n");
            printf("\taccountno: an integer > 0.\n");
            printf("[6 or n >= 6] = EXIT\n");
            printf("\t**Quits the program.**\n");
            printf("------------------\n");

            scanf("%s", input);
            result = atoi(input);

            switch (result) {
                case 1:
                    accountno = get_accountno();
                    get_name(name, 25);
                    get_address(address, 80);
                    addRecord(&start, accountno, name, address);
                    break;
                case 2:
                    accountno = get_accountno();
                    printRecord(start, accountno);
                case 3:
                    printAllRecords(start);
                    break;
                case 4:
                    accountno = get_accountno();
                    get_address(address, 80);
                    printf("%s", modifyRecord(start, accountno, address) ? "" : "Could not find such record.\n");
                    break;
                case 5:
                    accountno = get_accountno();
                    deleteRecord(&start, accountno);
                    break;
                default:
                    break;
            }
        }
        while (result < 6);
        writefile(start, FILE_NAME);
    }
    return 0;
}

/*****************************************************************
//
//  Function name: get_accountno
//
//  DESCRIPTION:   Continually requests a positive integer from the user
//                 until one is recieved and then returned by this function.
//
//  Parameters:    N/A
//
//  Return values:  integer that represents the users entered positive number.
//
****************************************************************/

int get_accountno()
{

    char input[10];
    int i;

    if (debugmode)
    {
        printf("---- Invoked get_accountno() ----\n");
    }
    printf("Enter account number (n > 0):\n");
    do
    {
        scanf("%s", input);
        i = atoi(input);
    }
    while (i <= 0);
    return i;
}

/*****************************************************************
//
//  Function name: get_name
//
//  DESCRIPTION:   Requests a single line string from the user with no special characters.
//                 Line length must be within max_length 
//
//  Parameters:    str | string to hold the name
//                 max_length | maximum length of an entered line
//
//  Return values: N/A
//
****************************************************************/

void get_name(char str[ ], int max_length)
{

    int i;
    char c;
    i = 0;

    if (debugmode)
    {
        printf("---- Invoked get_name() ----\n");
        printf("str = '%s'.\n", str);
        printf("max_length = '%d'.\n", max_length);
        printf("------------\n");
    }
    printf("Enter a name for the user (only alphabetic and numerical characters are considered):\n");
    getchar();
    do {
        c = getchar();
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.')
        {
            str[i++] = c;
        }
    }
    while (i < max_length && c != '\n');
    str[i] = '\0';
}

/*****************************************************************
//
//  Function name: get_address
//
//  DESCRIPTION:   Requests a multi-line integer from the user. Can contain
//                 newline and special characters, user must enter a $ to stop.
//
//  Parameters:    str | string to hold the name
//                 max_length | maximum length of an entered line
//
//  Return values:  N/A
//
****************************************************************/

void get_address(char str[ ], int max_length)
{

    int i;
    char c;
    i = 0;

    if (debugmode)
    {
        printf("---- Invoked get_address() ----\n");
        printf("str = '%s'.\n", str);
        printf("max_length = '%d'.\n", max_length);
        printf("------------\n");
    }
    printf("Enter an address (can be multi-line, consider the '$' character to be the delimiter):\n");
    do {
        c = getchar();
        str[i++] = c;
    }
    while (i < max_length && (c != '$'));
    if (str[i - 1] == '\n' || str[i - 1] == '$')
    {
        str[i - 1] = '\0';
    }
    else if (str[i - 2] == '\n' || str[i - 2] == '$')
    {
        str[i - 2] = '\0';
    }
    else
    {
        str[i] = '\0';
    }
}
