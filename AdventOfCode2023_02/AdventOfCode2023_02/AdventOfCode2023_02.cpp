#include <iostream>
#include <string>
#include <list>
#include <fstream>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 2 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
To get information, once a bag has been loaded with cubes, the Elf will reach into the bag, grab a handful of random cubes, show them to you, and then put
them back in the bag. He'll do this a few times per game.

You play several games and record the information from each game (your puzzle input). Each game is listed with its ID number (like the 11 in Game 11: ...)
followed by a semicolon-separated list of subsets of cubes that were revealed from the bag (like 3 red, 5 green, 4 blue).

Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the
IDs of those games?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together. The power of the minimum set of cubes in game 1 is
48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 2 ----- ----- ----- ----- -----

*/

struct gameMaxStats
{
    int gameNbr = 0;
    int redMaxCount = 0;
    int blueMaxCount = 0;
    int greenMaxCount = 0;
};

int main() {
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

    int gameNbr = 1;
    std::list<gameMaxStats> gamesStats;
    gameMaxStats stats;
    stats.redMaxCount = 12;
    stats.blueMaxCount = 14;
    stats.greenMaxCount = 13;

    for (std::string& str : input) 
    {
        gameMaxStats currentGameStats;
        

        // Substr from str "Game X: "
        if (gameNbr < 10) // Game 1 -> 9
        {
            str = str.substr(7);
        }
        else if (gameNbr >= 10 and gameNbr < 100) // Game 10 -> 99
        {
            str = str.substr(8);
        }
        else // Game 100
        {
            str = str.substr(9);
        }
        
        char separator = ';';
        int j = 0;

        std::string s;
        std::list<std::string> tempListForGame;

        // Separate each line at ';'
        for (char c : str) {
            if (c != separator) {
                s += c;
            }
            else {
                //std::cout << s << std::endl; // Each ; split
                tempListForGame.push_back(s);
                s.clear();
            }
        }
        tempListForGame.push_back(s);

        for (std::string str2 : tempListForGame) {
            //std::cout << str2 << std::endl;

            separator = ',';
            j = 0;

            std::string s;
            std::list<std::string> tempListForGame2;

            // Separate each line at ';'
            for (char c : str2) {
                if (c != separator) {
                    s += c;
                }
                else {
                    //std::cout << s << std::endl; // Each ; split
                    tempListForGame2.push_back(s);
                    s.clear();
                }
            }
            tempListForGame2.push_back(s);

            // Blue :
            for (std::string str3 : tempListForGame2) 
            {
                std::cout << str3 << std::endl;
                size_t foundBlue = str3.find("blue");
                if (foundBlue != std::string::npos) {
                    bool ended = false;
                    std::string tempStr2 = "";
                    for (char const& c : str3) 
                    {
                        if (std::isdigit(c)) // An int
                        {
                            if (currentGameStats.blueMaxCount == 0) 
                            {
                                currentGameStats.blueMaxCount = c - '0';
                                std::string tempStr(1, c);
                                tempStr2 = tempStr;
                                ended = true;
                            }
                            else
                            {
                                if (ended)
                                {
                                    // Add digits (ex : 20)
                                    std::string strFirst = tempStr2;
                                    std::string strLast = std::string(1, c);

                                    std::string strTwoDigits = strFirst + strLast;

                                    // Add to sum
                                    if (std::stoi(strTwoDigits) > currentGameStats.blueMaxCount) 
                                    {
                                        currentGameStats.blueMaxCount = std::stoi(strTwoDigits);
                                    }
                                }
                                else {
                                    if (c - '0' > currentGameStats.blueMaxCount) {
                                        currentGameStats.blueMaxCount = c - '0';
                                    }
                                    ended = true;
                                    std::string tempStr(1, c);
                                    tempStr2 = tempStr;
                                }
                            } 
                        }          
                    }
                }

                // Red : 
                size_t foundRed = str3.find("red");
                if (foundRed != std::string::npos) {
                    bool ended = false;
                    std::string tempStr2 = "";
                    for (char const& c : str3)
                    {
                        if (std::isdigit(c)) // An int
                        {
                            if (currentGameStats.redMaxCount == 0)
                            {
                                currentGameStats.redMaxCount = c - '0';
                                std::string tempStr(1, c);
                                tempStr2 = tempStr;
                                ended = true;
                            }
                            else
                            {
                                if (ended)
                                {
                                    // Add digits (ex : 20)
                                    std::string strFirst = tempStr2;
                                    std::string strLast = std::string(1, c);

                                    std::string strTwoDigits = strFirst + strLast;

                                    // Add to sum
                                    if (std::stoi(strTwoDigits) > currentGameStats.redMaxCount)
                                    {
                                        currentGameStats.redMaxCount = std::stoi(strTwoDigits);
                                    }
                                }
                                else {
                                    if (c - '0' > currentGameStats.redMaxCount) {
                                        currentGameStats.redMaxCount = c - '0';
                                    }
                                    ended = true;
                                    std::string tempStr(1, c);
                                    tempStr2 = tempStr;
                                }
                            }
                        }
                    }
                }

                // Green :
                size_t foundGreen = str3.find("green");
                if (foundGreen != std::string::npos) {
                    bool ended = false;
                    std::string tempStr2 = "";
                    for (char const& c : str3)
                    {
                        if (std::isdigit(c)) // An int
                        {
                            if (currentGameStats.greenMaxCount == 0)
                            {
                                currentGameStats.greenMaxCount = c - '0';
                                std::string tempStr(1, c);
                                tempStr2 = tempStr;
                                ended = true;
                            }
                            else
                            {
                                if (ended)
                                {
                                    std::string strFirst = tempStr2;
                                    std::string strLast = std::string(1, c);

                                    std::string strTwoDigits = strFirst + strLast;

                                    // Add to sum
                                    if (std::stoi(strTwoDigits) > currentGameStats.greenMaxCount)
                                    {
                                        currentGameStats.greenMaxCount = std::stoi(strTwoDigits);
                                    }
                                }
                                else {
                                    if (c - '0' > currentGameStats.greenMaxCount) {
                                        currentGameStats.greenMaxCount = c - '0';
                                    }
                                    ended = true;
                                    std::string tempStr(1, c);
                                    tempStr2 = tempStr;
                                }
                            }
                        }
                    }
                }
            }
        }

        currentGameStats.gameNbr = gameNbr;

        gamesStats.push_back(currentGameStats);
        std::cout << "Game " << currentGameStats.gameNbr << " stats :" << std::endl;
        std::cout << "Max Blue Count : " << currentGameStats.blueMaxCount << std::endl;
        std::cout << "Max Red Count : " << currentGameStats.redMaxCount << std::endl;
        std::cout << "Max Green Count : " << currentGameStats.greenMaxCount << std::endl;
        std::cout << "-----" << std::endl;
        gameNbr += 1;
    }

    int sumIds = 0;

    for (gameMaxStats gameStats : gamesStats) {
        // Part 1:
        /* 
        if (gameStats.blueMaxCount <= stats.blueMaxCount && gameStats.redMaxCount <= stats.redMaxCount && gameStats.greenMaxCount <= stats.greenMaxCount)
        {
            std::cout << "Game " << gameStats.gameNbr << " possible!" << std::endl;
            sumIds += gameStats.gameNbr;
        }*/

        // Part 2:
        sumIds += gameStats.redMaxCount * gameStats.blueMaxCount * gameStats.greenMaxCount;
    }

    std::cout << "Sum Ids : " << sumIds << std::endl;

    return 0;
}
