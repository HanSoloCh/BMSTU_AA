#include <iostream>

#include "functions.h"

int main(int argc, char *argv[])
{
    SiteProcessing site("https://redmond.company");
    site.setMaxPages(1);

    std::regex linkRegex(R"(<div class="col-md-6 col-xl-4 js-item">[\s\S]*?href="(.*?)\"[\s\S]*?</div>)");
    std::regex divRegex(R"(<div class="recipe-description">[\s\S]*?<div class="text">([\s\S]*?)</div>[\s\S]*?</div>)");
    site.startPagesProcessing(linkRegex, divRegex);
    return 0;
}
