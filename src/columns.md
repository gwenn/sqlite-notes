# Columns

## [Generated](https://sqlite.org/gencol.html) columns

```sql
CREATE TABLE table_name (
	...
  column_name column_type AS (expr),
);
```

## [Hidden](https://sqlite.org/vtab.html#hidden_columns_in_virtual_tables) columns

> If a column datatype contains the special keyword "HIDDEN" [...] in the SQL is passed to sqlite3_declare_vtab()