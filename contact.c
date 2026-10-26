#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"
//function to initialize addressbook
void initialize(AddressBook *addressbook)
{
   FILE *fp;

    //  Initialize count
    addressbook->contact_count = 0;

     // Open file in read mode
    fp = fopen("contacts.txt", "r");

    if(fp == NULL)
    {
        printf(RED"No file found! Starting with empty address book.\n"RESET);
        return;
    }

    //  Read contact count
    fscanf(fp, "%d\n", &addressbook->contact_count);

    //  Read all contacts
    for(int i = 0; i < addressbook->contact_count; i++)
    {
        fscanf(fp, " %[^,],%[^,],%[^\n]\n",
            addressbook->contact_details[i].name,
            addressbook->contact_details[i].number,
            addressbook->contact_details[i].email);
    }

    //  Close file
    fclose(fp);

    printf(GREEN"Contacts loaded successfully during initialization!\n"RESET);
}
//function to create new contact.
//take input and validates name,number and email
void create_contact(AddressBook *addressbook)
{
    char ch;
    do
    {
        int i= addressbook->contact_count;
        
         do
        {
            printf("Enter name : ");
            scanf(" %[^\n]",addressbook->contact_details[i].name);
        }
        while(validate_name(addressbook->contact_details[i].name)==Failure ||
            existing_name(addressbook, addressbook->contact_details[i].name, -1)==Failure);

        do
        {
        printf("Enter phone number : ");
        scanf(" %[^\n]",addressbook->contact_details[i].number);
        }while(validate_number(addressbook->contact_details[i].number)==Failure || existing_number(addressbook,addressbook->contact_details[i].number, i)==Failure);
        
        do
        {
        printf("Enter email id : ");
        scanf(" %[^\n]",addressbook->contact_details[i].email);
        }while(validate_email(addressbook->contact_details[i].email)==Failure || existing_email(addressbook,addressbook->contact_details[i].email, i)==Failure);

        printf("\n");
        addressbook->contact_count ++;
        
        printf(YELLOW"Do you want to create more contact : Enter (Y/N) : "RESET);
        scanf(" %c",&ch);
    }while(ch=='y' || ch=='Y');
    if(ch=='n' || ch=='N')
    {
        printf(GREEN"\nContact Added Successfully : \n"RESET);
    }
}
//function to display all contacts
void list_contacts(AddressBook *addressbook)
{
    printf(YELLOW"%-20s%-20s%-30s\n","NAME:","PHONE NO:","EMAIL:"RESET);
    printf(YELLOW"%-20s%-20s%-30s\n", "----", "--------", "-----"RESET);
    for(int i=0;i<addressbook->contact_count;i++)
    {
        printf("%-20s%-20s%-30s",
            addressbook->contact_details[i].name,addressbook->contact_details[i].number,addressbook->contact_details[i].email);
        printf("\n");
    }
}
//function to provide search menu(name,number,email)
int search_contacts(AddressBook *addressbook)
{
    int option;
    int index=-1;
    do{
        printf(CYAN"1.Search by Name\n2.Search by Contact\n3.Search by mail\n4.return to main menu\n\n"RESET);
        printf("Enter the option : ");
        scanf("%d",&option);
        printf("\n");

        switch(option)
        {
            case 1:
            search_name(addressbook,&index);//search by name
            break;

            case 2:
            search_number(addressbook,&index);//search by number
            break;

            case 3:
            search_email(addressbook,&index);//search by email
            break;

            default:
            printf(RED"Invalid option\n"RESET); //invalid option
            break;
        }

    }while(option<4);
    return index;
}

Status search_name(AddressBook *addressbook,int *index) //function to search  name
{
    
    char name[25];
    do
    {
    printf("Enter name for search : ");
    scanf(" %[^\n]",name);
    }while(validate_name(name)==Failure);
    printf("\n");

    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(name,addressbook->contact_details[i].name)==0)
        {
            printf("Details:\n");
            printf("Name : %s\nNumber : %s\nEmail : %s\n\n",
                addressbook->contact_details[i].name,addressbook->contact_details[i].number,addressbook->contact_details[i].email);
            *index=i;
            return Success;
        }
        
    }
    
        printf(RED"Contact not found !!!\n\n"RESET);
        return Failure;

}

Status search_number(AddressBook *addressbook,int *index) //function to search number
{
   
    char number[11];
    do{
    printf("Enter number for search : ");
    scanf(" %[^\n]",number);
    }while(validate_number(number)==Failure);
    printf("\n");

    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(number,addressbook->contact_details[i].number)==0)
        {
           
            printf("Name : %s\nNumber : %s\nEmai : %s\n\n",
                addressbook->contact_details[i].name,addressbook->contact_details[i].number,addressbook->contact_details[i].email);
                *index=i;
                return Success;
        }
    }
    
        printf(RED"Contact not found !!!\n"RESET);
        return Failure;
}

Status search_email(AddressBook *addressbook,int *index) //function to search email
{
    
    char email[30];
    do
    {
    printf("Enter email for search : ");
    scanf(" %[^\n]",email);
    }while(validate_email(email)==Failure);
    printf("\n");

    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(email,addressbook->contact_details[i].email)==0)
        {
            printf("Name : %s\nNumber : %s\nEmai : %s\n\n",
                addressbook->contact_details[i].name,addressbook->contact_details[i].number,addressbook->contact_details[i].email);
            *index=i;
            return Success;
        }
    }
   
        printf(RED"Contact not found !!!\n"RESET);
        return Failure;
    
}

void edit_contact(AddressBook *addressbook)//function to edit contact
{
    int index=-1;
    int option;
    Status result=Failure;
    do{
        printf(CYAN"1.Search by Name\n2.Search by Contact\n3.Search by mail\n4.return to main menu\n\n"RESET);
        printf("Enter the option : ");
        scanf("%d",&option);
        printf("\n");
        
        switch(option)
        {
            case 1:
            result=search_name(addressbook,&index);
            break;

            case 2:
            result=search_number(addressbook,&index);
            break;

            case 3:
            result=search_email(addressbook,&index);
            break;

            case 4:
            printf(CYAN"Return to main menu\n"RESET);
            break;

            default:
            printf(RED"Invalid option\n"RESET);
            break;
        }

    }while(option<4 && result!=Success);

    if(result==Failure)
    {
        printf(RED"Contact not found!!!\n"RESET);
        return ;
    }
    
       int mode;
        printf(CYAN"\t\t---EDIT CONTACT---:\n"RESET);
        printf(CYAN"1.Name\n2.Number\n3.Email\n4.All\n"RESET);
       printf("Enter option:");
       scanf(" %d",&mode);
       if(mode==1 || mode==4)
       {
        do {
        printf("Enter new name:");
        scanf(" %[^\n]", addressbook->contact_details[index].name);
           } while(validate_name(addressbook->contact_details[index].name)==Failure);
       }
      if(mode==2 || mode==4)
      {
        do {
        printf("Enter new number:");
       scanf(" %[^\n]", addressbook->contact_details[index].number);
       } while(validate_number(addressbook->contact_details[index].number)==Failure ||
        existing_number(addressbook,addressbook->contact_details[index].number,index)==Failure);
       }
       if(mode==3 || mode==4)
        {
            do {
                printf("Enter new email:");
                scanf(" %[^\n]",addressbook->contact_details[index].email);
            } while(validate_email(addressbook->contact_details[index].email)==Failure ||
                    existing_email(addressbook,addressbook->contact_details[index].email,index)==Failure);
        }
}

void delete_contact(AddressBook *addressbook)//function to delete contact
{
    char ch;

    do
    {
        int option, index = -1;
        Status result = Failure;

        do{
            printf(CYAN"1.Search by Name\n2.Search by Contact\n3.Search by mail\n4.return to main menu\n\n"RESET);
            printf("Enter the option : ");
            scanf("%d",&option);
            printf("\n");
            
            switch(option)
            {
                case 1:
                    result = search_name(addressbook,&index);
                    break;

                case 2:
                    result = search_number(addressbook,&index);
                    break;

                case 3:
                    result = search_email(addressbook,&index);
                    break;

                case 4:
                    return;

                default:
                    printf(RED"Invalid option\n"RESET);
            }

        }while(option < 4 && result != Success);

        if(result == Failure)
        {
            printf(RED"Contact not found!!!\n"RESET);
        }
        else
        {
            printf(YELLOW"Are you sure want to delete this contact : (Y/N) :"RESET);
             scanf(" %c",&ch);

             if(ch=='Y' || ch=='y')
             {
            for(int i = index; i < addressbook->contact_count - 1; i++)
            {
                addressbook->contact_details[i] =
                    addressbook->contact_details[i + 1];
            }
            addressbook->contact_count--;
           // printf("Contact deleted Successfully :)\n\n");
           
           printf(GREEN"Contact deleted Successfully!:\n\n"RESET);
           
        }
        else
        {
            printf(RED"Contact not deleted\n"RESET);
        }
    }

        printf(YELLOW"Do you want to delete another contact (Y/N): "RESET);
        scanf(" %c", &ch);

    }while(ch=='Y' || ch=='y');
}
void load_contacts(AddressBook *addressbook)//function to load contacts
{
    FILE *fp = fopen("contacts.txt", "r");   // OPEN FILE

    if(fp == NULL)
    {
        printf(YELLOW"No file found! Starting fresh.\n"RESET);
        return;
    }

    fscanf(fp, "%d\n", &addressbook->contact_count);

    for(int i = 0; i < addressbook->contact_count; i++)
    {
        fscanf(fp, " %[^,],%[^,],%[^\n]\n",
            addressbook->contact_details[i].name,
            addressbook->contact_details[i].number,
            addressbook->contact_details[i].email);
    }

    fclose(fp);   // CLOSE FILE

    printf(GREEN"Contacts loaded successfully!\n"RESET);
}
void save_contacts(AddressBook *addressbook)//function to save contacts
{
    FILE *fp = fopen("contacts.txt", "w");   // OPEN FILE

    if(fp == NULL)
    {
        printf(RED"Error opening file!\n"RESET);
        return;
    }

    fprintf(fp, "%d\n", addressbook->contact_count);

    for(int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
            addressbook->contact_details[i].name,
            addressbook->contact_details[i].number,
            addressbook->contact_details[i].email);
    }

    fclose(fp);   // CLOSE FILE

    printf(GREEN"Contacts saved successfully!\n"RESET);
}
