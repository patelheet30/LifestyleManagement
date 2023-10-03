#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>

/*
 * Gets a list of file names and database files from the database
 * directory
 *
 * @param directoryPath String the path to the directory containing the text file
 * @return Container names of the text files.
 */
std::vector<std::string> fileNameCollected(const std::string& directoryPath) {
    // https://en.cppreference.com/w/cpp/filesystem/directory_iterator
    // https://en.cppreference.com/w/cpp/filesystem/path

    std::vector<std::string> fileNames;
    std::filesystem::directory_iterator iterator(directoryPath);

    for (auto& file : iterator) {
        if (file.path().extension() == ".txt") {
            fileNames.push_back(file.path().filename().string());
        }
    }

    return fileNames;
}

