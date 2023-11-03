#pragma once

enum class CapeType
{
	Katana,
	EvilHands,
	Hammer,
	EvilBirds,
	Tornado,
	Fire,
	Meteor,
	None,
	Max,
};


class CapeData
{
	std::string ImgName;

};

// Ό³Έν :
class Cape
{
	friend class Player;
public:
	// constrcuter destructer
	Cape();
	~Cape();

	// delete Function
	Cape(const Cape& _Other) = delete;
	Cape(Cape&& _Other) noexcept = delete;
	Cape& operator=(const Cape& _Other) = delete;
	Cape& operator=(Cape&& _Other) noexcept = delete;

	std::string_view GetImgName(CapeType _Type)
	{
		return Data[static_cast<int> (_Type)];
	}

	static std::shared_ptr<class Cape> CapeDataManager;

protected:

private:
	std::vector<std::string> Data;
};

