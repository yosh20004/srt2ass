#ifndef srtTransfer_H
#define srtTransfer_H

#include "SRTReader.h"
#include "SRTChecker.h"
#include <optional>

using SubtitleEntry = SRTReader::SubtitleEntry;

class srtTransfer {

    public:
        struct AssSubtitleEntry {
            int layer = 0;                                 // 层级
            std::string Time;                          // 时间戳
            std::string style = "Default";             // 样式
            std::optional<std::string> name = {};      // 字幕角色名称
            int marginL = 0;                           // 左边距
            int marginR = 0;                           // 右边距
            int marginV = 0;                           // 垂直边距
            std::optional<std::string> effect = {};    // 特效
            std::string text;                          // 字幕文本

            //AssSubtitleEntry(const std::string& time, const std::string& txt) 
            //    : Time(time), text(txt) {}
        };

    public:
        srtTransfer() = delete;
        srtTransfer(const std::vector<SubtitleEntry>& file_data);
        ~srtTransfer();
        const auto getEntry() const {return __ass_data;}

    private:
        void transfer();
        std::string time_transfer(std::string_view Time);

    private:
        const std::vector<SubtitleEntry>& __file_data;
        std::vector<AssSubtitleEntry> __ass_data;
        
};

#endif
