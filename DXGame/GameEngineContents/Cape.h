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
	static std::shared_ptr<class Cape> CapeDataManager;

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

	void SetImgName(CapeType _Type, std::string_view _Name)
	{
		Data[static_cast<int> (_Type)] = _Name;;
	}

	

	void Start();

protected:

private:
	std::vector<std::string> Data;
};

