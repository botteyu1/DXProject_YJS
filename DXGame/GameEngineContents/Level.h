#pragma once
#include <GameEngineCore/GameEngineLevel.h>


struct ScreenShake{
	float duration; // 흔들림이 지속되는 시간
	float magnitude; // 흔들림의 세기
	float elapsed; // 흔들림이 지속되는 시간 타이머
	float frequency = 2.0f; // 흔들림의 빈도

};

// 설명 :
class Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Level();
	~Level();

	// delete Function
	Level(const Level& _Other) = delete;
	Level(Level&& _Other) noexcept = delete;
	Level& operator=(const Level& _Other) = delete;
	Level& operator=(Level&& _Other) noexcept = delete;

	std::shared_ptr<class Map> GetMap()
	{
		return MapPtr;
	}
	void SetMap(std::shared_ptr<Map> _MapPtr)
	{
		MapPtr = _MapPtr;
	}

	std::shared_ptr<class FX> GetFXActor()
	{
		return FXActor;
	}

	std::shared_ptr<class Shader> GetShaderActor()
	{
		return ShaderActor;
	}

	std::shared_ptr<class CurseUI> GetCurseUI()
	{
		return CurseUIPtr;
	}


	std::shared_ptr<class ContentObject> AddActor(ActorType _Type, float4 _Pos,float4 _Rotation, bool _Flip, bool _Debug);

	void Serializer(GameEngineSerializer& _Data) ;
	void DeSerializer(GameEngineSerializer& _Data, bool _Debug);

	void SerializerObject(GameEngineSerializer& _Data, std::vector<std::shared_ptr<ContentObject>> _vector);
	std::shared_ptr<ContentObject> CopyObject(std::shared_ptr<ContentObject> _Object);


	void LevelChangerStart(std::string_view _Name);
	

	void ClearContentsObject();

	bool OtherWindow = false;
	bool PaperWallValue = false;  //기믹용 페이퍼 벽이 생길때 체크

	void StartScreenShake(float duration, float magnitude, float frequency) {
		screenShake.duration = duration;
		screenShake.magnitude = magnitude;
		screenShake.frequency = frequency;
		screenShake.elapsed = 0.0f;
	}

protected:
	std::shared_ptr<FX> FXActor;
	std::shared_ptr<class Shader> ShaderActor = nullptr;
	std::vector< std::shared_ptr<class PaperWall>> PaperWallvec;
	std::vector<std::shared_ptr<class Enemy>> GimicEnemyvec;
	std::vector< std::shared_ptr<class Enemy>> Gimic2Enemyvec;
	std::shared_ptr<class LevelChanger> LevelChangerPtr = nullptr;
	std::shared_ptr<class CurseUI> CurseUIPtr = nullptr;
	std::shared_ptr<class MovieBar> MovieBarPtr = nullptr;


	void Start()  override;
	void Update(float _Delta);
	void UpdateScreenShake(float _deltaTime);

	ScreenShake screenShake;

	float4 PrevShackeMovePos = float4::ZERO;
	float4 PrevShackeRotationPos = float4::ZERO;

	//class GameEngineSoundPlayer Bgm;

private:

	std::shared_ptr<Map> MapPtr = nullptr;
};

