/*
 * Custom parsers throughout the program for multiple purposes.
 */

#include <string>
#include <sstream>
#include <array>
#include <fstream>

/*
 * Converts the delimited information into an array for later use.
 *
 * @param toDoString String a delimited string which is broken into an array
 * @return Container the broken down string into an array
 */
std::array<std::string,4> toDoParser(const std::string& toDoString) {
    // https://favtutor.com/blogs/split-string-cpp
    // https://www.digitalocean.com/community/tutorials/return-array-in-c-plus-plus-function

    const std::string& unParsedString = toDoString;
    std::stringstream ss(unParsedString);
    std::string item;
    std::array<std::string,4> values;
    int i = 0;

    while (std::getline(ss, item, ';') && i < 4){
        values[i++] = item;
    }

    return values;
}

/*
 * Converts information provided into a delimited string to be stored
 *
 * @param id, desc, date, p Strings all the information needed for a to-do
 * @return String the delimited string
 */
std::string linesInDBs(const std::string& id, const std::string& desc, const std::string& date, const std::string& p){
    return id + ";" + desc + ';' + date + ';' + p;
}

/*
 * The same as the function above and the opposite of the first function
 * in this file. Converts an array into a delimited string
 *
 * @param array Container the array containing information about the string
 * @return String the delimited string
 */
std::string linesInDBsAlt(const std::array<std::string,4>& array) {
    return array[0] + ";" + array[1] + ';' + array[2] + ';' + array[3] + "\n";
}

/*
 * Converts the array into a string to use for output
 * Used when something is added into the to-do list
 *
 * @param Container the information about the to-do
 * @return String the string which will be printed out
 */
std::string toAddedString(const std::array<std::string,4>& toDoArray) {
    const std::array<std::string,4>& basicArray = toDoArray;
    std::string parsedString = "ID: " + basicArray[0] + "\nTo-do with description: " + basicArray[1] + "\nWith a due date at: " + basicArray[2] + "\nAnd a priority of: " + basicArray[3];
    return parsedString;
}

/*
 * Gets rid of the .txt extension from each of file names to clean up
 * and make everything look nice.
 *
 * @param fileName String the name of the file containing .txt extension
 * @return String the name of the file without the .txt extension
 */
std::string fileNameParser(const std::string& fileName) {
    return fileName.substr(0, fileName.length() - 4);
}

