#include <stdio.h>
#include <sqlite3.h>

static int init(
        sqlite3 *db,
        char **pzErrMsg,
        const sqlite3_api_routines *pApi
){
    char *zErr;
    zErr = sqlite3_mprintf("broken autoext!");
    *pzErrMsg = zErr;
    return SQLITE_IOERR_AUTH;
}

int main() {
    int rc = sqlite3_initialize();
    if (rc != SQLITE_OK) {
        printf("sqlite3_initialize: %d\n", rc);
        return rc;
    }
    rc = sqlite3_auto_extension((void(*)(void))init);
    if (rc != SQLITE_OK) {
        printf("sqlite3_auto_extension: %d\n", rc);
        return rc;
    }
    sqlite3 *db = NULL;
    rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_EXRESCODE, NULL);
    if (rc != SQLITE_OK || db == NULL) {
        printf("sqlite3_open_v2: %d, %s\n", rc, sqlite3_errmsg(db));
        return rc;
    }
    return 0;
}
