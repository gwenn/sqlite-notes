# Delete

## with JOIN
```sql
DELETE FROM Payments WHERE UserID IN (SELECT UserID FROM Users WHERE UserName = 'John Smith');
```