#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "../include/db.h"
#include "../include/auth.h"
#include "../include/book.h"
#include "../include/issue.h"
#include "../include/fine.h"

void menuAdmin() {
    printf("\n--- ADMIN MENU ---\n");
    printf("1. Add Book\n");
    printf("2. View Books\n");
    printf("3. Search Book\n");
}

void menuStudent() {
    printf("\n--- STUDENT MENU ---\n");
    printf("1. View Books\n");
    printf("2. Issue Book\n");
    printf("3. Return Book\n");
}

int main() {
    sqlite3 *db = connectDB();
    initDB(db);

    char role[20];

    if (!loginUser(db, role)) {
        printf("Login failed\n");
        return 0;
    }

    printf("Login success as %s\n", role);

    int choice;

    while (1) {
        if (strcmp(role, "admin") == 0)
            menuAdmin();
        else
            menuStudent();

        printf("Choice: ");
        scanf("%d", &choice);

        if (strcmp(role, "admin") == 0) {
            if (choice == 1) addBook(db);
            else if (choice == 2) viewBooks(db);
            else if (choice == 3) searchBook(db);
        } else {
            if (choice == 1) viewBooks(db);
            else if (choice == 2) issueBook(db, 1);
            else if (choice == 3) returnBook(db, 1);
        }
    }
}

