# Task 4: Data Compression Tool (RLE)

## 📌 Description
A file utility that implements the **Run-Length Encoding (RLE)** algorithm to compress data. This project demonstrates algorithmic efficiency by reducing the storage footprint of files that contain repetitive character sequences.

## ⚙️ How it Works (Logic)
* **RLE Algorithm:** The program performs a single-pass scan of the source file. It counts consecutive identical bytes and replaces them with a "Frequency-Character" pair.
* **Stream Processing:** Uses `fgetc()` and `fprintf()` to process files byte-by-byte, ensuring a low memory footprint regardless of the file size.
* **Safety & Stability:** * Handles **EOF (End Of File)** markers correctly using `int` types.
    * Includes **Empty File** validation to prevent processing errors.
    * Limits individual counts to **99** to maintain a predictable two-digit output format.
* **Performance Metrics:** Automatically calculates the compression ratio and displays original vs. compressed file sizes in bytes.

## 🚀 Key Features
* **Lossless Compression:** Data can be perfectly reconstructed without any loss of information.
* **Cross-Platform Binary Mode:** Opens files in `rb` and `wb` modes to ensure consistent behavior across different operating systems.
* **Real-time Analytics:** Provides a summary of the compression percentage after every run.

## 💻 Sample
**Input Data (`source.txt`):**
```text
AAAAABBBCC
