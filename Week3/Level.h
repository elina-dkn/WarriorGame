#ifndef LEVEL_H
#define LEVEL_H

#include "SpriteSheet.h"
#include "Renderer.h"
#include "Timing.h"
#include "TTFont.h"
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
	bool IsPlaying() { return m_status; }
	void RenderWarriors();

	float GetLastTime() { return m_gameTime; }
	void SetGameTime(float _time) { m_gameTime = _time; }
	

private:
	
	float m_gameTime;
	bool m_status;
	vector<SpriteSheet*> m_warriors;

	vector<SpriteSheet*> m_rocks;
	vector<int> m_speeds;
	SpriteSheet* m_warrior;

	SpriteSheet* m_rock;
	Renderer* r;
	Timing* t;
	TTFont* font;

};

#endif