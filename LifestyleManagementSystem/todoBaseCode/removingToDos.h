#include <string>
#include <fstream>
#include <array>
#include <vector>

/*
 * Removes a certain piece of information from the already existing database
 *
 * @param toDoToBeRemoved Container one of the current informations you are planning to remove
 * @param vectorOfTodos Container a whole bunch of information you are planning to remove something from
 * @return Container the new bunch of information with the removed things gone
 */
std::vector<std::array<std::string,4>> removingToDo(const std::array<std::string,4>& toDoToBeRemoved, std::vector<std::array<std::string,4>> vectorOfTodos) {
    // https://www.geeksforgeeks.org/iterators-c-stl/
    for (auto i = vectorOfTodos.begin(); i != vectorOfTodos.end(); ) {
        if (*i == toDoToBeRemoved) {
            i = vectorOfTodos.erase(i);
        } else {
            ++i;
        }
    }

    std::vector<std::array<std::string,4>> newVector = vectorOfTodos;

    return newVector;
}
