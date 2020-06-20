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

##### 在LongRange的attack函数中获取子弹的信息（伤害，暴击率，子弹速度，子弹射出的方向等），使用MoveBy完成发射子弹的动作，提供碰撞检测函数，在TollgateScene中进行碰撞检测。

#### Bullet派生类

##### ExplosiveBullet类使用粒子特效作为爆炸效果，利用成员变量与回调函数实现在一定时间内的范围伤害。TrackBullet通过update函数实现子弹跟踪。

