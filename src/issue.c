#include <stdio.h>
#include <sqlite3.h>
#include "../include/issue.h"

void issueBook(sqlite3 *db, int user_id) {
    int book_id;
    char date[20];

    printf("Book ID: ");
    scanf("%d", &book_id);

    printf("Issue Date (YYYY-MM-DD): ");
    scanf("%s", date);

    char sql[200];
    sprintf(sql,
        "INSERT INTO issues(user_id, book_id, issue_date, returned) "
        "VALUES(%d, %d, '%s', 0);",
        user_id, book_id, date);

    sqlite3_exec(db, sql, 0, 0, NULL);

    // mark book unavailable
    sprintf(sql, "UPDATE books SET available=0 WHERE id=%d;", book_id);
    sqlite3_exec(db, sql, 0, 0, NULL);

    printf("Book issued!\n");
}

void returnBook(sqlite3 *db, int issue_id) {
    char return_date[20];

    printf("Return Date (YYYY-MM-DD): ");
    scanf("%s", return_date);

    char sql[200];

    sprintf(sql,
        "UPDATE issues SET return_date='%s', returned=1 WHERE id=%d;",
        return_date, issue_id);

    sqlite3_exec(db, sql, 0, 0, NULL);

    printf("Book returned!\n");
}
