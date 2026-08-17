/*
 * ProjectTwo.cpp
 * Edited by: Charles Schwettmann
 * Date: 2026 August 16
 * ABCU Advising Assistance Program
 *
 * Loads course information from a comma-separated file into a binary
 * search tree and provides menu-driven access to course data.
 *
 * Required menu options:
 *   1 - Load Data Structure
 *   2 - Print Course List
 *   3 - Print Course
 *   9 - Exit
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

    constexpr int kLoadDataOption = 1;
    constexpr int kPrintCourseListOption = 2;
    constexpr int kPrintCourseOption = 3;
    constexpr int kExitOption = 9;

    struct Course {
        std::string courseNumber;
        std::string courseTitle;
        std::vector<std::string> prerequisites;
    };

    class CourseTree {
    private:
        struct Node {
            explicit Node(Course courseValue)
                : course(std::move(courseValue)) {}

            Course course;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
        };

        std::unique_ptr<Node> root_;

        static void insertNode(std::unique_ptr<Node>& node, Course course) {
            if (!node) {
                node = std::make_unique<Node>(std::move(course));
                return;
            }

            if (course.courseNumber < node->course.courseNumber) {
                insertNode(node->left, std::move(course));
            }
            else if (course.courseNumber > node->course.courseNumber) {
                insertNode(node->right, std::move(course));
            }
            else {
                // Update an existing record if the same course number appears again.
                node->course = std::move(course);
            }
        }

        static const Course* searchNode(
            const Node* node,
            const std::string& courseNumber) {

            if (node == nullptr) {
                return nullptr;
            }

            if (courseNumber == node->course.courseNumber) {
                return &node->course;
            }

            if (courseNumber < node->course.courseNumber) {
                return searchNode(node->left.get(), courseNumber);
            }

            return searchNode(node->right.get(), courseNumber);
        }

        static void printInOrder(const Node* node) {
            if (node == nullptr) {
                return;
            }

            printInOrder(node->left.get());

            std::cout << node->course.courseNumber << ", "
                << node->course.courseTitle << '\n';

            printInOrder(node->right.get());
        }

    public:
        CourseTree() = default;
        ~CourseTree() = default;

        CourseTree(const CourseTree&) = delete;
        CourseTree& operator=(const CourseTree&) = delete;

        CourseTree(CourseTree&&) noexcept = default;
        CourseTree& operator=(CourseTree&&) noexcept = default;

        void insert(Course course) {
            insertNode(root_, std::move(course));
        }

        [[nodiscard]]
        const Course* search(
            const std::string& courseNumber) const {

            return searchNode(root_.get(), courseNumber);
        }

        void printCourseList() const {
            printInOrder(root_.get());
        }
    };

    [[nodiscard]]
    std::string trim(const std::string& text) {

        constexpr char kWhitespace[] = " \t\r\n";

        const std::size_t first =
            text.find_first_not_of(kWhitespace);

        if (first == std::string::npos) {
            return {};
        }

        const std::size_t last =
            text.find_last_not_of(kWhitespace);

        return text.substr(first, last - first + 1);
    }

    [[nodiscard]]
    std::string toUpper(std::string text) {

        std::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char character) {
                return static_cast<char>(
                    std::toupper(character));
            });

        return text;
    }

    [[nodiscard]]
    std::vector<std::string> splitCsvLine(
        const std::string& line) {

        std::vector<std::string> fields;
        std::stringstream lineStream(line);
        std::string field;

        while (std::getline(lineStream, field, ',')) {
            fields.push_back(trim(field));
        }

        // Preserve a final empty field when the line ends with a comma.
        if (!line.empty() && line.back() == ',') {
            fields.emplace_back();
        }

        return fields;
    }

    [[nodiscard]]
    bool isValidCourseRecord(
        const std::vector<std::string>& fields) {

        return fields.size() >= 2
            && !fields[0].empty()
            && !fields[1].empty();
    }

    [[nodiscard]]
    bool loadCourses(
        const std::string& fileName,
        CourseTree& courseTree,
        std::size_t& courseCount) {

        std::ifstream inputFile(fileName);

        if (!inputFile) {
            std::cout
                << "Error: Unable to open file \""
                << fileName
                << "\".\n";

            return false;
        }

        // Build into a temporary tree so existing data is retained
        // if the new file cannot be loaded successfully.
        CourseTree loadedTree;

        std::size_t loadedCourseCount = 0;
        std::size_t lineNumber = 0;

        std::string line;

        while (std::getline(inputFile, line)) {

            ++lineNumber;

            line = trim(line);

            if (line.empty()) {
                continue;
            }

            const std::vector<std::string> fields =
                splitCsvLine(line);

            if (!isValidCourseRecord(fields)) {

                std::cout
                    << "Warning: Invalid course data on line "
                    << lineNumber
                    << ". Line skipped.\n";

                continue;
            }

            Course course;

            course.courseNumber =
                toUpper(fields[0]);

            course.courseTitle =
                fields[1];

            for (std::size_t index = 2;
                index < fields.size();
                ++index) {

                if (!fields[index].empty()) {

                    course.prerequisites.push_back(
                        toUpper(fields[index]));
                }
            }

            loadedTree.insert(std::move(course));

            ++loadedCourseCount;
        }

        if (loadedCourseCount == 0) {

            std::cout
                << "Error: No valid course records "
                << "were found in the file.\n";

            return false;
        }

        courseTree = std::move(loadedTree);

        courseCount = loadedCourseCount;

        return true;
    }

    void printCourseInformation(
        const CourseTree& courseTree,
        const Course& course) {

        std::cout
            << '\n'
            << course.courseNumber
            << ", "
            << course.courseTitle
            << '\n';

        if (course.prerequisites.empty()) {

            std::cout
                << "Prerequisites: None\n";

            return;
        }

        std::cout
            << "Prerequisites: ";

        for (std::size_t index = 0;
            index < course.prerequisites.size();
            ++index) {

            if (index > 0) {
                std::cout << ", ";
            }

            const std::string& prerequisiteNumber =
                course.prerequisites[index];

            const Course* prerequisiteCourse =
                courseTree.search(prerequisiteNumber);

            if (prerequisiteCourse != nullptr) {

                std::cout
                    << prerequisiteCourse->courseNumber
                    << " ("
                    << prerequisiteCourse->courseTitle
                    << ")";
            }
            else {

                std::cout
                    << prerequisiteNumber
                    << " (title unavailable)";
            }
        }

        std::cout << '\n';
    }

    void displayMenu() {

        std::cout
            << "\nWelcome to the ABCU "
            << "Advising Assistance Program.\n\n"

            << "1. Load Data Structure.\n"
            << "2. Print Course List.\n"
            << "3. Print Course.\n"
            << "9. Exit\n\n"

            << "What would you like to do? ";
    }

    [[nodiscard]]
    int getMenuChoice() {

        std::string input;

        if (!std::getline(std::cin, input)) {
            return kExitOption;
        }

        std::stringstream inputStream(input);

        int choice = -1;

        char extraCharacter = '\0';

        if (!(inputStream >> choice)) {
            return -1;
        }

        if (inputStream >> extraCharacter) {
            return -1;
        }

        return choice;
    }

    [[nodiscard]]
    bool handleLoadCourses(
        CourseTree& courseTree,
        std::size_t& courseCount) {

        std::cout
            << "Enter the course data file name: ";

        std::string fileName;

        std::getline(std::cin, fileName);

        fileName = trim(fileName);

        if (fileName.empty()) {

            std::cout
                << "Error: A file name is required.\n";

            return false;
        }

        if (!loadCourses(
            fileName,
            courseTree,
            courseCount)) {

            return false;
        }

        std::cout
            << courseCount
            << " course record(s) loaded successfully.\n";

        return true;
    }

    void handlePrintCourseList(
        const CourseTree& courseTree,
        bool dataLoaded) {

        if (!dataLoaded) {

            std::cout
                << "Error: You must load the course data first "
                << "by selecting option 1.\n";

            return;
        }

        std::cout
            << "\nHere is a sample schedule:\n\n";

        courseTree.printCourseList();
    }

    void handlePrintCourse(
        const CourseTree& courseTree,
        bool dataLoaded) {

        if (!dataLoaded) {

            std::cout
                << "Error: You must load the course data first "
                << "by selecting option 1.\n";

            return;
        }

        std::cout
            << "What course do you want to know about? ";

        std::string courseNumber;

        std::getline(std::cin, courseNumber);

        courseNumber =
            toUpper(trim(courseNumber));

        if (courseNumber.empty()) {

            std::cout
                << "Error: A course number is required.\n";

            return;
        }

        const Course* course =
            courseTree.search(courseNumber);

        if (course == nullptr) {

            std::cout
                << "Error: Course "
                << courseNumber
                << " was not found.\n";

            return;
        }

        printCourseInformation(
            courseTree,
            *course);
    }

}  // namespace

int main() {

    CourseTree courseTree;

    std::size_t courseCount = 0;

    bool dataLoaded = false;

    while (true) {

        displayMenu();

        const int menuChoice =
            getMenuChoice();

        switch (menuChoice) {

        case kLoadDataOption:

            if (handleLoadCourses(
                courseTree,
                courseCount)) {

                dataLoaded = true;
            }

            break;

        case kPrintCourseListOption:

            handlePrintCourseList(
                courseTree,
                dataLoaded);

            break;

        case kPrintCourseOption:

            handlePrintCourse(
                courseTree,
                dataLoaded);

            break;

        case kExitOption:

            std::cout
                << "Thank you for using the ABCU "
                << "Advising Assistance Program.\n";

            return 0;

        default:

            std::cout
                << "Error: Please choose "
                << "1, 2, 3, or 9.\n";

            break;
        }
    }
}




