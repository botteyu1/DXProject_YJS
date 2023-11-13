#pragma once

#include "UI.h"


class SelectStageUI : public UI
{
public:
	// constrcuter destructer
	SelectStageUI();
	~SelectStageUI();

	// delete Function
	SelectStageUI(const SelectStageUI& _Other) = delete;
	SelectStageUI(SelectStageUI&& _Other) noexcept = delete;
	SelectStageUI& operator=(const SelectStageUI& _Other) = delete;
	SelectStageUI& operator=(SelectStageUI&& _Other) noexcept = delete;

	void SelectStageUIStart(int _Type);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

