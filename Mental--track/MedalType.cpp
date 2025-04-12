#include "MedalType.h"
#include <stdexcept>


std::string medalToString(MedalType type)
{
    switch(type) {
        case MedalType::FirstBlood: return "FirstBlood";
        case MedalType::SpeedRunner: return "SpeedRunner";
        case MedalType::Collector: return "Collector";
        case MedalType::PerfectScore: return "PerfectScore";
        case MedalType::Marathoner: return "Marathoner";
        default: throw std::invalid_argument("Invalid medal type");
    }
}

MedalType stringToMedal(const std::string& str) {
    if(str == "FirstBlood") return MedalType::FirstBlood;
    if(str == "SpeedRunner") return MedalType::SpeedRunner;
    if(str == "Collector") return MedalType::Collector;
    if(str == "PerfectScore") return MedalType::PerfectScore;
    if(str == "Marathoner") return MedalType::Marathoner;
    throw std::invalid_argument("Invalid medal string");
}
