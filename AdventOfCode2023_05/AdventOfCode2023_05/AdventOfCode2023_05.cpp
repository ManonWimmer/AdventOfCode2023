#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 4 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
The almanac (your puzzle input) lists all of the seeds that need to be planted. It also lists what type of soil to use with each kind of seed, what type
of fertilizer to use with each kind of soil, what type of water to use with each kind of fertilizer, and so on. Every type of seed, soil, fertilizer and
so on is identified with a number, but numbers are reused by each category - that is, soil 123 and fertilizer 123 aren't necessarily related to each
other.

The rest of the almanac contains a list of maps which describe how to convert numbers from a source category into numbers in a destination category.
That is, the section that starts with seed-to-soil map: describes how to convert a seed number (the source) to a soil number (the destination). This
lets the gardener and his team know which soil to use with which seeds, which water to use with which fertilizer, and so on.

Rather than list every source number and its corresponding destination number one by one, the maps describe entire ranges of numbers that can be
converted. Each line within a map contains three numbers: the destination range start, the source range start, and the range length.

The gardener and his team want to get started as soon as possible, so they'd like to know the closest location that needs a seed. Using these maps, find
the lowest location number that corresponds to any of the initial seeds. To do this, you'll need to convert each seed number through other categories 
until you can find its corresponding location number.

What is the lowest location number that corresponds to any of the initial seed numbers?
=> ONLY WORKING WITH EXEMPLE, NOT WITH FULL INPUT...
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
???
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 4 ----- ----- ----- ----- -----
*/

int main()
{
    std::vector<std::string> input;
    std::string line;
    std::ifstream myfile("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {

            
            input.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

    std::string firstLine = input[0].substr(7);
    //std::cout << "seeds : " << firstLine << std::endl;
    input.erase(input.begin());
    input.erase(input.begin());

    

    std::list<std::string> gameDatas; 
    std::string tempStr;

    for (const std::string& str : input) {
        if (str.empty()) {
            //std::cout << "empty " << tempStr << std::endl;
            gameDatas.push_back(tempStr);
            tempStr.clear();
        }
        else {
            tempStr =  tempStr + str + ' ';
        }
    }

    if (!tempStr.empty()) {
        gameDatas.push_back(tempStr);
    }

    //std::cout << tempListForGame.size() << std::endl;

    char separator = ':';
    tempStr.clear();
    std::vector<std::string> newGameDatas; // Without ex "seed-to-soil:"

    for (const std::string& str : gameDatas)
    {
        //std::cout << "etape 1" << std::endl;
        //std::cout << str << std::endl;
        for (char c : str) {
            if (c != separator) {
                tempStr += c;
            }
            else {
                //std::cout << s << std::endl; 
                //tempListForGame.push_back(s);
                tempStr.clear();
            }
        }
        newGameDatas.push_back(tempStr);
    }

    std::vector<double> tempIntVector;
    std::vector<std::vector<double>> maps;

    separator = ' ';
    tempStr.clear();

    int i = 1;

    for (std::string str : newGameDatas) 
    {
        //std::cout << "etape 2" << std::endl;
        //std::cout << str << std::endl;

        for (char c : str) {
            if (c != separator) {
                tempStr += c;
            }
            else {
                if (!tempStr.empty()) {
                    //std::cout << tempStr << ",";
                    try {
                        tempIntVector.push_back(std::stod(tempStr));
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error converting string to integer: " << e.what() << std::endl;
                        // Handle the error as needed
                    }
                    tempStr.clear();
                }
                
            }
        }
        //std::cout << tempStr << std::endl;

        if (!tempStr.empty()) {
            //std::cout << tempStr << std::endl;
            try {
                tempIntVector.push_back(std::stod(tempStr));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error converting string to integer: " << e.what() << std::endl;
                // Handle the error as needed
            }
            tempStr.clear();
        }

        maps.push_back(tempIntVector);

        tempStr.clear();
        tempIntVector.clear();
        i++;
    }

    i = 0;
    std::vector<double> seeds;

    for (char c : firstLine) {
        //std::cout << "etape 3" << std::endl;
        if (c != separator) {
            tempStr += c;
        }
        else {
            if (!tempStr.empty()) {
                //std::cout << tempStr << ",";
                try {
                    seeds.push_back(std::stod(tempStr));
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting string to integer: " << e.what() << std::endl;
                    // Handle the error as needed
                }
                tempStr.clear();
            }

        }
    }
    if (!tempStr.empty()) {
        //std::cout << tempStr << ",";
        try {
            seeds.push_back(std::stod(tempStr));
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error converting string to integer: " << e.what() << std::endl;
            // Handle the error as needed
        }
        tempStr.clear();
    }

    std::cout << std::endl;
    std::map<double, double> currentMapDict;
    std::vector<double> seedsMapped = seeds;

    for (std::vector<double> map : maps)
    {
        //std::cout << "etape 4" << std::endl;
        for (int i = 0; i < map.size(); i+=3) 
        {
            double destinationRangeStart = map[i];
            double sourceRangeStart = map[i + 1];
            double rangeLength = map[i + 2];

            for (int j = 0; j < rangeLength; j++) 
            {
                currentMapDict[sourceRangeStart + j] = destinationRangeStart + j;
                std::cout << sourceRangeStart + j << " : " << destinationRangeStart + j << std::endl;
            }
        }

        for (int k = 0; k < seedsMapped.size(); k++)
        {
            auto it = currentMapDict.find(seedsMapped[k]);
            if (it != currentMapDict.end()) {
                // Key found, retrieve and print the associated value
                std::cout << seedsMapped[k] << " is in the keys of the map. Associated value: " << it->second << std::endl;
                seedsMapped[k] = it->second;
            }
            else {
                //std::cout << seedsMapped[k] << " is not in the keys of the map." << std::endl;
                // Dont change seedsMapped[k]
            }
        }
        // Check avec chaque seed dans le dict
        // Si pas dedans, value = value

        currentMapDict.clear();
        //std::cout << std::endl;
    }

    int lowestMappedValue = seedsMapped[0];

    for (int finalMappedValue : seedsMapped) 
    {
        std::cout << "etape 5" << std::endl;
        if (finalMappedValue < lowestMappedValue) 
        {
            lowestMappedValue = finalMappedValue;
        }
    }

    std::cout << "Lowest mapped value : " << lowestMappedValue << std::endl;
}


