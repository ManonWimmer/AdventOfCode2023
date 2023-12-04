#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 3 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really
understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not
count as a symbol.)

What is the sum of all of the part numbers in the engine schematic?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
The missing part wasn't the only issue - one of the gears in the engine is wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its
gear ratio is the result of multiplying those two numbers together.

What is the sum of all of the gear ratios in your engine schematic?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 3 ----- ----- ----- ----- -----
*/

std::string CheckLeft(int checkingI, int checkingJ, std::vector<std::string>& input)
{
    bool over = false;
    std::string tempStr = "";

    while (!over)
    {
        //std::cout << "while " << std::endl;
        char c;

        if (checkingJ - 1 >= 0)
        {
            c = input[checkingI][checkingJ - 1];
            //std::cout << "left " << c << ", ";
            if (isdigit(c))
            {
                tempStr = c + tempStr;

                input[checkingI][checkingJ - 1] = 'X';

                if (checkingJ - 1 >= 0) {
                    checkingJ--;
                }
                else {
                    over = true;
                }
            }
            else {
                over = true;
            }
        }
        else {
            over = true;
        }
    }

    return tempStr;
}

std::string CheckRight(int checkingI, int checkingJ, std::vector<std::string>& input)
{
    bool over = false;
    std::string tempStr = "";

    while (!over)
    {
        //std::cout << "while " << std::endl;
        char c;

        if (checkingJ + 1 < input[checkingI].size())
        {
            c = input[checkingI][checkingJ + 1];
            //std::cout << "right " << c << ", ";
            if (isdigit(c))
            {
                tempStr = tempStr + c;
                
                input[checkingI][checkingJ + 1] = 'X';

                if (checkingJ + 1 < input[checkingI].size()) {
                    checkingJ++;
                }
                else {
                    over = true;
                }
            }
            else {
                over = true;
            }
        }
        else {
            over = true;
        }
        //std::cout << tempStr << std::endl;
    }

    return tempStr;
}

std::string CheckLeftAndRight(int checkingI, int checkingJ, std::vector<std::string>& input) 
{
    std::string tempStr = "";
    //std::cout << input[checkingI][checkingJ] << std::endl;
    if (checkingI >= 0 && checkingJ < input[checkingI].size()) 
    {
        if (isdigit(input[checkingI][checkingJ]))
        {
            //std::cout << "left : " << CheckLeft(checkingI, checkingJ, input) << " middle : " << input[checkingI][checkingJ] << " right : " << CheckRight(checkingI, checkingJ, input) << std::endl;

            tempStr = input[checkingI][checkingJ];

            std::string left = CheckLeft(checkingI, checkingJ, input);
            if (!left.empty()) {
                tempStr = left + tempStr;
            }

            std::string right = CheckRight(checkingI, checkingJ, input);
            if (!right.empty()) {
                tempStr = tempStr + right;
            }

            input[checkingI][checkingJ] = 'X';
        }
    }
    
    //std::cout << "Check Left and right result : " << tempStr << std::endl;
    return tempStr;
}

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

    std::vector<char> symbols = { '*', '$', '#', '-', '+', '/', '%', '=', '@', '&'};
    int sum = 0;
    std::list<int> numbersToAdd;

    for (int i = 0; i < input.size(); i++) 
    {
        std::string line = input[i];
        for (int j=0; j <input[i].size(); j++) 
           {
            numbersToAdd.clear();

            //std::cout << "i " << i << " j " << j << std::endl;
            char targetChar = input[i][j];
            //std::cout << "target char " << targetChar << std::endl;

            auto it = std::find(symbols.begin(), symbols.end(), targetChar);

            if (it != symbols.end()) 
            {
                std::cout << "Character " << targetChar << " found in the list." << std::endl;

                //std::cout << "Check left " << std::endl;
                std::string resultLeft = CheckLeft(i, j, input);

                if (!resultLeft.empty()) 
                {
                    std::cout << "Number at left of symbol : " << resultLeft << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultLeft)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultLeft));
                    }
                }

                //std::cout << "Check right " << std::endl;
                std::string resultRight = CheckRight(i, j, input);

                if (!resultRight.empty())
                {
                    std::cout << "Number at right of symbol : " << resultRight << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultRight)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultRight));
                    }
                }

                //std::cout << "Check top " << std::endl;
                std::string resultTop = CheckLeftAndRight(i - 1, j, input);

                if (!resultTop.empty())
                {
                    std::cout << "Number at top of symbol : " << resultTop << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultTop)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultTop));
                    }
                }

                //std::cout << "Check bottom " << std::endl;
                std::string resultBottom = CheckLeftAndRight(i + 1, j, input);

                if (!resultBottom.empty())
                {
                    std::cout << "Number at bottom of symbol : " << resultBottom << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultBottom)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultBottom));
                    }
                }

                //std::cout << "Check top left " << std::endl;
                std::string resultTopLeft = CheckLeftAndRight(i - 1, j - 1, input);

                if (!resultTopLeft.empty())
                {
                    std::cout << "Number at top left of symbol : " << resultTopLeft << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultTopLeft)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultTopLeft));
                    }
                }

                //std::cout << "Check top right " << std::endl;
                std::string resultTopRight = CheckLeftAndRight(i - 1, j + 1, input);

                if (!resultTopRight.empty())
                {
                    std::cout << "Number at top right of symbol : " << resultTopRight << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultTopRight)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultTopRight));
                    }
                }

                //std::cout << "Check bottom left " << std::endl;
                std::string resultBottomLeft = CheckLeftAndRight(i + 1, j - 1, input);

                if (!resultBottomLeft.empty())
                {
                    std::cout << "Number at bottom left of symbol : " << resultBottomLeft << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultBottomLeft)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultBottomLeft));
                    }
                }

                //std::cout << "Check bottom right " << std::endl;
                std::string resultBottomRight = CheckLeftAndRight(i + 1, j + 1, input);

                if (!resultBottomRight.empty())
                {
                    std::cout << "Number at bottom left of symbol : " << resultBottomRight << std::endl;
                    if (std::find(numbersToAdd.begin(), numbersToAdd.end(), std::stoi(resultBottomRight)) == numbersToAdd.end()) // Vector doesn't already contains the number
                    {
                        numbersToAdd.push_back(std::stoi(resultBottomRight));
                    }
                }

                
            }
            else {
                //std::cout << "Character not found in the list." << std::endl;
            }

            // Part 2:
            if (numbersToAdd.size() == 2)
            {
                sum += numbersToAdd.front() * numbersToAdd.back();
            }
            /* // Part 1:
            for (int i = 0; i < taille; ++i) 
            {
                sum += maListe[i];
            }
            */
        }
        std::cout << "-----" << std::endl;
    }

    // Final list with X
    for (int i = 0; i < input.size(); i++) {
        std::string line = input[i];
        std::cout << line << std::endl;
    }

    std::cout << "Sum : " << sum << std::endl;


    return 0;
}
