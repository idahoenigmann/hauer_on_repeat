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

void File::write(std::string input, std::string filetype) {
    std::ofstream file;

    std::string temp = filename + "." + filetype;
    file.open(temp);

    file << input;

    file.close();
}

void File::create_midi_pdf(bool upload) {
    std::string temp = "lilypond " + filename + ".ly";

    system(temp.c_str());

    temp = "timidity " + filename + ".midi -Ow -o " + filename + ".mp3";

    system(temp.c_str());

    if (upload) {
        //temp = "aplay " + filename + ".mp3 &";   //moved to javascript
        //system(temp.c_str());

        std::string path = getexepath();
        path.erase(path.rfind('/'));

        /*std::string uploader_str =
                "bash ../Uploader/uploadToServer/uploadToServer.sh &";
        system(uploader_str.c_str());*/

        std::string str = "firefox file://" + path + "/../web/nr1.html";
        system(str.c_str());
    }
}


File::File(std::string filename) {
    this->filename = std::move(filename);
}
