#include <sys/stat.h>
#include "FileHandler.h"

namespace biemgine
{
    FileHandler::FileHandler(string filePath, bool overwrite)
    {
        if (overwrite) {
            currentFile.open(filePath, fstream::in | fstream::out | fstream::trunc);
        }
        else {
            currentFile.open(filePath, fstream::in | fstream::out | fstream::app);
        }
    }

    vector<vector<string>> FileHandler::getValues()
    {
        vector<vector<string>> values;
        string line;

        for (string row_line; getline(currentFile, row_line);)
        {
            values.emplace_back();
            istringstream row_stream(row_line);

            for (string column; getline(row_stream, column, ',');) {
                values.back().push_back(column);
            }
        }

        return values;
    }

    void FileHandler::writeLine(vector<string> values)
    {
        for (auto v = values.begin(); v != values.end(); v++) {
            if (v != values.begin()) {
                currentFile << ",";
            }
            currentFile << *v;
        }
        currentFile << "\n";
    }

    void FileHandler::writeLine(string value)
    {
        currentFile << value << "\n";
    }

    bool FileHandler::remove(const string filePath)
    {
        const char *str = filePath.c_str();
        return std::remove(str);
    }

    bool FileHandler::exists(const string filePath)
    {
        struct stat buffer;
        return (stat(filePath.c_str(), &buffer) == 0);
    }
	void FileHandler::close()
	{
        currentFile.close();
	}
}
