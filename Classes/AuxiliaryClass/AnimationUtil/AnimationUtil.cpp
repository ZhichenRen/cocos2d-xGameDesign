#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"

Animation* AnimationUtil::createWithSingleFrameName(const char* address, const char* name, float delay, int iLoops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	int index = 1;
	do
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%s%d.png", address, name, index++));

		if (frame == NULL)
			break;

		frameVec.pushBack(frame);
	} while (true);
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);

	return animation;

}

Animation* AnimationUtil::createWithFrameNameAndNum(const char* address, const char* name, int iNum, float delay, int iLoops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	for (int i = 1; i <= iNum; i++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%s%d.png", address, name, i));

		if (frame == NULL)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);

	return animation;
}

Animation* AnimationUtil::createWithFrameNameAndNumUsingPlist(const char* address, const char* name, int iNum, float delay, int iLoops)
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(StringUtils::format("%s%s.plist", address, name),
		StringUtils::format("%s%s.png", address, name));

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	for (int i = 1; i <= iNum; i++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, i));

		if (frame == NULL)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);

	return animation;
}