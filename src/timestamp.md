# Timestamp

- `datetime('now')`: utc
- `datetime('now', 'localtime')`: local
- `strftime('%s', 'now')`: utc
- `strftime('%s', 'now', 'localtime')`: local

```sql
SELECT CURRENT_TIMESTAMP;
-- 2024-07-21 09:34:11
-- utc
```

# Date

```sql
SELECT CURRENT_DATE;
-- 2024-07-21
SELECT date();
-- idem
SELECT date('nom');
-- idem
```

## As human readable compact INT

```sql
SELECT cast(strftime('%Y%m%S', 'now') AS INT);
--20240713
```
but format not supported by SQLite standard function.