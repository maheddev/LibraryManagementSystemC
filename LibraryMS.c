#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
#include<string.h>
struct book
{
    int id;
    int isbn;
    char name[20];
    char author[20];
    int edition;
    int copies;
    int copiesleft;
}b,bc;
struct date
{
    int dd,mm,yy;
};
struct user
{
    int id;
    char name[20];
    int bookid;
    struct date issue;
    struct date due;
}u,uc;
int mainmenu();
void addbook(void);
int bidcheck(int);
void deletebook(int);
void editbook(void);
void listbook(void);
void issuebook(void);
void issuebookmain(void);
void adduser();
void deleteuser(int);
void searchbookbyisbn(void);
void searchbookbyname(void);
void searchbookbyauthor(void);
int uidcheck(int);
int validdatecheck(struct date);
void duedate(void);
FILE *pb,*pu;

int main(int argc, char const *argv[])
{
    back:
    system("CLS");
    printf("\n\t\t\t\t                    ____________");
    printf("\n\t\t\t\t              ______________________");
    printf("\n\t\t\t\t          ________________________________");
    printf("\n\t\t\t\t    ___________________________________________");
    printf("\n\t\t\t\t __________________________________________________");
    printf("\n\t\t\t\t|--------------------------------------------------|");
    printf("\n\t\t\t\t|---------- [ LIBRARY MANAGMENT SYSTEM ] ----------|");
    printf("\n\t\t\t\t|--------------------------------------------------|");
    printf("\n\t\t\t\t|----- [ Developed By *Mahed Shahzad Nasir* ] -----|");
    printf("\n\t\t\t\t|--------------------------------------------------|");
    printf("\n\t\t\t\t|------------ [ REG # FA20-BCS-032 ] --------------|");
    printf("\n\t\t\t\t|--------------------------------------------------|");
    printf("\n\t\t\t\t|___________ Press '''ENTER''' to Proceed _________|");
    printf("\n\t\t\t\t    ___________________________________________");
    printf("\n\t\t\t\t          ________________________________");
    printf("\n\t\t\t\t              ______________________");
    printf("\n\t\t\t\t                    ____________\n\n");
    
    if(getch() == 13)
    {
        mainmenu();
    }
        
    else
    {
        printf("\n\n=================  Invalid Input  =================\n\n");
        goto back;
    }
    return 0;
}

int mainmenu()
{
    int choice;
    do{
        system("cls");
        printf("\n\n====================================================\n");
        printf("=========={{{ LIBRARY MANAGMENT SYSTEM }}}==========\n");
        printf("=================={{{ Main Menu }}}=================");
        printf("\n====================================================\n\n");
        printf("Please enter the serial number of your specific task\n\n1. Add Book\n2. Delete Book\n3. Search Book\n4. Modify/Update a book record\n5. Display all the books in library\n6. Issue book to any one\n7. Exit\n\n====================================================\n\nEnter your choice here: ");
        scanf("%d",&choice);

        switch (choice){
                case 1: addbook(); break;
            case 2: deletebook(0); break;
            case 3:
                system("cls");
                printf("\n====================================================\n");
                printf("=============={{{ SEARCH BOOK MENU }}}==============");
                printf("\n====================================================\n");
                int search_choice;
                printf("Press 1 to search by book ISBN Number\nPress 2 to search by book name\nPress 3 to search by Author name\nYour Choice: ");
                scanf("%d",&search_choice);
                switch (search_choice){
                    case 1: searchbookbyisbn(); break;
                    case 2: searchbookbyname(); break;
                    case 3: searchbookbyauthor(); break;
                }
                break;
            case 4: editbook(); break;
            case 5: listbook(); break;
            case 6: issuebook(); break;
            case 7:
            {
                system("cls");
                printf("\n====================================================\n");
                printf("=============={{{ EXIT SYSTEM MENU }}}==============");
                printf("\n====================================================\n");

                printf("\n\nPress ''Enter'' to Exit\n\nAny other Key to Go Back");
                if (getch()==13)
                {  
                    system("CLS");
                    printf("\n\n=========={{{{ System is Exiting }}}}==========\n");
                    printf("==========={{ THANK YOU FOR USING }}===========\n\n");
                    system("PAUSE");
                    exit(0);
                    
                }
                else
                {
                    system("CLS");
                    mainmenu();
                }
                break;
            }
            default:
                printf("\nInvalid Choice");
                getch();
        }
    }while(1);
    return 0;
}
void addbook(void)
{
    pb=fopen("Books.txt","a");
    char ch;
    do
    {
        label:
        system("cls");
        printf("\n====================================================\n");
        printf("==============={{{ Add Book Menu }}}================");
        printf("\n====================================================\n");
        printf("\nPlease Enter the following details");
        printf("\nSerial number of the Book:      ");
        scanf("%d",&b.id);
        if(bidcheck(b.id)==0)
        {
            printf("ISBN Number of the Book:        ");
            scanf("%d",&b.isbn);
            printf("Name of the Book :              ");
            scanf(" %[^\n]s",b.name);
            printf("Author of the Book:             ");
            scanf(" %[^\n]s",b.author);
            printf("Edition of the Book:            ");
            scanf("%d",&b.edition);
            printf("No. Copies of the Book :        ");
            scanf("%d",&b.copies);
            b.copiesleft=b.copies;
            fwrite(&b,sizeof(struct book),1,pb);
            printf("\n==============Book Added Successfully===============\n");
            printf("\nDo you want to enter details of another book? (Y/N)");
            scanf(" %c",&ch);
        }
        else
        {
            printf("\nBookId already exists ");
            printf("\nPress any key to continue ");
            getch();
            goto label;
        }
    }while(ch=='Y'||ch=='y');
    fclose(pb);
    return;
}
void editbook(void)
{
    int id,choice;
    char ch;
    system("cls");
    printf("\n====================================================\n");
    printf("==============={{{ Edit Book Menu }}}===============");
    printf("\n====================================================\n");
    printf("\nEnter the serial No. you want to edit : ");
    scanf("%d",&id);
    if(bidcheck(id)==1)
    {
        deletebook(id);
        struct book be;
        be=bc;
        l2:
        printf("\nExisting Book Information : ");
        printf("\nSerial number of the Book:      %d \n1. isbn : %d \n2. Book Name : %s \n3. Author : %s \n4. Edition : %d \n5. Number of copies : %d ",be.id,be.isbn,be.name,be.author,be.edition,be.copies);
        printf("\nPlease Enter the field to edit : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: printf("\nEnter the New ISBN : ");
                    scanf("%d",&be.isbn);
                    break;
            case 2: printf("\nEnter the new book name : ");
                    scanf(" %[^\n]s",be.name);
                    break;
            case 3: printf("\nEnter the new author name : ");
                    scanf(" %[^\n]s",be.author);
                    break;
            case 4: printf("\nEnter the New Edition: ");
                    scanf("%d",&be.edition);
                    break;
            case 5: printf("\nEnter the new number of copies : ");
                    int temp;
                    temp=be.copies;
                    scanf("%d",&be.copies);
                    be.copiesleft=be.copiesleft+be.copies-temp;
                    break;
            default: printf("\nInvalid choice");
                     printf("\nPress any key to continue");
                     getch();
                     goto l2;
        }
        printf("\nDo you want to edit anything else ? (Y/N)");
        scanf(" %c",&ch);
        if(ch=='Y'||ch=='y')
                goto l2;
        pb=fopen("Books.txt","a");
        fwrite(&be,sizeof(struct book),1,pb);
        fclose(pb);
        printf("\nBook Successfully updated ");
        printf("\nPress any key to continue ");
        getch();
    }
    else
    {
        printf("\nEntered BookId does not exist");
        printf("\nPress any key to continue");
        getch();
    }
    return;
}
void deletebook(int id)
{
    FILE *temp;
    int flag=0;
    temp=fopen("temp.txt","w");
    if(id==0)
    {
        flag=1;
        label:
        system("cls");
        printf("\n====================================================\n");
        printf("=============={{{ Delete Book Menu }}}==============");
        printf("\n====================================================\n");
        printf("\nEnter the BookId to be deleted : ");
        scanf("%d",&id);
        if(bidcheck(id)==0)
        {
            printf("\n\nBookId does not exist");
            printf("\n\nPress Enter to try again\n\nPress Space to go Back\n");
            if(getch() == (13))
            {goto label;}
            else {mainmenu();}
        }
    }
    pb=fopen("Books.txt","r");
    while(!feof(pb))
    {
        if(fread(&b,sizeof(struct book),1,pb)==1)
            if(b.id!=id)
                fwrite(&b,sizeof(struct book),1,temp);
    }
    fclose(pb);
    fclose(temp);
    remove("Books.txt");
    rename("temp.txt","Books.txt");
    if(flag)
    {
        printf("\n\nBook successfully deleted");
        printf("\n\nPress any key to continue");
        getch();
    }
    return;
}
int bidcheck(int id)
{
    FILE *b;
    int i=0;
    b=fopen("Books.txt","r");
    while(!feof(b))
    {
        if(fread(&bc,sizeof(struct book),1,b)==1)
            if(bc.id==id)
        {
            i=1;
            break;
        }
    }
    fclose(b);
    return i;
}
void listbook(void)
{
    pb=fopen("Books.txt","r");
    system("cls");
    printf("\n\t\t\t\t\t====================================================\n");
    printf("\t\t\t\t\t============={{{ DISPLAY BOOK MENU }}}==============");
    printf("\n\t\t\t\t\t====================================================\n");
    printf("\n%5s %20s %30s %30s %12s %20s %20s\n","Id","ISBN","Book Name","Author Name","Edition","No.of Copies","Copies Left");
    while(!feof(pb))
    {
        if(fread(&b,sizeof(struct book),1,pb)==1)
        printf("\n\n%5d %20d %30s %30s %12d %20d %20d ",b.id,b.isbn,b.name,b.author,b.edition,b.copies,b.copiesleft);
    }
    fclose(pb);
    printf("\n\n\t\t\t\t\t===========[Press any key to continue]==============");
    getch();
    return;
}
void issuebook(void)
{
    system("cls");
    printf("\n====================================================\n");
    printf("=============={{{ ISSUE BOOK MENU }}}===============");
    printf("\n====================================================\n");
    printf("\nEnter 0 to add New User\nUser id for existing user: ");
    int idb,idu;
    scanf("%d",&idu);

    if (idu == 0)
    {
        adduser();
        issuebookmain();
    }
    else
        issuebookmain();
    return;
}
int validdatecheck(struct date a)
{
    if((a.dd>=1)&&(a.dd<=30)&&(a.mm>=1)&&(a.mm<=12)&&(a.yy>2000))
        return 1;
    else
        return 0;
}
void duedate(void)
{
    uc.due=uc.issue;
    uc.due.dd+=30;
    if(uc.due.dd>30)
    {
        uc.due.dd-=30;
        uc.due.mm++;
        if(uc.due.mm>12)
        {
            uc.due.mm-=12;
            uc.due.yy++;
        }
    }
    return;
}
void searchbookbyname(void)
{
    pb=fopen("Books.txt","r");
    char ch,name[20];int i;
    do
    {
        system("cls");
        i=0;
        rewind(pb);
        printf("\n====================================================\n");
        printf("============={{{ SEARCH BOOK (NAME) }}}=============");
        printf("\n====================================================\n");
        printf("\nEnter the name of the book to search : ");
        scanf(" %[^\n]s",name);
        while(!feof(pb))
        {
            if(fread(&b,sizeof(struct book),1,pb)==1)
            if(strcmpi(b.name,name)==0)
            {
                i++;
                printf("\nSearch results : %d",i);
                printf("\nBookId : %d \nIsbn : %d \nBook Name : %s \nAuthor : %s \nEdition : %d \nNumber of copies : %d \nNumber of copies left : %d",b.id,b.isbn,b.name,b.author,b.edition,b.copies,b.copiesleft);
            }
        }
    if(i==0)
        printf("\nNo such book found");
    printf("\n\nDo you want to search for any other book ? (Y/N)");
    scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    fclose(pb);
    return;
}
void searchbookbyisbn(void)
{
    pb=fopen("Books.txt","r");
    char ch;int i, isbn;
    do
    {
        system("cls");
        i=0;
        rewind(pb);
        printf("\n====================================================\n");
        printf("============={{{ SEARCH BOOK (ISBN) }}}=============");
        printf("\n====================================================\n");
        printf("\nEnter the ISBN number of the book to search : ");
        scanf(" %d",&isbn);
        while(!feof(pb))
        {
            if(fread(&b,sizeof(struct book),1,pb)==1)
            if(b.isbn==isbn)
            {
                i++;
                printf("\nSearch Result : %d",i);
                printf("\nBookId : %d \nIsbn : %d \nBook Name : %s \nAuthor : %s \nEdition : %d \nNumber of copies : %d \nNumber of copies left : %d",b.id,b.isbn,b.name,b.author,b.edition,b.copies,b.copiesleft);
            }
        }
    if(i==0)
        printf("\nNo such book found");
    printf("\n\nDo you want to search for any other book ? (Y/N)");
    scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    fclose(pb);
    return;
}
void searchbookbyauthor(void)
{
    pb=fopen("Books.txt","r");
    char ch,author[20];int i;
    do
    {
        system("cls");
        i=0;
        rewind(pb);
        printf("\n====================================================\n");
        printf("============{{{ SEARCH BOOK (AUTHOR) }}}============");
        printf("\n====================================================\n");
        printf("\nEnter the name of Author of the book to search : ");
        scanf(" %[^\n]s",author);
        while(!feof(pb))
        {
            if(fread(&b,sizeof(struct book),1,pb)==1)
            if(strcmpi(b.author,author)==0)
            {
                i++;
                printf("\nSearch Result : %d",i);
                printf("\nBookId : %d \nIsbn : %d \nBook Name : %s \nAuthor : %s \nEdition : %d \nNumber of copies : %d \nNumber of copies left : %d",b.id,b.isbn,b.name,b.author,b.edition,b.copies,b.copiesleft);
            }
        }
    if(i==0)
        printf("\nNo such book found");
    printf("\n\nDo you want to search for any other book ? (Y/N)");
    scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    fclose(pb);
    return;
}
int uidcheck(int id)
{
    FILE *u;
    int i=0;
    u=fopen("Users.txt","r");
    while(!feof(u))
    {
        if(fread(&uc,sizeof(struct user),1,u)==1)
            if(uc.id==id)
        {
            i=1;
            break;
        }
    }
    fclose(u);
    return i;
}
void deleteuser(int id)
{
    FILE *temp;
    int flag=0;
    temp=fopen("temp.txt","w");
    if(id==0)
    {
        flag=1;
        label:
        system("cls");
        printf("\nDelete User");
        printf("\nEnter the UserId to be deleted : ");
        scanf("%d",&id);
        if(uidcheck(id)==0)
        {
            printf("\nUserId does not exist");
            printf("\nPress any key to continue");
            getch();
            goto label;
        }
    }
    pu=fopen("Users.txt","r");
    while(!feof(pu))
    {
        if(fread(&u,sizeof(struct user),1,pu)==1)
            if(u.id!=id)
                fwrite(&u,sizeof(struct user),1,temp);
    }
    fclose(pu);
    fclose(temp);
    remove("Users.txt");
    rename("temp.txt","Users.txt");
    if(flag)
    {
        printf("\nUser successfully deleted");
        printf("\nPress any key to continue");
        getch();
    }
    return;
}
void adduser(void)
{
    pu=fopen("Users.txt","a");
    char ch;
    do
    {
        label:
        system("cls");
        printf("\nAdd User");
        printf("\nPlease Enter the following details");
        printf("\nUserId : ");
        scanf("%d",&u.id);
        if(uidcheck(u.id)==0)
        {
            printf("\nName : ");
            scanf(" %[^\n]s",u.name);
            u.bookid=0;
            u.issue.dd=u.issue.mm=u.issue.yy=u.due.dd=u.due.mm=u.due.yy=0;
            fwrite(&u,sizeof(struct user),1,pu);
            printf("\nUser Successfully added");
            printf("\nDo you want to enter details of another user? (Y/N)");
            scanf(" %c",&ch);
        }
        else
        {
            printf("\nUserId already exists");
            printf("\nPress any key to continue");
            getch();
            goto label;
        }
    }while(ch=='Y'||ch=='y');
    fclose(pu);
    return;
}
void issuebookmain(void)
{
    printf("Please Enter the User Id: ");
    int idb,idu;
    scanf("%d",&idu);
    if(uidcheck(idu)==1)
    {
        if(uc.bookid>0)
        {
            printf("\nOne Book is already issued");
            printf("\nPress any key to continue");
            getch();
        }
        else
        {
            printf("\nEnter the BookId to be issued : ");
            scanf("%d",&idb);
            if(bidcheck(idb)==1)
            {
                if(bc.copiesleft==0)
                {
                    printf("\nBook not available now");
                    printf("\nPress any key to continue");
                    getch();
                }
                else
                {
                    do
                    {
                        printf("\nEnter the date of issue : (dd-mm-yyyy) : ");
                        scanf("%d-%d-%d",&uc.issue.dd,&uc.issue.mm,&uc.issue.yy);
                        if(validdatecheck(uc.issue))
                            break;
                        printf("\nEnter a valid date");
                        getch();
                    }while(1);
                    duedate();
                    printf("\nThe due date is : %d-%d-%d ",uc.due.dd,uc.due.mm,uc.due.yy);
                    deleteuser(uc.id);
                    pu=fopen("Users.txt","a");
                    uc.bookid=idb;
                    fwrite(&uc,sizeof(struct user),1,pu);
                    fclose(pu);
                    deletebook(bc.id);
                    pb=fopen("Books.txt","a");
                    bc.copiesleft--;
                    fwrite(&bc,sizeof(struct book),1,pb);
                    fclose(pb);
                    printf("\nBook Issued Successfully");
                    printf("\nPress any key to continue");
                    getch();
                }
            }
            else
            {
                printf("\nBookId does not exist");
                printf("\nPress any key to continue");
                getch();
            }
        }
    }
    else
    {
        printf("\nUserId does not exist");
        printf("\nPress any key to continue");
        getch();
    }
}  