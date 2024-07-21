/*************************************************************************
  > File Name: main.cpp
  > Author: yosh20004
  > Mail: 2172622103@qq.com 
  > Created Time: 2024/7/17 19:24:10
 ************************************************************************/

#include "SRTReader.h"
#include "srtTransfer.h"
#include "ASSWriter.h"
#include <ctime>

std::string path;
std::string Tpath;

auto analyse(int argc, char* argv[]) -> const bool {
    if (argc == 1) {
        std::cout << "necessary message needed";
        return false;
    } else if (argc == 2) {
        path = argv[1];
        if (path.ends_with(".srt")) {
            Tpath = std::string(argv[1]);
            Tpath.erase(Tpath.length() - 3);
            Tpath += "ass";
            return true;
        } else {
            return false;
        }
    } else {
        path = argv[1];
        Tpath = argv[2];
        return true;
    }
}

int main(int argc, char* argv[]) {
    if (!analyse(argc, argv)) {
        return -1;
    }

    auto a = SRTReader(path);
    a.readLine();
    //按行读取原文件

    auto sT = srtTransfer(a.getEntry());
    //解析信息 进行转换

    auto aW = ASSWriter(Tpath, sT.getEntry());
    aW.write();
    //写入ass文件

}

