#ifndef SRTChecker_H
#define SRTChecker_H

#include "SRTReader.h"
#include <vector>


using SubtitleEntry = SRTReader::SubtitleEntry;


struct SRTCheckError {
    SRTCheckError(const char* msg) : msg_(msg) {}
    const char* what() {return msg_;}
    private:
        const char* msg_;
};


class SRTChecker {
    public:
        SRTChecker() = delete;
        SRTChecker(const std::vector<SubtitleEntry>& file_data) : file_data(file_data) {}
        const bool test();

    private:
        void idx_check();
        void empty();
        void time_check();

    const std::vector<SubtitleEntry>& file_data;
};

#endif
