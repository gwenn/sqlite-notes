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

    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY NOT NULL, name TEXT); \
                        INSERT INTO test (name) VALUES ('Bart'), ('Lisa');", NULL, NULL, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to create table: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_prepare_v2(db, "SELECT * FROM TEST", -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: prepare stmt: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_exec(db, "ALTER TABLE test ADD COLUMN data DEFAULT 'missing'", NULL, NULL, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to create table: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_step(stmt);
    if (SQLITE_OK != rc && SQLITE_DONE != rc && SQLITE_ROW != rc) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    printf("%d, %s, %s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));

    sqlite3_finalize(stmt);


    sqlite3_close(db);
}
