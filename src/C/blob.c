#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    int rc = 0;
    rc = sqlite3_open_v2("blob.sqlite", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    // 1000000000
    // 2147483647
    rc = sqlite3_exec(db, "CREATE TABLE foo (data BLOB); \
                        INSERT INTO foo (ROWID, data) VALUES (1, zeroblob(2147483647+8));", NULL, NULL, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to create table: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_blob *blob = NULL;
    rc = sqlite3_blob_open(db, "main", "foo", "data", 1, 0, &blob);
    if (blob == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open blob: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    printf("%d\n", sqlite3_blob_bytes(blob));

    sqlite3_blob_close(blob);
    sqlite3_close(db);
}

