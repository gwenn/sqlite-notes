#!/bin/sh
cc -Wall -I/usr/local/Cellar/sqlite/3.8.11/include -L/usr/local/Cellar/sqlite/3.8.11/lib -lsqlite3 -o test db_filename.c
