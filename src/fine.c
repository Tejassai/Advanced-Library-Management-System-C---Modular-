#include <stdio.h>
#include <sqlite3.h>
#include "../include/fine.h"

// simple rule: 10 per day late (mock logic)
void calculateFine(sqlite3 *db, int issue_id) {
    int daysLate;

    printf("Days late: ");
    scanf("%d", &daysLate);

    int fine = 0;
    if (daysLate > 0)
        fine = daysLate * 10;

    printf("Fine = %d\n", fine);

    char sql[200];
    sprintf(sql,
        "INSERT INTO fines(user_id, amount) VALUES((SELECT user_id FROM issues WHERE id=%d), %d);",
        issue_id, fine);

    sqlite3_exec(db, sql, 0, 0, NULL);
}
