# Patterns

## INSERT OR UPDATE aka UPSERT

<https://sqlite.org/lang_upsert.html>

```sql
INSERT INTO tbl ...
ON CONFLICT(...)
DO UPDATE ...
```

## SELECT OR INSERT

We cannot use `DO NOTHING` to retrieve the `rowid` in all cases so: 
```sql
INSERT INTO tbl (...) VALUES (...) 
ON CONFLICT DO UPDATE SET c = c
RETURNING rowid;
```