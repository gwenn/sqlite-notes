# Restore corrupted SQLite database

<https://stackoverflow.com/a/57872238>
```sh
sqlite3 broken.db ".recover" | sqlite3 new.db
mv broken.db corrupted.db && mv new.db broken.db
```

<https://sqlite.org/recovery.html>