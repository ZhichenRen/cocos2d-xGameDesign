#ifndef _PosBase_H_
#define _PosBase_H_

#include "cocos2d.h"
USING_NS_CC;

class PosBase : public Layer {
public:
    PosBase();
    ~PosBase();

    static PosBase* create(Point pos);
    static PosBase* create(Point pos, bool isDebug);
    bool init(Point pos);
    bool init(Point pos, bool isDebug);

    CC_SYNTHESIZE(Point, m_pos, Pos);

    virtual bool isClickMe(Point pos);   /* 判断坐标是否进入范围 */

    /* 开启或关闭调试模式 */
    void setDebug(bool isDebug);    
protected:
    bool m_isDebug;    /* 是否为调试状态 */
};

#endif