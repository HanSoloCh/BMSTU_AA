#include "functions.h"

#include <curl/curl.h>
#include <iostream>
#include <fstream>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    size_t total_size = size * nmemb;
    userp->append(static_cast<const char *>(contents), total_size);
    return total_size;
}

std::string SiteProcessing::getPageContentByUrl(const std::string &pageUrl)
{
    CURL* curl;
    curl = curl_easy_init();
    std::string readBuffer;
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, pageUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "Curl ERROR: " << curl_easy_strerror(res) << std::endl;
            readBuffer.clear();
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}


void SiteProcessing::setMaxPages(size_t nMax)
{
    pages.clear();
    for (size_t i = 0; i < nMax; ++i)
    {
        pages.push_back(siteUrl + "/recipes/?page=" + std::to_string(i + 1));
    }
}

void SiteProcessing::startPagesProcessing(const std::regex &linkRegex, const std::regex &divRegex)
{
    for (const auto &x : pages)
    {
        std::string pageContent = getPageContentByUrl(x);
        std::vector<std::string> links = getPageLinks(pageContent, linkRegex);
        saveLinksContent(links, divRegex);
    }
}

std::vector<std::string> SiteProcessing::getPageLinks(const std::string &htmlPage, const std::regex &linkRegex)
{
    std::vector<std::string> matches;
    std::sregex_iterator iter(htmlPage.begin(), htmlPage.end(), linkRegex);
    std::sregex_iterator end;

    while (iter != end) {
        matches.push_back(siteUrl + (*iter)[1].str());
        ++iter;
    }
    return matches;
}

void SiteProcessing::saveLinksContent(std::vector<std::string> links, const std::regex &regularExpression)
{
    for (const auto &x : links)
    {
        std::string pageContent = getPageContentByUrl(x);
        pageContent = extractPageContent(pageContent, regularExpression);
        savePageContent(preparePageContentToSave(pageContent), "recipes/" + getPageName(x, pageContent));
    }
}

std::string SiteProcessing::extractPageContent(const std::string &pageContent, const std::regex &regularExpression)
{
    std::smatch match;
    if (std::regex_search(pageContent, match, regularExpression))
    {
        return match[1].str();
    }
    return "";
}

std::string SiteProcessing::preparePageContentToSave(const std::string &pageContent)
{
    auto startIt = pageContent.begin();
    auto endIt = pageContent.rbegin();
    while (std::isspace(*startIt))
        ++startIt;
    while (std::isspace(*endIt))
        ++endIt;
    return std::string(startIt, endIt.base());
}

std::string SiteProcessing::getPageName(const std::string &url, const std::string &pageContent)
{
    size_t lastSlashPos = url.find_last_of('/');
    size_t prevSlashPos = url.find_last_of('/', lastSlashPos - 1);

    if (prevSlashPos != std::string::npos && lastSlashPos != std::string::npos) {
        return url.substr(prevSlashPos + 1, lastSlashPos - prevSlashPos - 1);
    }
    return "";
}

void SiteProcessing::savePageContent(const std::string &pageContent, const std::string &fileName)
{
    std::ofstream file(fileName);
    file << pageContent;
    file.close();
}



