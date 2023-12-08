#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <utility> // for std::pair

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 8 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
One of the camel's pouches is labeled "maps" - sure enough, it's full of documents (your puzzle input) about how to
navigate the desert. At least, you're pretty sure that's what they are; one of the documents contains a list of
left/right instructions, and the rest of the documents seem to describe some kind of network of labeled nodes.

It seems like you're meant to use the left/right instructions to navigate the network. Perhaps if you have the camel
follow the same instructions, you can escape the haunted wasteland!

After examining the maps for a bit, two nodes stick out: AAA and ZZZ. You feel like AAA is where you are now, and
you have to follow the left/right instructions until you reach ZZZ.

Starting at AAA, follow the left/right instructions. How many steps are required to reach ZZZ?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
After examining the maps a bit longer, your attention is drawn to a curious fact: the number of nodes with names
ending in A is equal to the number ending in Z! If you were a ghost, you'd probably just start at every node that
ends with A and follow all of the paths at the same time until they all simultaneously end up at nodes that end with
Z.

Simultaneously start on every node that ends with A. How many steps does it take before you're only on nodes that
end with Z?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 8 ----- ----- ----- ----- -----
*/

// Function to calculate the greatest common divisor (GCD) using Euclid's algorithm
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the least common multiple (LCM) of two numbers
long long lcm(long long a, long long b) {
    return (a * b) / gcd(a, b);
}

// Function to calculate the LCM of a vector of integers
long long lcmOfVector(const std::vector<long long>& numbers) {
    long long result = 1;

    for (long long number : numbers) {
        result = lcm(result, number);
    }

    return result;
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

    std::string firstLine = input[0];
    std::cout << "first line: " << firstLine << std::endl;

    // Supprimer les deux premiers éléments
    auto it = input.begin();
    std::advance(it, 2);  // Avancer l'itérateur de deux positions
    input.erase(input.begin(), it);

    std::map<std::string, std::pair<std::string, std::string>> mapNodeLR;

    //std::string firstNode = input[0].substr(0, 3);
    std::string firstNode = "AAA";
    std::cout << "first node: " << firstNode << std::endl; 

    //std::string lastNode = input[input.size() - 1].substr(0, 3);
    std::string lastNode = "ZZZ";
    std::cout << "last node: " << lastNode << std::endl;

    for (std::string str : input) {
        //std::cout << str << std::endl;
        std::string tempStr;

        for (char c : str) {
            if (c != ' ' && c != '=' && c != '(' && c != ')' && c != ',') {
                tempStr += c;
            }
        }

        //std::cout << tempStr << std::endl;

        std::vector<std::string> tempListNodeLR;

        for (int i = 0; i < tempStr.length(); i += 3) {
            std::string segment = tempStr.substr(i, 3);
            tempListNodeLR.push_back(segment);
            //std::cout << segment << std::endl;
        }

        mapNodeLR[tempListNodeLR[0]] = { tempListNodeLR[1], tempListNodeLR[2] };
        //std::cout << "map node: " << tempListNodeLR[0] << " left: " << tempListNodeLR[1] << " right: " << tempListNodeLR[2] << std::endl;
    }


    std::cout << "-----" << std::endl;
    std::cout << "Part 1:" << std::endl;

    
    std::string currentNode = firstNode;
    int currentIndexLR = 0;
    int nbrSteps = 0;

    
    while (currentNode != lastNode) 
    {
        if (currentIndexLR > firstLine.size() - 1) 
        {
            currentIndexLR = 0;
        }

        if (firstLine[currentIndexLR] == 'L') {
            currentNode = mapNodeLR[currentNode].first;
        }
        else { // right
            currentNode = mapNodeLR[currentNode].second;
        }

        //std::cout << "current node: " << currentNode << std::endl;
        currentIndexLR++;
        nbrSteps++;
    }
    

    std::cout << std::endl;
    std::cout << "nbr steps: " << nbrSteps << std::endl;
    std::cout << "-----" << std::endl;

    std::cout << "-----" << std::endl;
    std::cout << "Part 2:" << std::endl;

    std::vector<std::string> currentNodes;

    std::cout << "first nodes : " << std::endl;
    for (std::string str : input) {
        if (str[2] == 'A') {
            currentNodes.push_back(str.substr(0,3));
            std::cout << "- " << str.substr(0, 3) << std::endl;
        }
    }

    bool ended = false;
    currentIndexLR = 0;
    nbrSteps = 0;

    // Optimize using Lowest Common Multiple: (infinite time if i do the same as part 1!)
    std::vector<long long> currentNodesStepToEnd;

    for (int i = 0; i < currentNodes.size(); i++)
    {
        std::string currentNode = currentNodes[i];
        std::cout << "current node: " << currentNode << std::endl;
        currentIndexLR = 0;
        nbrSteps = 0;
        bool ended = false;

        while (!ended) {
            if (currentIndexLR > firstLine.size() - 1)
            {
                currentIndexLR = 0;
            }

            //std::cout << "current node: " << currentNodes[i] << std::endl;
            if (firstLine[currentIndexLR] == 'L') {
                //std::cout << "L" << std::endl;
                currentNode = mapNodeLR[currentNode].first;
            }
            else { // right
                //std::cout << "R" << std::endl;
                currentNode = mapNodeLR[currentNode].second;
            }
            //std::cout << "changed node: " << currentNodes[i] << std::endl;

            // check end
            if (currentNode[2] == 'Z') {
                ended = true;
            }

            currentIndexLR++;
            nbrSteps++; 
        }
        currentNodesStepToEnd.push_back(nbrSteps);
        std::cout << "nbr of steps: " << nbrSteps << std::endl;
        std::cout << "---" << std::endl;
    }

    long long resultNbrSteps = lcmOfVector(currentNodesStepToEnd);
    std::cout << "total nbr steps: " << resultNbrSteps << std::endl;
    std::cout << "-----" << std::endl;
}