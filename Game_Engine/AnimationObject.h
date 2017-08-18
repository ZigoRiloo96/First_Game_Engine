#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "agdlib.h"

using namespace sf;
using namespace std;

class AnimationObject {

private:
	bool m_isPlay;
	Direction m_Direction;
	int m_Frames;
	int m_Iter;
	Frame m_Frame;

	Vector2i m_Position;
	Texture m_Texture;
	IntRect m_TextureRect;
	Sprite m_Sprite;

public:
	AnimationObject(string img, Vector2i pos, Frame frame, int frames, Direction d);
	AnimationObject(string img, Vector2i pos, IntRect textureRect, int frames, Direction d);
	AnimationObject(Texture tex, Vector2i pos, IntRect textureRect, int frames, Direction d);
	~AnimationObject();

	AnimationObject(const AnimationObject& rhs);

	const Sprite& getSprite();
	const bool& isPlaying();

	void Play();
	void Stop();

	void Update(float dt);
};

