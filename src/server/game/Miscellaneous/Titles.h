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
    TITLE_START = 0,
    TITLE_BREWMASTER,
    TITLE_ELDER,
    TITLE_FLAME_KEEPER,
    TITLE_FLAME_WARDEN,
    TITLE_MATRON,
    TITLE_MERRYMAKER,
    TITLE_THE_NOBLE,
    TITLE_PATRON,
    TITLE_THE_PILGRIM,
    TITLE_THE_HALLOWED,
    TITLE_THE_LOVE_FOOL
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
