#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 检查文件是否已经被处理
bool ifFileProcessed(const string &filename, const vector<string> &processedFiles)
{
    for (const auto &file : processedFiles)
    {
        if (file == filename)
        {
            return true; // 如果已处理，返回true
        }
    }
    return false; // 否则返回false
}

string processFile(const string &filename, vector<string> &processedFiles);

// 替换文件中的#include指令
string replaceIncludes(const string &content, vector<string> &processedFiles)
{
    istringstream iss(content);
    string line, result, fname;
    while (getline(iss, line))
    {
        if (line.find("#include") != string::npos && line.find("\"") != string::npos)
        {
            istringstream ls(line);
            ls >> fname >> fname;                        // 从#include指令中提取文件名
            fname = fname.substr(1, fname.length() - 2); // 去掉文件名周围的引号
            if (!ifFileProcessed(fname, processedFiles))
            {
                processedFiles.push_back(fname);              // 将文件名添加到已处理列表
                result += processFile(fname, processedFiles); // 递归处理该文件
            }
        }
        else
        {
            result += line + "\n"; // 如果不是#include指令，保持原样
        }
    }
    return result; // 返回处理后的文件内容
}

// 处理单个文件
string processFile(const string &filename, vector<string> &processedFiles)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "无法打开文件: " << filename << endl;
        return ""; // 无法打开文件时返回空字符串
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close(); // 读取文件内容并关闭文件

    return replaceIncludes(content, processedFiles); // 替换文件中的#include指令
}

int main(int argc, char *argv[])
{
    string rootFilename = "MainNested.cpp"; // 设置根文件名
    vector<string> processedFiles;
    processedFiles.push_back(rootFilename); // 将根文件添加到已处理列表

    string processedContent = processFile(rootFilename, processedFiles); // 处理根文件

    // 保存或输出处理后的内容
    ofstream out("output.cpp");
    out << processedContent;
    out.close(); // 写入输出文件并关闭

    return 0;
}
