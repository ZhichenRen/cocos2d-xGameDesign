#include "PosLoadUtil.h"
#include "EnumPosType.h"
#include "TowerPos.h"
#include "MonsterPos.h"

PosLoadUtil* PosLoadUtil::m_posLoadUtil = NULL;

PosLoadUtil* PosLoadUtil::getInstance() {
    if (m_posLoadUtil == NULL) {
        m_posLoadUtil = new PosLoadUtil();

        if (m_posLoadUtil && m_posLoadUtil->init()) {
            m_posLoadUtil->autorelease();
            m_posLoadUtil->retain();
        }
        else {
            CC_SAFE_DELETE(m_posLoadUtil);
        }
    }

    return m_posLoadUtil;
}

bool PosLoadUtil::init() {

    return true;
}
Vector<PosBase*> PosLoadUtil::loadPosWithFile(const char* sFilePath, EnumPosType enPosType, Node* container, int iLevel, bool isDebug) {
    Vector<PosBase*> posList;

    ValueMap fileDataMap = FileUtils::getInstance()->getValueMapFromFile(sFilePath);

    int size = fileDataMap.size();
    for (int i = 1; i <= size; i++){
        Value value = fileDataMap.at(StringUtils::toString(i));
        ValueMap data = value.asValueMap();

        /* 创建坐标对象 */
        PosBase*  posBase = NULL;
        switch (enPosType) {
        case enTowerPos:
            posBase = TowerPos::create(Point(data["x"].asInt(), data["y"].asInt()), isDebug);
            break;
        case enMonsterPos:
            posBase = MonsterPos::create(Point(data["x"].asInt(), data["y"].asInt()), isDebug);
            break;
        default:
            posBase = TowerPos::create(Point(data["x"].asInt(), data["y"].asInt()), isDebug);
            break;
        }
        posList.pushBack(posBase);

        if (container != NULL) {
            container->addChild(posBase, iLevel);
        }
    }
    
    return posList;
}

