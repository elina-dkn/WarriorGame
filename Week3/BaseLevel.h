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

	virtual void Serialize(std::ostream& _stream);
	virtual void Deserialize(std::istream& _stream);
	virtual void ToString();
	virtual void AssignNonDefaultValues();
	virtual void Update() = 0;


private:


};

#endif