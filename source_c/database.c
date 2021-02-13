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
//  FILE:        database.c
//
//  DESCRIPTION:
//   This file contains the implementations for the database header file.
//
//
****************************************************************/

#include "database.h"


/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record to the end of the list.

//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//                 int accountno | account number, greater than zero, of the record to be added
//                 char name [ ] | name field for record to be added, only letters and numbers, maxmimum of twentity-five characters
//                 char address [ ] | address field for record to be added, can be multiline, maximum eighty characters
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
int addRecord (struct record** start_pntr, int accountno, char name[ ],char address[ ])
{
    int r = 0;
    if (debugmode)
    {
        printf("---- Invoked addRecord() ----\n");
        printf("accountno = '%d'.\n", accountno);
        printf("name = '%s'.\n", name);
        printf("address = '%s'.\n", address);
        printf("------------\n");
    }
    if ((*start_pntr) == NULL)
    {
        (*start_pntr) = malloc(sizeof(struct record));
        (*start_pntr)->accountno = accountno;
        strcpy((*start_pntr)->name, name);
        strcpy((*start_pntr)->address, address);
        (*start_pntr)->next = NULL;
        r = 1;
    }
    else
    {
        while ((*start_pntr)->next != NULL)
        {
            start_pntr = &(*start_pntr)->next;
        }
        (*start_pntr)->next = malloc(sizeof(struct record));
        (*start_pntr)->next->accountno = accountno;
        strcpy((*start_pntr)->next->name, name);
        strcpy((*start_pntr)->next->address, address);
        (*start_pntr)->next->next = NULL;
        r = 1;
    }
    return r;
}

/*****************************************************************
//
//  Function name: printRecord
//
//  DESCRIPTION:   Prints all the fields of an existing record, given its account number.

//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//                 int accountno | account number, greater than zero, of the record to be printed
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
int printRecord (struct record* start_pntr, int accountno)
{
    if (debugmode)
    {
        printf("---- Invoked printRecord() ----\n");
        printf("accountno = '%d'.\n", accountno);
        printf("------------\n");
    }
    int r = 0;
    while (start_pntr != NULL)
    {
        if (start_pntr->accountno == accountno)
        {
            r = 1;
            printf("----\naccountno: '%d'\nname: '%s'\naddress: '%s'\n------\n", start_pntr->accountno, start_pntr->name, start_pntr->address);
        }
        start_pntr = start_pntr->next;
    }
    return r;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all the fields of all existing records.

//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
void printAllRecords(struct record * start_pntr)
{
    if (debugmode)
    {
        printf("---- Invoked printAllRecords() ----\n");
        printf("------------\n");
    }
    while (start_pntr != NULL)
    {
        printf("----\naccountno: '%d'\nname: '%s'\naddress: '%s'\n------\n", start_pntr->accountno, start_pntr->name, start_pntr->address);
        start_pntr = start_pntr->next;
    }
}

/*****************************************************************
//
//  Function name: modifyRecord
//
//  DESCRIPTION:   Modifies a records address field to be a new address field, given its account number.
//
//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//                 int accountno | account number, greater than zero, of the record to be modified
//                 char address [ ] | address field for record to be added, can be multiline, maximum eighty characters
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
int modifyRecord (struct record* start_pntr, int accountno, char address[ ])
{
    int r = 0;
    if (debugmode)
    {
        printf("---- Invoked modifyRecord() ----\n");
        printf("accountno = '%d'.\n", accountno);
        printf("address = '%s'.\n", address);
        printf("------------\n");
    }
    while (start_pntr != NULL)
    {
        if (start_pntr->accountno == accountno)
        {
            r = 1;
            strcpy(start_pntr->address, address);
        }
        start_pntr = start_pntr->next;
    }
    return r;
}


/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes a record given its account number.
//
//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//                 int accountno | account number, greater than zero, of the record to be deleted
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
int deleteRecord(struct record** start_pntr, int accountno)
{
    struct record * temp, * prev;
    int r;
    temp = *start_pntr;
    r = 0;
    if (debugmode)
    {
        printf("---- Invoked deleteRecord() ----\n");
        printf("accountno = '%d'.\n", accountno);
        printf("------------\n");
    }
    if (temp != NULL && accountno == temp->accountno)
    {
        *start_pntr = temp->next;
        free(temp);
        temp = *start_pntr;
        prev = *start_pntr;
        r = 1;
    }
    while (temp != NULL)
    {
        if (accountno == temp->accountno)
        {

            prev->next = temp->next;
            free(temp);
            temp = prev->next;
            r = 1;
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
    return r;
}

/*****************************************************************
//
//  Function name: readFile
//
//  DESCRIPTION:   Reads consecutive records from a file given each field as a string with its own line, and a special
//                  '$' character to denote the end of the address.
//
//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//                 char filename [ ] | filename of the file to be read.
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
int readfile(struct record ** start_pntr, char filename[])
{
    FILE * fp;
    int r;
    fp = fopen(filename, "r");
    r = 0;
    if (fp != NULL)
    {
        int i, stage, read, taccountno;
        char c, buff[512], tname[25];
        tname[0] = '\0';
        r = 1;
        i = 0;
        stage = 0;
        read = 0;
        while ((c = fgetc(fp)) != EOF)
        {
            if (c == '\n' && stage < 2)
            {
                buff[i] = '\0';
                if (stage == 0)
                {
                    taccountno = atoi(buff);
                }
                else if (stage == 1)
                {
                    if (i >= 25) buff[24] = '\0';
                    strcpy(tname, buff);
                }
                stage += 1;
                buff[0] = '\0';
                i = 0;
            }
            else if (c == '$' && stage == 2)
            {
                buff[i] = '\0';
                if (i >= 80)
                {
                    buff[78] = '$';
                    buff[79] = '\0';
                }
                addRecord(start_pntr, taccountno, tname, buff);
                read += 1;
                stage = 0;
                buff[0] = '\0';
                tname[0] = '\0';
                i = 0;
                c = fgetc(fp);
            }
            else
            {
                buff[i++] = c;
            }
        }
        fclose(fp);
    }
    return r;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Writes consecutive records from a file given each field as a string with its own line, and a special
//                  '$' character to denote the end of the address.
//
//  Parameters:    struct record ** start_pntr | pointer to the start of the list
//                 char filename [ ] | filename of the file to be written.
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
int writefile(struct record * start_pntr, char filename[])
{
    FILE * fp;
    int i, r;
    fp = fopen(filename, "w");
    i = 0;
    r = 0;
    while (start_pntr != NULL)
    {
        r = 1;
        fprintf(fp, "%s%d\n%s\n%s%s", i++ > 0 ? "\n" : "", start_pntr->accountno, start_pntr->name, start_pntr->address, "$");
        start_pntr = start_pntr->next;
    }
    fclose(fp);
    return r;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:  Removes all heap assigned memory in the program by freeing the struct record
//                of all pointers not NULL denotes from 'next' from 'start_pntr'.
//
//  Parameters:    struct record ** start_pntr | pointer to the start of the list pointer
//
//  Return values:  0 : failure
//                  1 : success
//
****************************************************************/
void cleanup(struct record ** start_pntr)
{
    struct record * temp;
    while (*(start_pntr) != NULL)
    {
        temp = (*(start_pntr))->next;
        free(*(start_pntr));
        start_pntr = &temp;
    }
}