
# ✅ `pthread_create()` — Full Breakdown

## 🧪 Function Signature
```c
int pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attr,
    void *(*start_routine)(void *),
    void *arg
);
```

### 1. 🧵 `pthread_t *thread` — The Thread Identifier

✅ **What it is:**  
This is a pointer to a variable of type `pthread_t`, which will store the ID of the new thread.

✅ **Why we use it:**  
After the thread is created, you can use this `pthread_t` to interact with the thread (e.g., to join it with `pthread_join()`).

✅ **Example:**
```c
pthread_t thread;
pthread_create(&thread, ...);  // &thread stores the ID
```

---

### 2. ⚙️ `const pthread_attr_t *attr` — Thread Attributes (Optional)

✅ **What it is:**  
This is a pointer to a `pthread_attr_t` structure that can specify custom settings for the thread, like:

- Stack size
- Scheduling policy
- Detachment state (joinable or detached)

✅ **Why we use it:**  
To customize how the thread behaves. If you don't need customization, just pass `NULL` (most common case).

✅ **Example (with default settings):**
```c
pthread_create(&thread, NULL, ...);  // Use default attributes
```

If you want to set attributes manually:
```c
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setstacksize(&attr, 1024 * 1024); // set 1MB stack size
pthread_create(&thread, &attr, ...);
```

---

### 3. 🚀 `void *(*start_routine)(void *)` — Thread Start Function

✅ **What it is:**  
This is a pointer to the function that the new thread should run.  

It must:
- Take one argument of type `void *`
- Return a `void *` (optional, can be `NULL` if not used)

✅ **Why we use it:**  
This is the entry point for the thread — the thread starts executing this function.

✅ **Example:**
```c
void *thread_function(void *arg) {
    // Do work here
    return NULL;
}

pthread_create(&thread, NULL, thread_function, ...);
```

---

### 4. 📦 `void *arg` — Argument to the Thread Function

✅ **What it is:**  
This is the argument passed into the `start_routine` (i.e., the thread function).

It's a `void *`, so it can point to any data type (like `int`, `struct`, etc.).

✅ **Why we use it:**  
It lets us pass data into the thread (like a number, array, or struct).  
Inside the thread function, we cast it to the expected type.

✅ **Example:**
```c
int input = 10;
pthread_create(&thread, NULL, thread_function, (void *)&input);
```

Inside the thread function:
```c
void *thread_function(void *arg) {
    int *value = (int *)arg;
    printf("Received: %d
", *value);
    return NULL;
}
```

---

### ✅ **Summary Table**

| Parameter                        | What it Does                                | Common Usage          |
|-----------------------------------|---------------------------------------------|-----------------------|
| `pthread_t *thread`               | Saves the thread ID                         | `&thread`             |
| `const pthread_attr_t *attr`      | Sets thread attributes (stack size, etc.)   | Usually `NULL`        |
| `void *(*start_routine)`          | The function the thread runs                | `thread_function`     |
| `void *arg`                       | Argument passed into the thread function    | `(void *)&some_data`  |
