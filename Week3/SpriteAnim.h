#ifndef SPRITEANIM_H
#define SPRITEANIM_H

#include "Resource.h"

class SpriteAnim : Resource
{
public:
	SpriteAnim();
	virtual ~SpriteAnim();

	short GetClipCurrent() { return (short)m_clipCurrent; }

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	
	void ClearMemory();
	void Create(short _clipStart, short _clipCount, float _clipSpeed, int m_speed);
	void Update(float _deltaTime);
	void UpdateFinal(float _deltaTime);


	static ObjectPool<SpriteAnim>* Pool;

private:
	short m_clipStart;
	short m_clipCount;
	short m_clipEnd;
	float m_clipCurrent;
	float m_clipSpeed;
	int m_speed;
};

#endif