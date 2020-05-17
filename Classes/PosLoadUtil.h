/*
    文件名：    PosLoadUtil.h
    描　述：    坐标对象加载工具
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

    创建日期：   2013.03.23
*/
#ifndef _PosLoadUtil_H_
#define _PosLoadUtil_H_

#include "cocos2d.h"
#include "EnumPosType.h"
USING_NS_CC;

class PosBase;
class PosLoadUtil : public Node {
public:
	static PosLoadUtil* getInstance();
	virtual bool init();

	/* 
		根据坐标类型从plist配置文件中读取坐标对象 
		sFilePath：配置文件路径
		enPosType：坐标对象类型
		container：存放坐标对象的容器
		iLevel：如果存在container，该参数表示坐标对象在容器中的层次
		isDebug：是否开启调试模式
	*/
	Vector<PosBase*> loadPosWithFile(
		const char* sFilePath, 
        EnumPosType enPosType,
		Node* container, 
		int iLevel, 
		bool isDebug);
private:
	static PosLoadUtil* m_posLoadUtil;
};

#endif