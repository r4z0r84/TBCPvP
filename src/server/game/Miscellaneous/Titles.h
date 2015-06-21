#ifndef __TRINITY_TITLES_H
#define __TRINITY_TITLES_H

#include "Common.h"

#define MAX_TITLE_COUNT 31 // Will be removed and replaced by titleEntry enum end TITLE_ENUM_END

enum TitleEntry
{
    TITLE_START = 1,
};

struct Titles
{
    TitleEntry      titleEntry;
    std::string     titleName;
    bool            isPrefixTitle;
};

const std::string TitleStrings[MAX_TITLE_COUNT] =
{
    // World Events
    "",
};

// Titles with Whitespaces here
static Titles titleTable[MAX_TITLE_COUNT] =
{
    // ArrayEntry  titleEntry               titleName,                  isPrefixTitle
    /* 0 */      { TitleEntry(0),           "",                         true  },
};

#endif
