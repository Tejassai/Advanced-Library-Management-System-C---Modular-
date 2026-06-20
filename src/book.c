#include <stdio.h>
#include <sqlite3.h>
#include "../include/book.h"

void addBook(sqlite3 *db) {
    int id;
    char name[50], author[50];

    printf("Book ID: ");
    scanf("%d", &id);

    printf("Name: ");
    scanf("%s", name);

    printf("Author: ");
    scanf("%s", author);

    char sql[200];
    sprintf(sql,
        "INSERT INTO books VALUES (%d, '%s', '%s', 1);",
        id, name, author);

    char *err;
    sqlite3_exec(db, sql, 0, 0, &err);

    printf("Book added!\n");
}

void viewBooks(sqlite3 *db) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db,
        "SELECT * FROM books;",
        -1, &stmt, NULL);

    printf("\nID | Name | Author | Available\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%d | %s | %s | %d\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_int(stmt, 3));
    }

    sqlite3_finalize(stmt);
}

void searchBook(sqlite3 *db) {
    int id;
    printf("Enter book ID: ");
    scanf("%d", &id);

    sqlite3_stmt *stmt;

    char sql[] = "SELECT * FROM books WHERE id=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Found: %s by %s\n",
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2));
    } else {
        printf("Not found\n");
    }

    sqlite3_finalize(stmt);
}
