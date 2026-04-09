# Task 1: Inventory Management System

## 📌 Description
A C-based system for managing product records with permanent storage. This project demonstrates how to handle structured data and ensure information is saved even after the program exits.

##  How it Works (Logic)
* **Persistence:** Uses **Binary File Handling** (`fread`/`fwrite`) to save data into `inventory.dat`.
* **Data Integrity:** Includes an `idExists()` check to prevent duplicate Product IDs.
* **Deletion Logic:** Implements a **Temporary File Swap**; it copies all records *except* the deleted one to a new file, then renames it.
* **Input Safety:** Uses a custom `clearBuffer()` function to prevent input errors and infinite loops.

##  Key Features
* **Add/Display/Delete** product records.
* **Automatic Saving** to a binary database file.
* **Validation** for IDs, quantity, and price.

##  Sample
```text
Choice: 1
Enter ID: 101
Enter Name: Monitor
Enter Quantity: 10
Enter Price: 150.00
Product added successfully!
