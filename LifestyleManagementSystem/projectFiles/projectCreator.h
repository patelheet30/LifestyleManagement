#include <fstream>
#include <string>
#include <array>
#include <iostream>

/*
 * Naming for the project details.
 *
 * @return String the name of the project
 */
std::string infoGenerator() {
    // https://en.cppreference.com/w/cpp/io/manip/ws
    std::string name, description;

    std::cout << "Enter the name for the project (Try not to include spaces): ";
    std::cin >> std::ws;
    std::getline(std::cin, name);


    return name;
}

/*
 * Creates the text file for the actual storage of projects
 *
 * @param information String the name of the project
 * @return String A string stating if the file was created or an error.
 */
std::string creatingATxtFile(const std::string& information) {
    std::fstream file;
    file.open("../database/" + information + ".txt", std::ios::app);
    if (file.is_open()) {
        file.close();
        return "File with name " + information + " was created";
    } else {
        return "Error";
    }
}
