#include <iostream>  // For standard I/O operations
#include <fstream>   // For file I/O operations
#include <vector>    // For using the std::vector container
#include <string>    // For using the std::string class
#include <sstream>   // For string stream to handle numeric conversions

// Class definition for the TextEditor
class TextEditor {
    public:
        // Displays the main menu
        void displayMenu();
        // Opens a file and reads its contents into the vector
        void openFile(const std::string& filename);
        // Saves the content of the vector to a file
        void saveFile(const std::string& filename);
        // Allows the user to edit the content
        void editContent();
        // Displays the current content
        void showContent();
    private:
        // Vector to store the lines of text
        std::vector<std::string> content;
        // Helper function to display content with line numbers
        void displayContentWithLineNumbers();
        // Helper function to read a valid line number from the user
        int readLineNumber();
        // Helper function to add .txt extension if not present
        std::string addTxtExtension(const std::string& filename);
};

// Function to display the main menu
void TextEditor::displayMenu() {
    std::cout << "Simple Text Editor\n";
    std::cout << "1. Open File\n";
    std::cout << "2. Save File\n";
    std::cout << "3. Edit Content\n";
    std::cout << "4. Show Content\n";
    std::cout << "5. Exit\n";
}

// Function to add .txt extension if not present
std::string TextEditor::addTxtExtension(const std::string& filename) {
    if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt") {
        return filename;
    }
    else {
        return filename + ".txt";
    }
}

// Function to open a file and read its contents into the vector
void TextEditor::openFile(const std::string& filename) {
    std::string fullFilename = addTxtExtension(filename);
    std::ifstream file(fullFilename);  // Open the file
    if (file.is_open()) {  // Check if the file is successfully opened
        content.clear();  // Clear the current content
        std::string line;
        while (getline(file, line)) {  // Read the file line by line
            content.push_back(line);  // Add each line to the vector
        }
        file.close();  // Close the file
        std::cout << "File opened successfully.\n";
    }
    else {
        std::cout << "Failed to open file.\n";
    }
}

// Function to save the content of the vector to a file
void TextEditor::saveFile(const std::string& filename) {
    std::string fullFilename = addTxtExtension(filename);
    std::ofstream file(fullFilename);  // Open the file for writing
    if (file.is_open()) {  // Check if the file is successfully opened
        for (const auto& line : content) {  // Write each line to the file
            file << line << '\n';
        }
        file.close();  // Close the file
        std::cout << "File saved successfully.\n";
    }
    else {
        std::cout << "Failed to save file.\n";
    }
}

// Helper function to display content with line numbers
void TextEditor::displayContentWithLineNumbers() {
    for (size_t i = 0; i < content.size(); ++i) {
        std::cout << i + 1 << ": " << content[i] << '\n';
    }
}

// Helper function to read a valid line number from the user
int TextEditor::readLineNumber() {
    std::string input;
    int lineNumber;
    while (true) {
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> lineNumber && ss.eof()) {
            return lineNumber;
        }
        std::cout << "Invalid input. Please enter a valid line number: ";
    }
}

// Function to allow the user to edit the content
void TextEditor::editContent() {
    std::string command;
    std::cout << "Editing content (type 'help' for commands):\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "help") {
            std::cout << "Commands:\n";
            std::cout << "  add             - Add a new line \n";
            std::cout << "  edit            - Edit a line with <text>\n";
            std::cout << "  delete          - Delete a line\n";
            std::cout << "  show            - Show current content\n";
            std::cout << "  save            - Save changes\n";
            std::cout << "  end             - End editing session\n";
        }
        else if (command == "add") {
            std::cout << "Enter text to add: ";
            std::string newLine;
            std::getline(std::cin, newLine);
            content.push_back(newLine);
        }
        else if (command == "edit") {
            displayContentWithLineNumbers();
            std::cout << "Enter line number to edit: ";
            int lineNumber = readLineNumber();
            if (lineNumber > 0 && lineNumber <= content.size()) {
                std::cout << "Enter new text for line " << lineNumber << ": ";
                std::string newText;
                std::getline(std::cin, newText);
                content[lineNumber - 1] = newText;
            }
            else {
                std::cout << "Invalid line number.\n";
            }
        }
        else if (command == "delete") {
            displayContentWithLineNumbers();
            std::cout << "Enter line number to delete: ";
            int lineNumber = readLineNumber();
            if (lineNumber > 0 && lineNumber <= content.size()) {
                content.erase(content.begin() + lineNumber - 1);
            }
            else {
                std::cout << "Invalid line number.\n";
            }
        }
        else if (command == "show") {
            displayContentWithLineNumbers();
        }
        else if (command == "save") {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            saveFile(filename);
        }
        else if (command == "end") {
            break;
        }
        else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }
}

// Function to display the current content
void TextEditor::showContent() {
    std::cout << "Current Content:\n";
    std::cout << "--------------------\n";
    for (const auto& line : content) {  // Print each line in the vector
        std::cout << line << '\n';
    }
    std::cout << "--------------------\n";
}

// Main function to run the text editor
int main() {
    TextEditor editor;  // Create an instance of TextEditor
    int choice;
    std::string filename;

    while (true) {
        editor.displayMenu();  // Display the menu

        // Validate input
        std::cin >> choice;  // Get the user's choice
        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the newline character after the integer input

        // Handle the user's choice
        switch (choice) {
        case 1:
            std::cout << "Enter filename to open: ";
            std::getline(std::cin, filename);
            editor.openFile(filename);  // Open the specified file
            break;
        case 2:
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            editor.saveFile(filename);  // Save the content to the specified file
            break;
        case 3:
            editor.editContent();  // Allow the user to edit the content
            break;
        case 4:
            editor.showContent();  // Show the current content
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;  // Exit the program
        default:
            std::cout << "Invalid choice. Please try again.\n";  // Handle invalid choices
            break;
        }
    }
}
