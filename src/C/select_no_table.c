#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

int xAuth(void *udp, int action, const char *arg1, const char *arg2, const char *dbName, const char *triggerName) {
    printf("%d, %s, %s, %s, %s\n", action, arg1, arg2, dbName, triggerName);
    return SQLITE_OK;
}

int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_set_authorizer(db, xAuth, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: set authorizer: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_prepare_v2(db, "SELECT 1 WHERE 1 = 1", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_step(stmt);
    if (SQLITE_OK != rc && SQLITE_DONE != rc && SQLITE_ROW != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_finalize(stmt);


    rc = sqlite3_prepare_v2(db, "SELECT 1 WHERE 1 = ?", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_bind_int(stmt, 1, 1);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: bind param: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_step(stmt);
    if (SQLITE_OK != rc && SQLITE_DONE != rc && SQLITE_ROW != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);
}
