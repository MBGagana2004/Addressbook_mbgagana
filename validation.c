#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"

//function to validate name(only alphabets and spaces allowed)
Status validate_name(char *name)
{
    for(int i=0;name[i]!='\0';i++)
    {
    if(!isalpha(name[i]) && name[i]!=' ')
    {
        printf(RED"Name should contain only alphabets and space!!!\n"RESET);
        return Failure;
    }
    }
    return Success;
}
//function to check duplicate name in addressbook
Status existing_name(AddressBook *addressbook, char *name, int current_index)
{
    for(int i = 0; i < addressbook->contact_count; i++)
    {
        if(i != current_index && strcmp(addressbook->contact_details[i].name, name) == 0)
        {
            printf(RED "Name already exists! Try again.\n" RESET);
            return Failure;
        }
    }
    return Success;
}
//function to validate phone number
//conditions
Status validate_number(char *number)
{
    if(strlen(number)!=10)//must be 10 digits
    {
        printf(RED"Number should be of 10 digits!!!\n"RESET);
        return Failure;
    }
    for(int j=0;number[j]!='\0';j++)
    {
        if(!isdigit(number[j]))//only digits allowed
        {
            printf(RED"Number must contain digit numbers only!!!\n"RESET);
           
            return Failure;
        }
    }
        if(number[0]<'6' || number[0]>'9')//should start with 6-9
        {
            printf(RED"It should start between '6 to 9' !!!\n"RESET);
            
            return Failure;
        }
        return Success;
}
//function to check duplicate phone number
Status existing_number(AddressBook *addressbook, char *num, int current_index)
{
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(i != current_index && strcmp(addressbook->contact_details[i].number,num)==0)
        {
            printf(RED"Number already exist! Try again.\n"RESET);
            return Failure;
        }
    }
    return Success;
}
//function to validate email format
//conditions
Status validate_email(char *email)
{
    int len = strlen(email);
    int at_count = 0;
    char *at = NULL;
    char *p;

    if(len == 0)
    {
        printf(RED"Email cannot be empty!!!\n"RESET);
        return Failure;
    }

    for(int i = 0; email[i] != '\0'; i++)
    {
        char ch = email[i];

        if(isupper(ch))
        {
            printf(RED"Email should contain only lowercase letters!!!\n"RESET);
            return Failure;
        }

        if(!isalnum(ch) && ch != '.' && ch != '_' && ch != '-' && ch != '@')
        {
            printf(RED"Email contains invalid characters!!!\n"RESET);
            return Failure;
        }

        if(ch == '@')
        {
            at_count++;
            at = email + i;
        }
    }

    if(at_count != 1)
    {
        printf(RED"Email must contain exactly one '@'!!!\n"RESET);
        return Failure;
    }

    if(at == NULL || at == email || at + 1 == email + len)
    {
        printf(RED"Email must contain text before and after '@'!!!\n"RESET);
        return Failure;
    }

    if(strcmp(at, "@gmail.com") != 0)
    {
        printf(RED"Email must be a valid Gmail address ending with '@gmail.com'!!!\n"RESET);
        return Failure;
    }

    for(p = email; p < at; p++)
    {
        if(!isalnum(*p) && *p != '.' && *p != '_' && *p != '-')
        {
            printf(RED"Invalid character in email name!!!\n"RESET);
            return Failure;
        }
    }

    if(at == email || *(at - 1) == '.' || *(at - 1) == '_' || *(at - 1) == '-')
    {
        printf(RED"Email local part cannot start or end with special characters!!!\n"RESET);
        return Failure;
    }

    for(p = email; p < at - 1; p++)
    {
        if(*p == '.' && *(p + 1) == '.')
        {
            printf(RED"Email local part cannot contain consecutive dots!!!\n"RESET);
            return Failure;
        }
    }

    return Success;
}
//function to check duplicate email
Status existing_email(AddressBook *addressbook,char *e, int current_index)
{
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(i != current_index && strcmp(addressbook->contact_details[i].email,e)==0)
        {
            printf(RED"email id already exist !!! Try again.\n"RESET);
            return Failure;
        }
    }
    return Success;
}

