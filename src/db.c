#include <stdio.h>
#include <sqlite3.h>
#include "../include/db.h"

sqlite3* connectDB() {
    sqlite3 *db;
    int rc = sqlite3_open("library.db", &db);

    if (rc) {
        printf("Can't open database\n");
        return NULL;
    }

    return db;
}

void initDB(sqlite3 *db) {
    char *err;

    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, username TEXT, password TEXT, role TEXT);",
        0, 0, &err);

    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS books(id INTEGER PRIMARY KEY, name TEXT, author TEXT, available INTEGER);",
        0, 0, &err);

    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS issues(id INTEGER PRIMARY KEY, user_id INT, book_id INT, issue_date TEXT, return_date TEXT, returned INT);",
        0, 0, &err);
}
