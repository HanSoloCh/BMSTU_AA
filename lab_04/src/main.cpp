#include <iostream>
#include <fstream>
#include <limits>

#include "functions.h"

int main()
{

    int count;
    std::cout << "Введите количество обрабатываемых страниц: ";
    while (!(std::cin >> count) || count <= 0)
    {
        std::cout << "Некорректное число страниц! Введите положительное число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int countThreads;
    std::cout << "Введите количество потоков (1 для последовательного режима): ";
    while (!(std::cin >> countThreads) || countThreads <= 0)
    {
        std::cout << "Некорректное число потоков! Введите положительное число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    SiteProcessing site("https://redmond.company");
    site.setMaxPages(count);
    std::regex linkRegex(R"(<div class="col-md-6 col-xl-4 js-item">[\s\S]*?href="(.*?)\"[\s\S]*?</div>)");
    std::regex divRegex(R"(<div class="recipe-description">[\s\S]*?<div class="text">([\s\S]*?)</div>[\s\S]*?</div>)");
    if (countThreads == 1)
        site.sequentialProcessing(linkRegex, divRegex);
    else
        site.parallelProcessing(linkRegex, divRegex, countThreads);
    return 0;
}
