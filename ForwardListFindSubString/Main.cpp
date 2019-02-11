
#include <list>
#include <iostream>
#include <forward_list>

using IndexLeftRight = std::pair<int, int>; //������� ������ � ������� �����
using LeftRightEqual = std::pair<IndexLeftRight, int>; //����� ���������, ������ ��������� - ������������ ������


std::list <LeftRightEqual> firndSumString(const std::forward_list<char> left, const std::forward_list<char> right)
{
    std::list <LeftRightEqual > finding_substring;

    
    
   
    
    LeftRightEqual tempFind;
    tempFind.second = 0;
    tempFind.first.first = 0;
    tempFind.first.second = 0;

    int indexLeft = 0;
    //�������� ���������� ������ �����
    for (auto lIt = left.begin(); lIt != left.end(); )
    {

        //���� ����������� � ������� �������� ��� - �������� ������
        if (tempFind.second == 0)
        {
            tempFind.first.first = indexLeft;
        }
        
        int indexRight = 0;
        
        //�������� ����������� �� ������� ������.
        auto tmpIt = lIt;
        
        for (auto rIt = right.begin(); rIt != right.end(); rIt++)
        {
            if (tmpIt == left.end())
                break;
            //���� ��������� ��� ��� �� �������
            if (tempFind.second == 0)
            {
                //����������� ������ ������
                tempFind.first.second = indexRight;
            }
            
            //���� ����������� �������
            if (*tmpIt == *rIt)
            {
                //����������� �������
                tempFind.second++;
                
                //���� ������ ������ ��� ��� �� ����������
                if (tmpIt != left.end())
                {
                    //����������� �������� ������� ������
                    tmpIt++;
                }
                else //����� �����
                {
                    break;
                }
            }
            else //���� ������� ������ - ��������� �����������
            {
                if (tempFind.second != 0)
                    break;
            }
            //��������� ����� ������ ������
            indexRight++;
        }

        //���� ��������� �� ������� - ��������� ���������
        if (tempFind.second > 0)
        {
            bool isContains = false;
            for (auto &&v : finding_substring)
            {
                int rangeBegin = v.first.first;
                int rangeEnd = rangeBegin + v.second;
                if ((tempFind.first.first >= rangeBegin) && (tempFind.first.first < rangeEnd))
                {
                    std::cout << "collision first \n";
                    isContains = true;
                }

                rangeBegin = v.first.second;
                rangeEnd = rangeBegin + v.second;
                if ((tempFind.first.second >= rangeBegin) && (tempFind.first.second < rangeEnd))
                {
                    std::cout << "collision second \n";
                    isContains = true;
                }

            }
            if (!isContains)
                finding_substring.push_back(tempFind);
            tempFind.second = 0;
        }
        
        if (lIt != left.end())
        {
            lIt++;
            indexLeft++;
        }

    }

    return finding_substring;
}


int main()
{
    std::forward_list<char> a = { 'a', 'b', 'c', 'd', 'e', 'r', 't' };
    std::forward_list<char> b = { 'c', 'a', 'b', 't', 'z', 'f', 'd', 'e' };

    auto result = firndSumString(a, b);

    for (auto ch : a)
        std::cout << ch << " ";
    std::cout << std::endl;
    for (auto ch : b)
        std::cout << ch << " ";
    std::cout << std::endl;

    for (auto &&v : result)
    {
        std::cout << "find index a:" << v.first.first << " b:" << v.first.second << "  Length:" << v.second << std::endl;
        {
            std::cout << "a: ";
            auto it = a.begin();
            std::advance(it, v.first.first);
            auto end = it;
            std::advance(end, v.second);
            for (; it != end; it++)
            {
                std::cout << *it;
            }
            std::cout << std::endl;
        }

        {
            std::cout << "b: ";
            auto it = b.begin();
            std::advance(it, v.first.second);
            auto end = it;
            std::advance(end, v.second);
            for (; it != end; it++)
            {
                std::cout << *it;
            }
            std::cout << std::endl;
        }
    }

    system("pause");

    return 0;
}