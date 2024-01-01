# Checks

## At compilation time (and a SQL parser)

### without access to the complete schema (only the current query)

- syntax errors relative to the SQLite grammar
- parameters count / name / index

### with schema + query

- syntax errors relative to schema
- parameters type

## At runtime time

### parameters / placeholders

- `sqlite3_bind_parameter_count`

### In STRICT mode

- `sqlite3_column_type` vs `sqlite3_column_[double,int,text, ...]` but not possible for expression

### Misc

- `sqlite3_changes` with `SELECT` / `CREATE` / `ALTER` / `PRAGMA` / `EXPLAIN`
- `sqlite3_changes` vs `sqlite3_stmt_readonly`
- `sqlite3_last_insert_rowid` without `INSERT`
- `sqlite3_last_insert_rowid` vs `sqlite3_stmt_readonly`
- `sqlite3_column_count` without `SELECT` / some `PRAGMA` / `EXPLAIN`

```sql
EXPLAIN SELECT 1; --> sqlite3_column_count == 8
EXPLAIN QUERY PLAN SELECT 1; --> sqlite3_column_count == 4
PRAGMA locking_mode = 'exclusive'; --> sqlite3_column_count == 1
INSERT INTO test (data) VALUES ('') RETURNING rowid; --> sqlite3_column_count == 1
```