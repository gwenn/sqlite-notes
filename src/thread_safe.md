# Thread safe

When compiled with `SQLITE_THREADSAFE=2`, SQLite can be used in a multithreaded program so long as no two threads attempt to use the same database connection at the same time.

To put it another way, `SQLITE_THREADSAFE=1` sets the default threading mode to Serialized. `SQLITE_THREADSAFE=2` sets the default threading mode to Multi-threaded. And `SQLITE_THREADSAFE=0` sets the threading mode to Single-threaded.

When SQLite has been compiled with `SQLITE_THREADSAFE=1` or `SQLITE_THREADSAFE=2` then the threading mode can be altered at run-time using the `sqlite3_config()` interface together with one of these verbs:
`SQLITE_CONFIG_SINGLETHREAD`
`SQLITE_CONFIG_MULTITHREAD`
`SQLITE_CONFIG_SERIALIZED`

The `SQLITE_OPEN_NOMUTEX` and `SQLITE_OPEN_FULLMUTEX` flags to `sqlite3_open_v2()` can also be used to adjust the threading mode of individual database connections at run-time.

## Unsafe API

### [sqlite3_changes](http://sqlite.org/c3ref/changes.html)

> If a separate thread makes changes on the same database connection while sqlite3_changes() is running then the value returned is unpredictable and not meaningful.

### [sqlite3_last_insert_rowid](http://sqlite.org/c3ref/last_insert_rowid.html)

> If a separate thread performs a new INSERT on the same database connection while the sqlite3_last_insert_rowid() function is running and thus changes the last insert rowid, then the value returned by sqlite3_last_insert_rowid() is unpredictable and might not equal either the old or the new last insert rowid.

### [sqlite3_errcode](http://sqlite.org/c3ref/errcode.html)

> When the serialized threading mode is in use, it might be the case that a second error occurs on a separate thread in between the time of the first error and the call to these interfaces. When that happens, the second error will be reported since these interfaces always report the most recent result. To avoid this, each thread can obtain exclusive use of the database connection D by invoking sqlite3_mutex_enter(sqlite3_db_mutex(D)) before beginning to use D and invoking sqlite3_mutex_leave(sqlite3_db_mutex(D)) after all calls to the interfaces listed here are completed.