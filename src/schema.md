# Schema

<https://sqlite.org/schematab.html>

- <https://sqlite.org/pragma.html#pragma_table_list>
- <https://sqlite.org/pragma.html#pragma_index_info>
- <https://sqlite.org/pragma.html#pragma_index_xinfo>
- <https://sqlite.org/pragma.html#pragma_function_list>
- <https://sqlite.org/pragma.html#pragma_table_xinfo>

```sql
SELECT * FROM pragma_table_list();
-- schema|name|type|ncol|wr|strict
SELECT * FROM pragma_table_xinfo('tbl');
-- cid|name|type|notnull|dflt_value|pk|hidden
SELECT * FROM pragma_index_list('tbl');
-- seq|name|unique|origin|partial
SELECT * FROM pragma_index_info('idx');
-- seqno|cid|name
SELECT * FROM pragma_index_xinfo('idx');
-- seqno|cid|name|desc|coll|key
```

```sql
SELECT * FROM pragma_index_list('invoice') WHERE unique = 1; -- does not work !
```

```sql
SELECT * FROM pragma_index_xinfo('invoice_contract');
seqno|cid|name|desc|coll|key
0|4|contract_id|0|BINARY|1
1|-1||0|BINARY|0
```

desc => ASC_OR_DESC