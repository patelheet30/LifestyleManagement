#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <array>

/*
 * Creates a string to add to the database
 *
 * @param toDoBeingEdited Container the array containing information about the to-do being edited
 * @param valueChosen String what part of the already writen to-do are you editing information about
 * @param newVersion String the new information you are adding
 * @return String the returned and new to-do
 */
std::string editingToDo(std::array<std::string,4>& toDoBeingEdited, const std::string& valueChosen, const std::string& newVersion) {
    std::array<std::string,4> array = toDoBeingEdited;
    if (valueChosen == "desc") {
        array[1] = newVersion;
    } else if (valueChosen == "date") {
        array[2] = newVersion;
    } else if (valueChosen == "p") {
        array[3] = newVersion;
    } else {
        return "invalid-id";
    }
    std::string newToDo = linesInDBs(array[0], array[1], array[2], array[3]);
    return newToDo;
}

/*
 * The replacement value for the edited information
 *
 * @return String the new value.
 */
std::string newChangedValue() {
    std::string newValue;
    std::cout << "\nEnter your replacement value: ";
    std::cin.ignore();
    std::getline(std::cin, newValue);

    return newValue;
}

/*
 * Replaces the old stuff with the new stuff
 *
 * @param oldArray Container the old array containing the old information
 * @param newArray Container the new array containing the new information
 * @param fileName String which file you are planning on replacing the functions with
 * @return Container an entire list of todos but with the new information
 */
std::vector<std::array<std::string,4>> replacerFunc(const std::array<std::string,4>& oldArray, const std::array<std::string,4>& newArray, const std::string& fileName){
    std::vector<std::array<std::string,4>> vectorList = todoGatherer(fileName);
    for (auto& array : vectorList) {
        if (oldArray == array){
            array = newArray;
        }
    }

    return vectorList;
}
