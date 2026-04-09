# Task 3: Lexical Cleaner (Whitespace & Comment Remover)

## 📌 Description
A file-processing utility that cleans C source code by removing comments and redundant whitespaces. This acts as a basic pre-processor to reduce file size and prepare code for minification.

## ⚙️ How it Works (Logic)
* **State Recognition:** Uses flags (`inString`, `inChar`) to ensure comments inside quotes are **not** accidentally deleted.
* **Comment Removal:** Identifies `//` for single-line and `/* ... */` for multi-line comments, skipping them during the file-writing process.
* **Whitespace Compression:** Detects sequences of spaces or tabs and collapses them into a single space to optimize formatting.
* **Non-Destructive Streaming:** Uses `ungetc()` to "peek" at the next character in the file stream without losing its position.

## 🚀 Key Features
* **Full Comment Stripping:** Handles both block and inline comments.
* **Literal Protection:** Safely ignores syntax inside string and character literals.
* **Space Optimization:** Removes redundant formatting for a cleaner output.

## 💻 Sample
**Input Code:**
```c
int x = 10; // This is a comment
/* Multi-line
   Comment */
printf("Keep this space");
