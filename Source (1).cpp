// Tabitha Pawlowski
// Module Seven Project Two
// 4/18/23

/* I decided to change my chosen ADT due to the feedback I received and difficulty I expereinced coding the assignment through
a vector ADT. I chose to use a binary search tree instead of a vector because I felt that it would have been a more efficient
data structure, as well as an easier data structure to code for this specific task. I am still having trouble opening my csv file
and getting the program to recognize more than 2 tokens per line, however I believe all my functions follow the correct
algorithms. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;


//This is the structure for the Course class and holds information that each course will contain
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisite;
};




//Class for the Binary Search Tree and holds information for the tree
class BinarySearchTree {
private:

    //Structure that holds information for each node in the course
    struct Node {
        Course course;
        Node* left;
        Node* right;

        // Default node constructor
        Node() {
            left = nullptr;
            right = nullptr;
        }

        // Initializes the node with a course
        Node(Course oneCourse) :
            Node() {
            course = oneCourse;
        }
    };

    //Declares the inOrder function that will help organize the courses into alphanumeric order
    void inOrder(Node* node);

    //Initalizes the size function of the the course list to 0, meaning there are zero courses
    int size = 0;

//Public functions used by the binary search tree that will help organize and perform the menu operations
public:
    BinarySearchTree();
    void InOrder();
    void addNode(Course course);
    Course Search(string courseNumber);
    int Size();

    Node* root;

};

//Default root constructor is set to null
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}



//This function will allow the binary search tree to traverse in order and organize the courses alphanumerically
void BinarySearchTree::InOrder() {
    inOrder(root);
}




//This function traverses the binary search tree in order and will organize the course data alphanumerically
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ": " << node->course.courseName;
        inOrder(node->right);

    }
}



//This will read in data and add it to the binary search tree. 

void BinarySearchTree::addNode(Course course) {
    Node* current = root;
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        while (current != nullptr) {
            if (course.courseNumber < current->course.courseNumber) {
                if (current->left == nullptr) {
                    current->left = new Node(course);
                    current = nullptr;
                }

                else {
                    current = current->left;
                }
            }
            else {
                if (current->right == nullptr) {
                    current->right = new Node(course);
                    current = nullptr;
                }
                else {
                    current = current->right;
                }
            }
        }
    }
    size++;
}







//This function will help if the user wants to find the course name and prerequsites for a specific given course number
Course BinarySearchTree::Search(string courseNumber) {
    Course course;
    Node* current = nullptr;
    if (current->course.courseNumber == courseNumber) {
        return current->course;
    }
    else if (courseNumber < current->course.courseNumber) {
        current = current->left;
    }
    else {
        current = current->right;
    }
    return course;
}







//This will return the number of courses that were read in and put into the binary search tree

int BinarySearchTree::Size() {
    return size;

}



//This function turns the csvFile data into a vector of lines. It is parsed by the commas. This is used in the loadCourses function
vector<string>Parse(string line) {
    char parser = ',';
    line += parser;
    vector<string>lines;
    string tmp = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == parser) {
            lines.push_back(tmp);
            tmp = "";
            i++;

        }
        tmp += line[i];
    }
    return lines;

}




//This function opens the csvFile given by the user, reads in the data, and then closes the file. It uses the parse operation
//from the previous function to separate each token number, name, and prerequsite. For the prerequisites, it checks to see if
//there are more than two tokens, and if there are, they are considered to be prerequisites. For each line, they are added as
// a new node in the binary search tree. I have been working on this function, and I am still having errors when I insert my 
//csvFile name. I get the messages Please try a different file name, 0 courses read, or There must be at least two items per
//course. I am not sure if I have an error with my CSVfile or the code.

void loadCourses(string csvPath, BinarySearchTree* courses) {

    ifstream inputFile;
    string line = "";
    vector<string>strings;
    cout << "Please enter a file name you would like to open" << endl;
    cin >> csvPath;
    inputFile.open(csvPath);

    if (!inputFile.is_open()) {
        cout << "Please try a different file name" << endl;
        return;
    }

    while (!inputFile.eof()) {
        Course course;
        getline(inputFile, line);
        strings = Parse(line);

        if (strings.size() < 2) {
            cout << "Error. There must be at least two items for this course" << endl;
        }

        else {
            course.courseNumber = strings.at(0);
            course.courseName = strings.at(1);

            for (int i = 2; i < strings.size(); i++) {
                course.prerequisite.push_back(strings.at(i));
            }

            courses->addNode(course);
        }
    }
    inputFile.close();
}



//This will print out a specific course's number, name, and any prerequisites it may have
void displayCourse(Course course) {
    cout << course.courseNumber << ", " << course.courseName << endl;
    for (int i = 0; i < course.prerequisite.size(); i++) {
        cout << ", " << course.prerequisite.at(i) << endl;
    }
   
}






//This will print out the menu options for the user
void mainMenu() {
    cout << "Please select one of the available options: " << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;
}



//This is the main function that will utlize all the functions defined for the binary search tree
int main(int argc, char* argv[]) {

    //These are the switch cases for the parsing file. The default is the name of the given csvFile to use
    string csvPath, courseNumber;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        courseNumber = argv[2];
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input2.csv";
    }

    //Course object
    Course course;
    //This is a new object of the binary search tree
    BinarySearchTree* courses = new BinarySearchTree();
  
    //Intialize user choice to 0. The program will exit if the user chooses 9.
    int choice = 0;
    while (choice != 9) {
        mainMenu();
        cin >> choice;

        switch (choice) {
            //This will execute if the user wants to load in all of the course data from the csv file. The amount of courses
            //read in will be displayed
        case 1:
            loadCourses(csvPath, courses);
            cout << courses->Size() << " courses read ";
            break;


            //This will execute if the user wants to print the courses in alphanumeric order
        case 2:
            courses->InOrder();
            break;

            //This will execute if the user wants to know the course name and prerequisites for a given course number
        case 3:
            cout << "Enter the course number for the course you would like information about: " << endl;
            cin >> courseNumber;
            course = courses->Search(courseNumber);
            displayCourse(course);
            break;


            //This will execute if the user wants to exit the program
        case 9:
            exit;
            break;

        }

        //These will clear out the user input each time the for loop returns again
        cin.clear();
        cin.ignore();

    }
    return 0;
};

