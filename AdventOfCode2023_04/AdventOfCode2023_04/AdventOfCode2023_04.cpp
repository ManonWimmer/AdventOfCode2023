#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <math.h>
#include <map>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 4 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
The Elf leads you over to the pile of colorful cards. There, you discover dozens of scratchcards, all with their
opaque covering already scratched off. Picking one up, it looks like each card has two lists of numbers separated
by a vertical bar (|): a list of winning numbers and then a list of numbers you have. You organize the information
into a table (your puzzle input).

As far as the Elf has been able to figure out, you have to figure out which of the numbers you have appear in the
list of winning numbers. The first match makes the card worth one point and each match after the first doubles the
point value of that card.

Take a seat in the large pile of colorful cards. How many points are they worth in total?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
There's no such thing as "points". Instead, scratchcards only cause you to win more scratchcards equal to the
number of winning numbers you have.

Specifically, you win copies of the scratchcards below the winning card equal to the number of matches. So, if card
10 were to have 5 matching numbers, you would win one copy each of cards 11, 12, 13, 14, and 15.

Process all of the original and copied scratchcards until no more scratchcards are won. Including the original set
of scratchcards, how many total scratchcards do you end up with?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 4 ----- ----- ----- ----- -----
*/

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

    std::map<int, int> gameCards;
    int gameNbr = 1;
    int sum = 0;

    int i = 1;
    for (std::string& str : input) 
    {
        gameCards[i] = 1;
        i++;
    }

    for (std::string& str : input)
    {
        // Substr from str "Game X: "
        if (gameNbr < 10) // Game 1 -> 9
        {
            str = str.substr(8);
        }
        else if (gameNbr >= 10 and gameNbr < 100) // Game 10 -> 99
        {
            str = str.substr(9);
        }
        else // Game 100
        {
            str = str.substr(10);
        }

        char separator = '|';
        int j = 0;

        std::string s;
        std::vector<std::string> tempListForGame; // x x x x x, x x x x x

        // Separate each line at '|'
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

        s.clear();
        separator = ' ';
        j = 0;

        std::vector<std::string> tempListWithNumbersWinning; // x x x x x
        std::vector<std::string> tempListWithNumbersPlayer; // x x x x x

        // Separate each line at ' '
        for (char c : tempListForGame[0]) {
            if (c != separator) {
                s += c;
            }
            else {
                //std::cout << s << std::endl; // Each ; split
                tempListWithNumbersWinning.push_back(s);
                s.clear();
            }
        }
        tempListWithNumbersWinning.push_back(s);

        //tempListForGame[1] = tempListForGame[1].substr(1);

        // Separate each line at ' '
        for (char c : tempListForGame[1]) {
            if (c != separator) {
                s += c;
            }
            else {
                //std::cout << s << std::endl; // Each ; split
                tempListWithNumbersPlayer.push_back(s);
                s.clear();
            }
        }

        tempListWithNumbersPlayer.push_back(s);

        std::cout << "Game " << gameNbr << std::endl;

        std::vector<int> listIntNumbersWinning;
        std::vector<int> listIntNumbersPlayer;

        std::cout << "Winning numbers : " << std::endl;
        for (std::string number : tempListWithNumbersWinning) 
        {
            if (!number.empty()) {
                try {
                    int intValue = std::stoi(number);
                    std::cout << intValue << ", ";
                    listIntNumbersWinning.push_back(intValue);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
                }
            }
        }

        std::cout << std::endl;

        std::cout << "Player numbers : " << std::endl;
        for (std::string number : tempListWithNumbersPlayer) {
            if (!number.empty()) 
            {
                try {
                    int intValue = std::stoi(number);
                    std::cout << intValue << ", ";
                    listIntNumbersPlayer.push_back(intValue);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
                }
            }
        }

        std::cout << std::endl;

        std::vector<int> playerWinningNumbers;

        for (const auto& element : listIntNumbersPlayer) {
            // Check if the element is in list2
            if (std::find(listIntNumbersWinning.begin(), listIntNumbersWinning.end(), element) != listIntNumbersWinning.end()) {
                std::cout << element << " is present in winning numbers." << std::endl;
                playerWinningNumbers.push_back(element);
            }
            else {
                //std::cout << element << " is not present in list2." << std::endl;
            }
        }
        
        // Part 1
        /*
        if (playerWinningNumbers.size() > 0) 
        {
            std::cout << "sum += " << pow(2, playerWinningNumbers.size() - 1) << std::endl;
            sum += pow(2, playerWinningNumbers.size() - 1);
        }
        */

        // Part 2 :
        std::cout << "game cards nbr : " << gameCards[gameNbr] << std::endl;

        for (int i = 0; i < gameCards[gameNbr]; i++) 
        {
            if (playerWinningNumbers.size() > 0)
            {
                //std::cout << playerWinningNumbers.size() << std::endl;
                for (int i = gameNbr + 1; i < gameNbr + 1 + playerWinningNumbers.size(); i++)
                {
                    //std::cout << "game " << i << " += 1" << std::endl;
                    gameCards[i] += 1;
                }
            }
        }
       

        std::cout << std::endl;

        std::cout << "-----" << std::endl;

        gameNbr++;
    }

    // Part 2
    for (const auto& pair : gameCards) 
    {
        sum += pair.second;
    }

    std::cout << "sum : " << sum << std::endl;
}

