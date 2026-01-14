# Chapter 2: Objects, Types, and Values

This folder contains exercises and notes from Chapter 2 of *Programming: Principles and Practice Using C++*. This chapter focuses on making programs interactive by using memory (objects) and user input.

## Key Learning Objectives
* Understanding the concept of **Objects** and **Variables**.
* Mastering the **"Big Five"** basic types.
* Interacting with users via the **Standard Input Stream (cin)**.
* Distinguishing between **Initialization** and **Assignment**.

## Core Concepts

### 1. Objects and Variables
* **Object**: A region of memory with a specific type (a "box" in memory).
* **Type**: Specifies what kind of information can be placed in an object.
* **Variable**: A named object.
* **Value**: The specific data stored in the variable.



### 2. The "Big Five" Types
C++ uses types to determine which operations are legal.

| Type | Name | Purpose | Example Literal |
| :--- | :--- | :--- | :--- |
| `int` | Integer | Whole numbers | `42` |
| `double` | Floating-point | Decimals/Real numbers | `3.5` |
| `char` | Character | Single characters | `'A'` |
| `string` | String | Sequence of characters | `"Nicholas"` |
| `bool` | Boolean | Logical true or false | `true` |

### 3. Standard Input (cin)
We use `cin >> variable;` to read from the keyboard.
* **Whitespace**: By default, `>>` stops reading at whitespace (space, tab, newline).
* **Type Sensitivity**: `cin` is smart—it expects data that matches the variable's type. If you try to read "Carlos" into an `int`, it will fail.

## Operations and Operators
The meaning of an operator changes based on the **Type** of the variable:
* **Integers**: `5 / 2` is `2` (Integer division drops the remainder).
* **Doubles**: `5.0 / 2.0` is `2.5`.
* **Strings**: `+` performs concatenation (joining strings).
* **Modulo (%)**: Returns the remainder (e.g., `5 % 2` is `1`).

## Initialization vs. Assignment
1. **Initialization**: Giving a variable its first value.
2. **Assignment**: Replacing an existing value with a new one.
   * *Example*: `a = a + 7` means "get current value, add 7, store result back in a."

## Exercises in this Folder
* `hello_name.cpp`: Simple input/output practice.
* `age_to_months.cpp`: Using `double` for precise calculations.
* `operator_exercise.cpp`: Comparing integer vs. floating-point division.
* `repeated_words.cpp`: Using assignment inside a loop.
