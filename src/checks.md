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

### rusqlite API

- execute_batch => multiple statements allowed
- others => disallowed

- execute => sqlite3_changes
- insert => sqlite3_last_insert_rowid (~ table without rowid)

| Statement         | execute_batch | execute | insert | query* / exists   |
| ----------------- | ------------- | ------- | ------ | --------- |
| ANALYZE           | yes           | no      | no     | no        |
| ATTACH/DETACH     | yes           | no      | no     | no        |
| BEGIN/COMMIT/END  | yes           | no      | no     | no        |
| EXPLAIN           | no            | no      | no     | yes       |
| CREATE/ALTER/DROP | yes           | no      | no     | no        |
| DELETE/UPDATE     | yes           | yes     | no     | RETURNING |
| INSERT            | yes           | yes     | yes    | RETURNING |
| REINDEX           | yes           | no      | no     | no        |
| RELEASE/ROLLBACK  | yes           | no      | no     | no        |
| SAVEPOINT         | yes           | no      | no     | no        |
| SELECT            | no ~          | no      | no     | yes       |
| PRAGMA            | yes           | no      | no     | yes ~     |
| VACUUM            | yes           | no      | no     | no        |
