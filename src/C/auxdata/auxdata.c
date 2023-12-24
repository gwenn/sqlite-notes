#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

static void reuseAuxDataCountFunc(
        sqlite3_context *ctx,
        int argc,
        sqlite3_value **argv
        ){
    int *reuseAuxDataCount;
    int value;
    (void)argc;  /* Unused parameter */

    reuseAuxDataCount = (int*)sqlite3_get_auxdata(ctx, 0);
    if (reuseAuxDataCount == NULL) {
        reuseAuxDataCount = (int *)malloc(sizeof(int));
        if (reuseAuxDataCount == NULL) {
            sqlite3_result_error_nomem(ctx);
            return;
        }
        *reuseAuxDataCount = 0;
        sqlite3_set_auxdata(ctx, 0, reuseAuxDataCount, free);
    } else {
        (*reuseAuxDataCount)++;
    }
    sqlite3_result_int(ctx, *reuseAuxDataCount);
}

int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char *zErrMsg = NULL;
    const char *z;
    int rc = 0;
    rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_create_function_v2(db, "reuseAuxDataCountFunc", 1, SQLITE_UTF8, 0, reuseAuxDataCountFunc, NULL, NULL, NULL);
    // at least, one constant must be passed to make SQLite reuse auxiliary data...
    rc = sqlite3_prepare_v2(db, "select reuseAuxDataCountFunc('test') from (select 1 union all select 2)", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    for (int i = 1; i <= 2; i++) {
        printf("loop %d\n", i);
        rc = sqlite3_step(stmt);
        while (rc == SQLITE_ROW) {
            z = (const char*)sqlite3_column_text(stmt, 0);
            printf("%s\n", z);
            rc = sqlite3_step(stmt);
        }
        if (SQLITE_OK != rc && SQLITE_DONE != rc) {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
            exit(1);
        }
        rc = sqlite3_reset(stmt);
        if (SQLITE_OK != rc) {
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
            exit(1);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
