/*
    文件名：    TollgateScene.h
    描　述：    关卡场景
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)
*/
#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
using namespace cocos2d;

class TollgateScene : public Layer {
public:
    static Scene* createScene();
    CREATE_FUNC(TollgateScene);
    virtual bool init();

};
#endif