#include <filesystem>
#include <vector>
#include <string>

/*
 * Removes the daily.txt base file from Containers
 *
 * @param fileNames Container a vector containing all the file names.
 * @return fileNames Container the same vector just without the daily.txt file
 */
std::vector<std::string> dailyRemover(std::vector<std::string> fileNames) {
    for (auto i = fileNames.begin(); i != fileNames.end(); ){
        if (*i == "daily.txt") {
            i = fileNames.erase(i);
        } else {
            ++i;
        }
    }
    return fileNames;
}