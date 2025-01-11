#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const char* greenCode = "\033[32m";
const char* redCode = "\033[31m";
const char* resetCode = "\033[0m";

void RL_Encode() 
{
    std::string rawLine;
    std::string encryptedLine;

    std::ifstream fileToReadFrom("input.txt");
    std::ofstream fileToWriteTo("output.txt");

    if (fileToReadFrom.is_open()) 
    {
        while (std::getline(fileToReadFrom, rawLine)) 
        {
            std::cout << redCode << "Raw: " << rawLine << "\n";

            for (size_t i = 0; i < rawLine.length(); i++) 
            {
                int currentCharacterCount = 1;
                encryptedLine += rawLine[i];

                while (i < rawLine.length() - 1 && rawLine[i + 1] == rawLine[i]) 
                {
                    currentCharacterCount++;
                    i++;
                }

                encryptedLine += std::to_string(currentCharacterCount);
            }

            std::cout << greenCode << "Encrypted: " << encryptedLine << "\n";

            if (fileToWriteTo.is_open()) 
            {
                fileToWriteTo << encryptedLine << "\n";
            }
            else 
            {
                std::cout << redCode << "\nUnable to write to file." << std::endl;
            }

            encryptedLine.clear();
        }

        fileToReadFrom.close();
    }
    else 
    {
        std::cout << redCode << "\nUnable to read from file." << std::endl;
    }

    std::cout << resetCode;
}

void RL_Decode() 
{
    std::string rawLine;
    std::string decryptedLine;

    std::ifstream fileToReadFrom("output.txt");
    std::ofstream fileToWriteTo("decrypted.txt");

    if (fileToReadFrom.is_open())
    {
        while (std::getline(fileToReadFrom, rawLine))
        {
            std::cout << redCode << "Raw: " << rawLine << "\n";

            for (size_t i = 0; i < rawLine.length(); i++)
            {
                char character = rawLine[i];
                std::string countStr;

                while (i + 1 < rawLine.length() && std::isdigit(rawLine[i + 1])) {
                    countStr += rawLine[++i];
                }

                int count = std::stoi(countStr);

                decryptedLine.append(count, character);
            }

            std::cout << greenCode << "Decrypted: " << decryptedLine << "\n";

            if (fileToWriteTo.is_open())
            {
                fileToWriteTo << decryptedLine << "\n";
            }
            else
            {
                std::cout << redCode << "\nUnable to write to file." << std::endl;
            }

            decryptedLine.clear();
        }

        fileToReadFrom.close();
    }
    else
    {
        std::cout << redCode << "\nUnable to read from file." << std::endl;
    }

    std::cout << resetCode;
}

int main() 
{
	std::cout << "<=== File Compression Utility ===>\n\n";

    std::cout << "<=== Encryption ===>\n\n";
	RL_Encode();

    std::cout << "\n<=== Decryption ===>\n\n";
    RL_Decode();

	return 0;
}