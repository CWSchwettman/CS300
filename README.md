# CS 300: Data Structures and Algorithms
My repository contains selected work from the CS 300: DSA Analysis and Design course. The projects demonstrate my abilities to analyze data structures,
evaluate algorithm efficiency, and apply those concepts to a working C++ application. In Project 1, I analyzed vectors, hash tables, and binary search trees
to determine which data structure would meet the requirements of the ABCU Advising Assistance Program. For Project 2, I took this data structure and used it to 
create a C++ application with a binary search tree.

The primary problem I was solving was how to efficiently organize and retrieve course information for ABCU academic advisors. The program needed to load course 
information from a comma-separated file, store each course and its prerequisites, print the Computer Science courses in alphanumeric order, and allow the ABCU advisors
to search for an individual course and view its information. For Project 1, I designed a solution using vectors, hash tables, and a binary search tree, analyzing
the advantages/disadvantages and runtime performance of each approach. Based on this analysis, I selected a binary search tree because it naturally maintains the courses for
in-order traversal while also providing an average search time of O(log n). For Project 2, I applied this design by developing a working C++ application using a binary
search tree.

My approach to this problem was to first identify the operations the program needed to perform by looking at the two most important requirements: 1) printing the entire
course list in alphanumeric order, and 2) retrieving the information about a specific course. Next, I compared the characteristics of the three data structures (vector, hash
table, and binary search tree). A vector can be implemented simply, has a relatively low memory overhead, but searching requires a linear search and must be sorted before
displaying the courses. A hash table provides a very fast lookup performance, but it does not naturally maintain the courses in sorted order. A binary search tree provides
average O(log n) searching while allowing an in-order traversal to produce the course list in alphanumeric order. This project deepened my understanding of data structures
and why choosing the right one is so important. Using different data structures can affect the efficiency, organization, readability, and scalability of the program.
Instead of using the data structure I was most familiar with, I learned to evaluate how each structure supports the program's actual requirements.

One challenge I faced while compiling this program was translating the design and pseudocode from Project 1 into a working C++ application. I needed to ensure that the
course records were read from the input files, the courses were inserted, the tree was searched, the course list was printed, and user input was handled. I also
incorporated error handling and input validation by checking the program to see whether the course data was loaded before allowing the user to search/print the course
information. It also handles invalid menu selections or course records, missing filenames, and course numbers that cannot be found. I gained a better understanding of why
I should test each individual component to identify and correct errors before completing the program. This allowed me to catch small mistakes early on and to save time. I
also ran the completed program to make sure that the expected output was displayed.

In this project, I learned the importance of a step-by-step software development process by first analyzing the problem, considering the requirements, writing pseudocode,
and comparing data structures and their run-time characteristics before implementing the code. I also learned that a solution that works correctly is not always the best
solution. As a developer, I must consider efficiency, maintainability, scalability, and how the program will use the data. The relationship between the two projects was 
extremely valuable. I was able to take my analysis of the binary search tree and implement it into a working C++ application. This way, I can organize courses according to
their course numbers and use an in-order traversal that allows the program to print them in alphanumeric order without having to run a separate sorting operation.

In Project 2, I used a Course structure to represent individual course records and a CourseTree class to manage the binary search tree. I separated tasks such as trimming
input, converting course numbers to uppercase, parsing CSV records, validating the course data, loading the file, printing the course information, and processing the menu
selection. I also used descriptive names, constants for menu options, consistent formatting, and comments to make the program easy to read and understand. The use of
`std::unique_ptr` for the binary search tree nodes provides automatic memory management and reduces the need for manual memory handling. Overall, this shifted my focus from
only whether a program worked to how it is designed. Moving forward, while developing software, I will consider data structure selection, algorithm efficiency, modularity,
readability, input validation, and maintainability. 
