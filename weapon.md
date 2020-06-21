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

