#include "PreCompile.h"
#include "Bullet.h"

Bullet::Bullet() 
{
}

Bullet::~Bullet()
{
}



void Bullet::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\\Sprite\\Bullet");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());

	}
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy_Attack);
	

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 0.5f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);


}

void Bullet::Init(BulletType _Type,float4 _Pos, float _Damage,  float4 _Dir, float _Power)
{
	
	switch (_Type)
	{
		case BulletType::Fire:
		{
			MainSpriteRenderer->CreateAnimation("Fire", "Fire", 0.0666f, -1, -1, true);
			MainSpriteRenderer->ChangeAnimation("Fire");

			AttackCollision->Transform.SetLocalPosition({0.0f,0.0f});
			AttackCollision->Transform.SetLocalScale({ 100.0f,50.0f });
			break;
		}
		default:
			break;
	}
	
	Transform.SetLocalPosition(_Pos);
	Damage = _Damage;
	Vecter = _Dir.NormalizeReturn() * _Power;
}

void Bullet::BulletHit(GameEngineCollision* _Bullet, GameEngineCollision* _Target)
{

}

void Bullet::Update(float _Delta)
{

	Transform.AddLocalPosition(Vecter * _Delta);

	EventParameter Parameter;

	Parameter.Enter = BulletHit;

	AttackCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Enemy, Parameter);
}

