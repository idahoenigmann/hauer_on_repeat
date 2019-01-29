#include <utility>

//
// Created by ida on 03.11.18.
//

#include <limits.h>
#include <unistd.h>

#include "files.h"


std::string getexepath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return std::string(result, static_cast<unsigned long>((count > 0) ? count : 0));
}

void File::write(std::string input) {
    std::ofstream file;

    std::string temp = filename + ".ly";
    file.open(temp);

    file << input;

    file.close();
}

void File::create_midi_pdf() {
    std::string temp = "lilypond " + filename + ".ly";

    system(temp.c_str());

    temp = "timidity " + filename + ".midi -Ow -o " + filename + ".mp3";

    system(temp.c_str());

    temp = "cvlc " + filename + ".mp3 &";   //cvlc does not display a interface, opposed to vlc

    system(temp.c_str());

    std::string path = getexepath();
    path.erase(path.rfind('/'));


    std::string uploader_str = "bash ../Uploader/complete.sh ../build/" + filename + ".mp3 ../build/" + filename + ".pdf &";
    system(uploader_str.c_str());

    //std::string uploader_str = "bash ../Uploader/complete.sh " + filename + ".mp3 " + filename + ".pdf &";
    //system(uploader_str.c_str());


    std::string str = "firefox file://" + path + "/" + filename + ".pdf";
    system(str.c_str());
}


File::File(std::string filename) {
    this->filename = std::move(filename);
}
