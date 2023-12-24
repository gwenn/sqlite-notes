#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_exec(db, "CREATE TABLE test (data TEXT); \
                        INSERT INTO test (data) VALUES ('{\"equity_spot[at_andr]\":34.3}');", NULL, NULL, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to create table: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_prepare_v2(db, "UPDATE test SET data = json_set(data, '$.\"' || ? || '\"', json(32));", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    rc = sqlite3_bind_text(stmt, 1, "equity_spot[at_andr]", -1, SQLITE_TRANSIENT);
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

		rc = sqlite3_prepare_v2(db, "SELECT json_each.key, json_each.value FROM test, json_each(test.data);", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_step(stmt);
    if (SQLITE_OK != rc && SQLITE_DONE != rc && SQLITE_ROW != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    printf("%s, %s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1));

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
