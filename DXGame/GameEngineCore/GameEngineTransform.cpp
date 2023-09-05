#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
{
}

GameEngineTransform::~GameEngineTransform() 
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatrix;
	}



	// TransData.WorldMatrix.ArrVector[3]

	// ���� ũ��
	// ���� ȸ��
	// ���� ��ġ
	// TransData.WorldMatrix

	// ���� ũ��
	// ���� ȸ��
	// ���� ��ġ
	// TransData.WorldMatrix

	// TransData.WorldMatrix<= ���ο��� 
	// TransData.WorldMatrix

	// �����̶� ���带 ��������� �����.



	// ColData.AABB

	CalChilds();
}

void GameEngineTransform::CalculationViewAndProjection(const TransformData& _Transform)
{
	CalculationViewAndProjection(_Transform.ViewMatrix, _Transform.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::CalChilds()
{
	if (0 == Childs.size())
	{
		return;
	}

	for (GameEngineTransform* Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}

bool GameEngineTransform::Collision(const CollisionParameter& _Data)
{
	DirectX::BoundingSphere SPHERE;
	DirectX::BoundingBox AABB;
	DirectX::BoundingOrientedBox OBB;

	//SPHERE.Center;
	//SPHERE.Radius;

	//AABB.Center;
	//AABB.Extents;

	bool Check = SPHERE.Intersects(AABB);

	return true;
}