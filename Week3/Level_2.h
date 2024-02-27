#ifndef LEVEL_2_H
#define LEVEL_2_H

#include "BaseLevel.h"

class Level_2 : public BaseLevel
{
public:
	Level_2();
	virtual ~Level_2();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void Update() override;
	bool IsPlaying() { return m_status; }

	void RenderLabels();
	void RenderWarriors();



private:
	float m_gameTime;
	bool m_status;
	bool m_saved;
	float m_timer;
	SpriteSheet* m_warrior;
	vector<SpriteSheet*> m_warriors;
	SpriteSheet* m_rock;
	vector<SpriteSheet*> m_rocks;
	vector<int> m_speeds;
	vector<int> m_rockSpeeds;
	vector<bool> m_dead;

	Renderer* r;
	Timing* t;
	TTFont* font;


};

#endif
