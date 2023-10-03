#include <string>
#include <fstream>
#include <vector>

#include "../utils/parsers.h"
#include "../utils/chooser.h"

/*
 * Creates an ID which is added to each todostring for easier use
 *
 * @param fileName String the name of the file it uses to see which ID to generate
 * @return int ID the actual ID that is generated for use.
 */
int idGenerator(const std::string& fileName) {
    // https://www.mygreatlearning.com/blog/vectors-in-c/#:~:text=to%20copy%20vectors.-,Vectors%20and%20Array%20in%20C%2B%2B,Array%20is%20index%20based.
    std::fstream file;
    std::vector<std::string> lines;
    file.open("../database/" + fileName, std::ios::in);
    if (file.is_open()) {
        std::string values;
        while (std::getline(file, values)) {
            lines.push_back(values);
        }
    }

    if (lines.empty()){
        return 1;
    } else if (lines.size() == 1) {
        return 2;
    } else {
        std::string secondLastValue = lines.rbegin()[0];

        std::array<std::string,4> unParsedID = toDoParser(secondLastValue);
        std::string parsedID = unParsedID[0];
        int insertedValue = std::stoi(parsedID) + 1;

        return insertedValue;
    }
}

/*
 * Adding values to a text file
 *
 * @param modeUsed String the file to add the todos to
 * @return String A parsed string showing information showing what has been added
 */
std::string addValue(const std::string& modeUsed) {
    // https://linuxhint.com/use-cpp-fstream/
    // https://stackoverflow.com/questions/70628471/clang-tidy-loop-variable-is-copied-but-only-used-as-const-reference-consider
    // https://www.freecodecamp.org/news/string-to-int-in-c-how-to-convert-a-string-to-an-integer-example/#:~:text=One%20effective%20way%20to%20convert,the%20integer%20version%20of%20it.
    // https://stackoverflow.com/questions/4825483/code-for-getting-multiple-words-in-a-string-from-user

    std::string fileUsed = optionReturns(modeUsed);

    if (fileUsed == "invalid-id"){
        return "invalid-id";
    } else {
        std::string description, time;
        int id, priority;

        std::cout << "PlEASE DO NOT USE A SEMI COLON IN ANY OF THE INPUTS\n" << std::endl;

        std::cout << "\nEnter a description for the to-do: ";
        std::cin.ignore();
        std::getline(std::cin, description);

        std::cout << "Enter a deadline for the to-do: ";
        std::getline(std::cin, time);

        std::cout << "Enter the level of priority for the to-do: ";
        std::cin >> priority;

        id = idGenerator("../database/" + fileUsed);

        std::string insertedStr = linesInDBs(std::to_string(id), description, time, std::to_string(priority)) + "\n";
        std::fstream file;
        std::array<std::string, 4> values = toDoParser(insertedStr);
        std::string returnedString = toAddedString(values);

        file.open("../database/" + fileUsed, std::ios::out | std::ios::app);
        if (file.is_open()) {
            file << insertedStr;
            file.close();
            return returnedString;
        } else {
            std::cout << "Error opening the text file" << std::endl;
            file.close();
            return "Failed";
        }
    }
}
