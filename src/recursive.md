# Recursive

```sql
CREATE TABLE leaf (
  id INTEGER PRIMARY KEY NOT NULL
) STRICT;

CREATE TABLE node (
  id INTEGER PRIMARY KEY NOT NULL,
  type TEXT NOT NULL
) STRICT;

CREATE TABLE node_leaf (
  node_id INTEGER NOT NULL REFERENCES node(id),
  leaf_id INTEGER NOT NULL REFERENCES leaf(id),
  PRIMARY KEY (node_id, leaf_id)
) STRICT, WITHOUT ROWID;

CREATE TABLE tree (
  parent INTEGER NOT NULL REFERENCES node(id),
  child INTEGER NOT NULL REFERENCES node(id),
  PRIMARY KEY (parent, child)
) STRICT, WITHOUT ROWID;

INSERT INTO node (id, type) VALUES (1, 'A'), (11, 'P'), (12, 'P');
INSERT INTO node (id, type) VALUES (2, 'A'), (21, 'P'), (22, 'P');
INSERT INTO tree (parent, child) VALUES (1, 11), (1, 12);
INSERT INTO tree (parent, child) VALUES (2, 21), (2, 22);

INSERT INTO leaf (id) VALUES (111), (112), (113);
INSERT INTO leaf (id) VALUES (211), (212);
INSERT INTO leaf (id) VALUES (221);
INSERT INTO node_leaf (node_id, leaf_id) VALUES (11, 111), (11, 112), (11, 113);
INSERT INTO node_leaf (node_id, leaf_id) VALUES (21, 211), (21, 212);
INSERT INTO node_leaf (node_id, leaf_id) VALUES (22, 221);
PRAGMA foreign_key_check;

-- WITH parent_of(parent_id, leaf_id) AS (SELECT node.id, leaf_id FROM node LEFT OUTER JOIN node_leaf ON node_leaf.node_id = node.id WHERE type = 'P')
-- SELECT * FROM parent_of;

WITH RECURSIVE
parent_of(parent_id, leaf_id) AS (SELECT node_id, leaf_id FROM node LEFT OUTER JOIN node_leaf ON node_leaf.node_id = node.id WHERE type = 'P'),
ancestor_of(ancestor_id, leaf_id) AS (SELECT parent_id, leaf_id FROM parent_of
UNION SELECT parent, leaf_id FROM ancestor_of INNER JOIN tree ON tree.child = ancestor_of.ancestor_id)
SELECT * FROM ancestor_of;
```