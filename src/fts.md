# FTS

```sql
CREATE TABLE history
(
    id        INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    entry     TEXT                              NOT NULL,
    timestamp REAL                              NOT NULL DEFAULT (julianday('now'))
);
-- only if ignore_dups is activated:
CREATE UNIQUE INDEX ignore_dups ON history(entry);
CREATE VIRTUAL TABLE fts USING fts4(content=history, entry);

CREATE TRIGGER history_bu BEFORE UPDATE ON history BEGIN
    DELETE FROM fts WHERE docid=old.rowid;
END;
CREATE TRIGGER history_bd BEFORE DELETE ON history BEGIN
    DELETE FROM fts WHERE docid=old.rowid;
END;
CREATE TRIGGER history_au AFTER UPDATE ON history BEGIN
    INSERT INTO fts (docid, entry) VALUES (new.rowid, new.entry);
END;
CREATE TRIGGER history_ai AFTER INSERT ON history BEGIN
    INSERT INTO fts (docid, entry) VALUES(new.rowid, new.entry);
END;

INSERT OR REPLACE INTO history (entry) VALUES ('line') RETURNING id;
-- reverse search
SELECT * FROM fts WHERE entry MATCH ? || '*'  AND docid < ?;
-- start with
SELECT * FROM fts WHERE entry MATCH '^' || x || '*'  AND docid < ?;
```