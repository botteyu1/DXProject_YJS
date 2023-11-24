#include "PreCompile.h"
#include "Bullet.h"
#include "Actor.h"
#include "Map.h"
#include "Level.h"
#include "FX.h"

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
	MainSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
	

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 0.5f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
}

void Bullet::Init(BulletType _Type,float4 _Pos, float _Damage,  float4 _Dir, float _Power , bool _Flip)
{
	Flip = _Flip;
	float4 Pos = _Pos;
	Damage = _Damage;
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
		case BulletType::Rock:
		{
			MainSpriteRenderer->CreateAnimation("Rock", "Rock", 0.0666f, -1, -1, true);
			MainSpriteRenderer->ChangeAnimation("Rock");
			//MainSpriteRenderer->SetAutoScaleRatio({ 0.5f,0.5f });
			AttackCollision->Transform.SetLocalPosition({-50.0f,-50.0f});
			AttackCollision->Transform.SetLocalScale({ 100.0f,100.0f });
			ForceGrivityOff = false;
			GrivityForce.Y = 1500.0f;

			TargetCollision = ContentsCollisionType::Player;
			break;
		}
		case BulletType::Tornado:
		{
			if (Flip == true)
			{
				Pos += float4{ -170.0f, 0.0f };
				MainSpriteRenderer->LeftFlip();
			}
			else
			{
				Pos += float4{ 170.0f, 0.0f };
			}

			MainSpriteRenderer->CreateAnimation("Tornado", "Tornado", 0.0333f, -1, -1, true);
			MainSpriteRenderer->SetFrameEvent("Tornado", 10, [&](GameEngineSpriteRenderer* Renderer) {
				if (BulletCount < 3)
				{
					std::shared_ptr <Bullet> Object = GetLevel()->CreateActor<Bullet>(ContentsObjectType::Bullet);
					float4 Dir = float4::RIGHT;
					Object->Init(BulletType::Tornado, Transform.GetLocalPosition(), Damage, Dir, 0.0f,Flip);
					Object->BulletCount = BulletCount + 1;
				}
				});
			MainSpriteRenderer->ChangeAnimation("Tornado");
			MainSpriteRenderer->SetPivotValue({ 0.5f,1.0f });
			MainSpriteRenderer->SetAutoScaleRatio({ 1.3f,1.3f,1.0f });

			AttackCollision->Transform.SetLocalPosition({0.0f,300.0f});
			AttackCollision->Transform.SetLocalScale({ 150.0f,600.0f });
			TargetCollision = ContentsCollisionType::Enemy;
			break;
		}
		default:
			break;
	}
	
	float4 Normal = _Dir.NormalizeReturn();
	float Deg = Normal.Angle2DDeg();
	if (Normal.Y < 0.0f)
	{
		Deg = -Deg;
	}


	/*float4 Normal2 = float4{ 0.0f,1.0f,0.0f }.NormalizeReturn();
	float4 Deg2 = Normal2.Angle2DDeg();*/
	
	Transform.SetLocalPosition(Pos);
	
	Vecter = Normal * _Power;
	Transform.AddLocalRotation({0.0f,0.0f,Deg});
	Type = _Type;

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

	Time += _Delta;
	
	switch (Type)
	{
	case BulletType::Fire:
	case BulletType::Paperplane:
		Parameter.Enter = BulletHit;
		AttackCollision->CollisionEvent<ContentsCollisionType>(TargetCollision, Parameter);

		if (Time >= 5.0f)
		{
			Death();
		}
		break;
		break;
	case BulletType::Tornado:
		if (MainSpriteRenderer->GetCurIndex() >= 21)
		{
			Parameter.Enter = BulletHit;
			AttackCollision->CollisionEvent<ContentsCollisionType>(TargetCollision, Parameter);
		}
		
		if (MainSpriteRenderer->IsCurAnimationEnd() == true)
		{
			Death();
		}
		break;

	case BulletType::Rock:
	{
		Parameter.Enter = BulletHit;
		AttackCollision->CollisionEvent<ContentsCollisionType>(TargetCollision, Parameter);
		//공중인지 체크
		GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });

		//공중
		if ((GameEngineColor::WHITE == Color) and ForceGrivityOff == false)
		{
			AerialCheck = true;
			GrivityForce.Y -= _Delta * 5000.f;
			Transform.AddLocalPosition(GrivityForce * _Delta);
		}
		//중력이 꺼져도 공중인지 체크하고 중력초기화
		else if (GameEngineColor::WHITE == Color)
		{
			AerialCheck = true;
			GrivityForce = 0.0f;
		}
		//지상 
		else if (ForceGrivityOff == false)
		{
			GrivityForce = 0.0f;
			AerialCheck = false;
			if (Type == BulletType::Rock)
			{
				static_cast<Level*>(GetLevel())->GetFXActor()->FXStart(FXType::Gargoyle_Falling_Rock, Flip, Transform.GetLocalPosition() + float4(0.0f, 0.0f, -5.0f), { 1.0f,1.0f,1.0f }, { 0.5f,1.0f });
			}
			Death();
		}
	}
		break;
	case BulletType::Max:
		break;
	default:
		break;
	}

	



}

GameEngineColor Bullet::PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor)
{
	float4 WorldPosition = Transform.GetWorldPosition();
	WorldPosition += _Pixel;
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);

	return Color;
}

GameEngineColor Bullet::PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor)
{

	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(_Pos, GameEngineColor::RED);

	return Color;
}
