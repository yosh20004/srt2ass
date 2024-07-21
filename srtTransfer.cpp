#include "srtTransfer.h"
#include "SRTChecker.h"
#include <vector>


srtTransfer::srtTransfer(const std::vector<SubtitleEntry>& file_data) : __file_data(file_data) {

    SRTChecker check(file_data);
    if (!check.test()) {
        this->~srtTransfer();
    }

    std::vector<AssSubtitleEntry> ass_data;
    for (const auto& [__index__, Time, Text] : file_data) {
        AssSubtitleEntry temp {
            .Time = time_transfer(Time), .text = Text
        };
        ass_data.push_back(temp);
    }

    this -> __ass_data = std::move(ass_data);
}


std::string srtTransfer::time_transfer(std::string_view data) {
    //将srt文件的时间戳转换为ass文件的时间戳 需要注意的是
    //两种文件在毫秒上的精度存在差异，因此我们只保留毫秒的前两位
    std::string StartTime;
    std::string EndTime;
    bool StartTimeCount = true;

    for (const auto& i : data) {
        if (i == ',' && StartTimeCount == true) {
            StartTime.push_back('.');
        }
        else if (i == ',' && StartTimeCount == false) {
            EndTime.push_back('.');
        }
        else if (i == '>') {
            StartTimeCount = false;
        }
        else if (StartTimeCount && (std::isdigit(i) || i == ':')) {
            StartTime.push_back(i);
        } 
        else if (!StartTimeCount && (std::isdigit(i) || i == ':')) {
            EndTime.push_back(i);
        }
    }

    auto DealWithMilliseconds = [](std::string& Time) -> void {
        for (int i = 0; i <= Time.length(); ++i) {
            if (Time[i] == '.') {
                Time.erase(i + 3);  // i+1是点号的位置，再加上2是删除后面的两位数字
                break;  // 只处理第一个点号后面的两位数字
            }
        }
    };

    /*
     * Before: 00:00:01,210 --> 00:00:08,090  After: 0:00:01.21,0:00:08.09
     *
     */

    DealWithMilliseconds(StartTime);
    DealWithMilliseconds(EndTime);
    return StartTime + ',' + EndTime;
}

void searchNumBack(std::string& time, const int loc) {
    for (int i = loc; i >= 0; ++i) {
        if (std::isdigit(time[i])) {
            time.erase(i);
            break;
        }
    }
}
