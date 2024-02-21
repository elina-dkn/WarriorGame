#ifndef LEVEL_H
#define LEVEL_H

#include "SpriteSheet.h"
class Level : public Resource
{
public:
	Level();
	virtual ~Level();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	virtual void Render();

	

private:
	float m_gameTime;
	SpriteSheet* m_warrior;
	SpriteSheet* m_rock;

};

#endif