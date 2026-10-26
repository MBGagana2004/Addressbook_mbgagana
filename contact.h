#include<stdio.h>
#include<string.h>
#include<ctype.h>
#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
//COLORS 
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
//structure to store single contact details
typedef struct Contact_data
{
    char name[35]; //contact name
    char number[11]; //phone number
    char email[36]; //email id
}contacts;
//structure to store entire addressbook
typedef struct AddressBook_Data
{
    contacts contact_details[100]; //array of contacts
    int contact_count; //total number of contacts
} AddressBook;
//status used for validation functions
typedef enum Status_info
{
    Failure,
    Success,
} Status;

//function declarations
void initialize(AddressBook *addressbook);  //initialize contacts
void save_contacts(AddressBook *addressbook); //save all contacts
void load_contacts(AddressBook *addressbook); //load contacts from file
Status existing_name(AddressBook *addressbook, char *name, int current_index); //check duplicate name
void create_contact(AddressBook *addressbook); // create contacts
void list_contacts(AddressBook *addressbook); //list contacts
int search_contacts(AddressBook *addressbook); //search contacts
Status search_name(AddressBook *addressbook,int *index); //search by name
Status search_number(AddressBook *addressbook,int *index); //search by number
Status search_email(AddressBook *addressbook,int *index); //search by email
void edit_contact(AddressBook *addressbook); //edit all contact details
Status validate_name(char *name); //validate name
Status validate_number(char *number);//validate number
Status existing_number(AddressBook *addressbook,char *num, int current_index);// check duplicate number
Status validate_email(char *email);//validate email
Status existing_email(AddressBook *addressbook, char *e, int current_index);//check duplicate email
void delete_contact(AddressBook *addressbook);//delete contacts


#endif
// CONTACT_H
// CONTACT_H