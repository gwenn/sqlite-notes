# Array

<https://sqlite.org/carray.html>

## Pointer passing interfaces

<https://sqlite.org/bindptr.html>

### `sqlite3_bind_pointer`

```C
int sqlite3_bind_pointer(sqlite3_stmt* S, int I, void* P, const char* T, void(*)(void*) D);
```

bind pointer `P` of type `T` to the `I`-th parameter of prepared statement `S`.
`D` is an optional destructor function for `P`.

```rust
extern "C" {
    pub fn sqlite3_bind_pointer(
        S: *mut sqlite3_stmt,
        I: c_int,
        P: *mut c_void,
        T: *const c_char,
        D: Option<unsafe extern "C" fn(arg1: *mut c_void)>,
    ) -> c_int;
}
```

### `sqlite3_result_pointer` (not used for `carray`)

```C
void sqlite3_result_pointer(sqlite3_context* C, void* P, const char* T, void(*)(void*) D);
```

`sqlite3_result_pointer(C,P,T,D)` return pointer `P` of type `T` as the argument of function `C`.
`D` is an optional destructor function for `P`.

```rust
extern "C" {
    pub fn sqlite3_result_pointer(
        C: *mut sqlite3_context,
        P: *mut c_void,
        T: *const c_char,
        D: Option<unsafe extern "C" fn(arg1: *mut c_void)>,
    );
}

```

### `sqlite3_value_pointer`

to be used from vtab `filter` or SQL functions implementation body.

```C
void *sqlite3_value_pointer(sqlite3_value* V, const char* T);
```

return the pointer of type `T` associated with value `V`,
or if `V` has no associated pointer, or if the pointer on `V` is of a type different from `T`, then return `NULL`.

```rust
extern "C" {
    pub fn sqlite3_value_pointer(
        arg1: *mut sqlite3_value,
        arg2: *const c_char,
    ) -> *mut c_void;
}
```

## Rust

```rust
unsafe trait TypedPointer {
	const TYPE: *const c_char;
    /// To be used as 3rd / 2nd argument of `sqlite3_bind_pointer` / `sqlite3_result_pointer`
	fn into_raw(self) -> *mut c_void;
    /// To be used to cast SQLite pointer returned by `sqlite3_value_pointer`
    fn from_raw(p: *mut c_void) -> Self;
    /// Destructor
    fn drop(p: *mut c_void);
}
```