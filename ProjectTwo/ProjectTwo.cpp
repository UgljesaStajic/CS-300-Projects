// CS 300 - Project Two
// Ugljesa Stajic
// Using a Binary Search Tree (BST).


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>
#include <limits>

using namespace std;

// Trim whitespace from both ends
static inline string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace((unsigned char)s[start])) ++start;
    size_t end = s.size();
    while (end > start && isspace((unsigned char)s[end-1])) --end;
    return s.substr(start, end - start);
}

// Normalize course IDs/prereqisites
static inline string normalize(const string& s) {
    string t = trim(s);
    for (char &c : t) c = (char)toupper((unsigned char)c);
    return t;
}

// Course struct that is used by all data structures
struct Course {
    string courseNumber;              // ID for the course
    string courseName;                // title of the course
    vector<string> prerequisites;     // stores all prerequisites, can be empty

    Course() = default;
};

// Node struct for BST
struct Node {
    Course course;    // All information in the box
    Node* left;       // for navigation smaller courses
    Node* right;      // for navigation larger courses
    Node(const Course& c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class
class BST {
private:
    Node* root;       // this is the reference to the first node in the tree

    // function insertHelper(node, course) for recursive placement
    Node* insertHelper(Node* node, const Course& c) {
        if (node == nullptr) {
            return new Node(c);  // first course becomes the root
        }
        if (c.courseNumber < node->course.courseNumber) {
            node->left = insertHelper(node->left, c); // if course number is less than node.course number for comparison: go left
        } else if (c.courseNumber > node->course.courseNumber) {
            node->right = insertHelper(node->right, c); // else go right for larger course numbers
        } else {
            // do not insert duplicate
        }
        return node;
    }

    // function search(course number) in the tree
    Course searchHelper(Node* node, const string& number) const {
        while (node != nullptr) {
            if (node->course.courseNumber == number) return node->course; // if course number matches the current node's course: return the matching course immediately 
            if (number < node->course.courseNumber) node = node->left;  // else if course number is less than current node's value: go left to continue searching
            else node = node->right;                                      // else go right for larger values
        }
        return Course(); // return an empty course struct when not found 
    }

    // to print course list: perform in-order traversal
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseName << '\n';
        inOrder(node->right);
    }

    void freeNodes(Node* node) {
        if (!node) return;
        freeNodes(node->left);
        freeNodes(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}  // create an empty BST for organizing the data properly
    ~BST() { freeNodes(root); }

    // function insert(course) to place course in tree
    void insert(const Course& c) {
        root = insertHelper(root, c); // insert the course into the BST structure correctly
    }

    // function search(course number)
    Course search(const string& number) const {
        return searchHelper(root, number); // search the BST for that prerequisite course number
    }

    void printCourseList() const {
        inOrder(root); 
    }
};

//Reading the File
vector<Course> readCoursesFromFile(const string& fileName) {
    vector<Course> list; // create an empty list to hold all courses temporarily
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Cannot open file '" << fileName << "'. Please check the filename and try again." << endl; // if the file cannot be opened properly: show an appropriate error message to user
        return list; // stop processing entirely because file is missing
    }

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token)); // split the line by commas into individual tokens
        }

        if (tokens.size() < 2) {
            cout << "Warning: Line " << lineNumber << " format incorrect (needs at least course number and name), skipping line." << endl; // if there are fewer than two tokens total on line: show a clear format error message to inform the user
            continue; // skip the entire line and move next
        }

        Course c;
        c.courseNumber = normalize(tokens[0]); // set course number to the first token read from line
        c.courseName = trim(tokens[1]);        // set course name to the second token read from line

        for (size_t i = 2; i < tokens.size(); ++i) {
            string pre = normalize(tokens[i]);
            if (!pre.empty()) c.prerequisites.push_back(pre); // for each remaining token found in line: add the token to the prerequisites list appropriately
        }

        if (c.courseNumber.empty()) {
            cout << "Warning: Line " << lineNumber << " has empty course number, skipping." << endl;
            continue;
        }

        list.push_back(c); // add the temporary course into the course list finally
    }

    file.close(); // close the file once finished reading all data
    return list;
}

// Validate prerequisites
vector<Course> validatePrerequisites(const vector<Course>& list) {
    vector<Course> current = list; // create an empty validated list for storing correct courses
    bool removedAny = false;

    while (true) {
        set<string> ids;
        for (const auto& c : current) ids.insert(c.courseNumber); // ensures all the prerequisites exists as a course

        vector<Course> next;
        removedAny = false;

        for (const auto& c : current) {
            bool valid = true;
            for (const auto& pre : c.prerequisites) {
                if (ids.find(pre) == ids.end()) {
                    cout << "Warning: prerequisite " << pre << " for course " << c.courseNumber << " not found." << endl; // tells user which prerequisite is missing
                    valid = false; // mark course as invalid for removal
                }
            }
            if (valid) next.push_back(c); // if the course is still valid after checks: add it to the validated list 
            else removedAny = true;       // else: skip this course entirely so it will not be inserted into the BST
        }

        if (!removedAny) {
            return next; // stable
        } else {
            current = move(next);
        }
    }
}

//Print the course information
void printCourseInfo(const BST& tree, const string& number) {
    Course c = tree.search(number);  // search the BST for this specific course number

    if (c.courseNumber.empty()) {
        cout << "Course not found." << endl; // if the course is not found: show “course not found” to user
        return;
    }

    cout << c.courseNumber << ", " << c.courseName << endl; // show the course number and the course name properly

    if (c.prerequisites.empty()) {
    cout << "No prerequisites" << endl; // if the course has no prerequisites at all: show “no prerequisites” to user 
} else {
    cout << "Prerequisites: "; // display prerequisites 
    for (size_t i = 0; i < c.prerequisites.size(); ++i) {
        cout << c.prerequisites[i]; // only print course number as requested by the announcements
        if (i + 1 < c.prerequisites.size()) cout << ", "; // separate with comma
    }
    cout << endl;
}

}

//Menu
int main() {
    cout << "Welcome to the course planner." << endl;

    BST tree;            // create a BST and store courses
    vector<Course> loaded;
    bool dataLoaded = false;

    while (true) {
        cout << "\nMenu:\n"
             << " 1. Load Data Structure.\n"
             << " 2. Print Course List.\n"
             << " 3. Print Course.\n"
             << " 9. Exit\n"
             << "What would you like to do? ";

        int choice;
        if (!(cin >> choice)) {
            // handle non-integer input
            cin.clear();
            string garbage;
            getline(cin, garbage);
            cout << "Invalid input. Please enter a numeric menu option." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remainder

        if (choice == 1) {
            cout << "Enter file name: ";
            string fileName;
            getline(cin, fileName);
            fileName = trim(fileName);
            if (fileName.empty()) {
                cout << "No filename entered." << endl;
                continue;
            }

            
            loaded = readCoursesFromFile(fileName);
            if (loaded.empty()) {
                cout << "No courses loaded from file." << endl;
                dataLoaded = false;
                continue;
            }
            
            loaded = validatePrerequisites(loaded);

            // store courses in the data structure (Binary Search Tree)
            tree = BST(); // reset
            for (const auto& c : loaded) {
                tree.insert(c);
            }
            dataLoaded = true;
            cout << "Data loaded successfully. " << loaded.size() << " course(s) available." << endl;
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Error: Load data first (option 1)." << endl;
            } else {
                cout << "Here is a sample schedule:\n";
                tree.printCourseList(); // call "to print course list" (in-order traversal) 
            }
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Error: Load data first (option 1)." << endl;
            } else {
                cout << "What course do you want to know about?";
                string num;
                getline(cin, num);
                num = normalize(num);
                if (num.empty()) {
                    cout << "No course number entered." << endl;
                    continue;
                }
                printCourseInfo(tree, num); // call "Searching for a Course and Printing Info"
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
