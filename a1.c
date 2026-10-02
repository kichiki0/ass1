/*
 * Name:
 * Student ID:
 * Date:
 * Assignment: CIS*2520 F26 Assignment 1 - Rental Car Linked Lists
 *
 * a1.c: main() and the menu loop of the car rental program.
 */

#include "a1.h"

/*
 * A basic menu based structure has been provided.
 */

int main(void) {

    /* Our three linked lists */
    struct car *available_head = NULL;
    struct car *rented_head = NULL;
    struct car *repair_head = NULL;

    int choice = 0;
    char buffer[100];
    int mileage;
    int total_mileage;
    int return_date;
    int month;
    int day;

    /*
     * TODO: restore the three lists from AVAILABLE_FILE, RENTED_FILE and
     * REPAIR_FILE here, before the menu starts.
     */
       read_file_into_list(AVAILABLE_FILE, &available_head);
       read_file_into_list(RENTED_FILE, &rented_head);
       read_file_into_list(REPAIR_FILE, &repair_head);

    do {
        prompt();

        if (scanf("%d", &choice) != 1) {
            if (feof(stdin)) {
                choice = 7;
            } else {
                choice = 0;
                while (getchar() != '\n' && !feof(stdin)) {
                }
            }
        }

        /*
         * You will need to add the code for each case:
         *  - Call the appropriate functions.
         *  - Check every input (plate, mileage, date) and print an error
         *    message when it is not valid.
         *  - Read the plate number into a buffer larger than 8 characters
         *    and limit the width, e.g.:  char buf[100]; scanf("%99s", buf);
         *    then check its length and characters yourself.
         *  - On quit (7): save the three lists to their files and free them.
         * File format: plate,mileage,return_date
         */
        switch (choice) {
        case 1:
            bool valid = true;

            printf("Enter plate number(The given requirement for plate number is a length of 2-8 characters with only numbers and letter): ");
            scanf("%99s", buffer);

            for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = toupper(buffer[i]); //turn all the caracters to upper case
                if (!isalnum(buffer[i])) { //if the character is not an alphabet or a naumber then it wont be valid
                    valid = false;
                }
            }

            if (strlen(buffer) <2 || strlen(buffer) > MAX_PLATE_LEN || !valid) { //if the length is less tahn 2 or more than the max plate length or if it is not valid
                printf("Invalid plate number.\n");
                break;
            }

            if (is_plate_in_list(available_head, buffer) || is_plate_in_list(rented_head, buffer) || is_plate_in_list(repair_head, buffer)) { //check if the plate is in the list fir all of them
                printf("Error: plate %s is already in the system.\n", buffer);
                break;
            }

            printf("Enter mileage: ");
            scanf("%d", &mileage);

            if (mileage < 0) { //if the mileage is less than 0
            printf("Invalid mileage.\n");
             break;
    }
            insert_to_list(&available_head, buffer, mileage, NO_RETURN_DATE);
            printf("Car %s has been added to the available-for-rent list.\n", buffer);
            break;

        case 2:
            /* TODO: returned car -> available-for-rent list, print the charge */
            valid = true;

            printf("Enter plate number(The given requirement for plate number is a length of 2-8 characters with only numbers and letter): ");
            scanf("%99s", buffer);
                   for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = toupper(buffer[i]); //turn all the caracters to upper case
                if (!isalnum(buffer[i])) { //if the character is not an alphabet or a naumber then it wont be valid
                    valid = false;
                }
            }

            if (strlen(buffer) <2 || strlen(buffer) > MAX_PLATE_LEN || !valid) { //if the length is less tahn 2 or more than the max plate length or if it is not valid
                printf("Invalid plate number.\n");
                break;
            }

            struct car *returned_car=remove_car_from_list(&rented_head, buffer);
            if (!returned_car) {
                printf("Error: plate %s is not in the system.\n", buffer);
                break;
            }

            printf("Enter current mileage: ");
            scanf("%d", &total_mileage);

            if (total_mileage < 0 || total_mileage <= returned_car->mileage) { //if the mileage is 0 or less than the previous mileage
                printf("Invalid mileage.\n");
                insert_to_list(&rented_head, returned_car->plate, returned_car->mileage, returned_car->return_date);
                free(returned_car);
                break;
            }

            insert_to_list(&available_head, returned_car->plate, total_mileage, NO_RETURN_DATE);
            printf("returned car have been added to the available for rent list.\n");
            printf("The charge for the customer is: $%.2f\n", profit_calculator(returned_car->mileage, total_mileage));
            free(returned_car);
            break;

        case 3:
            /* TODO: returned car -> repair list, print the charge */
            valid = true;

            printf("Enter plate number(The given requirement for plate number is a length of 2-8 characters with only numbers and letter): ");
            scanf("%99s", buffer);

            for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = toupper(buffer[i]); //turn all the caracters to upper case
                if (!isalnum(buffer[i])) { //if the character is not an alphabet or a naumber then it wont be valid
                    valid = false;
                }
            }

            if (strlen(buffer) <2 || strlen(buffer) > MAX_PLATE_LEN || !valid) { //if the length is less tahn 2 or more than the max plate length or if it is not valid
                printf("Invalid plate number.\n");
                break;
            }

            struct car *returned1_car=remove_car_from_list(&rented_head, buffer);
            if (!returned1_car) {
                printf("Error: plate %s is not in the system.\n", buffer);
                break;
            }

            printf("Enter current mileage: ");
            scanf("%d", &total_mileage);

            if (total_mileage < 0 || total_mileage <= returned1_car->mileage) { //if the mileage is 0 or less than the previous mileage
                printf("Invalid mileage.\n");
                insert_to_list(&rented_head, returned1_car->plate, returned1_car->mileage, returned1_car->return_date);
                free(returned1_car);
                break;
            }

            insert_to_list(&repair_head, returned1_car->plate, total_mileage, NO_RETURN_DATE);
            printf("returned car have been added to the repair list.\n");
            printf("The charge for the customer is: $%.2f\n", profit_calculator(returned1_car->mileage, total_mileage));
            free(returned1_car);
            break;

        case 4:
            /* TODO: repair list -> available-for-rent list */
            valid = true;
            printf("Enter plate number(The given requirement for plate number is a length of 2-8 characters with only numbers and letter): ");
            scanf("%99s", buffer);

            for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = toupper(buffer[i]); //turn all the caracters to upper case
                if (!isalnum(buffer[i])) { //if the character is not an alphabet or a naumber then it wont be valid
                    valid = false;
                }
            }

            if (strlen(buffer) <2 || strlen(buffer) > MAX_PLATE_LEN || !valid) { //if the length is less tahn 2 or more than the max plate length or if it is not valid
                printf("Invalid plate number.\n");
                break;
            }

           struct car *repair_car=remove_car_from_list(&repair_head, buffer);
            if (!repair_car) {
                printf("Error: plate %s is not in the system.\n", buffer);
                break;
            }

            insert_to_list(&available_head, repair_car->plate, repair_car->mileage, NO_RETURN_DATE);
            free(repair_car);
            printf("repaired car have been added to the available for rent list.\n");
            break;

        case 5:
            /* TODO: rent the first available car */

            printf("Expected date of return in yymmdd: ");
            scanf("%d", &return_date);

            if (return_date <= 0) {
                printf("Invalid return date.\n");
                break;
            }

            if (return_date < 100000 || return_date > 999999) {
                printf("Invalid return date.\n");
                break;
            }
            month=(return_date/100) %100;
            day=return_date%100;
            if (day<1 || day>31 || month<1 || month>12) { //if the day is less than 1 or more than 31 or if the month is less than 1 or more than 12
                printf("Invalid return date.\n");
                break;
            }

            struct car *rent_car=remove_first_from_list(&available_head);
            if (!rent_car){
                printf("No available cars to rent.\n");
                break;
            }
            insert_to_list(&rented_head, rent_car->plate, rent_car->mileage, return_date);
            printf("Car %s has been rented. Return date: ", rent_car->plate);
            date(return_date);
            printf("\n");
            free(rent_car);
            break;

        case 6:
            /* TODO: print all the lists */
            printf("Available-for-rent list:\n");
            print_list(available_head);
            printf("Rented list:\n");
            print_list(rented_head);
            printf("Repair list: \n");
            print_list(repair_head);
            break;

        case 7:
            /* TODO: save the lists to the files and free the memory */
            sort_list(&available_head, true, false);
            sort_list(&rented_head, false, true);
            sort_list(&repair_head, true, false);
            write_list_to_file(AVAILABLE_FILE, available_head);
            write_list_to_file(RENTED_FILE, rented_head);
            write_list_to_file(REPAIR_FILE, repair_head);
            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);
            break;

        default:
            /* TODO: print a message for an invalid choice */
            printf("Invalid choice. Please enter a number from (1-7)\n");
            break;
        }

    } while (choice != 7);

    return 0;
}
