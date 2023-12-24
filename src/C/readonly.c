#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_prepare_v2(db, "CREATE TABLE test (data TEXT)", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_stmt_readonly(stmt);
    printf("%s read only? %d\n", sqlite3_sql(stmt), rc);
    rc = sqlite3_step(stmt);
    if (SQLITE_OK != rc && SQLITE_DONE != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_reset(stmt);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    //sqlite3_finalize(stmt);


    rc = sqlite3_prepare_v2(db, "DROP TABLE IF EXISTS test", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_stmt_readonly(stmt);
    printf("%s read only? %d\n", sqlite3_sql(stmt), rc);
    sqlite3_finalize(stmt);

    sqlite3_close(db);
}
