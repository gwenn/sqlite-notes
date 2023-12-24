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
    rc = sqlite3_prepare_v2(db, "PRAGMA index_list('sqlite_master')", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_column_count(stmt);
    printf("column count before step? %d\n", rc);
    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc && SQLITE_ROW != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_column_count(stmt);
    printf("column count after step? %d\n", rc);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

