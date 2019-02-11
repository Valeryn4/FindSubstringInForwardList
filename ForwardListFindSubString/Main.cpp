
#include <list>
#include <iostream>
#include <forward_list>

using IndexLeftRight = std::pair<int, int>; //индексы левого и правого листа
using LeftRightEqual = std::pair<IndexLeftRight, int>; //длина подстроки, начало подстроки - определенный индекс


std::list <LeftRightEqual> firndSumString(const std::forward_list<char> left, const std::forward_list<char> right)
{
    std::list <LeftRightEqual > finding_substring;

    
    
   
    
    LeftRightEqual tempFind;
    tempFind.second = 0;
    tempFind.first.first = 0;
    tempFind.first.second = 0;

    int indexLeft = 0;
    //начинаем перебирать первый писок
    for (auto lIt = left.begin(); lIt != left.end(); )
    {

        //если результатов с прошлой итерации нет - обнуляем индекс
        if (tempFind.second == 0)
        {
            tempFind.first.first = indexLeft;
        }
        
        int indexRight = 0;
        
        //начинаем проходиться по второму списку.
        auto tmpIt = lIt;
        
        for (auto rIt = right.begin(); rIt != right.end(); rIt++)
        {
            if (tmpIt == left.end())
                break;
            //если подстрака все еще не найдена
            if (tempFind.second == 0)
            {
                //передвигаем индекс дальше
                tempFind.first.second = indexRight;
            }
            
            //если совподнения найдены
            if (*tmpIt == *rIt)
            {
                //увеличиваем счетчик
                tempFind.second++;
                
                //если первый список все еще не закончился
                if (tmpIt != left.end())
                {
                    //передвигаем итератор первого списка
                    tmpIt++;
                }
                else //иначе выход
                {
                    break;
                }
            }
            else //если символы разные - подстрока закончилась
            {
                if (tempFind.second != 0)
                    break;
            }
            //обновляем индкс второо списка
            indexRight++;
        }

        //если подстрока не нулевая - сохраняем результат
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