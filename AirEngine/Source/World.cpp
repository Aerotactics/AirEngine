#include "World.h"

#include "AirEngine.h"
#include "GameObject.h"
#include "Texture.h"
#include "Window.h"
#include "DefaultComponents.h"

bool World::Init(XMLElement* pElement)
{
	const char* pImage = nullptr;
	pElement->QueryStringAttribute("background", &pImage);

	m_pTexture = static_cast<Texture*>(AirEngine::GetResourceManager()->Load(pImage));
	if(!m_pTexture)
		return false;
	return true;
}

void World::Update()
{
	//THIS SHOULD BE IN COLLISION CODE
	//- Get which partitions they overlap
	/*
	for (const auto& object : objects)
	{
		IComponent* pComponent = object->GetComponent("TransformComponent");
		if(!pComponent)
			continue;

		Vector2<float> position = static_cast<TransformComponent*>(pComponent)->GetPosition();
		
		pComponent = object->GetComponent("SpriteComponent");
		if(!pComponent)
			continue;
		
		Vector2<float> size = static_cast<SpriteComponent*>(pComponent)->GetSize();
		
		size_t index[4];
		index[0] = int(position.x / kPartitionWidthSize);
		index[1] = int(position.y / kPartitionHeightSize);
		index[2] = int(position.x + size.x / kPartitionWidthSize);
		index[3] = int(position.y + size.y / kPartitionHeightSize);
		
		for (size_t i = 0; i < 4; ++i)
		{
			// Dont index if out of bounds
			if(index[i] >= kPartitionWidth * kPartitionHeight)
				continue;

			std::vector<GameObject*>& partitionObjects = m_partitions[index[i]].objects;
			if(auto it = std::find(partitionObjects.begin(), partitionObjects.end(), object); it == partitionObjects.end())
				partitionObjects.push_back(object);
		}
	}
	
	//- loop through each partition and collide
	for (auto& partition : m_partitions)
	{
		if (partition.objects.size() < 2)
		{
			partition.objects.clear();
			continue;
		}

		for (size_t i = 0; i < partition.objects.size() - 1; ++i)
		{
			for (size_t j = i + 1; j < partition.objects.size(); ++j)
			{
				if(i == j)
					continue;

				static_cast<CollisionComponent*>(partition.objects[i]->GetComponent("CollisionComponent"))->IsColliding(partition.objects[j]);
			}
		}

		partition.objects.clear();
	}
	*/
}

void World::Draw(Window* pWindow)
{
	if(m_pTexture)
		m_pTexture->Draw(pWindow);
}
