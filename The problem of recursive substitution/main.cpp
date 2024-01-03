#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

std::string processFile(const std::string &filename, std::unordered_map<std::string, bool> &visited);

std::string replaceIncludes(const std::string &content, std::unordered_map<std::string, bool> &visited)
{
    std::istringstream iss(content);
    std::string line, result, fname;
    while (std::getline(iss, line))
    {
        if (line.find("#include") != std::string::npos && line.find("\"") != std::string::npos)
        {
            std::istringstream ls(line);
            ls >> fname >> fname;                        // 提取文件名
            fname = fname.substr(1, fname.length() - 2); // 移除引号
            if (visited.find(fname) == visited.end())
            {
                visited[fname] = true;
                result += processFile(fname, visited);
            }
        }
        else
        {
            result += line + "\n";
        }
    }
    return result;
}

std::string processFile(const std::string &filename, std::unordered_map<std::string, bool> &visited)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return replaceIncludes(buffer.str(), visited);
}

int main(int argc, char *argv[])
{
    std::string rootFilename = "MainNested.cpp"; // Change to your root file name
    std::unordered_map<std::string, bool> visited;
    visited[rootFilename] = true;

    std::string processedContent = processFile(rootFilename, visited);

    // Save or output the processed content
    std::ofstream out("output.cpp");
    out << processedContent;
    out.close();

    return 0;
}
