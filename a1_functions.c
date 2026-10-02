/*
 * Name:
 * Student ID:
 * Date:
 * Assignment: CIS*2520 F26 Assignment 1 - Rental Car Linked Lists
 *
 * a1_functions.c: the linked list functions used by main() in a1.c.
 * Do NOT change the names, parameters or return types of the functions below.
 * You may add helper functions. A helper called by any function in this file
 * must be defined (and declared, if needed) in this file, not in a1.c or a1.h.
 * Note: strcasecmp() is not part of C99. To compare plates without regard to
 * case, compare them character by character with toupper() (from ctype.h).
 */

#include "a1.h"


/* Displays the primary user interface. This is already done for you. */
void prompt(void) {

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  printf("Enter your choice: ");
}

/**
 * Adds a new car at the END of the list. It does not sort the list and does
 * not check for duplicate plates (the caller does that).
 * @param head Pointer to the head of the list (*head is NULL for an empty list).
 * @param plate Character array containing the car's plate number (copied into the new node).
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer in yymmdd format, or NO_RETURN_DATE (-1) if the car has none.
 * @return Pointer to the newly added car, or NULL if memory could not be allocated.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date) {
    struct car *new_car = malloc(sizeof(struct car));
    if (!new_car) return NULL; //if new_car is null return
    strncpy(new_car->plate, plate, MAX_PLATE_LEN); //safely copy
    new_car->plate[MAX_PLATE_LEN] = '\0';
    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;

    struct car *current = *head;
    if (!current) {
        *head = new_car;
        return new_car;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_car;
    return new_car;
}

/**
 * Prints all the cars in the list, one car per line, in this format:
 *     Plate: ABC123, Mileage: 10000
 *     Plate: JKL890, Mileage: 98000, Return date: 26/10/05
 * The return date (printed with date()) is shown only if the car has one.
 * An empty list prints the single line:  (empty)
 * @param head Pointer to the head of the list.
 */
void print_list(struct car *head) {
    if (!head) { //if head is null
        printf(" (empty)\n");
        return;
    }
    struct car *current = head;
    while (current) {
        printf("Plate: %s, Mileage: %d", current->plate, current->mileage);
        if (current->return_date!=-1){ //if return date isnt -1 then it is rented
            printf(", Return date:");
            date(current->return_date);
        }
        printf("\n");
        current = current->next; //move to the next node
    }
}

/**
 * Checks if a plate is already in the list. The comparison ignores case:
 * "abc123" and "ABC123" are the same plate.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the plate number to look for.
 * @return true if the plate is found, false otherwise (including an empty list).
 */
bool is_plate_in_list(struct car * head, char plate[]) {
    if (!head) return false;
    struct car *current = head;
    bool same=true;
    while(current){
        for (int i=0; i<MAX_PLATE_LEN && plate[i]!='\0'; i++){ //turn all of the characters to upper case
            plate[i]=toupper(plate[i]);
            if (plate[i]!=toupper(current->plate[i])){
                same=false;
                break; //if it is not equal break
            }
        }
        if (same==true) return true; //if it is equal return true
        current=current->next;
}
return false;

}

/**
 * Swaps the data of two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage and return date of the two cars. The next
 * pointers are not changed.
 */
void swap(struct car *a, struct car *b) {
    char tempplate[MAX_PLATE_LEN+1]; //a temp to store the value of a
    int tempmile;
    int tempdate;

    strcpy(tempplate, a->plate); //because it a string we nned to use strcpy
    strcpy(a->plate,b->plate);
    strcpy(b->plate,tempplate);

    tempmile=a->mileage;
    a->mileage=b->mileage;
    b->mileage=tempmile;

    tempdate=a->return_date;
    a->return_date=b->return_date;
    b->return_date=tempdate;
    return;
}

/**
 * Sorts the list in ascending order.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage If true, sort by mileage (least miles first).
 * @param sort_by_return_date If true (and sort_by_mileage is false), sort by
 *        return date (earliest first).
 * If both are false the list is not changed. Cars with an equal key keep
 * their current order. An empty list or a list with one car is fine.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date) {
    if (sort_by_mileage==false && sort_by_return_date==false) return;
    struct car *current=*head;
        while(current){
            struct car *temp=current->next;
            while (temp!=NULL){
                if (sort_by_mileage==true){
                    if (temp->mileage < current->mileage){ // if the next one is higher than the current one
                    swap(current,temp); //swap them
                    }
                }
                else if (sort_by_return_date==true){
                    if (temp->return_date < current -> return_date){
                        swap(current,temp);
                    }
                }
                temp=temp->next;
            }
            current=current->next;
        }
}

/**
 * Removes a car from the list by its plate number (case is ignored).
 * The car is unlinked from the list but NOT freed: the caller becomes the
 * owner of the returned node and must free it when done.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the plate number.
 * @return Pointer to the removed car, or NULL if the plate is not in the list.
 */
struct car * remove_car_from_list(struct car **head, char plate[]) {
    struct car *current = *head;
    struct car *previous=NULL;
    while (current){
        if (is_plate_in_list(current,plate)==true){
            
            if (previous==NULL){
                *head=current->next;
            }
            else{
            previous->next=current->next;
        }
        current->next=NULL;
        return current;
        }
       
        previous=current;
        current=current->next;
    }
    return NULL;
}

/**
 * Removes the first car from the list. The car is unlinked but NOT freed:
 * the caller must free it.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car, or NULL if the list is empty.
 */
struct car * remove_first_from_list(struct car **head) {
    struct car*current=*head;
    if (!*head) return NULL;
        *head=current->next;
        current->next=NULL;
        return current;

}

/**
 * Calculates the rental charge for a returned car.
 * The distance driven is final_mileage - initial_mileage (in km).
 * The charge is $80.00 for up to 200 km, plus $0.15 for each km beyond 200.
 * (The function name says "profit"; it returns the charge for the customer.)
 * @param initial_mileage Integer representing the car's mileage before the rental.
 * @param final_mileage Integer representing the car's mileage when it is returned.
 * @return Double value representing the charge in dollars.
 */
double profit_calculator(int initial_mileage, int final_mileage) {
    int distance=final_mileage-initial_mileage;
    if (distance>=200) {
        return 80 + (distance-200)*0.15;
}
    return 80.00;
}

/**
 * Writes the list of cars to a text file, one car per line, in the format:
 *     plate,mileage,return_date
 * The return date is written as six digits (e.g. 050101) or as -1 if the car
 * has none. An existing file is overwritten. An empty list gives an empty file.
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 */
void write_list_to_file(char *filename, struct car *head) {
    FILE *fp_in= fopen(filename,"w");
    if (!fp_in) return; //if file is null exit
    struct car *current=head;
    while (current){ //while current is not null 
        fprintf(fp_in ,"%s,%d,%d\n",current->plate,current->mileage,current->return_date);
        current=current->next; //moves on to the next node
    }
    fclose(fp_in);
    return;
}

/**
 * Reads cars from a text file (format: plate,mileage,return_date) and adds
 * each one at the END of the list, in the order they appear in the file (no
 * sorting). If the file cannot be opened the list is left unchanged.
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 */
void read_file_into_list(char *filename, struct car **head) {
    FILE *fp_out= fopen(filename,"r");
    if (!fp_out) return;

    char plate[MAX_PLATE_LEN+1]; //create new 
    int mileage;
    int return_date;

    while (fscanf(fp_out, " %8[^,],%d,%d",plate, &mileage, &return_date) == 3) { //if the argument is equal to 3
        insert_to_list(head, plate, mileage, return_date);

    }

    fclose(fp_out);
}

/**
 * Prints a date in the format yy/mm/dd, without a newline. For example,
 * 261005 prints 26/10/05 and 050101 prints 05/01/01.
 * @param yymmdd Integer representing the date in yymmdd format.
 */
void date(int yymmdd) {
    int year=yymmdd/10000;
    int date_month=(yymmdd/100) %100;
    int date_day=yymmdd%100;
    printf("%02d/%02d/%02d",year,date_month,date_day);
    return;
}

/**
 * Frees all the memory allocated for the cars in the list and sets *head
 * to NULL.
 * @param head Pointer to the head of the list.
 */
void free_list(struct car ** head) {
    while (*head){
        struct car *next= (*head)->next;
        free(*head);
        *head=next;
    }
}
