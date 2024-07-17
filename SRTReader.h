#ifndef SRTReader_H
#define SRTReader_H

#include<iostream>
#include<fstream>
#include <optional>
#include <vector>
#include<algorithm>


class SRTReader {
    private:
        struct SubtitleEntry {
            std::optional<int> index;
            std::string Time;
            std::string text;
        };

    public:
        SRTReader() = delete;
        SRTReader(const std::string& _path) : path(_path) {}
        std::vector<SubtitleEntry> readLine();

    public:
        std::string & getPath() & {return path;}
        const auto & getEntry() & {return input_file;}

    private:
        std::vector<SubtitleEntry> input_file;
        std::string path;

    private:
        static const bool isNumber(std::string_view str);
        const bool check_empty(std::string_view data);
        void __test_write_back(const std::vector<SubtitleEntry>& t);

};


#endif

