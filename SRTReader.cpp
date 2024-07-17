#include "SRTReader.h"

const bool SRTReader::isNumber(std::string_view str) {
    /*检查改行是否为数字*/
    const int offset = str.ends_with("\r") ? 2 : 0; 

    if (!str.empty() && std::all_of(str.begin(), str.end() - offset, [](char c){
                return std::isdigit(c);}))
        return true;

    else return false;
}



const bool SRTReader::check_empty(std::string_view data) {
    /*判断改行是否为空*/
    return data == "\r";
}



std::vector<SRTReader::SubtitleEntry> SRTReader::readLine() {
    const std::string& input_file = this -> path;
    std::ifstream in(input_file, std::ios::binary);
    std::string data;
    std::vector<SubtitleEntry> file_data;
    SubtitleEntry a;

    enum STEP {
        initIndex,
        initTime,
        initText,
        __blank
    } state= initIndex;


    auto __initIndex = [&a, &data, &file_data]() -> STEP {
        if (isNumber(data)) {
            a.index = stoi(data);
            std::cout << "yes";
            auto next_state = initTime;
            return next_state;
        } else {
            a.Time = data;
            a.index = std::nullopt;
            auto next_state = initText;
            return next_state;
        }
    };

    auto __initTime = [&]() -> STEP {
        a.Time = data;
        auto next_state = initText;
        return next_state;
    };

    auto __initText = [&]() -> STEP {
        a.text = data;
        auto next_state = __blank;
        return next_state;
    };

    auto __waitForBlank = [&]() -> STEP {
        auto next_state = __blank;
        if (check_empty(data)) { /*如果是空行(两个字幕块的分割)
                                  * 则开始初始化下一字幕块*/
            file_data.push_back(a);
            next_state = initIndex;
        } else {
            a.text += "\n";
            a.text += data; //若不是 则说明该字幕块还未完全匹配
                            // next_state = __blank; //因此继续匹配当前字幕块
        }
        return next_state;
    };


    while (std::getline(in, data)) {
        if (state == initIndex) {
            //处理index或Time
            state = __initIndex();
        }

        else if (state == initTime) {
            a.Time = data;
            state = __initTime();
        }

        else if (state == initText) {
            a.text = data;
            state = __initText();
        }

        else {
            state = __waitForBlank();
        }
    }

    if (state == __blank) {file_data.push_back(a);} 
    /*有时候文件结尾没有空行
     *导致最后一个字幕块保存不下来 这一句代码尝试解决之
     */
    return file_data;
}



void SRTReader::__test_write_back(const std::vector<SubtitleEntry>& t) {
    std::ofstream out("./test.ass", std::ios::binary);

    for (const auto& i : t) {
        try {
            out << std::to_string(i.index.value()) + "\r";
            out << i.Time;
            out << i.text;
            out << "\r";
        } catch (const std::exception& e) {
            out << i.Time;
            out << i.text;
            out << "\r";
        }
    }
}

