#pragma once
#include "ContentObject.h"

// Ό³Έν :
class UI : public ContentObject
{
public:
	// constrcuter destructer
	UI();
	~UI();

	// delete Function
	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;

	virtual void UIOn() {}

protected:

private:

};

