#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
void generateTXT();
void splitString(std::string input, std::vector<std::string>& output);
bool parseTXT(std::vector<std::vector<uint8_t>>& pyramid);
void walkPyramid();


int main()
{
    srand(time(NULL));

    int input = 4;
    while (input != 3)
    {
        system("cls");
        std::cout << "generate txt - 1; parse - 2; exit - 3. \nyour input: ";
        std::cin >> input;

        if (input == 1)
        {
            generateTXT();

        }
        if (input == 2)
        {
            walkPyramid();
        }
    }
   



}


void walkPyramid()
{
    std::vector<std::vector<uint8_t>> pyramid;
    if (parseTXT(pyramid))
    {
        std::vector<uint8_t> cur;
        std::vector<int> sums;
        int index = pyramid.size() - 1;

        cur = pyramid[index];
        for (int i = 0; i < cur.size(); ++i)
        {
            sums.push_back((int)cur[i]);
        }
        while (index > 0)
        {
            index--;
            cur = pyramid[index];
            std::vector<int> tmpSums = sums;
            sums.clear();
            for (int i = 0; i < cur.size(); ++i)
            {
                sums.push_back((int)cur[i] + std::max(tmpSums[i], tmpSums[i + 1]));
            }

        }
        std::cout << sums[0];
        system("pause");
    }




}


bool parseTXT(std::vector<std::vector<uint8_t>>& pyramid)
{
    std::ifstream in;
    in.open("pyramid.txt", std::ios::in);
    if (in.is_open())
    {
        while (!in.eof())
        {
            std::string tmp = "";
            char tmpC = '0';
            while (tmpC != '\n' && !in.eof())
            {
                in.read((char*)&tmpC, sizeof(char));
                tmp += tmpC;
            }
            tmp.pop_back();
            std::vector<std::string> midTmp;
            splitString(tmp, midTmp);
            std::vector<uint8_t> row;
            for (int i = 0; i < midTmp.size(); ++i)
            {
                row.push_back((uint8_t)std::stoi(midTmp[i]));
            }
            if (row.size() > 0)
                pyramid.push_back(row);
        }
        in.close();
        return true;

    }
    else
    {
        std::cout << "cant open txt";
        return false;
    }
}




void generateTXT()
{
    std::ofstream out;
    out.open("pyramid.txt", std::ios::out);
    if (out.is_open())
    {
        //420 rows
        for (int i = 0; i < 420; ++i)
        {
            //there is a row number count of elements in a row
            for (int j = 0; j < i + 1; ++j)
            {
                out << rand() % 100;
                out << " ";
            }
            out << "\n";
        }
        out.close();
        std::cout << "txt generated";
        system("pause");
    }
    else
    {
        std::cout << "cant open txt";
    }
}

void splitString(std::string input, std::vector<std::string>& output)
{
    std::string tmp = "";
    for (int i = 0; i < input.length(); ++i)
    {
        if (input[i] != ' ')
        {
            tmp += input[i];
        }
        else
        {
            output.push_back(tmp);
            tmp = "";
        }
    }
}

