# Home v1.0

函数:HomeScene::createScene();

功能:生成游戏初始界面，包括设置按钮，开始游戏按钮和退出游戏按钮。



# Setting v1.0

函数:SettingScene::createScene();

功能:生成一个游戏设置菜单，包括按钮和滑动条控制的音量调节部分。

相应头文件:SettingScene.h

实现文件:SettingScene.cpp



# SafeMap v1.0

##安全地图的生成

函数:SafeMapScene::createScene();

功能：生成一个地图场景，包括传送门（开始冒险）、怪物图鉴（待开发）、武器图鉴（待开发）。

相应头文件:SafeMapScene.h

实现文件:SafeMapScene.cpp



# AdventureMap   v1.0

##冒险地图的生成

函数:AdventureMapScene::createScene();

功能：生成一个包含七个房间的随机地图场景，地图中随机添加障碍物，并对相应的起始房间，冒险房间（怪物房），奖励房间（宝箱房），特殊房间（商店、BUFF），终点房间（传送房）进行标记。（功能房间暂未完成）

相应头文件:AdventureMapScene.h

实现文件:AdventureMapScene.h,RandomMap.cpp

###地图成员

cocos2d::TMXTiledMap* m_tileMap;瓦片地图成员

cocos2d::TMXTiledMap* m_collidable,m_ground,m_wall,m_road;相应地图组成

cocos2d::Sprite* m_player;绑定玩家的精灵成员

...待开发

###随机地图方法

函数:AdventureMapLayer::createRandomMap();

功能：根据源地图文件为AdventureMapLayer成员m_tileMap绑定一个生成的随机地图

###小地图组件

...待开发