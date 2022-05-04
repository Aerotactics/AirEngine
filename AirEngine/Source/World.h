#pragma once

#include <vector>
#include "TinyXML/tinyxml2.h"

static constexpr size_t kWorldWidth = 10'000;
static constexpr size_t kWorldHeight = 10'000;

// There's a chance with smaller partitions for objects
//	to be ignored when they are actaully overlapping.
static constexpr size_t kPartitionWidth = 10;
static constexpr size_t kPartitionHeight = 10;

static constexpr float kPartitionWidthSize = float(kWorldWidth) / float(kPartitionWidth);
static constexpr float kPartitionHeightSize = float(kWorldHeight) / float(kPartitionHeight);

using namespace tinyxml2;

class GameObject;
class Texture;
class Window;

struct Partition
{
	std::vector<GameObject*> objects;
};

class World
{
private:
	std::vector<Partition> m_partitions;
	Texture* m_pTexture;

public:
	World()
		: m_partitions(kPartitionWidth * kPartitionHeight)
		, m_pTexture(nullptr)
	{}

	bool Init(XMLElement* pElement);
	void Update();
	void Draw(Window* pWindow);
};
