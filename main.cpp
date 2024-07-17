/*************************************************************************
  > File Name: main.cpp
  > Author: yosh20004
  > Mail: 2172622103@qq.com 
  > Created Time: 2024/7/17 19:24:10
 ************************************************************************/

#include "SRTReader.h"

int main() {
    std::string path =
        ".\\[zmk.pw]Koe.no.katachi.2016.1080p.BluRay.x264.DTS-HDChina.srt";
    auto a = SRTReader(path);
    a.readLine();


}

