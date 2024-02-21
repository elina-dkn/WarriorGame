#ifndef LEVEL1_H
#define LEVEL1_H

#include "Level.h"

class Level1 : public Level
{
public:
	Level1();
	virtual ~Level1();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void Render() override;
	SpriteSheet* GetWarrior() { return m_warrior; }



private:
	float m_gameTime;
	SpriteSheet* m_warrior;
	

};

#endif
