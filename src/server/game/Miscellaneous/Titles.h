#ifndef __TRINITY_TITLES_H
#define __TRINITY_TITLES_H

#include "Common.h"

#define MAX_TITLE_COUNT 82 // Will be removed and replaced by titleEntry enum end TITLE_ENUM_END

struct Titles
{
    uint32          titleEntry;
    std::string     titleName;
    bool            isPrefixTitle;
};

enum TitleEntry
{
    TITLE_START                         = 0x00000001,
    TITLE_BREWMASTER                    = 0x00000002,
    TITLE_ELDER                         = 0x00000004,
    TITLE_FLAME_KEEPER                  = 0x00000008,
    TITLE_FLAME_WARDEN                  = 0x00000010,
    TITLE_MATRON                        = 0x00000020,
    TITLE_MERRYMAKER                    = 0x00000040,
    TITLE_THE_NOBLE                     = 0x00000080,
    TITLE_PATRON                        = 0x00000100,
    TITLE_THE_PILGRIM                   = 0x00000200,
    TITLE_THE_HALLOWED                  = 0x00000400,
    TITLE_THE_LOVE_FOOL                 = 0x00000800
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
    // titleEntry,              titleName,                  isPrefixTitle             
    { TITLE_START,              "",                         true  },
    { TITLE_BREWMASTER,         "Brewmaster ",              true  },
    { TITLE_ELDER,              "Elder ",                   true  },
    { TITLE_THE_NOBLE,          " the Noble",               false }
};

#endif
