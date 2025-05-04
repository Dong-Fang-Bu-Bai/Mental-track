#include "MedalType.h"
#include <stdexcept>


std::string medalToString(MedalType type)
{
    switch(type) {
        case MedalType::BlazeMaster: return "火焰大师";
        case MedalType::FrostLord: return "寒冰领主";
        case MedalType::GaiasChampion: return "盖亚冠军";
        case MedalType::CelestialSage: return "天界贤者";
        case MedalType::ThunderWielder: return "雷霆掌控者";
        case MedalType::UmbraKing: return "暗影之王";
        case MedalType::EternalLuminary: return "永恒之光";
        default: throw std::invalid_argument("Invalid medal type");
    }
}


MedalType stringToMedal(const std::string& str)
{
    if(str == "火焰大师") return MedalType::BlazeMaster;
    if(str == "寒冰领主") return MedalType::FrostLord;
    if(str == "盖亚冠军") return MedalType::GaiasChampion;
    if(str == "天界贤者") return MedalType::CelestialSage;
    if(str == "雷霆掌控者") return MedalType::ThunderWielder;
    if(str == "暗影之王") return MedalType::UmbraKing;
    if(str == "永恒之光") return MedalType::EternalLuminary;
    throw std::invalid_argument("Invalid medal string");
}
