# CS352 – Object Oriented Programming  
### **Assignment 01: Polynomial and Matrix Operations**
**Name:** Vansh Gandharva  
**Roll No:** 230102102  
**Department:** Electronics and Communication Engineering (ECE)   

---

## 📘 Overview
This project is a part of **CS352 – Object Oriented Programming** coursework.  
It implements two core C++ classes — **Polynomial** and **Matrix** — to perform various arithmetic operations while demonstrating **Object-Oriented Programming (OOP)** principles.

The program reads polynomial matrices from an input file, performs:
- **Polynomial addition, subtraction, and multiplication**
- **Matrix addition, subtraction, and multiplication (of polynomials)**  
and displays all results in a structured format.

---

## 🧩 Key Concepts Demonstrated
| Concept | Description |
|----------|-------------|
| **Encapsulation** | Data members are private, ensuring controlled access through member functions. |
| **Operator Overloading** | Arithmetic (`+`, `-`, `*`) and stream (`>>`, `<<`) operators are overloaded for natural syntax. |
| **Dynamic Memory Management** | Arrays for coefficients and degrees are created and destroyed dynamically. |
| **Deep Copy** | Copy constructor and assignment operator handle deep copying of dynamic arrays. |
| **Exception Handling** | Throws and catches errors when matrix dimensions don’t match for operations. |

---

## 🧠 Features
### **Polynomial Class**
- Represents a polynomial using arrays for coefficients and degrees.
- Supports:
  - **Addition (`+`)**
  - **Subtraction (`-`)**
  - **Multiplication (`*`)**
- Automatically merges like terms and arranges powers in descending order.
- Overloaded `>>` and `<<` operators for easy input/output.

### **Matrix Class**
- Represents a 2D matrix of polynomial objects.
- Supports:
  - **Addition (`+`)**
  - **Subtraction (`-`)**
  - **Multiplication (`*`)**
- Overloaded `[]` operator for easy element access.
- Handles invalid dimension operations gracefully.

---

## 📂 File Structure
