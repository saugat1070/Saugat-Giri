#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
struct bookinf{
    int bid;
    char bookname[70];
    char authorname[50];
    char bdate[20];
}book;
struct Studentinf{
    char roll[30];
    char sname[50];
    char sfaculty[50];
    int id;
    char bookName[50];
    char date[20];
}student;
FILE* fp;
int main()
{
        system("cls");
      int ch;
    printf("\t\t\t**************************************************************************************\t\t\n");
    printf("\t\t\t**************************************************************************************\t\t\n");
    printf("\t\t\t**********                    WELCOME TO LIBRARY                        **************\t\t\n");
    printf("\t\t\t**********                 PASHIMANCHAL CAMPUS,IOE                      **************\t\t\n");
    printf("\t\t\t**********                  Lamachaur, Kaski                            **************\t\t\n");
    printf("\t\t\t**************************************************************************************\t\t\n");
    printf("\t\t\t**************************************************************************************\t\t\n");
    printf("\t\t\t\t\t\t\t#MAIN SYSTEM OF LIBERARY \n");
    printf("\t\t\t 1.ADD_BOOKS\n");
    printf("\t\t\t 2.Display_BOOKS\n");
    printf("\t\t\t 3.Delete_Books\n");
    printf("\t\t\t 4 .Issue_Books\n");
    printf("\t\t\t 5.Issue Book List \n");
    printf("\t\t\t 0.Exit. \n");
    printf("Enter your choice:");
    scanf("%d",&ch);

    switch(ch){
case 1:
    addbook();
    break;
case 2:
    BookInfo();
    break;
case 3:
 Delete();
     break;
case 4:
    issueBook();
    break;
case 5:
    list();
    getchar();
    break;

    }
    getch();
        return 0;

      }


void addbook()
{

// <Taking time from system>
   char mydate[20];
time_t t = time(NULL);
struct tm tm = *localtime(&t);
sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
strcpy(book.bdate, mydate);

    // Adding Books Information
    fp=fopen("bookstore1.txt","ab");
    char ch;
    do{
        printf("Enter the book id:");
        scanf("%d",&book.bid);

        printf("Book Name:");
        fflush(stdin);
        gets(book.bookname);

        printf("Author Name:");
        fflush(stdin);
        gets(book.authorname);

        printf("Book Added Successfully \n If you add more books,press y:");
        scanf("%c",&ch);
    fwrite(&book, sizeof(book), 1, fp);
    }while(ch=='y');

    fclose(fp);

}
void BookInfo()
{
    system("cls");
    printf("\t\t\t\t\t Available Books\n");
    printf("\t\t\t\t\t-----------------\n\n");
    printf("\t %-15s %-30s %-30s %-30s","Book id","Book Name","Author Name","Date");
    fp=fopen("bookstore1.txt","rb");
    while(fread(&book, sizeof(book), 1, fp)==1)
    {
     printf("\n\t %-15d %-30s %-30s %-30s", book.bid, book.bookname, book.authorname, book.bdate);

    }
    fclose(fp);
}

    void Delete() {
    int id, f = 0;
    printf("%-30s", "Remove Section");
    printf("Enter the Book Code to remove:");
    scanf("%d", &id);
    FILE *ft;
    fp = fopen("bookstore1.txt", "rb");
    ft = fopen("temp.txt", "wb");
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (id != book.bid)
            {
            fwrite(&book, sizeof(book), 1, ft);
        }
        else {
            f = 1;
        }
    }
    fclose(fp);
    fclose(ft);
    if (f == 1) {
        remove("bookstore1.txt"); // Remove the original file
        rename("temp.txt", "bookstore1.txt"); // Rename temp file to original file name
        printf("\n\nDeleted Successfully\n");
    } else {
        printf("Record not found!\n");
    }
}
void issueBook()
{
    char mydate[12];
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
     sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
     strcpy(student.date, mydate);

  /*   int f1=0;
     printf("Issue Book Section\n");
     printf("Enter the Book Id:");
     scanf("%d",&student.id);
     fp=fopen("bookstore1.txt","rb");
     while(fread(&book,sizeof(book),1,fp)==1)
{
    if(student.id==book.bid)
    {
        strcpy(student.bookName,book.bookname);
        f1=1;
        break;
    }
}
if(f1==0)
{
    printf("No Book Found With This book id\n");
    printf("please Try Again");
}
fp = fopen("issuebystudent.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(student.sname);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(student.sfaculty);

    printf("Enter Student Roll: ");
    fflush(stdin);
    gets(student.roll);

    printf("Book Issued Successfully\n\n");

    fwrite(&student, sizeof(student), 1, fp);
    fclose(fp);*/
    int f1=0;
    char ch1;
    printf("Name:");
    fflush(stdin);
    gets(student.sname);
    printf("Roll No:");
    fflush(stdin);
    gets(student.roll);
    printf("Faculty");
    fflush(stdin);
    gets(student.sfaculty);
    fp=fopen("bookstore1.txt","rb");
        fp = fopen("issuebystudent.txt", "ab");

    do
    {
            printf("Enter the book code:");
    scanf("%d",&student.id);
     while(fread(&book,sizeof(book),1,fp)==1)
     {
         if(student.id==book.bid)
        {
            strcpy(student.bookName,book.bookname);
         student.id=book.bid;
        }
        else{
            printf("The book code you provided is not found!");
        }
     }
         fwrite(&student, sizeof(student), 1, fp);

        printf("To add more book,press y:");
        scanf("%c",&ch1);

    }while(ch1== 'y');
   // fwrite(&student, sizeof(student), 1, fp);
    fclose(fp);
}
void list()
{
    printf("%-20s","BOOK ISSUED BY SRUDENT\n");
    printf("%-10s %-30s %-20s %-10s %-30s  %-10s\n\n", "S.id", "Name", "Class", "Book Name", "Date");
    fp = fopen("issuebystudent.txt", "rb");
    while(fread(&student, sizeof(student), 1, fp)==1)
    {
        printf("%-10s %-30s %-20s %-10s %-30s  %-10s",student.roll,student.sname,student.sfaculty,student.bookName,student.date);
    }
    fclose(fp);

}





