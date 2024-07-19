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
    }

    this -> __ass_data = ass_data;
}


std::string srtTransfer::time_transfer(std::string_view data) {

    std::string target; 
    for (const auto& i : data) {
        if (i == ',') {
            target.push_back('.');
        } else if (i == '>') {
            target.push_back(',');
        } else if (std::isdigit(i)) {
            target.push_back(i);
        }
    }

    /*
     * Before: 00:00:01,210 --> 00:00:08,090  After: 0:00:01.21,0:00:08.09
     *
     */

    return target;
}
