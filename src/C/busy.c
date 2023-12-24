#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    rc = sqlite3_open_v2("", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_exec(db, "BEGIN EXCLUSIVE", NULL, NULL, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: tx start: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_prepare_v2(db, "ROLLBACK", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_stmt_busy(stmt);
    printf("%s busy before step? %d\n", sqlite3_sql(stmt), rc);
    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_stmt_busy(stmt);
    printf("%s busy after step? %d\n", sqlite3_sql(stmt), rc);

    rc = sqlite3_reset(stmt);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_stmt_busy(stmt);
    printf("%s busy after reset? %d\n", sqlite3_sql(stmt), rc);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

