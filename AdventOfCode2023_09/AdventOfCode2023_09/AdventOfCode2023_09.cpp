#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 9 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
To best protect the oasis, your environmental report should include a prediction of the next value in each history.
To do this, start by making a new sequence from the difference at each step of your history. If that sequence is not
all zeroes, repeat this process, using the sequence you just generated as the input sequence. Once all of the value
in your latest sequence are zeroes, you can extrapolate what the next value of the original history should be.

Analyze your OASIS report and extrapolate the next value for each history. What is the sum of these extrapolated
values?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
Of course, it would be nice to have even more history included in your report. Surely it's safe to just extrapolate
backwards as well, right?

For each history, repeat the process of finding differences until the sequence of differences is entirely zero.
Then, rather than adding a zero to the end and filling in the next values of each previous sequence, you should
instead add a zero to the beginning of your sequence of zeroes, then fill in new first values for each previous
sequence.

Analyze your OASIS report again, this time extrapolating the previous value for each history. What is the sum of
these extrapolated values?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 9 ----- ----- ----- ----- -----
*/

int main()
{
    std::vector<std::string> input;
    std::string line;
    std::ifstream myfile("input.txt");
    if (myfile.is_open())
    {

        while (getline(myfile, line)) 
        {
            //std::cout << line << std::endl;
            input.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

    std::cout << "-----" << std::endl;
    std::cout << "Sensors: " << std::endl;

    char separator = ' ';
    std::string tempStr;
    std::vector<int> tempVector;
    std::vector<std::vector<int>> sensors;

    for (std::string str : input) {
        for (char c : str) {
            if (c != separator) {
                tempStr += c;
            }
            else {
                if (!tempStr.empty()) {
                    try {
                        int intValue = std::stoi(tempStr);
                        tempVector.push_back(intValue);
                        std::cout << intValue << ", ";
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
                    }
                    tempStr.clear();
                }
            }
        }
        if (!tempStr.empty()) {
            try {
                int intValue = std::stoi(tempStr);
                tempVector.push_back(intValue);
                std::cout << intValue << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
            }
        }
 
        sensors.push_back(tempVector);
        tempVector.clear();
        tempStr.clear();
    }
    std::cout << "-----" << std::endl;

    std::vector<std::vector<int>> sensorHistory;
    int sumExtrapolatedValues = 0;
    int sumExtrapolatedValues2 = 0;

    for (std::vector<int> sensor : sensors) 
    {
        sensorHistory.push_back(sensor);
        bool ended = false;
        int currentExtrapolatedValue = 0;

        while (!ended) {
            std::vector<int> vectorDifferences;
            for (int i = 0; i < sensorHistory[sensorHistory.size() - 1].size() - 1; i++) {
                int difference = sensorHistory[sensorHistory.size() - 1][i + 1] - sensorHistory[sensorHistory.size() - 1][i];
                std::cout << difference << ", ";
                vectorDifferences.push_back(difference);
            }

            sensorHistory.push_back(vectorDifferences);

            // check ended
            bool tempBool = true;
            for (int value : vectorDifferences) {
                if (value != 0) {
                    tempBool = false;
                }
            }
            ended = tempBool;

            std::cout << std::endl;

        }

        // part 1:
        int newValue = 0;

        for (auto it = sensorHistory.rbegin(); it != sensorHistory.rend(); ++it) {
            if (it != sensorHistory.rbegin()) {  // skip the first iteration 0, 0, 0...
                //std::cout << "current last: " << (*it)[(*it).size() - 1] << std::endl;
                newValue += (*it)[(*it).size() - 1];
                //std::cout << "new value: " << newValue << std::endl;
            }
        }
        std::cout << "sum 1 += " << newValue << std::endl;
        sumExtrapolatedValues += newValue;

        // part 2:
        int lastDifference2 = 0;
        std::vector<int> vectorDifferences2;

        for (auto it = sensorHistory.rbegin(); it != sensorHistory.rend(); ++it) {
            if (it != sensorHistory.rbegin()) {  // skip the first iteration 0, 0, 0...
                //std::cout << "current last: " << (*it)[0] << std::endl;
                int difference2 = (*it)[0] - lastDifference2;
                lastDifference2 = difference2;
                //std::cout << "new difference: " << difference2 << std::endl;
                vectorDifferences2.push_back(difference2);
            }
        }
        std::cout << "sum 2 += " << vectorDifferences2[vectorDifferences2.size() - 1] << std::endl;
        sumExtrapolatedValues2 += vectorDifferences2[vectorDifferences2.size() - 1];

        std::cout << "-----" << std::endl;
        sensorHistory.clear();
    }

    std::cout << "sum extrapolated values, part 1: " << sumExtrapolatedValues << std::endl;
    std::cout << "sum extrapolated values, part 2: " << sumExtrapolatedValues2 << std::endl;
}

