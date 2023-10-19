#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BookOfTheDead : public GameEngineActor
{
public:
	// constrcuter destructer
	BookOfTheDead();
	~BookOfTheDead();

	// delete Function
	BookOfTheDead(const BookOfTheDead& _Other) = delete;
	BookOfTheDead(BookOfTheDead&& _Other) noexcept = delete;
	BookOfTheDead& operator=(const BookOfTheDead& _Other) = delete;
	BookOfTheDead& operator=(BookOfTheDead&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _Delta) override;

private:


};

