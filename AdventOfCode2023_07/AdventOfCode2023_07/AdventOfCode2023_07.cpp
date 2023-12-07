#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility> // for std::pair
#include <algorithm>

/*
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 7 ----- ----- ----- ----- -----
----- ----- PART 1 ----- -----
In Camel Cards, you get a list of hands, and your goal is to order them based on the strength of each hand. A hand
consists of five cards labeled one of A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2. The relative strength of each card
follows this order, where A is the highest and 2 is the lowest.

Every hand is exactly one type. From strongest to weakest, they are:
- Five of a kind, where all five cards have the same label: AAAAA
- Four of a kind, where four cards have the same label and one card has a different label: AA8AA
- Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
- Three of a kind, where three cards have the same label, and the remaining two cards are each different from any
    other card in the hand: TTT98
- Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a
    third label: 23432
- One pair, where two cards share one label, and the other three cards have a different label from the pair and each
    other: A23A4
- High card, where all cards' labels are distinct: 23456

Hands are primarily ordered based on type; for example, every full house is stronger than any three of a kind.

If two hands have the same type, a second ordering rule takes effect. Start by comparing the first card in each
hand. If these cards are different, the hand with the stronger first card is considered stronger. If the first card
in each hand have the same label, however, then move on to considering the second card in each hand. If they differ,
the hand with the higher second card wins; otherwise, continue with the third card in each hand, then the fourth,
then the fifth.

This example shows five hands; each hand is followed by its bid amount. Each hand wins an amount equal to its bid
multiplied by its rank, where the weakest hand gets rank 1, the second-weakest hand gets rank 2, and so on up to the
strongest hand. Because there are five hands in this example, the strongest hand will have rank 5 and its bid will
be multiplied by 5.

Find the rank of every hand in your set. What are the total winnings?
----- ----- PART 1 ----- -----

----- ----- PART 2 ----- -----
To make things a little more interesting, the Elf introduces one additional rule. Now, J cards are jokers -
wildcards that can act like whatever card would make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even than 2. The other cards stay in the same
order: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J.

J cards can pretend to be whatever card is best for the purpose of determining hand type; for example, QJJQ2 is now
considered four of a kind. However, for the purpose of breaking ties between two hands of the same type, J is always
treated as J, not the card it's pretending to be: JKKK2 is weaker than QQQQ2 because J is weaker than Q.

Using the new joker rule, find the rank of every hand in your set. What are the new total winnings?
----- ----- PART 2 ----- -----
----- ----- ----- ----- ----- AVENT OF CODE 2023 - DAY 7 ----- ----- ----- ----- -----
*/

enum HandType {
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard,
    NotDefined
};

std::string HandTypeToStr(HandType handType) {
    switch (handType) {
        case (HandType::FiveOfAKind):
            return "Five Of A Kind";
        case (HandType::FourOfAKind):
            return "Four Of A Kind";
        case (HandType::FullHouse):
            return "Full House";
        case (HandType::ThreeOfAKind):
            return "Three Of A Kind";
        case (HandType::TwoPair):
            return "Two Pair";
        case (HandType::OnePair):
            return "One Pair";
        case (HandType::HighCard):
            return "High Card";
        case (HandType::NotDefined):
            return "Not Defined";
    }
}

bool compareStrings(const std::string& str1, const std::string& str2) {
    // Part 1:
    //const std::string order = "AKQJT98765432";

    //Part 2:
    const std::string order = "AKQT98765432J";

    size_t minLength = std::min(str1.length(), str2.length());

    for (size_t i = 0; i < minLength; ++i) {
        size_t pos1 = order.find(str1[i]);
        size_t pos2 = order.find(str2[i]);

        //std::cout << "Comparaison : " << str1[i] << " (" << pos1 << ") vs " << str2[i] << " (" << pos2 << ")" << std::endl;

        if (pos1 < pos2) {
            return false; 
        }
        else if (pos1 > pos2) {
            return true;
        }
    }
    return str1.compare(minLength, std::string::npos, str2);
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

    char separator = ' ';

    // Get list int time
    std::string tempStr;
    std::string handStr;
    std::map < std::string, std::pair<int, HandType>> hands;

    for (std::string str : input){
        for (char c : str) {
            if (c != separator) {
                tempStr += c;
            }
            else {
                if (!tempStr.empty()) {
                    handStr = tempStr;
                    tempStr.clear();
                }
            }
        }
        if (!tempStr.empty()) {
            try {
                int intValue = std::stoi(tempStr);
                hands[handStr] = { intValue, HandType::NotDefined };
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error converting winning number to int: " << e.what() << std::endl;
            }
        }

        handStr.clear();
        tempStr.clear();
    }

    // Search hand type
    for (auto& hand : hands) {
        //std::cout << "Key: " << hand.first << ", Value: " << hand.second.first << ", " << hand.second.second << std::endl;

        // Iterations of each char in hand
        std::map<char, int> cardsIt;

        for (char c : hand.first) {
            auto it = cardsIt.find(c);

            if (it != cardsIt.end()) {
                cardsIt[c]++;
            }
            else {
                cardsIt[c] = 1;
            }
        }

        std::pair<char, int> highestCountCardIt = {'x', 0};
        std::pair<char, int> jCountCardIt = {'x', 0};

        for (auto it = cardsIt.begin(); it != cardsIt.end(); ) {
            std::cout << it->first << " : " << it->second << std::endl;
            

            // ----- Part 2, J = Joker:
            if (it->first == 'J') 
            {
                //std::cout << "highest cound card it " << it->first << " : " << it->second << std::endl;
                jCountCardIt = { it->first, it->second };
                it = cardsIt.erase(it);
            }
            else {
                if (highestCountCardIt.first == 'x') {
                    highestCountCardIt = { it->first, it->second };
                    //std::cout << "new highest cound card it " << it->first << " : " << it->second << std::endl;
                }
                if (it->second > highestCountCardIt.second) {
                    highestCountCardIt = { it->first, it->second };
                    //std::cout << "new highest cound card it " << it->first << " : " << it->second << std::endl;
                }
                ++it;
            }
            // ----- Part 2 

            
        }
        // ----- Part 2
        cardsIt[highestCountCardIt.first] = highestCountCardIt.second + jCountCardIt.second;

        std::cout << "cards it after j" << std::endl;

        for (auto it = cardsIt.begin(); it != cardsIt.end(); ) {
            std::cout << it->first << " : " << it->second << std::endl;
            if (it != cardsIt.end())
            {
                ++it;
            }
        }
        // ----- Part 2

        if (cardsIt.size() == 1) 
        {
            std::cout << "size 1" << std::endl;
            hand.second.second = HandType::FiveOfAKind; // AAAAA
        }
        else if (cardsIt.size() == 2) {
            std::cout << "size 2" << std::endl;
            auto firstCard = cardsIt.begin();
            if (firstCard->second == 4 || firstCard->second == 1) { // AAAAB
                //std::cout << "1" << std::endl;
                hand.second.second = HandType::FourOfAKind;
            }
            else {
                //std::cout << "2" << std::endl;
                hand.second.second = HandType::FullHouse; // AAABB
            }
        }
        else if (cardsIt.size() == 3) {
            std::cout << "size 3" << std::endl;
            for (const auto& pair : cardsIt) {
                int key = pair.first;
                char value = pair.second;

                if (value == 3) {
                    //std::cout << "1" << std::endl;
                    hand.second.second = HandType::ThreeOfAKind; // AAABC
                    break;
                }
                else {
                    //std::cout << "2" << std::endl;
                    hand.second.second = HandType::TwoPair; // AABBC
                }
            }
        }
        else if (cardsIt.size() == 4) {
            std::cout << "size 4" << std::endl;
            hand.second.second = HandType::OnePair; // AABCD
        }
        else {
            std::cout << "size 5" << std::endl;
            hand.second.second = HandType::HighCard; // ABCDE
        }

        std::cout << "Key: " << hand.first << ", Value: " << hand.second.first << ", " << hand.second.second << std::endl;
    }

    std::cout << std::endl;

    std::vector<HandType> handTypesLowToHighOrder = { HandType::HighCard, HandType::OnePair, HandType::TwoPair, HandType::ThreeOfAKind, HandType::FullHouse, HandType::FourOfAKind, HandType::FiveOfAKind };

    std::vector<std::string> tempSameHandType;
    std::vector<int> handsInStrengthOrder;

    for (HandType handType : handTypesLowToHighOrder)
    {
        std::cout << HandTypeToStr(handType) << std::endl;
        for (auto& hand : hands) 
        {
            if (hand.second.second == handType) 
            {
                //std::cout << handType << " : " << hand.first << std::endl;
                tempSameHandType.push_back(hand.first);
            }
        }
        
        if (tempSameHandType.size() > 1) {
            //std::cout << "size > 1" << std::endl;
            // Trier les chaînes en utilisant la fonction de comparaison personnalisée
            std::sort(tempSameHandType.begin(), tempSameHandType.end(), compareStrings);

            // Afficher les chaînes triées
            std::cout << "Chaines triees : ";
            for (const std::string& str : tempSameHandType) {
                handsInStrengthOrder.push_back(hands[str].first);
                std::cout << str << " : " << hands[str].first << ", ";
            }
            std::cout << std::endl;
        }
        else if (tempSameHandType.size() == 1) {
            //std::cout << "size 1" << std::endl;
            std::cout << handType << " : " << tempSameHandType[0] << std::endl;
            handsInStrengthOrder.push_back(hands[tempSameHandType[0]].first);
        }

        tempSameHandType.clear();
    }

    std::cout << std::endl;

    int totalWinnings = 0;

    for (int i = 0; i < handsInStrengthOrder.size(); i++) {
        std::cout << handsInStrengthOrder[i] << " * " << i + 1 << std::endl;
        totalWinnings += handsInStrengthOrder[i] * (i + 1);
    }

    std::cout << "Total Winnings: " << totalWinnings << std::endl;
}

