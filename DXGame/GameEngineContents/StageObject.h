#pragma once
#include "ContentObject.h"
//����


class StageObject : public ContentObject
{
public:
	// constrcuter destructer
	StageObject();
	~StageObject();

	// delete Function
	StageObject(const StageObject& _Other) = delete;
	StageObject(StageObject&& _Other) noexcept = delete;
	StageObject& operator=(const StageObject& _Other) = delete;
	StageObject& operator=(StageObject&& _Other) noexcept = delete;


	

protected:
	void Start() override;
	void Update(float _Delta) override;

	//std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //�⺻ ������
	std::shared_ptr<GameEngineCollision> MainCollision;


private:

};

