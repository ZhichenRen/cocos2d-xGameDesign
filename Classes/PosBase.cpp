#include "PosBase.h"

PosBase::PosBase() {
    m_pos = Point(0, 0);
    m_isDebug = false;
}

PosBase::~PosBase() {
}

PosBase* PosBase::create(Point pos) {
    PosBase* tPos = new PosBase();

    if (tPos && tPos->init(pos)) {
        tPos->autorelease();
    }
    else {
        CC_SAFE_DELETE(tPos);
    }
    return tPos;
}

PosBase* PosBase::create(Point pos, bool isDebug) {
    PosBase* tPos = new PosBase();

    if (tPos && tPos->init(pos, isDebug)) {
        tPos->autorelease();
    }
    else {
        CC_SAFE_DELETE(tPos);
    }
    return tPos;
}
bool PosBase::init(Point pos) {
    bool bRet = false;

    do {
        setPos(pos);
        bRet = true;
    } while (0);

    return bRet;
}

bool PosBase::init(Point pos, bool isDebug) {
    bool bRet = false;
    do {
        CC_BREAK_IF(!init(pos));

        m_isDebug = isDebug;

        bRet = true;
    } while (0);
    return bRet;
}

void PosBase::setDebug(bool isDebug) {
    this->m_isDebug = isDebug;
}

bool PosBase::isClickMe(Point pos)
{
    return false;
}
