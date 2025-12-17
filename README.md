CS 300 – Portfolio Reflection
Ugljesa Stajic

Portfolio Artifacts

Project One: Runtime and memory analysis comparing Vector, Hash Table, and Binary Search Tree data structures.
Project Two: A complete C++ program using a Binary Search Tree (BST) to load, store, sort, and display Computer Science courses in alphanumeric order.

Together, these artifacts demonstrate my understanding of data structures, algorithms, and performance tradeoffs.

The main problem I was solving was how to efficiently store, search, validate, and print course information from a file. Each course could have multiple prerequisites, and the program needed to handle missing or invalid data safely. The solution also had to allow users to search for individual courses and print an alphanumerically ordered list of all courses.

I approached the problem by implementing and comparing multiple data structures: Vector, Hash Table, and Binary Search Tree. Understanding data structures was important because each one has different performance characteristics.

Vectors are easy to implement but become slow when searching or validating prerequisites.
Hash tables provide very fast lookups but do not keep data sorted.
Binary Search Trees provide a good balance by allowing fast searching while keeping courses naturally ordered.
This comparison helped me choose the best structure based on both runtime efficiency and usability.

One of the main challenges was handling invalid prerequisites and preventing the program from crashing due to bad input data. I overcame this by adding a validation step that checks whether all prerequisites exist before inserting courses into the data structure.
Another roadblock was managing user input errors and file-reading issues. I solved this by adding clear error messages and input validation, which made the program more stable and user-friendly.

This project expanded my approach by teaching me to think more about performance, scalability, and data organization before writing code. Instead of focusing only on whether the program works, I now consider how well it works as the data size increases. The runtime analysis helped me understand why certain data structures are better choices depending on the problem being solved.

My work on this project improved how I write programs by emphasizing clear structure, meaningful comments, and modular design. I separated functionality into logical functions and classes, which makes the code easier to read, maintain, and adapt in the future.
Using consistent naming, clear menu options, and reusable components also made the program easier to extend if additional features were required later.
