#include <iostream>

#include "functions.h"

int main(int argc, char *argv[])
{
    SiteProcessing site("https://redmond.company");
    site.setMaxPages(1);
    site.startPagesProcessing();
    return 0;
}
