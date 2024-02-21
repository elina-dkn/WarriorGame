#ifndef LEVEL_1_H
#define LEVEL_1_H

#include "BaseLevel.h"

class Level_1 : public BaseLevel
{
public:
	Level_1();
	virtual ~Level_1();

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
	vector<int> m_speeds;


	Renderer* r;
	Timing* t;
	TTFont* font;


};

#endif
