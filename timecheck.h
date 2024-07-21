#ifndef timecheck_H
#define timecheck_H


#include <cctype>
#include <regex>

const bool __check(const std::string& time) __attribute__((noinline));


const bool __check(const std::string& time)  {
    std::regex full_timestamp_regex(R"((\d{2}):(\d{2}):(\d{2}),(\d{3})\s*-->\s*(\d{2}):(\d{2}):(\d{2}),(\d{3}))");
    std::regex single_timestamp_regex(R"((\d{2}):(\d{2}):(\d{2}),(\d{3}))");
    if (std::regex_match(time, full_timestamp_regex)) {
        return true;
    } 

    else if (std::regex_match(time, single_timestamp_regex)) {
        return true;
    }

    return false;
}


#endif
