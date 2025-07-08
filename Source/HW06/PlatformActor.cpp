#include "PlatformActor.h"

APlatformActor::APlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));

	SetRootComponent(RootComp);
	StaticMeshComp->SetupAttachment(RootComp);

	MoveSpeed = 400.0f;
	MaxRange = 500.0f;
	Direction = 1.0f;
	DirectionVector = FMath::VRand().GetSafeNormal();
	CurrentDist = 0.0f;

	bMovable = FMath::RandBool();
	bRotatable = FMath::RandBool();

	RotationSpeed = 300.0f;
}

void APlatformActor::RotatingPlatform(float DeltaTime)
{
	AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
}

void APlatformActor::MovingPlatform(float DeltaTime)
{
	CurrentDist += Direction * MoveSpeed * DeltaTime; // 이번 틱에 움직일 거리

	if (CurrentDist > MaxRange)
	{
		CurrentDist = MaxRange - (CurrentDist - MaxRange);
		Direction = -1.0f;
	}
	else if (CurrentDist < 0.0f)
	{
		CurrentDist = -CurrentDist;
		Direction = 1.0f;
	}

	const FVector MoveLocation = StartLocation + (DirectionVector * CurrentDist);
	SetActorLocation(MoveLocation);
}

void APlatformActor::DestroyPlatformActor()
{
	Destroy();
}

void APlatformActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(
		HandleTimer,
		this,
		&APlatformActor::DestroyPlatformActor,
		5.0f,
		true
	);
}

void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMovable)
		MovingPlatform(DeltaTime);

	if (bRotatable)
		RotatingPlatform(DeltaTime);
}
