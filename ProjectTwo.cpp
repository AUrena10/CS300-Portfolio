#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

bool compareCourses(Course a, Course b) {
    return a.courseNumber < b.courseNumber;
}

void loadCourses(string fileName, vector<Course>& courses) {
    ifstream inputFile;

    inputFile.open(fileName.c_str());

    if (!inputFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    courses.clear();

    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courses.push_back(course);
    }

    inputFile.close();

    cout << "Data loaded successfully." << endl;
}

void printCourseList(vector<Course> courses) {
    sort(courses.begin(), courses.end(), compareCourses);

    cout << endl;
    cout << "Here is a sample schedule:" << endl;
    cout << endl;

    for (unsigned int i = 0; i < courses.size(); i++) {
        cout << courses[i].courseNumber << ", " << courses[i].courseTitle << endl;
    }
}

void printCourse(vector<Course> courses, string courseNumber) {
    for (unsigned int i = 0; i < courses.size(); i++) {
        if (courses[i].courseNumber == courseNumber) {
            cout << courses[i].courseNumber << ", " << courses[i].courseTitle << endl;
            cout << "Prerequisites: ";

            if (courses[i].prerequisites.size() == 0) {
                cout << "None";
            }
            else {
                for (unsigned int j = 0; j < courses[i].prerequisites.size(); j++) {
                    cout << courses[i].prerequisites[j];

                    if (j < courses[i].prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }

            cout << endl;
            return;
        }
    }

    cout << "Course not found." << endl;
}

void displayMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << endl;
}

int main() {
    vector<Course> courses;
    int choice = 0;
    string fileName;
    string courseNumber;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();

        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadCourses(fileName, courses);
            break;

        case 2:
            if (courses.size() == 0) {
                cout << "Please load the data structure first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;

        case 3:
            if (courses.size() == 0) {
                cout << "Please load the data structure first." << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                printCourse(courses, courseNumber);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
