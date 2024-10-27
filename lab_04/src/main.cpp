#include <iostream>
#include <fstream>
#include <chrono>


#include "functions.h"

int main()
{
    SiteProcessing site("https://redmond.company");
    site.setMaxPages(5);
    std::regex linkRegex(R"(<div class="col-md-6 col-xl-4 js-item">[\s\S]*?href="(.*?)\"[\s\S]*?</div>)");
    std::regex divRegex(R"(<div class="recipe-description">[\s\S]*?<div class="text">([\s\S]*?)</div>[\s\S]*?</div>)");

    std::ofstream resultFile("performance_results.csv");
    resultFile << "threads|time\n";

    auto start = std::chrono::high_resolution_clock::now();
    site.sequentialProcessing(linkRegex, divRegex);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    resultFile << 1 << "|" << duration.count() << std::endl;

    int threadsNum[] = {2, 4, 8, 16, 32, 64};
    for (const auto &num : threadsNum)
    {
        std::cout << num;
        auto start = std::chrono::high_resolution_clock::now();
        site.parallelProcessing(linkRegex, divRegex, num);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        resultFile << num << "|" << duration.count() << std::endl;
    }
    resultFile.close();

    // site.sequentialProcessing(linkRegex, divRegex);
    return 0;
}
