/*
 * Gives you multiple actions to perform with to-dos.
 */

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <array>

const std::chrono::milliseconds DELAY_TIMER_LESS_THAN_FIVE = std::chrono::milliseconds(650);
const std::chrono::milliseconds DELAY_TIMER_LESS_THAN_TEN = std::chrono::milliseconds(350);
const std::chrono::milliseconds DELAY_TIMER_OTHERS = std::chrono::milliseconds(125);

/*
 * Gathers every todos there are in a file
 *
 * @param fileName String the file you are gathering from
 * @return Container a list containing a list of the parsed information
 */
std::vector<std::array<std::string,4>> todoGatherer(const std::string& fileName) {
    std::fstream file;
    std::vector<std::array<std::string,4>> lines;
    file.open("../database/" + fileName, std::ios::in);
    if (file.is_open()) {
        std::string values;
        while (std::getline(file, values)) {
            lines.push_back(toDoParser(values));
        }
    }
    return lines;
}

/*
 * Prints out all the information stored in a particular file. Delays are added based on how much info there is
 *
 * @param Container toDoLists Contains all the information that is being printed
 */
void outputLists(const std::vector<std::array<std::string,4>>& toDoLists) {
    std::vector<std::array<std::string,4>> vectorOfToDos = toDoLists;
    for (auto& vectorOfToDo : vectorOfToDos) {
        if (vectorOfToDos.size() < 5){
            std::this_thread::sleep_for(DELAY_TIMER_LESS_THAN_FIVE);
            std::cout << toAddedString(vectorOfToDo) << "\n" << std::endl;
        } else if (vectorOfToDos.size() < 10) {
            std::this_thread::sleep_for(DELAY_TIMER_LESS_THAN_TEN);
            std::cout << toAddedString(vectorOfToDo) << "\n" << std::endl;
        } else {
            std::this_thread::sleep_for(DELAY_TIMER_OTHERS);
            std::cout << toAddedString(vectorOfToDo) << "\n" << std::endl;
        }
    }
}