/*This project is prepare by:
    NAME                     ROLL NO
    Aayushma Khanal        PAS080BEI003
    Prem Joshi             PAS080BEI023
    Shambhu SAH            PAS080BEI035
    Saugat Giri            PAS080BEI033
    */
/* Library Management System Program */

#include<stdio.h>
#include<stdlib.h>
#include<time.h> //time.h header file is used to take local time from the system.

// Structure to represent a book
struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12]; // Date format DD/MM/YYYY
} b;

// Structure to represent a student
struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50]; // Name of the book issued to the student
    char date[12]; // Date format DD/MM/YYYY
} s;

FILE *fp; // File pointer

// Function prototypes
void addBook();
void booksList();
void del();
void issueBook();
void issueList();

int main() {
    int ch;

    // Main menu loop
    while (1) {
        system("cls");
                // Displaying the welcome message
        printf("\t\t\t**************************************************************************************\t\t\n");
        printf("\t\t\t**********                    WELCOME TO LIBRARY                        **************\t\t\n");
        printf("\t\t\t**********                 PASHIMANCHAL CAMPUS,IOE                      **************\t\t\n");
        printf("\t\t\t**********                  Lamachaur, Kaski                            **************\t\t\n");
        printf("\t\t\t**************************************************************************************\t\t\n");
        printf("\t\t\t**************************************************************************************\t\t\n");
        printf("\t\t\t\t\t\t\t#MAIN SYSTEM OF LIBERARY \n");
        // Displaying the menu options
        printf("\t\t\t 1.ADD_BOOKS\n");
        printf("\t\t\t 2.Display_BOOKS\n");
        printf("\t\t\t 3.Delete Books\n");
        printf("\t\t\t 4.Issue Book \n");
        printf("\t\t\t 5.Issue book list\n");
        printf("\t\t\t 0.Exit. \n");
        printf("Enter your choice:");
        scanf("%d", &ch);

        // Switch case to handle user choice
        switch (ch) {
            case 0:
                exit(0);
            case 1:
                addBook();
                break;
            case 2:
                booksList();
                break;
            case 3:
                del();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                issueList();
                break;
            default:
                printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}

// Function to add a book to the library
void addBook() {
    char myDate[12];
    // Get current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);
    char y;

    // Open file in append mode to add books
    fp = fopen("books.txt", "ab");
    do {
        printf("Enter book id: ");
        scanf("%d", &b.id);

        printf("Enter book name: ");
        fflush(stdin);
        gets(b.bookName);

        printf("Enter author name: ");
        fflush(stdin);
        gets(b.authorName);

        // Confirmation message for adding more books
        printf("Book Added Successfully");
        printf("You want add more book,if yes press y");
        scanf(" %c", &y);

        // Write book information to the file
        fwrite(&b, sizeof(b), 1, fp);
    } while (y == 'y');
            fclose(fp);

}

// Function to display list of available books
void booksList() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    // Open file in read mode to display books
    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

// Function to delete a book from the library
void del() {
    int id, f = 0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    // Open books file in read mode and temp file in write mode
    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.");
    } else {
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    // Remove old books file and rename temp file to books file
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

// Function to issue a book to a student
void issueBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    strcpy(s.date, myDate);

    int f = 0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    // Check if the requested book is available
    fp = fopen("books.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }

    if (f == 0) {
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    // Open issue file in append mode to add issued books
    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    // Write issued book information to the file
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

// Function to display list of issued books
void issueList() {
    system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    // Open issue file in read mode to display issued books
    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}

