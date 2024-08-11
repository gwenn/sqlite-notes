# sqlite3_ext

- `sqlite3_randomness`

## Macros

<https://docs.rs/sqlite3_ext/latest/sqlite3_ext/index.html#attributes>

## Connection

- `sqlite3_db_mutex`

## Statement

- `sqlite3_db_handle`

### SQLITE_ENABLE_COLUMN_METADATA

- `sqlite3_column_database_name`
- `sqlite3_column_origin_name`
- `sqlite3_column_table_name`

## Extensions

<https://github.com/CGamesPlay/sqlite3_ext>

- [Extension](https://docs.rs/sqlite3_ext/latest/sqlite3_ext/struct.Extension.html) vs [AutoExtension](https://docs.rs/rusqlite/latest/rusqlite/auto_extension/index.html)

### Context

- `ToContextResult` vs `ToSql` / `ToSqlOutput`
- `PassedRef`
- `UnsafePtr`

### Functions

- [AggregateFunction](https://docs.rs/sqlite3_ext/latest/sqlite3_ext/function/trait.AggregateFunction.html) vs [Aggregate](https://docs.rs/rusqlite/latest/rusqlite/functions/trait.Aggregate.html)
- `sqlite3_get_auxdata` (~ Arc)
- `sqlite3_overload_function`

### VTab

- [VTab](https://docs.rs/sqlite3_ext/latest/sqlite3_ext/vtab/trait.VTab.html) vs [VTab](https://docs.rs/rusqlite/latest/rusqlite/vtab/trait.VTab.html)
- sqlite3_context_db_handle (~ only for function)
- `sqlite3_vtab_distinct`
- `sqlite3_vtab_in`
- `sqlite3_vtab_in_first`
- `sqlite3_vtab_in_next`
- `sqlite3_vtab_nochange`
- `sqlite3_vtab_on_conflict`
- `sqlite3_vtab_rhs_value`