//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_FILES_H
#define HAUER_ON_REPEAT_FILES_H

#include <string>
#include <iostream>
#include <fstream>

std::string getexepath();

//!  A class for file operations. 
/*!
  With this class you can write into Files 
  and create midi Files from .ly (using other programs).
*/
class File {
public:

    //! Writes content into the File
    /*! @param input content which is to be written into the File
    */
    void write(std::string input, std::string filetype);

    /*! @param filename name of the file which is to be used
    */
    explicit File(std::string filename);

    //! Creates a .midi and .pdf file from a lilypond file (.ly) using lilypond
    /*! @param None
    */
    void create_midi_pdf(bool upload=true);
private:
    std::string filename;
};

#endif //HAUER_ON_REPEAT_FILES_H
