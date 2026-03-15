# 🎮 GO Game (C++)

## 📌 Programming Fundamentals Project

This project was developed as my **Programming Fundamentals (PF) Lab Final Project during my 1st semester**.
It is a **console-based implementation of the classic board game "Go"** built entirely using **C++ fundamentals**.

The goal of this project was to practice core programming concepts such as:

* Functions
* Arrays
* Recursion
* Conditional logic
* Game state management
* Basic user interaction in the console

---

# 🧠 Game Introduction

**Go** is one of the oldest strategic board games in the world.
It is played between **two players**, where each player places stones on the board to **capture territory and surround opponent stones**.

⚫ **Black plays first**
⚪ **White plays second**

The main objective is simple:

> Control more territory on the board than your opponent.

However, the strategy becomes extremely deep as the game progresses.

---

# 🖥️ Features Implemented

✨ Multiple board sizes

* `19 × 19` (standard board)
* `13 × 13`
* `9 × 9`

✨ Turn-based gameplay

* Black and White alternate turns

✨ Move validation

* Prevents invalid positions

✨ Capture mechanics

* Stones with no liberties are removed

✨ **KO Rule implemented**

* Prevents repeating board states

✨ Suicide move detection

✨ Territory calculation and final scoring

✨ Menu system with:

* Start Game
* Instructions
* Developer Information
* Exit

---

# 🎯 Game Controls

When the game starts:

1️⃣ Select the **board size**
2️⃣ Players enter **row and column numbers** to place a stone
3️⃣ Enter **`0 0`** to end the game

Example move input:

```
Enter row and column: 4 7
```

---

# 📂 Project Structure

The project is implemented using **modular functions**, including:

| Function            | Purpose                   |
| ------------------- | ------------------------- |
| `board_size()`      | Select board size         |
| `board_displayer()` | Prints the board          |
| `GO()`              | Handles gameplay loop     |
| `capture()`         | Removes surrounded stones |
| `hasLiberty()`      | Checks stone liberties    |
| `isKO()`            | Enforces KO rule          |
| `calculateScore()`  | Computes final scores     |

More details about the logic and implementation can be explored **directly inside the source code**.

---

# 🛠️ Technologies Used

* **Language:** C++
* **Environment:** Console / Terminal
* **Libraries Used:**

  * `iostream`
  * `iomanip`
  * `Windows.h`

---

# 👨‍💻 Developer

**Chaudhry Muhammad Abdullah**
BS Artificial Intelligence
FAST National University (Chiniot Faisalabad Campus)

This project was created as part of my **Programming Fundamentals Lab coursework**.

---

# 🚀 How to Run

1. Clone the repository
2. Open the project in any C++ IDE (Dev C++, CodeBlocks, Visual Studio, etc.)
3. Compile and run the program

Example:

```
g++ go_game.cpp -o go_game
./go_game
```

---

# 🎲 Final Note

This project focuses on **logic building and fundamental programming concepts** rather than graphics.
If you're curious about how the game mechanics work, **check out the source code** — that’s where the real magic happens.

⭐ If you like the project, feel free to explore and improve it!
