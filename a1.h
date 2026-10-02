/*
 * Name:
 * Student ID:
 * Date:
 * Assignment: CIS*2520 F26 Assignment 1 - Rental Car Linked Lists
 *
 * a1.h: structure definition, constants and function prototypes.
 * Do NOT change the structure, the constants or the prototypes given here.
 * Helper functions: a helper called by any function in a1_functions.c must be
 * defined (and declared, if needed) in a1_functions.c. A helper used only by
 * main() may be in a1.c. Do not add helper functions to this file.
 */

#ifndef A1_H
#define A1_H

/* Libraries used. Add more here if needed. */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PLATE_LEN 8          /* a plate has 2 to 8 letters/digits */
#define NO_RETURN_DATE (-1)      /* return date of a car that is not rented */

/* The three data files (hard-coded, they will not change) */
#define AVAILABLE_FILE "available.txt"
#define RENTED_FILE "rented.txt"
#define REPAIR_FILE "repair.txt"

/* Our linked list node */
struct car {
    char plate[MAX_PLATE_LEN + 1];   /* plate number + '\0' */
    int mileage;                     /* total mileage in km */
    int return_date;                 /* yymmdd, or NO_RETURN_DATE (-1) if not rented */
    struct car *next;
};

/* Function prototypes (descriptions are in a1_functions.c) */
void prompt(void);
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date);
void print_list(struct car *head);
bool is_plate_in_list(struct car * head, char plate[]);
void swap(struct car *a, struct car *b);
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date);
struct car * remove_car_from_list(struct car **head, char plate[]);
struct car * remove_first_from_list(struct car **head);
double profit_calculator(int initial_mileage, int final_mileage);
void write_list_to_file(char *filename, struct car *head);
void read_file_into_list(char *filename, struct car **head);
void date(int yymmdd);
void free_list(struct car ** head);

#endif



