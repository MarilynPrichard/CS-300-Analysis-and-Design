#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a Course struct to hold course data: course number, course title, and prerequisites
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load courses from a CSV file into the vector
bool loadCourses(const string& filename, vector<Course>& courses) {
    ifstream file(filename);  // Open the file for reading
    if (!file.is_open()) {  // Check if the file opened successfully
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {  // Read the file line by line
        stringstream ss(line);  // Create a stringstream to process each line
        Course course;
        string token;

        // Extract course number and title from the line
        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        // Extract prerequisites (if any) from the line
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                course.prerequisites.push_back(token);  // Add prerequisites to the course
            }
        }

        courses.push_back(course);  // Add the course to the courses vector
    }

    file.close();  // Close the file
    return true;
}

// Function to print the list of all courses
void printCourseList(const vector<Course>& courses) {
    cout << "Here is a sample schedule:" << endl;
    // Loop through the courses vector and print course number and title
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print detailed information about a specific course
void printCourseInfo(const vector<Course>& courses, const string& courseNumber) {
    // Loop through the courses to find the course matching the given course number
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << course.courseNumber << ", " << course.courseTitle << endl;
            // If the course has no prerequisites, print "None"
            if (course.prerequisites.empty()) {
                cout << "Prerequisites: None" << endl;
            }
            else {
                // Otherwise, print the list of prerequisites
                cout << "Prerequisites: ";
                for (const auto& prereq : course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
            return;
        }
    }
    // If the course number is not found, notify the user
    cout << "Course not found!" << endl;
}

// Function to sort courses alphanumerically by course number
bool compareCourses(const Course& a, const Course& b) {
    return a.courseNumber < b.courseNumber;  // Compare the course numbers
}

int main() {
    vector<Course> courses;  // Vector to store all course data
    string filename = "CS 300 ABCU_Advising_Program_Input.csv"; // The file name containing course data
    int choice;  // User's menu choice
    bool dataLoaded = false;  // Flag to check if data is loaded

    cout << "Welcome to the course planner." << endl;

    do {
        // Display the menu options
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;  // Get the user's menu choice

        switch (choice) {
        case 1:
            // Load course data into the vector
            if (loadCourses(filename, courses)) {
                dataLoaded = true;  // Set flag to true if data is loaded successfully
                cout << "Course data loaded successfully." << endl;
            }
            break;

        case 2:
            // Print the list of courses, sorted alphanumerically
            if (dataLoaded) {
                sort(courses.begin(), courses.end(), compareCourses);  // Sort the courses
                printCourseList(courses);  // Print the sorted list
            }
            else {
                cout << "Course data not loaded. Please load data first." << endl;
            }
            break;

        case 3:
            // Print information about a specific course
            if (dataLoaded) {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber;  // Get the course number from the user
                // Convert the course number to lowercase for case-insensitive comparison
                transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::tolower);
                printCourseInfo(courses, courseNumber);  // Print course details
            }
            else {
                cout << "Course data not loaded. Please load data first." << endl;
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;  // Exit message
            break;

        default:
            cout << choice << " is not a valid option." << endl;  // Handle invalid menu options
            break;
        }
    } while (choice != 9);  // Repeat until the user chooses to exit (option 9)

    return 0;
}
