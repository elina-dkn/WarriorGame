#ifndef BASELEVEL_H
#define BASELEVEL_H

#include "SpriteSheet.h"
#include "Renderer.h"
#include "Timing.h"
#include "TTFont.h"
class BaseLevel : public Resource
{
public:
	BaseLevel();
	virtual ~BaseLevel();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	virtual void Update() = 0;


private:

	float m_gameTime;
	Renderer* r;
	Timing* t;
	TTFont* font;

};

#endif