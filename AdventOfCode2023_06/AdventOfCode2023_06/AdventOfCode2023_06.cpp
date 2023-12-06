#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility> // for std::pair

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 6 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
As part of signing up, you get a sheet of paper (your puzzle input) that lists the time allowed for each race and also the best distance ever recorded
in that race. To guarantee you win the grand prize, you need to make sure you go farther in each race than the current record holder.

Boats move faster if their button was held longer, but time spent holding the button counts against the total race time. You can only hold the button at
the start of the race, and boats don't move until the button is released.

Your toy boat has a starting speed of zero millimeters per millisecond. For each whole millisecond you spend at the beginning of the race holding down
the button, the boat's speed increases by one millimeter per millisecond.

Determine the number of ways you could beat the record in each race. What do you get if you multiply these numbers together?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
As the race is about to start, you realize the piece of paper with race times and record distances you got earlier actually just has very bad kerning.
There's really only one race - ignore the spaces between the numbers on each line.

How many ways can you beat the record in this one much longer race?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 6 ----- ----- ----- ----- -----
*/

int main()
{
    std::vector<std::string> input;
    std::string line;
    std::ifstream myfile("input.txt");
    if (myfile.is_open())
    {

        while (getline(myfile, line)) {

            //std::cout << line << std::endl;
            input.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

    std::cout << "Part 1:" << std::endl;

    std::string strTime = input[0].substr(11);
    //std::cout << strTime << std::endl;

    std::string strDistance = input[1].substr(11);
    //std::cout << strDistance << std::endl;

    char separator = ' ';

    // Get list int time
    std::string tempStr;
    std::vector<int> tempListTime; 

    for (char c : strTime) {
        if (c != separator) {
            tempStr += c;
        }
        else {
            if (!tempStr.empty()) {
                try {
                    int intValue = std::stoi(tempStr);
                    //std::cout << intValue << ", ";
                    tempListTime.push_back(intValue);
                    tempStr.clear();
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
                }
            }
        }
    }
    
    if (!tempStr.empty()) {
        try {
            int intValue = std::stoi(tempStr);
            //std::cout << tempStr << std::endl;
            tempListTime.push_back(intValue);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
        }
    }

    tempStr.clear();

    // Get list int distance
    std::vector<int> tempListDistance;

    for (char c : strDistance) {
        if (c != separator) {
            tempStr += c;
        }
        else {
            if (!tempStr.empty()) {
                try {
                    int intValue = std::stoi(tempStr);
                    //std::cout << intValue << ", ";
                    tempListDistance.push_back(intValue);
                    tempStr.clear();
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
                }
            }
            
        }
    }
    if (!tempStr.empty()) {
        try {
            int intValue = std::stoi(tempStr);
            //std::cout << tempStr << std::endl;
            tempListDistance.push_back(intValue);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
        }
    }

    //std::map<int, int> timeDistance; // Can't use map when there can be two same keys !!!
    std::vector<std::pair<int, int>> timeDistance;

    for (int i = 0; i < tempListTime.size(); i++) {
        //std::cout << tempListTime[i] << " -> " << tempListDistance[i];
        std::pair<int, int> newPair(tempListTime[i], tempListDistance[i]);
        timeDistance.push_back(newPair);
    }

    std::vector<int> tempCurrentNewRecords;
    std::vector<int> allNbrRecords;

    for (const auto& pair : timeDistance) 
    {
        std::cout << "time : " << pair.first << ", distance : " << pair.second << std::endl;
        for (int i = 0; i < pair.first; i++) {
            int resultDistance = i * (pair.first - i);
            //std::cout << resultDistance << std::endl;
            if (resultDistance > pair.second) {
                //std::cout << i << " : " << resultDistance << " > " << pair.second << std::endl;
                tempCurrentNewRecords.push_back(pair.first);
            }
        }

        allNbrRecords.push_back(tempCurrentNewRecords.size());
        tempCurrentNewRecords.clear();
    }

    int multNbrRecords = 1;

    for (int nbrRecord : allNbrRecords) {
        //std::cout << nbrRecord << std::endl;
        multNbrRecords *= nbrRecord;    
    }
    std::cout << "sum all nbr records: " << multNbrRecords << std::endl;

    std::cout << std::endl;
    std::cout << "Part 2:" << std::endl;

    tempStr.clear();
    for (int value : tempListTime) {
        tempStr += std::to_string(value);
    }

    double part2time = std::stod(tempStr);
    std::cout << "time: " << part2time << ", ";

    tempStr.clear();
    for (int value : tempListDistance) {
        tempStr += std::to_string(value);
    }

    double part2distance = std::stod(tempStr);
    std::cout << "distance: " << part2distance << std::endl;

    int nbrWaysToWin = 0;

    for (int i = 0; i < part2time; i++) {
        double resultDistance = i * (part2time - i);
        //std::cout << resultDistance << std::endl;
        if (resultDistance > part2distance) {
            nbrWaysToWin++;
        }
    }

    std::cout << "nbr ways to win: " << nbrWaysToWin << std::endl;
}


