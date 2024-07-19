#include "SRTChecker.h"
#include <vector>
#include "timecheck.h"


struct IdxParseError : SRTCheckError {std::vector<int> nums;};
struct FileParseError : SRTCheckError {};
struct TimeStampError : SRTCheckError {std::vector<std::string_view> errLines;};


const bool SRTChecker::test() {

    try {
        empty();
    } catch (FileParseError& e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    try {
        idx_check();
    } catch (IdxParseError& e) {
        std::cout << e.what() << std::endl;
        int showNum = e.nums.size() >= 4 ? 
            3 : e.nums.size();
        for (int i = 0; i < showNum; ++i) {
            std::cout << " " << e.nums[i] ;
        }
        if (showNum == 3) {
            std::cout << " ..." << std::endl;
        }
        //打印部分错误信息
    }

    try {
        time_check();
    } catch (TimeStampError& e) {
        std::cout << e.what() << std::endl;
        int showNum = e.errLines.size() >= 4 ? 
            3 : e.errLines.size();
        for (int i = 0; i < showNum; i++) {
            std::cout << " " << e.errLines[i] << std::endl;
        }
        if (showNum == 3) {
            std::cout << " ..." << std::endl;
        }
        //打印部分错误信息
        return false;
    }

    return true;

}


void SRTChecker::idx_check() {
    IdxParseError e("[warning] some indexs missed");

    for (int correct_idx = 1; const auto& i : this -> file_data) {
        if (i.index.value_or(-1) != correct_idx) {
            e.nums.push_back(correct_idx);
        } 
        correct_idx += 1;
    }

    if (!e.nums.empty()) {
        throw e; //抛出原文件部分索引缺失异常
    }

}


void SRTChecker::empty() {
    if (this -> file_data.empty()) 
        throw FileParseError("[severe error] Original file was not parsed correctly");
}


void SRTChecker::time_check() {
    TimeStampError e("[severe error] illegal timestamp");

    for (const auto& i : this -> file_data) {
        if (!__check(i.Time)) {
            e.errLines.push_back(i.Time);
        }
    }

    if (!e.errLines.empty()) {
        throw e;
    }
}


