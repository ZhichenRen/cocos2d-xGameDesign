# SoulKnight项目说明文档

> 同济大学软件工程荣誉课2020年高级语言程序设计2课程期末大项目

## 项目信息

- 项目选题：**元气骑士**

- 项目成员：

  - 1850061 阮辰伟
  - 1850091 任致辰
  - 1851009 沈益立
  - 1852612 周涵嵩

- 项目Github地址：https://github.com/ZhichenRen/cocos2d-xGameDesign


- 选用引擎：**Cocos2d-x 3.17.2**

- 辅助软件：Tiled Map Editor 1.0.3、Adobe Photoshop CC 2018、Cocos Studio

- 支持平台：Windows

- 小组分工：

  |  姓名  |        分工        | 贡献比例 |
  | :----: | :----------------: | :------: |
  | 阮辰伟 |        人物        |   25%    |
  | 任致辰 | 武器、部分UI与场景 |   25%    |
  | 沈益立 |        怪物        |   25%    |
  | 周涵嵩 | 地图、部分UI与场景 |   25%    |

- 项目时间线：
  2020.5.15 完成远程武器基类
  2020.5.18 完成近战武器基类
  2020.5.20 完成两张简单地图，实现地图类
  2020.5.22 完成简单暂停功能，实现随机地图类
  2020.5.23 增加基础战斗UI
  2020.5.27 完成怪物类基本功能
  2020.6.1 完成人物类基本功能
  2020.6.4 完成暂停界面
  2020.6.5 增加怪物类生成新怪物功能，实现基本碰撞检测
  2020.6.6 地图中增加商店与宝箱
  2020.6.9 增加存储数据用的单例类GameData
  2020.6.10 完成药物
  2020.6.13 完成人物选择界面，增加牧师
  2020.6.14 完成死亡界面
  2020.6.15 地图增加雕像
  2020.6.18 增加作弊功能
  2020.6.20 增加骑士，增加通关场景，增加Boss

- 评分项完成度

  - 基础功能
    - [x] 游戏开始界⾯、背景⾳乐、⾳量控制、暂停及恢复功能、退出功能 
    - [x] 键盘控制 
    - [x] ⾄少2类武器，包括不限于枪械类武器、近战武器；每类武器⾄少包括2种具体的武器，如枪械类武器包括不限于⼀次发射单发⼦弹的枪械、⼀次发射多发⼦弹枪械等，近战武器包括不限于可快速攻击的⼩范围武器、攻击速度较慢的⼤范围武器等 
    - [x] ⾄少2种普通敌⼈类型，包括不限于近战型敌⼈和远程型敌⼈；每类普通敌⼈⾄少包括2类具体的敌⼈
    - [x]  ⾄少两种道具，包括不限于恢复⽣命、增加护甲的道具，可以通过击败敌⼈获取
    - [x] 宝箱机制，开启可获得新武器或者道具等
    - [x] 安全地图与探险地图，安全地图指进⼊关卡前的地图，可以查看武器信息、敌⼈信息等，探险地图指关卡地图
    - [x] 关卡中主角死亡，探险终⽌并返回安全地图
    - [x] ⾄少包括2个关卡
  - 基础功能以外的可选功能
    - [x] 每次进⼊即使相同关卡也会有不同的游戏地图、敌⼈、道具等（Roguelike!）
    - [x] 游戏⼩地图，可以显示已经探索过的地图，可以参考元⽓骑⼠的⼩地图
    - [x] 多个可选主角，每个主⻆拥有不同的属性加成（近战攻击速度提升、枪械⼦弹速度提升、⽣命值增加等）或者主动技能（移速增加、翻滚躲⼦弹）
    - [x] buﬀ机制，主角可以获得多种buﬀ，包括不限于移速增加、⽆敌等
    - [x] 武器升级机制，在探险中获得两把一样的武器时可以升级成更强大的武器
    - [x] ⾦币机制，击败敌⼈可以获取⾦币
      - [x] 探险地图中的⽼爷爷系统，可以在关卡中购买/获赠礼物，如武器/道具/buﬀ等
    - [x] 特殊地形，包括不限于可被破坏区域（如⽊墙）、移速受限区域（如沼泽）、通过受伤区域（如岩 浆）、机关地形（如时不时出现的地刺）等
    - [x] BOSS型敌⼈
    - [x] 秘籍，⼗倍攻击⼒、⽆敌、补充法力值、消除木箱、获取100金币
  - 使用的C++特性
    - [x] STL 容器，如 std::vector ， std::map 等；
    - [x] 迭代器；
    - [x] 类和多态；
    - [x] 函数重载；
    - [x] C++11 或以上功能。
  - 必须达成的代码规范
  	- [x] 代码在缩进、命名等⽅⾯基本遵循了统⼀和⼀致的⻛格（如 Google C++ Style）；
  	- [x] 正确、合理地使⽤了 C++ ⻛格类型转换（如 static_cast 、 dynamic_cast ）且没有使⽤ C⻛格的强制转换；
  	- [x] 尽可能地使⽤了 const 和引⽤；
  	- [x] 类的设计合理规范。
  - 其他亮点
    - [x] 游戏还原度高，画面精致
      - 使用了部分游戏原始素材，以及高质量武器素材包
    - [x] PLIST文件的使用
      - 利用PLIST文件存储游戏文字，避免了中文乱码
    - [x] 单例模式的应用
      - 利用单例模式设计了GameData类，储存游戏数据，避免了全局变量。

- 代码亮点

  1. PLIST文件的使用

  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
  ```
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>ShopFirstMeet</key>
	<string>这位勇士，您要花费20金币购买一把神秘武器吗？</string>
	<key>ShopLackMoney</key>
	<string>您的金币不足，请下次再来！</string>
	<key>ShopEnoughMoney</key>
	<string>谢谢惠顾，您会更加强大！</string>
	<key>StatueFirstMeet</key>
	<string>供奉此雕像 15</string>
	<key>StatueLackMoney</key>
	<string>金币不足！</string>
	<key>StatueEnoughMoney</key>
	<string>属性提升了！</string>
	<key>GreedyCheat</key>
	<string>作弊成功！金币+100</string>
	<key>SlaughterCheat</key>
	<string>颤抖着滚开吧杂鱼们！</string>
	<key>WoodWallCheat</key>
	<string>我最讨厌的就是木墙了！</string>
	<key>BossAppearence</key>
	<string>是我的晚餐来了吗？</string>
	<key>BossDeath</key>
	<string>地狱之门正在徐徐打开……</string>
</dict>
</plist>
  ```

- 踩坑记录

  播放背景音乐所需要用的`SimpleAudioEngine`中调节音量大小的函数` setBackgroundMusicVolume`是空函数，若要调节背景音乐的大小需要自行补全代码。

  cocostudio控件可能出现偏移现象，原因不明，通过手动调整位置解决

  地图与怪物管理器对接时，TiledMap的上下与笛卡尔坐标系的上下正好相反。

  

## 具体功能及实现

## 人物介绍

#### 基类Player类与Controller类。Player类中派生出了Ranger类，Priest类与Knight类，用于生成不同人物（游侠，牧师，骑士）以及人物的技能，武器控制，基本属性（血量，护甲）等等。Controller类派生出了PlayerController，用于控制人物。

#### PlayerController类

##### 提供绑定人物功能（setPlayer），控制人物移动，技能释放以及换武器（registeControllerEvent）判断人物是否遇到障碍物（isEncounterBarriers），调节人物的站立动画与行走动画之间的关系（animateOperate）等等功能。其中的update函数还可以通过与Player类配合来调整当前人物的cd，护甲等参数，营造出人物cd，护甲自动回复的效果。

#### Player类

##### Player函数主要提供三类功能。

##### 1，基础参数的设置与调节，例如血量，护甲，人物朝向，人物是否死亡等等。

##### 2，人物技能系统，核心函数有三：skill()、skillDuration()与skillEnd()。

##### 3，武器系统，主要功能有武器的捡起、武器的切换、武器的使用与武器的升级。

#### 人物技能介绍

##### 游戏支持三种人物。

##### 1，Ranger，技能为朝一个方向滚动一定距离。

##### 2，Priest，技能为生成一个法阵，可以法阵上方右方角色恢复生命值。

##### 3，Knight，技能为生成一把与当前手中所持武器相同的武器，同时手持两把一样的武器进行攻击，持续一段时间。

#### 基础参数的设置与调节

##### 这个部分主要包含若干set以及get函数来获取、调节各种属性，例如：getiNowCD、setiNowCD、getiTotalCD、setiTotalCD。还有些函数来负责人物收到打击（hit）、人物耗蓝等特殊场景（mpDepletion）。此外，还有诸如setArmorCd、setiNowSkillDuration之类的函数，这类函数主要在PlayerController中的update调用。其功能是每次调用回复一定的数值，直到到了某一个数字时改变人物一个属性。例如setArmorCd函数就是当护甲没满时，每次调用让m_iArmorCd增加1，如果到了100就使得人物当前护甲增加1点。

#### 人物技能系统

##### 人物技能系统主要由skill()、skillDuration()与skillEnd()组成。skill在人物使用技能时调用，用于为技能的释放做准备，例如Ranger的skill负责生成滚动的动画以及滚动方向、Priest的skill负责生成法阵，Knight的skill负责生成第二把武器。skillDuration是技能持续中所调用的，负责在技能释放期间与技能进行联动。如Priest的skillDuration是控制如果人物在法阵中一定时间，就给人物回复生命值。skillEnd主要负责给进行技能所生成的对象做回收或者复原。如Ranger的skillEnd还原人物的滚动方向；Priest的skillEnd负责回收生成的法阵；Knight的skillEnd负责回收生成的第二把武器。

#### 人物武器系统

##### 人物武器系统的核心函数有setWeapon、chooseWeapon、 loadLongRangeListener、loadCloseWeaponListener、resetWeapon、determineWhichWeapon、changeWeapon、chooseAbondonWeapon与abandonWeapon。

##### setWeapon负责把拿到的武器以string的方式存储至m_weapons（一个array）当中，同时调整当前已经拥有的武器以及当前所持武器的序号（m_numWeapon），如果之前所拥有的武器中刚好出现了一把武器与此次拿到的武器一致（同名），便会把这个武器所对应序号的m_isUpgrate（一个array）设置为true。

##### chooseWeapon根据武器武器序号（m_numWeapon）与存储武器名字的m_weapons来create新的武器指针，同时通过loadLongRangeListener、loadCloseWeaponListener两个函数来加载监听器。如果是近战武器就赋值给m_close，如果是远程武器就给赋值给m_longRange。监视器所生成的值赋值给m_listener。与此同时，根据武器的序号（m_numWeapon）以及m_isUpgrate来判断该武器是否应该升级，如果该值为true的话则调用m_longRange/m_close的upgrate函数。 

##### resetWeapon函数用来remove  m_longRange或者m_close。同时remove  m_longRange或者m_close的m_listener。

##### determineWhichWeapon首先通过调用resetWeapon来清除原来的武器与监听器，再通过调用chooseWeapon生成武器。最后再设置武器的位置。

##### chooseAbondonWeapon与abandonWeapon构成了武器系统中的抛弃武器部分。chooseAbondonWeapon负责找到需要抛弃的武器，而abandonWeapon负责把该武器放到地图上，并且加入AdventureMapLayer的m_longRangeList与m_closeWeaponList中，方便从地图上捡起武器。

### 武器介绍

#### 基类Weapon类，派生出近战武器CloseWeapon类，远程武器LongRange类，LongRange类中使用Bullet类

#### Weapon类

##### 提供绑定地图功能（bindMap），伤害（set/getDamage）、射速（set/getAttackSpeed）、暴击率（set/getCritRate）的设置与获取，蓝耗（set/getPowerCost）的获取，武器名称（getWeaponName）获取，同时提供攻击（attack）、获取子弹（getBullet）、升级（upgrade）、是否为近战武器（isCloseWeapon）等虚函数供派生类改写，主要负责提供与玩家及怪物交互的接口。

#### CloseWeapon类

##### 重写weapon类的attack函数，isCloseWeapon函数（返回true），getBullet函数（返回空的vector），提供自己的碰撞检测函数

#### LongRange类

##### 重写weapon类的attack函数，增加调整武器角度的函数（setPositionByPos），根据当前鼠标位置调整武器朝向，getBullet函数返回当前武器所射出的所有子弹，在类内使用std::vector<Bullet*>保存。

#### LongRange派生类

##### 攻击模式特殊的武器会对attack函数进行重写，例如Shotgun类，在attack函数中根据一次射出的子弹数量与子弹之间的夹角生成多发子弹，RPG类使用特殊的ExplosiveBullet

#### Bullet类

##### 在LongRange的attack函数中获取子弹的信息（伤害，暴击率，子弹速度，子弹射出的方向等），使用MoveBy完成发射子弹的动作，提供碰撞检测函数，作为map的子节点，在TollgateScene中进行碰撞检测，子弹使用过后（击中怪物或障碍物），则设置成已使用，在LongRange的update函数中利用cocos内存管理机制进行回收

#### Bullet派生类

##### ExplosiveBullet类使用粒子特效作为爆炸效果，利用成员变量与回调函数实现在一定时间内的范围伤害。TrackBullet通过update函数实现子弹跟踪。

#### 碰撞检测

##### 在TollgateScene中的update函数中实现，遍历所有主角射出的子弹与怪物，调用子弹的碰撞检测函数进行判断，反之同理。子弹打到怪物或墙则会被标记已使用（ExplosiveBullet则是爆炸）。近战武器则在玩家攻击时（通过isAttackWithCloseWeapon函数获取是否正在攻击）遍历怪物/玩家进行碰撞检测。



### 怪物介绍

#### 怪物类

##### 实现功能：在怪物的房间完全随机地生成不同数量、不同位置、不同体型的怪物，怪物具有一定的走位能力和智能施法攻击能力，每个房间的怪物一共有3波，当这一波怪物完全死光将会生成下一波怪物。死亡的怪物周围会爆蓝、金币、蓝药、红药等道具。



##### 实现思路：建立一个怪物管理器，用`std::vector<Monster*> m_monsterList`作为储存怪物的容器，每次更新时通过遍历`m_monsterList`来对每个怪物进行操作。进入每个怪物房间，会先判断是否已经初始化怪物了，若无则会随机生成一系列怪物。未嘲讽的怪物会在地图上漫步，而如果主角与怪物距离过近或怪物受到伤害，则怪物会受到嘲讽，主动向主角位置走位，并且攻击主角。若在走位的方向上遇到了障碍物，怪物会自行寻找一个无障碍的方向进行走位。



#### 木墙类：

##### 实现功能：怪物房间内随机生成若干个可摧毁的木墙，生成木墙的位置是随机的，是角色和怪物无法直接穿越的地形，当木墙被击破则可以穿越。

##### 实现思路：在进入每个怪物房间时，也生成一系列木墙对象，用`std::vector<Monster*> m_woodWallList`作为储存木墙对象的容器。并且在生成的过程中，与`AdventureMapScene`中的瓦片地图交互，使之也不可穿越；木墙被摧毁后，瓦片地图中的记录也消失。

### 地图介绍

#### 随机冒险地图

##### 实现功能：在5×5的25宫格内选取中间位置为起始房间，随机向四个方向不断延伸，派生出总共7个房间，包括起点房间、怪物房间（普通怪物及boss）、商店房、宝箱房、雕像房（购买buff）、终点房（传送至下一关或者结束冒险）。

##### 实现思路：利用Tiled工具，编辑一个tmx瓦片地图，包含5×5共25个独立房间，然后通过随机生成算法，加上相应限制（如初始房间只有一条通路），从初始房间出发向随机四个方向生成路径，并通过瓦片编辑函数`TMXLayer::setTileGID(uint32_t gid, const Vec2& pos)`，将相应的坐标集合可视化为“走廊”,生成过程中，将指定房间标记为上述房间类型之一，在后面的函数中，通过添加子节点的方式，将商店（Shop类）、宝箱（Chest类）、雕像（Statue类）、传送门（portal精灵）加入地图中，并赋予其与玩家互动的功能。



#### 小地图

##### 实现功能：游戏进程中，在屏幕右上角生成一个游戏小地图，对玩家已探索的房间进行简化标记，其中玩家所在的房间为深灰色，玩家探索过的其他房间为浅灰色。

##### 实现思路：利用Tiled工具，编辑一个9×9大小的tmx瓦片地图，设置变量lastRoomCoord，记录玩家所处的上一个房间的坐标。在玩家移动的过程中，获取玩家的坐标，通过坐标变换函数`AdventureMapLayer::tileCoordFromPosition(Vec2 position)`以及`AdventureMapLayer::roomCoordFromPosition(Vec2 position)`，得出玩家所在房间的瓦片坐标，标记为深灰色，并通过过道瓦片连接玩家所在的房间和上一个房间，更新lastRoomCoord。

## SoulKnight 游戏文档

### 游戏简介

SoulKnight是一款单机地牢冒险rouguelike游戏。

### 基本操作

|            操作             |              效果              |
| :-------------------------: | :----------------------------: |
|        按下`WSAD`键         |   控制玩家上、下、左、右移动   |
|        点击鼠标左键         |     玩家向鼠标位置进行攻击     |
|         按下`ESC`键         |              暂停              |
|         按下空格键          |       释放所选人物的技能       |
|          按下`E`键          |           与场景互动           |
| 按下`Enter`键并点击鼠标左键 | 打开输入框，可输入指令进行作弊 |

### 武器属性

- 默认属性

| 武器名 |          定位          | 攻击  | 蓝耗 | 暴击率 | 攻速  |
| :----: | :--------------------: | :---: | :--: | :----: | ----- |
|  金剑  |        近战武器        |  15   |  0   |  0.2   | 0.2s  |
| 小手枪 |    初始远程单体武器    |   5   |  1   |  0.1   | 0.15s |
| 糖果枪 |      远程单体武器      |  10   |  3   |  0.3   | 0.12s |
| 霰弹枪 |      远程多发武器      |  5*4  |  5   |  0.1   | 0.2s  |
|  鲸爆  | 远程范围持续伤害型武器 | 5+2*n |  5   |   0    | 0.3s  |
|  石剑  |      初始近战武器      |  10   |  0   |  0.05  | 0.18s |

- 升级属性

- | 武器名 |          定位          | 攻击  | 蓝耗 | 暴击率 | 攻速  |
| :----: | :--------------------: | :---: | :--: | :----: | ----- |
  |  金剑  |        近战武器        |  25   |  0   |  0.3   | 0.18s |
  | 小手枪 |    初始远程单体武器    |   5   |  0   |  0.15  | 0.12s |
  | 糖果枪 |      远程单体武器      |  20   |  3   |  0.5   | 0.1s  |
  | 霰弹枪 |      远程多发武器      |  8*5  |  5   |  0.15  | 0.18s |
  |  鲸爆  | 远程范围持续伤害型武器 | 5+3*n |  4   |   0    | 0.25s |
  |  石剑  |      初始近战武器      |  18   |  0   |  0.1   | 0.15s |

### 怪物属性

|     名称     |          定位           | 体力 | 移速 | 攻速 |        伤害        |
| :----------: | :---------------------: | :--: | :--: | :--: | :----------------: |
|    史莱姆    |        远程低dps        |  10  | 0.2  | 2.0  |         1          |
|      猪      |        近战低dps        |  30  | 0.5  | 3.0  |         1          |
| 迷失的旅行者 |        近战高dps        |  25  | 1.5  | 1.5  |         3          |
|   部落酋长   |        远程高dps        |  30  | 0.8  | 1.5  |         2          |
|    可达鸭    | 远程高dps（子弹可追踪） |  20  | 0.5  | 3.0  |         3          |
|   邪恶法师   |       Boss型敌人        | 800  | 0.8  | 1.5  | 3 * 11（11发子弹） |





