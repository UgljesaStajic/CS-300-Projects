CS 300 – Portfolio Reflection
Ugljesa Stajic

Portfolio Artifacts

Project One: Runtime and memory analysis comparing Vector, Hash Table, and Binary Search Tree data structures.
Project Two: A complete C++ program using a Binary Search Tree (BST) to load, store, sort, and display Computer Science courses in alphanumeric order.

Together, these projects demonstrate my understanding of data structures, algorithms, and performance.

The main problem I was solving was how to efficiently store, search, validate, and print course information from a file. Each course could have multiple prerequisites, and the program needed to handle missing or invalid data safely. The solution also had to allow users to search for individual courses and print an alphanumerically ordered list of all courses.

I started to approached this problem with comparing different data structures: Vector, Hash Table, and Binary Search Tree. Understanding data structures was important because each one has different performance characteristics. Even though all three would work, there is always a tradeoff in performance.

Vectors are easy to implement but become slow when searching or validating prerequisites.
Hash tables provide very fast lookups but do not keep data sorted.
Binary Search Trees provide a good balance by allowing fast searching while keeping courses naturally ordered.
This comparison helped me choose the best structure based on both runtime efficiency and usability that i attached in this repository.

One of the main challenges was handling invalid prerequisites and preventing the program from crashing due to bad input data. I overcame this by adding a validation step that checks whether all prerequisites exist before inserting courses into the data structure.
Another roadblock was managing user input errors and file-reading issues. I solved this by adding clear error messages and input validation, which made the program more stable and user-friendly. There were other minor obstacles during the development that I successfully could debug. 

This project expanded my approach by teaching me to think more about performance, scalability, and data organization before writing code. As well it showed me why planing the data management is so important and it could have a big inpact in the speed or usability of the application itslef.

My work on this project improved how I write programs and tought me that planing is a big and important step before the coding even starts. I learned about modular approach by separated functionality into logical functions and classes, which makes the code easier to read, maintain, and adapt in the future.
Using consistent naming, clear menu options, and reusable components also made the program easier to extend if additional features were required later.
