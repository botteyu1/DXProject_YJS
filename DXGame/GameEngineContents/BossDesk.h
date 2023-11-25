#pragma once
#include "StageObject.h"
//Ό³Έν



class BossDesk : public StageObject
{
	
public:
	// constrcuter destructer
	BossDesk();
	~BossDesk();

	// delete Function
	BossDesk(const BossDesk& _Other) = delete;
	BossDesk(BossDesk&& _Other) noexcept = delete;
	BossDesk& operator=(const BossDesk& _Other) = delete;
	BossDesk& operator=(BossDesk&& _Other) noexcept = delete;

	void ChangeDeskAnimation(std::string_view _str);

protected:	
	void Start() override;
		 void Update(float _Delta) override;

private:

};

