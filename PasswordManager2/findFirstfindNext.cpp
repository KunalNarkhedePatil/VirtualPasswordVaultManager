#include <windows.h>
#include <iostream>
#include <string>

void ListFilesInDirectory(const std::string& directory) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directory + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "FindFirstFile failed: " << GetLastError() << std::endl;
        return;
    }

    do {
        const std::string fileName = findFileData.cFileName;

        // Skip the "." and ".." entries
        if (fileName != "." && fileName != "..") {
            // Print the full path of the file or directory
            std::cout << directory << "\\" << fileName << std::endl;

            // Check if it's a directory
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // If it's a directory, call the function recursively
                ListFilesInDirectory(directory + "\\" + fileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        std::cerr << "FindNextFile failed: " << GetLastError() << std::endl;
    }

    FindClose(hFind);
}

int main() {
    std::string directoryPath = "C:\\Users\\Admin\\Desktop\\Samples1"; // Change this to your directory
    ListFilesInDirectory(directoryPath);
    return 0;
}