# Student Bar Account Management System

## Overview

This C application is designed to manage student accounts for a secondary school bar. It maintains up-to-date information about all students (name, date of birth, year, class, number, balance) and tracks their expenses over a calendar year. The application provides various functionalities for interactive management of student records and transactions.

## Features

- **Student Management:**
  - Add a new student.
  - Remove an existing student.
  - List all students in alphabetical order.
  - List students with a balance below a specified amount (sorted in descending order).
  - Display detailed information for a specific student.

- **Expense Management:**
  - Record an expense for a specific student.
  - Recharge a student's account with a specified amount.

- **Data Persistence:**
  - Student and expense data are stored in text files.
  - Data is loaded upon startup and saved to prevent loss.

## Data Files

- **Student Data File (students.txt):** Contains student records in the format:

    ```
    Name,DateOfBirth,Year,Class,Number,Balance
    ```

- **Expense Data File (expenses.txt):** Contains recorded expenses in the format:

    ```
    StudentNumber,Value,Description,Date
    ```

- **Data Format:** Ensure data follows the specified format for easy parsing and updating.

## Design Considerations

- **Data Structures:** Utilizes linked lists for dynamic management of student and expense records.
- **Memory Efficiency:** Focuses on efficient memory usage, including sorting and data handling.
- **Data Persistence:** Ensures data is saved and loaded from text files to maintain continuity.

## Example Operations

- **Add a Student:** Adds a new student's record to the system.
- **Remove a Student:** Deletes an existing student's record.
- **List Students:** Displays all students alphabetically or by balance.
- **View Student Details:** Shows detailed information for a selected student.
- **Record Expense:** Logs an expense for a specified student.
- **Recharge Account:** Adds funds to a student's account.

## Usage

- **Add a Student:** Choose the option to add a new student and provide the required details.
- **Remove a Student:** Select a student to remove by their number.
- **List Students:** View all students in alphabetical order or by their balance.
- **View Student Details:** Display detailed information for a specific student by their number.
- **Record Expense:** Enter details of the expense for a selected student.
- **Recharge Account:** Add funds to a student's account.
