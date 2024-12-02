#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <regex>

class SiteProcessing
{
public:
    SiteProcessing(const std::string &url) : siteUrl(url) {}

    void setMaxPages(size_t nMax);
    void sequentialProcessing(const std::regex &linkRegex, const std::regex &divRegex);
    void parallelProcessing(const std::regex &linkRegex, const std::regex &divRegex, size_t numThreads);
protected:
    std::string getPageContentByUrl(const std::string &pageUrl);
    std::vector<std::string> getPageLinks(const std::string &htmlPage, const std::regex &linkRegex);
    void getPageLinksParallel(const std::string &url, const std::regex &linkRegex);

    void saveLinksContent(std::vector<std::string> links, const std::regex &regularExpression);
    void saveLinksContentParallel(std::vector<std::string> links, const std::regex &regularExpression, size_t threadNum);

    std::string extractPageContent(const std::string &pageContent, const std::regex &regularExpression);
    std::string preparePageContentToSave(const std::string &pageContent);
    std::string getPageName(const std::string &url, const std::string &pageContent);
    void savePageContent(const std::string &pageContent, const std::string &fileName);
private:
    std::string siteUrl;
    std::vector<std::string> pages;
};

#endif // FUNCTIONS_H
