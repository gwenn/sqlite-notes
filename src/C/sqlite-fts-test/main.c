#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

sqlite3 *open(const char *path) {
    fprintf(stdout, "opening %s\n", path);
    sqlite3 *db = NULL;
    int rc = sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, NULL);
    if (db == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error opening %s: %d, %s\n", path, rc, sqlite3_errmsg(db));
        exit(1);
    }
    return db;
}

void exec(sqlite3 *db, const char *sql) {
    fprintf(stdout, "executing %s\n", sql);
    int rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error executing %s: %d, %s\n", sql, rc, sqlite3_errmsg(db));
        exit(1);
    }
}

sqlite3_stmt *prepare(sqlite3 *db, const char *sql) {
    fprintf(stdout, "preparing %s\n", sql);
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (stmt == NULL || SQLITE_OK != rc) {
        fprintf(stderr, "Error preparing %s: %d, %s\n", sql, rc, sqlite3_errmsg(db));
        exit(1);
    }
    return stmt;
}

void step(sqlite3_stmt *stmt) {
    fprintf(stdout, "stepping %s\n", sqlite3_sql(stmt));
    int rc = sqlite3_step(stmt);
    if (SQLITE_OK != rc && SQLITE_DONE != rc) {
        fprintf(stderr, "Error stepping %s: %d, %s\n", sqlite3_sql(stmt), rc, sqlite3_errmsg(sqlite3_db_handle(stmt)));
        exit(1);
    }
}

void reset(sqlite3_stmt *stmt) {
    fprintf(stdout, "resetting %s\n", sqlite3_sql(stmt));
    int rc = sqlite3_reset(stmt);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error resetting %s: %d, %s\n", sqlite3_sql(stmt), rc, sqlite3_errmsg(sqlite3_db_handle(stmt)));
        exit(1);
    }
}

void finalize(sqlite3_stmt *stmt) {
    int rc = sqlite3_finalize(stmt);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error finalizing %s: %d, %s\n", sqlite3_sql(stmt), rc,
                sqlite3_errmsg(sqlite3_db_handle(stmt)));
        exit(1);
    }
}

void close(sqlite3 *db) {
    fprintf(stdout, "closing %s\n", sqlite3_db_filename(db, NULL));
    int rc = sqlite3_close(db);
    if (SQLITE_OK != rc) {
        fprintf(stderr, "Error closing %s: %d, %s\n", sqlite3_db_filename(db, NULL), rc, sqlite3_errmsg(db));
        exit(1);
    }
}

int main() {
    sqlite3 *db1 = NULL;
    sqlite3_stmt *stmt = NULL;
    sqlite3 *db2 = NULL;

    int memoryDb = 1;
    db1 = open("file:db1?mode=memory");
    exec(db1, "PRAGMA trusted_schema = 1;");
    exec(db1, "CREATE TABLE history (entry TEXT);");
    exec(db1, "CREATE VIRTUAL TABLE fts USING fts4(content=history, entry);\n"
              "CREATE TRIGGER history_ai AFTER INSERT ON history BEGIN\n"
              "    INSERT INTO fts (docid, entry) VALUES(new.rowid, new.entry);\n"
              "END;");

    stmt = prepare(db1, "INSERT OR IGNORE INTO history (entry) VALUES ('abc');");
    step(stmt);
    reset(stmt); // useless

    if (memoryDb) {
        db2 = open("file:db2?mode=memory&cache=shared");
    } else {
        db2 = open("file:db2.sqlite");
    }
    exec(db2, "PRAGMA trusted_schema = 1;");
    exec(db2, "CREATE TABLE IF NOT EXISTS history (entry TEXT);");
    exec(db2, "CREATE VIRTUAL TABLE IF NOT EXISTS fts USING fts4(content=history, entry);\n"
              "CREATE TRIGGER IF NOT EXISTS history_ai AFTER INSERT ON history BEGIN\n"
              "    INSERT INTO fts (docid, entry) VALUES(new.rowid, new.entry);\n"
              "END;");

    if (memoryDb) {
        exec(db1, "ATTACH DATABASE 'file:db2?mode=memory&cache=shared' AS new;");
    } else {
        exec(db1, "ATTACH DATABASE 'file:db2.sqlite' AS new;");
    }
    exec(db1, "INSERT OR IGNORE INTO new.history (entry) SELECT entry FROM history;");
    exec(db1, "DETACH DATABASE new;");

    finalize(stmt);

    stmt = sqlite3_next_stmt(db1, NULL);
    while (stmt != NULL) {
        fprintf(stdout, "checking %s\n", sqlite3_sql(stmt));
        if (sqlite3_stmt_busy(stmt)) {
            fprintf(stderr, "%s: busy\n", sqlite3_sql(stmt));
        }
        stmt = sqlite3_next_stmt(db1, stmt);
    }

    close(db1); // => SQLITE_BUSY only if memoryDb == 1
    close(db2);

    return 0;
}
