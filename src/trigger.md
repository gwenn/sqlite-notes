# Trigger

```sql
CREATE TABLE test (a TEXT NOT NULL PRIMARY KEY, b INTEGER NOT NULL);

CREATE TRIGGER check_insert_zero_trigger
BEFORE INSERT 
ON test
WHEN NEW.b = 0
BEGIN
  SELECT RAISE(IGNORE);
END;

CREATE TRIGGER check_update_zero_trigger
BEFORE UPDATE OF b
ON test
WHEN NEW.b = 0
BEGIN
  SELECT RAISE(ABORT, 'check_update_zero_trigger');
END;

INSERT INTO test (a, b) VALUES ('foo', 1)
ON CONFLICT (a) DO UPDATE SET b = excluded.b
WHERE b <> excluded.b;

INSERT INTO test (a, b) VALUES ('bar', 0)
ON CONFLICT (a) DO UPDATE SET b = excluded.b
WHERE b <> excluded.b;

INSERT INTO test (a, b) VALUES ('foo', 0)
ON CONFLICT (a) DO UPDATE SET b = excluded.b
WHERE b <> excluded.b;

INSERT INTO test (a, b) VALUES ('baz', 1)
ON CONFLICT (a) DO UPDATE SET b = excluded.b
WHERE b <> excluded.b;

SELECT * FROM test;
```