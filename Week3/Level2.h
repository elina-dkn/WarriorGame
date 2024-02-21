#ifndef LEVEL2_H
#define LEVEL2_H

#include "Level.h"

class Level2 : public Level
{
public:
	Level2();
	virtual ~Level2();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void Render() override;
	SpriteSheet* GetWarrior() { return m_warrior; }
	bool IsPlaying() { return m_status; }



private:
	float m_gameTime;
	bool m_status;
	SpriteSheet* m_warrior;
	Renderer* r;
	Timing* t;
	TTFont* font;


};

#endif
