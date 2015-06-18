#ifndef __TRINITY_TITLES_H
#define __TRINITY_TITLES_H

#include "Common.h"

#define MAX_TITLE_COUNT 82 // Will be removed and replaced by titleEntry enum end TITLE_ENUM_END

enum TitleEntry
{
    TITLE_START                         = 1,
    TITLE_BREWMASTER                    = 2,
    TITLE_ELDER                         = 3,
    TITLE_FLAME_KEEPER                  = 4,
    TITLE_FLAME_WARDEN                  = 5,
    TITLE_MATRON                        = 6,
    TITLE_MERRYMAKER                    = 7,
    TITLE_THE_NOBLE                     = 8,
    TITLE_PATRON                        = 9,
    TITLE_THE_PILGRIM                   = 10,
    TITLE_THE_HALLOWED                  = 11,
    TITLE_THE_LOVE_FOOL                 = 12
};

enum TitleMask
{
    TITLE_MASK_START                        = 0x00000001,
    TITLE_MASK_BREWMASTER                   = 0x00000002,
    TITLE_MASK_ELDER                        = 0x00000004,
    TITLEMASK_MASK_FLAME_KEEPER             = 0x00000008,
    TITLE_MASK_FLAME_WARDEN                 = 0x00000010,
    TITLE_MASK_MATRON                       = 0x00000020,
    TITLE_MASK_MERRYMAKER                   = 0x00000040,
    TITLE_MASK_THE_NOBLE                    = 0x00000080,
    TITLE_MASK_PATRON                       = 0x00000100,
    TITLE_MASK_THE_PILGRIM                  = 0x00000200,
    TITLE_MASK_THE_HALLOWED                 = 0x00000400,
    TITLE_MASK_THE_LOVE_FOOL                = 0x00000800
};

struct Titles
{
    TitleEntry      titleEntry;
    TitleMask       titleMask;
    std::string     titleName;
    bool            isPrefixTitle;
};

const std::string TitleStrings[MAX_TITLE_COUNT] =
{
    // World Events
    "",
    "Brewmaster",
    "Elder",
    "FlameKeeper",
    "FlameWarden",
    "Matron",
    "Merrymaker",
    "theNoble",
    "Patron",
    "thePilgrim",
    "theHallowed",
    "theLoveFool",

    // Argent Tournament
    "Crusader",
    "ofDarnassus",
    "ofGnomeregan",
    "ofIronforge",
    "ofOrgrimmar",
    "ofSen'jin",
    "ofSilvermoon",
    "ofStormwind",
    "oftheExodar",
    "oftheUndercity",
    "ofThunderBluff",

    // Dungeons and Raids
    "ArgentDefender",
    ",BaneoftheFallenKing",
    ",ChampionoftheFrozenWastes",
    ",ChampionofUlduar",
    ",ConquerorofUlduar",
    ",HeraldoftheTitans",
    "Jenkins",
    "oftheNightfall",
    "Starcaller",
    "theAstralWalker",
    "theImmortal",
    "theKingslayer",
    "theLightofDawn",
    "theUndying",
    "TwilightVanquisher",
    ",Blackwing'sBane",
    ",BlessedDefenderofNordrassil",
    ",DefenderofaShatteredWorld",
    ",Destroyer'sEnd",
    "Firelord",
    "Dragonslayer",
    "oftheFourWinds",

    // Dungeons and Raids: Realm Firsts
    ",Conqueror of Naxxramas",
    ",Death'sDemise",
    "GrandCrusader",
    "ObsidianSlayer",
    "theCelestialDefender",
    "theMagicSeeker",

    // Miscellaneous
    "Loremaster",
    "thePatient",
    "theExplorer",
    "theSeeker",
    "theCamel-Hoarder",
    "theFlamebreaker",

    // PvP Achievments
    "oftheAlliance",
    "oftheHorde",
    ",theBloodthirsty",

    // Reputation
    "Ambassador",
    "BloodsailAdmiral",
    "GuardianofCenarius",
    "oftheAshen Verdict",
    "theArgent Champion",
    "theDiplomat",
    "theExalted",
    "theInsane",
    ",AvengerofHyjal",

    // Battleground
    "Battlemaster",
    "HeroofTheAlliance",
    "HerooftheHorde",
    "Warbound",
    "Warbringer",
    "VeteranoftheAlliance",
    "VeteranoftheHorde",

    // Arena
    "ArenaMaster",

    // Professions
    "Salty",
    "Chef",
    "Professor",
    "AssistantProfessor",
    "AssociateProfessor"
};

// Titles with Whitespaces here
static Titles titleTable[MAX_TITLE_COUNT] =
{
    // ArrayEntry  titleEntry,        titleMask                 titleName,                  isPrefixTitle
    /* 0 */      { TitleEntry(0),      TitleMask(0),             "",                         true  },
    /* 1 */      { TITLE_START,        TITLE_MASK_START,         "",                         true  },
    /* 2 */      { TITLE_BREWMASTER,   TITLE_MASK_BREWMASTER,    "Brewmaster ",              true  },
    /* 3 */      { TITLE_ELDER,        TITLE_MASK_ELDER,         "Elder ",                   true  },
    /* 4 */      { TitleEntry(0),      TitleMask(0),             "",                         true  },
    /* 5 */      { TitleEntry(0),      TitleMask(0),             "",                         true  },
    /* 6 */      { TitleEntry(0),      TitleMask(0),             "",                         true  },
    /* 7 */      { TitleEntry(0),      TitleMask(0),             "",                         true  },
    /* 8 */      { TITLE_THE_NOBLE,    TITLE_MASK_THE_NOBLE,     " the Noble",               false }
};

#endif
