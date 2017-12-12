/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 21.12.2017
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#include <iostream> // cout
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <string> // string, stoi

using namespace std;

int main(int argc, const char * argv[]) {
    // Input file name argument must be passed with run command
    if (argc != 2) {
        cout << endl << "Missing arguments to proceed." << endl << endl;
        return 0;
    }
    
    // Get input file name and open the file
    string input_filename(argv[1]);
    ifstream inputFile(input_filename, ifstream::in); // Read
    
    if (!inputFile.is_open()) { // Error while openning the file
        cout << endl << "Error opening input file." << endl << endl;
        return 0;
    }
    
    string line;
    while(!inputFile.eof()) {
        getline(inputFile, line); // Read the line
        
        // If line is empty, no need to take action
        if(line.empty()) break;
        
        // Create stringstream to parse with '\t'
        stringstream linestream(line);
        
        string read[3];
    
        // Parse the line
        getline(linestream, read[0], '\t');
        getline(linestream, read[1], '\t');
        linestream >> read[2];
    }
    
    // Close the input file since it is no longer needed
    inputFile.close();
    return 0;
}
