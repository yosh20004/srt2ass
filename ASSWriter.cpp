#include "ASSWriter.h"
#include <fstream>
#include <optional>
#include <string>


void ASSWriter::write() {
    std::ofstream out(this -> __path.data(), std::ios::binary);

    if (!out.is_open()) {
        throw "";
    }

    for(auto& [layer, Time, style, name, marginL, marginR, marginV, effect, text] :
            this ->__ass_data ) {

        std::string temp = "Dialogue:" + std::to_string(layer) + ',' + Time + ',' + style + ',' + name.value_or("") + ',' + std::to_string(marginL) + ',' + std::to_string(marginR) + ',' + std::to_string(marginV) + ',' + effect.value_or("") + ',' + text;  


        std::cout << temp << std::endl;
    }
}



