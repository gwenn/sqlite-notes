# Pragma

<https://sqlite.org/pragma.html#pragma_pragma_list>
```sql
SELECT * FROM pragma_pragma_list();
```
```csv
name
analysis_limit
...
```


## Database(s)
<https://sqlite.org/pragma.html#pragma_database_list>
```sql
SELECT * FROM pragma_database_list() WHERE name LIKE 'main%' OR name = 'temp';
```
```csv
seq|name|file
0|main|
1|temp|
```

## Functions
<https://sqlite.org/pragma.html#pragma_function_list>
```sql
SELECT * FROM pragma_function_list();
```
```csv
name|builtin|type|enc|narg|flags
pow|1|s|utf8|2|2099200
group_concat|1|w|utf8|1|2097152
...
```

## Collations
<https://sqlite.org/pragma.html#pragma_collation_list>
```sql
SELECT * FROM pragma_collation_list();
```
```csv
seq|name
0|decimal
1|uint
2|RTRIM
3|NOCASE
4|BINARY
```

## Tables
<https://sqlite.org/pragma.html#pragma_table_list>
```sql
SELECT * FROM pragma_table_list() WHERE schema LIKE 'main' AND name LIKE 'x%';
```
```csv
schema|name|type|ncol|wr|strict
main|x|table|1|0|0
```

## Table columns
<https://sqlite.org/pragma.html#pragma_table_info>
<https://sqlite.org/pragma.html#pragma_table_xinfo>
```sql
SELECT * FROM pragma_table_xinfo('x');
```
```
cid|name|type|notnull|dflt_value|pk|hidden
0|a|TEXT|1||0|0
```

## Foreign keys
<https://sqlite.org/pragma.html#pragma_foreign_key_list>
```sql
SELECT * FROM pragma_foreign_key_list('y');
```
```
id|seq|table|from|to|on_update|on_delete|match
0|0|x|a|a|NO ACTION|NO ACTION|NONE
```

## Indexes
<https://sqlite.org/pragma.html#pragma_index_list>
```sql
SELECT * FROM pragma_index_list('x');
```
```
seq|name|unique|origin|partial
0|sqlite_autoindex_x_1|1|u|0
```

## Index info
<https://sqlite.org/pragma.html#pragma_index_info>
<https://sqlite.org/pragma.html#pragma_index_xinfo>
```sql
SELECT * FROM pragma_index_xinfo('sqlite_autoindex_x_1');
```
```
seqno|cid|name|desc|coll|key
0|0|a|0|BINARY|1
1|-1||0|BINARY|0
```

