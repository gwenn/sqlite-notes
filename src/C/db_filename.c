#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

int main() {
    sqlite3 *db = NULL;
    int rc = 0;
    rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error: unable to open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    fprintf(stderr, "db filename: '%s'\n", sqlite3_db_filename(db, NULL));

    sqlite3_close(db);
}

