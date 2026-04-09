# Task 2: Music Playlist Manager

## 📌 Description
A C program that simulates a digital music queue using dynamic data structures. It allows for a flexible playlist that can be modified in real-time without the constraints of fixed array sizes.

## ⚙️ How it Works (Logic)
* **Linked List:** Uses a **Singly Linked List** (`struct Song`) to manage the queue. Each song points to the next, allowing efficient insertions and deletions.
* **Memory Management:** Dynamically allocates memory with `malloc()` and includes a `freePlaylist()` function to prevent memory leaks.
* **Current Track Logic:** Maintains a `currentPlay` pointer to track and move through the list.
* **Circular Simulation:** The `playNext()` function automatically loops back to the start of the list when the end is reached.

## 🚀 Key Features
* **Add & Delete:** Dynamically manage songs by name.
* **Play Next:** Skip through the queue in real-time.
* **Memory Efficient:** Only uses the exact amount of RAM needed for the current playlist.

## 💻 Sample
```text
Playlist:
  1. Starboy - The Weeknd (3.50 mins)
> 2. Nightcall - Kavinsky (4.18 mins)

Choice: 4
Now Playing: Nightcall - Kavinsky
