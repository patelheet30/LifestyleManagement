#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "todoBaseCode/addingToDos.h"
#include "todoBaseCode/removingToDos.h"
#include "todoBaseCode/editingToDos.h"
#include "projectFiles/projectCreator.h"
#include "projectFiles/projectViewer.h"

const std::chrono::seconds LOAD_TIMER = std::chrono::seconds(1);
const std::chrono::milliseconds STOP_TIMER = std::chrono::milliseconds(650);


class MainMenu {
public:
    static void start() {
        while (true) {

            std::string value = showMenu();

            if (value == "6"){
                std::this_thread::sleep_for(STOP_TIMER);
                std::cout << "\nThank you for trying out LM system. Stay organised! Goodbye" << std::endl;
                break;
            }

            std::string output = chooseOption(value);
            std::cout << output << std::endl;

        }
    }
private:
    static std::string showMenu() {
        std::string option;
        std::cout << "To-Do Manager Menu" << std::endl;
        std::cout << "1. Add a To-Do" << std::endl;
        std::cout << "2. Edit a To-Do" << std::endl;
        std::cout << "3. Remove a To-Do" << std::endl;
        std::cout << "4. Add a Project" << std::endl;
        std::cout << "5. View a Project" << std::endl;
        std::cout << "6. Stop the system" << "\n" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> option;

        return option;
    }

    /*
     * The function allows you to choose one of the options to use
     * to make the entire project work. It is vital and the main
     * system for the system
     *
     * @param options - String - The option you choose
     * @return string - The output put out on the console
     */
    static std::string chooseOption(const std::string& option) {

        std::string output;

        if (option == "1") {
            std::string modeForAdd = outputChoices();
            std::string addValueReturns = addValue(modeForAdd);
            if (addValueReturns == "invalid-id"){
                output = "Choose an existing project.";
            }
            else if (addValueReturns == "Failed") {
                std::cout << "\n" << addValueReturns << std::endl;
                output = "To-Do not added due to error.";
            } else {
                std::cout << "\n" << addValueReturns << std::endl;
                output = "To-Do Successfully Added!";
            }
        }

        else if (option == "2") {
            std::string modeForView = outputChoices();
            std::string viewChoicesReturns = optionReturns(modeForView);
            if (viewChoicesReturns == "invalid-id") {
                output = "Choose an existing project.";
            } else {
                std::vector<std::array<std::string, 4>> toDosGathered = todoGatherer(viewChoicesReturns);
                outputLists(toDosGathered);

                std::string toDotoEdit;
                std::cout << "Using the IDs, choose a To-Do to edit: ";
                std::cin >> toDotoEdit;

                std::array<std::string, 4> oldArray = toDoFinder(toDotoEdit, viewChoicesReturns);

                std::string choice = editChooser(toDotoEdit, viewChoicesReturns);
                if (choice == "invalid-id") {
                    std::cout << "Invalid ID was chosen. Try again" << std::endl;
                    output = "Choose an available To-Do.";
                } else {
                    std::cout << "The following to-do is going to be edited:\n" << std::endl;
                    std::cout << choice << "\n" << std::endl;

                    std::string choiceMade = whatToEdit();
                    std::string newEdit = newChangedValue();
                    std::string stringBeingConverted = editingToDo(oldArray, choiceMade, newEdit);
                    if (stringBeingConverted == "invalid-id") {
                        output = "Choose a valid option to edit";
                    } else {
                        std::array<std::string, 4> newArray = toDoParser(stringBeingConverted);

                        std::vector<std::array<std::string, 4>> newToDos = replacerFunc(oldArray, newArray, viewChoicesReturns);
                        std::fstream file;
                        file.open("../database/" + viewChoicesReturns, std::ios::out);
                        if (file.is_open()) {
                            for (const auto &array: newToDos) {
                                file << linesInDBsAlt(array);
                            }
                        }

                        file.close();

                        std::cout << "The following is the new to-do" << std::endl;
                        output = toAddedString(newArray);
                    }
                }
            }
        }

        else if (option == "3") {
            std::string modeForRemove = outputChoices();
            std::string removeChoicesReturn = optionReturns(modeForRemove);
            if (removeChoicesReturn == "invalid-id"){
                output = "Choose an existing project.";
            } else {
                std::vector<std::array<std::string, 4>> toDosGathered = todoGatherer(removeChoicesReturn);
                outputLists(toDosGathered);

                auto [toDoToRemove, completeOrDel] = removeVars(toDosGathered);

                if (toDoToRemove == "Error") {
                    output = "Enter a valid ID";
                } else {
                    std::array<std::string, 4> arrayToRemove = toDoFinder(toDoToRemove, removeChoicesReturn);
                    std::array<std::string,4> testingArray = {"", "", "", ""};
                    std::vector<std::array<std::string, 4>> updatingVector = removingToDo(arrayToRemove, toDosGathered);
                    std::fstream file;
                    file.open("../database/" + removeChoicesReturn, std::ios::out);
                    if (file.is_open()) {
                        for (const auto &array: updatingVector) {
                            file << linesInDBsAlt(array);
                        }
                    }

                    file.close();

                    if (completeOrDel == "del") {
                        std::cout << "The following has been deleted: " << std::endl;
                    } else {
                        std::cout << "The following has been completed and subsequently been removed: " << std::endl;
                    }
                    output = toAddedString(arrayToRemove);
                }
            }
        }
        else if (option == "4") {
            std::string informationCollected = infoGenerator();
            std::string newProject = creatingATxtFile(informationCollected);
            output = newProject;
        }
        else if (option == "5") {
            std::vector<std::string> files = fileNameCollected("../database/");
            std::vector<std::string> filesWithoutDaily = dailyRemover(files);
            for (const auto& file : filesWithoutDaily){
                std::cout << "\n" << fileNameParser(file) << std::endl;
            }

            output = "\n";
        }
        else if (option == "6") {
            output = "Closing";
        }
        else {
            output = "Please enter a valid option";
        }
        return output;
    }
};

int main() {
    // Boilerplate code simply for the introduction system
    std::cout << "Welcome to the LM System" << std::endl;
    std::cout << "------------------------\n" << std::endl;
    std::this_thread::sleep_for(LOAD_TIMER);

    MainMenu::start();


    return 0;
}
