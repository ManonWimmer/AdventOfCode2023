#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 1 ----- ----- ----- ----- ----- 
----- ----- PART 1 ----- -----
The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value
that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last
digit (in that order) to form a single two-digit number.
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four
five, six, seven, eight, and nine also count as valid "digits".
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 1 ----- ----- ----- ----- -----
*/

std::string findFirstMatchingWord(const std::string& input, const std::unordered_map<std::string, int>& wordList)
{
    for (const auto& pair : wordList) {
        if (input.find(pair.first) != std::string::npos) {
            return pair.first; // Found word
        }
    }

    return "";
}

std::string findLastMatchingWord(const std::string& input, const std::unordered_map<std::string, int>& wordList)
{
    std::string temp = "";
    for (const auto& pair : wordList) {
        if (input.find(pair.first) != std::string::npos) {
            temp = pair.first; // Found word
        }
    }

    return temp;
}

int main()
{
    std::list<std::string> input;
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

    int sum = 0;
    int tempFirst = -1;
    int tempLast = -1;
    std::string tempStr = "";

    std::unordered_map<std::string, int> wordToNum = { {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9} };

    for (const std::string& line : input) {
        tempFirst = -1;
        tempLast = -1;
        tempStr = "";


        // Order left -> right
        for (char const& c : line) {
            if (tempFirst == -1)
            {
                if (std::isdigit(c)) // An int
                {
                    std::cout << "first digit " << c << std::endl;
                    tempFirst = c - '0'; // Char to int
                    tempStr = "";
                    break;
                }
                // Part 2
                else // A letter
                {
                    tempStr += c;
                    // find word
                    std::string firstMatchingWord = findFirstMatchingWord(tempStr, wordToNum);

                    if (!firstMatchingWord.empty()) {
                        int associatedValue = wordToNum[firstMatchingWord];
                        std::cout << "first matching word " << firstMatchingWord << " associated value " << associatedValue << std::endl;
                        tempFirst = associatedValue;
                        tempStr = "";
                        break;
                    }
                }
            }
        }

        // Order right -> left
        for (auto rit = line.rbegin(); rit != line.rend(); ++rit) {
            char const& c = *rit;
            if (tempLast == -1) {
                if (std::isdigit(c)) {
                    std::cout << "last digit " << c << std::endl;
                    tempLast = c - '0'; // Char to int
                    tempStr = "";
                    break;
                }
                // Part 2
                else {
                    //tempStr.std::string::insert(0, std::to_string(c));
                    tempStr.insert(tempStr.begin(), c);
                    // find word
                    std::string lastMatchingWord = findLastMatchingWord(tempStr, wordToNum);

                    if (!lastMatchingWord.empty()) {
                        int associatedValue = wordToNum[lastMatchingWord];
                        std::cout << "last matching word " << lastMatchingWord << " associated value " << associatedValue << std::endl;
                        tempLast = associatedValue;
                        tempStr = "";
                        break;
                    }
                }
            }

        }

        // Add two digits
        std::string strFirst = std::to_string(tempFirst);
        std::string strLast = std::to_string(tempLast);

        std::string strTwoDigits = strFirst + strLast;
        std::cout << "sum += " << strTwoDigits << std::endl;

        // Add to sum
        sum += std::stoi(strTwoDigits);
        std::cout << "sum = " << sum << std::endl;
        std::cout << "----- ----- ----- ----- -----" << std::endl;
    }

    return 0;
}

