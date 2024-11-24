# Callbacks

## Authorization

```C
int sqlite3_set_authorizer(
  sqlite3*,
  int (*xAuth)(void*,int,const char*,const char*,const char*,const char*),
  void *pUserData
);
```
> Only a single authorizer can be in place on a database connection at a time.
> Each call to sqlite3_set_authorizer overrides the previous call.

## Auto-extension

```C
int sqlite3_auto_extension(void(*xEntryPoint)(void));
```

## Busy handler

```C
int sqlite3_busy_handler(sqlite3*,int(*)(void*,int),void*);
```
> There can only be a single busy handler defined for each database connection.
> Setting a new busy handler clears any previously set handler.
> Note that calling sqlite3_busy_timeout() or evaluating PRAGMA busy_timeout=N will change the busy handler and thus clear any previously set busy handler.

## Collation needed

```C
int sqlite3_collation_needed(
  sqlite3*,
  void*,
  void(*)(void*,sqlite3*,int eTextRep,const char*)
);
```

## Commit/rollback hooks

```C
void *sqlite3_commit_hook(sqlite3*, int(*)(void*), void*);
void *sqlite3_rollback_hook(sqlite3*, void(*)(void *), void*);
```
> Any callback set by a previous call for the same database connection is overridden.
> The sqlite3_commit_hook(D,C,P) and sqlite3_rollback_hook(D,C,P) functions return the P argument from the previous call of the same function on the same database connection D,
> or NULL for the first call for each function on D.

## Pre-update hook

```C
void *sqlite3_preupdate_hook(
  sqlite3 *db,
  void(*xPreUpdate)(
    void *pCtx,                   /* Copy of third arg to preupdate_hook() */
    sqlite3 *db,                  /* Database handle */
    int op,                       /* SQLITE_UPDATE, DELETE or INSERT */
    char const *zDb,              /* Database name */
    char const *zName,            /* Table name */
    sqlite3_int64 iKey1,          /* Rowid of row about to be deleted/updated */
    sqlite3_int64 iKey2           /* New rowid value (for a rowid UPDATE) */
  ),
  void*
);
```
> At most one preupdate hook may be registered at a time on a single database connection;
> each call to sqlite3_preupdate_hook() overrides the previous setting.
> The sqlite3_preupdate_hook(D,C,P) function returns the P argument from the previous call on the same database connection D,
> or NULL for the first call on D.

## Query progress

```C
void sqlite3_progress_handler(sqlite3*, int, int(*)(void*), void*);
```

## Profile / Trace

Old API:
```C
void *sqlite3_trace(sqlite3*,
   void(*xTrace)(void*,const char*), void*);
void *sqlite3_profile(sqlite3*,
   void(*xProfile)(void*,const char*,sqlite3_uint64), void*);
```
returns the previous user data.

New API:
```C
int sqlite3_trace_v2(
  sqlite3*,
  unsigned uMask,
  int(*xCallback)(unsigned,void*,void*,void*),
  void *pCtx
);
```
> Each call to either sqlite3_trace(D,X,P) or sqlite3_trace_v2(D,M,X,P) overrides (cancels) all prior calls to sqlite3_trace(D,X,P) or sqlite3_trace_v2(D,M,X,P) for the database connection D.
> Each database connection may have at most one trace callback.

## Unlock notification

```C
int sqlite3_unlock_notify(
  sqlite3 *pBlocked,                          /* Waiting connection */
  void (*xNotify)(void **apArg, int nArg),    /* Callback function to invoke */
  void *pNotifyArg                            /* Argument to pass to xNotify */
);
```
> There may be at most one unlock-notify callback registered by a blocked connection.
> If sqlite3_unlock_notify() is called when the blocked connection already has a registered unlock-notify callback,
> then the new callback replaces the old.

## Data change notification

```C
void *sqlite3_update_hook(
  sqlite3*,
  void(*)(void *,int ,char const *,char const *,sqlite3_int64),
  void*
);
```
> The sqlite3_update_hook(D,C,P) function returns the P argument from the previous call on the same database connection D, or NULL for the first call on D.

## Write-ahead log commit hook

```C
void *sqlite3_wal_hook(
  sqlite3*,
  int(*)(void *,sqlite3*,const char*,int),
  void*
);
```
> A single database handle may have at most a single write-ahead log callback registered at one time.
> Calling sqlite3_wal_hook() replaces any previously registered write-ahead log callback.
> The return value is a copy of the third parameter from the previous call, if any, or 0.
> Note that the sqlite3_wal_autocheckpoint() interface and the wal_autocheckpoint pragma both invoke sqlite3_wal_hook() and will overwrite any prior sqlite3_wal_hook() settings.
