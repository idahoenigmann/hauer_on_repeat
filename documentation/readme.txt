The software of this exhibit consists of multiple different programs, written in different languages and by different people (sorry).

## C++

The caclulation of the Hauer Zwölftonspiel is done by a C++ program. Is source code can be found in hauer_on_repeat/src/*.cpp
If you want to test the exhibit on your local machine go into main.cpp and change the following lines by commenting / uncommenting them:

//input using buttons:
input(numbers);

//use terminal to input numbers:
{
    time_t time_lpress{};
    time(&time_lpress);
    ... //continues until the curly bracet closes
}

main.cpp is the program, which starts after the raspi was booted. It interacts with the buttons (see GPIOClass.cpp), the sqlite database (in main.cpp), the twitter account (in files.cpp), lilypond (in files.cpp) and the html frontend.

For more details on the implementation have a look in the doxygen generated documentation (in hauer_on_repeat/documentation).

## HTML, CSS and JavaScript

Everything the user sees is written in html, css and javascript and located in the hauer_on_repeat/web directory. After booting nr0.html is openend in firefox. The order in which the pages appear is: nr0.html, nr01.html, nr02.html, nr1.html, nr2.html, nr3.html and nr4.html.

All html pages starting with 0 are displayed before and while the numbers are entered, the others while the music is being played.

In all pages the mouse pointer is made invisible. Press F11 to exit the fullscreen mode the window is started in.

Firefox is also used to play the music. To allow the exhibit to fully work some security settings had to be disabled (these can be found when entering about:config as the url in Firefox).

## Shell script and Java

The Uploader (to Twitter) can be found in hauer_on_repeat/Uploader. The server currently needed (raspi is too slow when processing the video) is run by Manuel Kubu (actually his father, i believe).

## SqliteDB

The sqliteDB is simple it stores datetime and numbers-entered pairs in a table called "saves". E.g. 2020-02-12 14:17:21|0,1,2,3,4,5,6,7,8,9,10,11

## Java

The database folder and its contents are not used anymore. They once added a new line to the sqlite3 database. This has been simplified and can now be found in main.cpp.

## Project Proposal

The project proposal for the school year 2019/20 can be found in the directory hauer_on_repeat/project_proposal.

## More documentation

Documentation on how twelve tone music works and why this exhibit was constructed can be found in the markdown files (*.md) in hauer_on_repeat.
