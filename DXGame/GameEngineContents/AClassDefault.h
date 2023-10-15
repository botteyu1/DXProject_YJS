#pragma once

// Ό³Έν :
class AClassDefault
{
public:
	// constrcuter destructer
	AClassDefault();
	~AClassDefault();

	// delete Function
	AClassDefault(const AClassDefault& _Other) = delete;
	AClassDefault(AClassDefault&& _Other) noexcept = delete;
	AClassDefault& operator=(const AClassDefault& _Other) = delete;
	AClassDefault& operator=(AClassDefault&& _Other) noexcept = delete;

protected:

private:

};

