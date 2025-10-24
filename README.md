# 🎵 MP3 Tag Reader and Editor

## 📘 Overview
The **MP3 Tag Reader and Editor** is a C-based command-line utility that allows users to **view and edit ID3v3 tags** in MP3 audio files.  
It reads metadata such as **Title**, **Artist**, **Album**, **Year**, **Genre**, and more, and provides functionality to modify these tags directly within the MP3 file.

---

## ⚙️ Features
- ✅ Read and display all standard MP3 ID3v3 tags.  
- ✏️ Edit specific tags such as Title, Artist, Album, Year, etc.  
- 🧩 Validates MP3 files before performing operations.  
- 🧱 Uses a temporary file to ensure data safety during editing.  
- 🖥️ Simple command-line interface.

---

## 🧩 Project Structure
```
📁 MP3_tagreader
├── edit.c          # Contains tag editing functions
├── view.c          # Contains tag viewing and validation functions
├── mp3_main.c      # Main file handling command-line arguments
├── header.h        # Function declarations and prototypes
├── sample.mp3      # Sample MP3 file for testing
└── a.out           # Compiled output (generated after build)
```

---

## 🧠 Functional Description

### **1. convert(int size)**
Converts a 4-byte sync-safe integer (big-endian ↔ little-endian).  
Used for reading and writing ID3v3 tag frame sizes correctly.

### *2. validate(FILE *fp)**
Validates that the file is an MP3 by checking for the `"ID3"` header.

### 3. view_mp3(FILE *fp)*
Reads all MP3 ID3v3 tags and displays tag names and their corresponding values.

### 4. edit_mp3(FILE *fp, char *tag, char *edits, char *song)**
Selects which tag to edit based on user input and calls the `edit()` function.

### 5. edit(FILE *fp, FILE *fp1, char *arr, char *edits, char *song)**
Performs the actual editing of the tag content by:
- Rewriting the new tag value to a temporary MP3 file.
- Copying unchanged tags as-is.
- Replacing the original file with the new one after a successful edit.

### **6. help(void)**
Displays available command-line options and usage instructions.

---

## 🧾 Supported Tags

| Flag | Tag Name | Description |
|------|-----------|-------------|
| `-t` | `TIT2` | Title |
| `-a` | `TPE1` | Artist |
| `-A` | `TALB` | Album |
| `-y` | `TYER` | Year |
| `-C` | `TCON` | Genre |
| `-c` | `COMM` | Comment |
| `-Y` | `TDRC` | Recording Time |
| `-w` | `TCOP` | Copyright |
| `-p` | `TPUB` | Publisher |
| `-m` | `TCOM` | Composer |
| `-s` | `TSSE` | Encoder/Software |
| `-l` | `TPE2` | Lead Artist/Album Artist |
| `-i` | `APIC` | Attached Picture (Album Art) |

---

## 💻 Compilation & Execution

### **1. Compile the project**
```bash
gcc mp3_main.c edit.c view.c -o mp3_editor
```

### **2. View MP3 Tags**
```bash
./mp3_editor -v sample.mp3
```

### **3. Edit a Tag**
```bash
./mp3_editor -e -t "New Song Title" sample.mp3
./mp3_editor -e -a "New Artist" sample.mp3
./mp3_editor -e -A "New Album" sample.mp3
./mp3_editor -e -y "2025" sample.mp3
```

### **4. Help Menu**
```bash
./mp3_editor --help
```

---

## 🧩 Example Output

### **View Mode**
```bash
$ ./mp3_editor -v sample.mp3

_____________________________________________________________
IDV3 Tag Reader and Viewer
____________________________________________________________
Title           :       pani_pani
Artist          :       Yo_Yo_honey_singh
Album           :       Yaariyan
Year            :       2017
Genre           :       Bollywood Music - [SongsPk.CC]
Comment         :       eng
Attached image  :       image/jpeg
______________________________________________________________
```

### **Edit Mode**
```bash
$ ./mp3_editor -e -t "Perfect" sample.mp3
Edited successfully
```

---

## ⚠️ Error Handling
- Detects invalid MP3 files.
- Displays messages for missing or corrupted files.
- Prevents accidental overwriting using temporary files.
- Gracefully handles memory allocation errors.

---

## 🧑‍💻 Author: Akshaya Raj Mullasseril
**Developed in C**  
This project demonstrates:
- Binary file handling  
- Metadata parsing  
- Endianness manipulation  
- Command-line argument processing

---
