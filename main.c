/*Name:MB Gagana
  Name of the project:AddressBook
  Date:08/04/2026
  Batch Name:int-26001B
  Description: an Addressbook is a C program used to store and manage contact details like name,phonenumber,email.
  it supports operations such as add,search,edit,delete and display contacts.
  it uses structures and file handling to organize and store data permanently.*/            

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"

int main()
{
     int option; //user choice
    AddressBook addressbook;//Addressbook structure
    addressbook.contact_count = 0;//addressbook contact count for track the conatcts


    initialize(&addressbook);   // INITIALIZE
    load_contacts(&addressbook); // LOAD FROM FILE
    
    //menu-driven loop
    do{
    printf(YELLOW"\n~~~~~~~~~~~*~~~~~~~~~~~~~~~~*~~~~~~~~~~~~~~~~~*~~~~~~~~~~~~~~~~~\n"RESET);
    printf(CYAN"\t\tADDRESS BOOK MENU"RESET); 
    printf(YELLOW"\n~~~~~~~~~~~*~~~~~~~~~~~~~~~~*~~~~~~~~~~~~~~~~~*~~~~~~~~~~~~~~~~~\n"RESET);
        printf(CYAN"1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n\n"RESET);
        printf("Enter the option : ");
        scanf("%d", &option);
        printf("\n");

        switch (option) 
        {
        case 1:
        {
            create_contact(&addressbook); //add  new contact
            break;
        }

        case 2:
        {
            search_contacts(&addressbook);//search contact
            break;
        }
        case 3:
        {
            edit_contact(&addressbook);//edit contact
            break;
        }
        case 4:
        {
            delete_contact(&addressbook);//delete contact
            break;
        }
        case 5:
        {
            printf(CYAN"------List Contacts------ :-\n\n"RESET);//list contacts
            list_contacts(&addressbook);
            break;
        }

        case 6:
       {
         printf(CYAN"Saving contacts\n"RESET);//save contacts
            save_contacts(&addressbook);
            break;
        }

        case 7:
            save_contacts(&addressbook);//save contacts to the file and exit
            printf(GREEN"INFO : Saving and Exit...\n"RESET);
            return 0;
        
        default:
            printf(RED"Invalid option \n"RESET);
            break;
        }
        printf("\n");
    }while(option!=8);
    
    return 0;

}