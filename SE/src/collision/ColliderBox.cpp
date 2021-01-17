#include "ColliderBox.h"
#include "src/graphics/window.h"
#include "glm.hpp"

#include <iostream>
namespace se { namespace collision {

	ColliderBox::ColliderBox(float width, float height, float posX, float posY)
		: m_Width(width), m_Height(height)
	{
		m_Min.x += posX - width / 2;
		m_Min.y += posY - height / 2;

		m_Max.x += posX + width / 2;
		m_Max.y += posY + height / 2;
	}

	void ColliderBox::AddCollider(std::vector<ColliderBox*> &colliderContenedor)
	{
		colliderContenedor.push_back(this);
	}

	bool IsColliding(std::vector<ColliderBox*> &colliderContenedor, ColliderBox& entityCollider)
	{
		for(int i = 0; i < colliderContenedor.size(); i++)
		{
			bool collisionX = colliderContenedor[i]->m_Min.x + colliderContenedor[i]->m_Width >= entityCollider.m_Min.x && entityCollider.m_Min.x + entityCollider.m_Width >= colliderContenedor[i]->m_Min.x;
			bool collisionY = colliderContenedor[i]->m_Min.y + colliderContenedor[i]->m_Height >= entityCollider.m_Min.y && entityCollider.m_Min.y + entityCollider.m_Height >= colliderContenedor[i]->m_Min.y;

			if(collisionX && collisionY == true)
			{
				return true;
			}
		}

		return false;
	}

	bool IsGointToCollide(std::vector<ColliderBox*> &colliderContenedor, ColliderBox& entityCollider, float move)
	{
		for(int i = 0; i < colliderContenedor.size(); i++)
		{
			bool collisionX = colliderContenedor[i]->m_Min.x + colliderContenedor[i]->m_Width >= entityCollider.m_Min.x && entityCollider.m_Min.x + entityCollider.m_Width - move >= colliderContenedor[i]->m_Min.x;
			bool collisionY = colliderContenedor[i]->m_Min.y + colliderContenedor[i]->m_Height >= entityCollider.m_Min.y && entityCollider.m_Min.y + entityCollider.m_Height - move >= colliderContenedor[i]->m_Min.y;

			if(collisionX && collisionY == true)
			{
				return true;
			}
		}

		return false;
	}

	void ActivateCollition(std::vector<ColliderBox*> &colliderContenedor, ColliderBox& entityCollider, graphics::Shader* shaderContenedor[], int contenedorLength, int shaderLength)
	{
		for(int i = 0; i < contenedorLength; i++)
		{
			//Left
			if(entityCollider.m_Min.x + entityCollider.m_Width >= colliderContenedor[i]->m_Min.x && entityCollider.m_Min.x <= colliderContenedor[i]->m_Min.x)
			{
				float distanceSeparate = entityCollider.m_Width / 2 - colliderContenedor[i]->m_Min.x;
				for(int i = 0; i < shaderLength; i++)
				{
					//shadercolliderContenedor[i]->SetPos(glm::vec3(shadercolliderContenedor[i]->m_ActualXPos + distanceSeparate, shadercolliderContenedor[i]->m_ActualYPos, 0));

				}
				for(int i = 0; i < contenedorLength; i++)
				{
					colliderContenedor[i]->m_Min.x += distanceSeparate;
					colliderContenedor[i]->m_Max.x += distanceSeparate;
				}
			}
			//Right
			//if(colliderContenedor[i]->m_Min.x + colliderContenedor[i]->m_Width >= entityCollider.m_Min.x && entityCollider.m_Min.x >= colliderContenedor[i]->m_Min.x )
			//{
			//	float distanceSeparate = colliderContenedor[i]->m_Min.x + colliderContenedor[i]->m_Width - entityCollider.m_Min.x;
			//	for(int i = 0; i < shaderLength; i++)
			//	{
			//		shadercolliderContenedor[i]->SetPos(glm::vec3(shadercolliderContenedor[i]->m_ActualXPos - distanceSeparate, shadercolliderContenedor[i]->m_ActualYPos, 0));

			//	}
			//	for(int i = 0; i < contenedorLength; i++)
			//	{
			//		colliderContenedor[i]->m_Min.x -= distanceSeparate;
			//		colliderContenedor[i]->m_Max.x -= distanceSeparate;
			//	}
			//}
			////Bottom
			//if(entityCollider.m_Min.y + entityCollider.m_Height >= colliderContenedor[i]->m_Min.y && entityCollider.m_Min.y >= colliderContenedor[i]->m_Min.y)
			//{
			//	std::cout << "Bottom" << std::endl;
			//	float distanceSeparate = entityCollider.m_Min.y + entityCollider.m_Height - colliderContenedor[i]->m_Min.y;
			//	for(int i = 0; i < shaderLength; i++)
			//	{
			//		shadercolliderContenedor[i]->SetPos(glm::vec3(shadercolliderContenedor[i]->m_ActualXPos, shadercolliderContenedor[i]->m_ActualYPos + distanceSeparate, 0));

			//	}
			//	for(int i = 0; i < contenedorLength; i++)
			//	{
			//		colliderContenedor[i]->m_Min.y += distanceSeparate;
			//		colliderContenedor[i]->m_Max.y += distanceSeparate;
			//	}
			//}
		}
	}
	
	void MoveBoxsColliderUp(std::vector<ColliderBox*> &colliderContenedor, float y)
	{
		for(int i = 0; i < colliderContenedor.size(); i++)
		{
			colliderContenedor[i]->m_Min.y -= y;
			colliderContenedor[i]->m_Max.y -= y;
		}
	}

	void MoveBoxsColliderDown(std::vector<ColliderBox*> &colliderContenedor, float y)
	{
		for(int i = 0; i < colliderContenedor.size(); i++)
		{
			colliderContenedor[i]->m_Min.y += y;
			colliderContenedor[i]->m_Max.y += y;
		}
	}

	void MoveBoxsColliderRight(std::vector<ColliderBox*> &colliderContenedor, float x)
	{
		for(int i = 0; i < colliderContenedor.size(); i++)
		{
			colliderContenedor[i]->m_Min.x -= x;
			colliderContenedor[i]->m_Max.x -= x;
		}
	}

	void MoveBoxsColliderLeft(std::vector<ColliderBox*> &colliderContenedor, float x)
	{
		for(int i = 0; i < colliderContenedor.size(); i++)
		{
			colliderContenedor[i]->m_Min.x += x;
			colliderContenedor[i]->m_Max.x += x;
		}
	}

}}