/*
 * Allows you to choose between different modes.
 */

#include <string>
#include <iostream>
#include <vector>

#include "../todoBaseCode/viewingToDos.h"
#include "../projectFiles/fileParsers.h"

/*
 * Prints out all the projects you can choose to edit info from
 *
 * @return String the project you chose
 */
std::string outputChoices() {
    std::vector<std::string> fileNames = fileNameCollected("../database/");

    int i = 1;
    std::cout << "Choose one of the following modes you wish to perform an update to:" << std::endl;

    for (const auto& file : fileNames) {
        std::cout << "\t" << i << ") " << fileNameParser(file) << std::endl;
        i++;
    }
    std::string mode;
    std::cin >> mode;

    return mode;
}

/*
 * Returns the file name which the program will add the information
 * to
 *
 * @param choiceTaken String the choice the user took out of all the available files
 * @return String the file name
 */
std::string optionReturns(const std::string& choiceTaken) {
    std::vector<std::string> fileNames = fileNameCollected("../database/");
    if (std::stoi(choiceTaken) > fileNames.size()) {
        return "invalid-id";
    } else {
        return fileNames[std::stoi(choiceTaken) - 1];
    }
}

/*
 * Finds the todoInformation you are planning on taking action upon and sees if it's
 * actually available/valid
 *
 * @param idGiven String the id of the to-do you choose
 * @param fileName String where the to-do is actually located
 * @return Container the to-do parsed into an array for easier updating
 */
std::array<std::string,4> toDoFinder(const std::string& idGiven, const std::string& fileName) {
    std::vector<std::array<std::string,4>> toDoLists = todoGatherer(fileName);
    std::array<std::string,4> neededArray = {"", "", "", ""};


    for (auto& arrays : toDoLists) {
        for (auto& strings : arrays) {
            if (strings == idGiven) {
                neededArray = arrays;
                break;
            }
        }
    }

    return neededArray;
}

/*
 * Lists out all the to-dos that you can update and allows you to choose which
 * one to update.
 *
 * @param idChosen String the particular to-do you have chosen
 * @param fileName String the file where the particular to-do is located
 * @return String the to-do you selected.
 */
std::string editChooser(const std::string& idChosen, const std::string& fileName) {
    std::array<std::string,4> toDoGoingToBeEdited = toDoFinder(idChosen, fileName);
    std::string choice;
    for (auto& string : toDoGoingToBeEdited) {
        if (string.empty()) {
            choice = "invalid-id";
        } else {
            std::string viewingChoice = toAddedString(toDoGoingToBeEdited);
            choice = viewingChoice;
        }
    }

    return choice;
}

/*
 * Allows you to choose what part of the to-do you wish to edit
 *
 * @return the particular part of the to-do you will edit.
 */
std::string whatToEdit() {
    std::string choice;
    std::cout << "Choose if you wish to edit the description(desc), due-date(date), priority(p). Simply enter the value inside the brackets to choose(Defaults to description): ";
    std::cin >> choice;
    if (choice != "desc" && choice != "date" && choice != "p") choice = "desc";
    return choice;
}

/*
 * Simply just allows you to choose what the reason behind a removal
 * of a to-do is. Mainly for aesthetic purpose rather than actual
 * any functionality
 *
 * @param vector Container A vector containing arrays which store the information for each to-do
 * @return Container the particular vector you wish to remove along with why it's being removed.
 */
std::array<std::string,2> removeVars(const std::vector<std::array<std::string,4>>& vector) {
    std::string toDoToRemove; std::string removeOrComplete = "del";
    std::cout << "Using the IDs, choose a To-Do to mark as complete or remove: ";
    std::cin >> toDoToRemove;
    std::cout << "\n";
    bool availableID = false;
    for (const auto& array : vector) {
        if (array[0] == toDoToRemove) {
            availableID = true;
            break;
        }
    }
    if (!availableID) {
        toDoToRemove = "Error";
    } else {
        std::cout << "Do you wish to mark as complete(done) or remove the To-Do(del). Simple enter the value inside the brackets to choose(Defaults to delete): ";
        std::cin >> removeOrComplete;
        std::cout << "\n";
    }

    if (removeOrComplete != "done" && removeOrComplete != "del") removeOrComplete = "del";

    std::array<std::string,2> returnedArray = {toDoToRemove, removeOrComplete};
    return returnedArray;
}
