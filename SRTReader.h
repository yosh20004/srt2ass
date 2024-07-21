#ifndef SRTReader_H
#define SRTReader_H

#include<iostream>
#include<fstream>
#include <optional>
#include <vector>
#include<algorithm>

struct SRTReaderError {
    SRTReaderError(const char* msg) : msg_(msg) {}
    const char* what() {return msg_;}
    private:
        const char* msg_;
};


class SRTReader {
    public:
        struct SubtitleEntry {
            std::optional<int> index;
            std::string Time;
            std::string text;
        };

    public:
        SRTReader() = delete;
        SRTReader(const std::string& _path);
        ~SRTReader();
        void readLine();
        void __test_write_back();

    public:
        std::string & getPath() & {return path;}
        const auto & getEntry() & {return file_data;}

    private:
        std::vector<SubtitleEntry> file_data;
        std::string path;

    private:
        static const bool isNumber(std::string& str);
        const bool check_empty(std::string_view data);

};


#endif

