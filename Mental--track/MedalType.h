#ifndef MEDALTYPE_H
#define MEDALTYPE_H


#include <string>

enum class MedalType {
    BlazeMaster,      // (火焰大师 - 征服所有烈焰挑战)
    FrostLord,     // (寒冰领主 - 突破所有极冻试炼)
    GaiasChampion,       // (盖亚冠军 - 驾驭自然之力)
    CelestialSage,    // (天界贤者 - 完成神圣试炼)
    ThunderWielder,      // (雷霆掌控者 - 征服所有闪电关卡)
    UmbraKing    ,       // (暗影之王 - 统治黑暗领域)
    EternalLuminary   // （永恒之光）象征通关后的终极荣耀，呼应宝石图案的璀璨。

};

// 辅助函数声明
std::string medalToString(MedalType type);
MedalType stringToMedal(const std::string& str);



#endif // MEDALTYPE_H
