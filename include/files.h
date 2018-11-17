//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_FILES_H
#define HAUER_ON_REPEAT_FILES_H

#include <string>
#include <iostream>
#include <fstream>

class File {
public:
    void write(std::string input);

    explicit File(std::string filename);

    void create_midi_pdf();
private:
    std::string filename;
};

#endif //HAUER_ON_REPEAT_FILES_H
