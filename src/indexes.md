# SQLite indexes

## [Partial Indexes](https://sqlite.org/partialindex.html)

```sql
CREATE INDEX ... WHERE ...;
```

## [Indexes On Expressions](https://sqlite.org/expridx.html)

```sql
CREATE INDEX ... ON table-name(expr);
```

## [Covering Indexes](https://sqlite.org/optoverview.html#covering_indexes)

> When an index contains all of the data needed for a query and when the original table never needs to be consulted, we call that index a "covering index".

## [Clustered Indexes](https://sqlite.org/withoutrowid.html)

> A WITHOUT ROWID table is a table that uses a Clustered Index as the primary key.