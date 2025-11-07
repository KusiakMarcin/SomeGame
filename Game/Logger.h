#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {


private:
    ofstream logFile;

    string levelToString(LogLevel level);


public:

    Logger(const string& filename);



    // Destructor: Closes the log file
    ~Logger() { logFile.close(); }

    // Logs a message with a given log level
    void log(LogLevel level, const string& message);
};