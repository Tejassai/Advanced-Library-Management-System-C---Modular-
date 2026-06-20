#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "../include/auth.h"

int loginUser(sqlite3 *db, char *role) {
    char username[50], password[50];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    sqlite3_stmt *stmt;

    char sql[] = "SELECT role FROM users WHERE username=? AND password=?";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(role, (char*)sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
