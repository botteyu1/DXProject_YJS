#include "PreCompile.h"
#include "Bullet.h"
#include "Actor.h"

Bullet::Bullet() 
{
}

Bullet::~Bullet()
{
}



void Bullet::Start()
{
	if (nullptr == GameEngineTexture::Find("Projectile_Fire02_atlas_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Sprite\\Bullet");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

		GameEngineDirectory Dir2;
		Dir2.MoveParentToExistsChild("GameEngineResources");
		Dir2.MoveChild("ContentsResources\\Texture\\Bullet");
		std::vector<GameEngineFile> Files = Dir2.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}
	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy_Attack);
	

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 0.5f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
}

void Bullet::Init(BulletType _Type,float4 _Pos, float _Damage,  float4 _Dir, float _Power)
{
	
	switch (_Type)
	{
		case BulletType::Fire:
		{
			MainSpriteRenderer->CreateAnimation("Fire", "Fire", 0.0666f, -1, -1, true);
			MainSpriteRenderer->ChangeAnimation("Fire");
			MainSpriteRenderer->SetAutoScaleRatio({ 0.7f,0.35f});
			//AttackCollision->Transform.SetLocalPosition({0.0f,0.0f});
			AttackCollision->Transform.SetLocalScale({ 80.0f,50.0f });

			TargetCollision = ContentsCollisionType::Player;
			break;
		}
		case BulletType::Paperplane:
		{

			MainSpriteRenderer->CreateAnimation("Paperplane", "Paperplane.png", 0.0666f, -1, -1, true);
			MainSpriteRenderer->ChangeAnimation("Paperplane");
			MainSpriteRenderer->SetAutoScaleRatio({ 0.35f,0.35f });
			//AttackCollision->Transform.SetLocalPosition({0.0f,0.0f});
			AttackCollision->Transform.SetLocalScale({ 80.0f,50.0f });

			TargetCollision = ContentsCollisionType::Player;
			break;
		}
		default:
			break;
	}
	
	float4 Normal = _Dir.NormalizeReturn();
	float Deg = Normal.Angle2DDeg();
	if (Normal.Y <= 0.0f)
	{
		Deg = -Deg;
	}


	/*float4 Normal2 = float4{ 0.0f,1.0f,0.0f }.NormalizeReturn();
	float4 Deg2 = Normal2.Angle2DDeg();*/
	
	Transform.SetLocalPosition(_Pos);
	Damage = _Damage;
	Vecter = Normal * _Power;
	Transform.AddLocalRotation({0.0f,0.0f,Deg});


	SetName("Bullet");
}

void Bullet::BulletHit(GameEngineCollision* _Bullet, GameEngineCollision* _Target)
{
	float Damagef = _Bullet->GetParent<Bullet>()->GetDamage();
	_Target->GetParent<Actor>()->TakeDamage(_Bullet, Damagef);
}

void Bullet::Update(float _Delta)
{

	Transform.AddLocalPosition(Vecter * _Delta);

	EventParameter Parameter;

	Parameter.Enter = BulletHit;

	AttackCollision->CollisionEvent<ContentsCollisionType>(TargetCollision, Parameter);

	Time += _Delta;

	if (Time >= 5.0f)
	{
		Death();
	}
}

