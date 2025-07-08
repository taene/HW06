#include "MyActorSpawner.h"
#include "Components/BoxComponent.h"
#include "PlatformActor.h"

AMyActorSpawner::AMyActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);
}

void AMyActorSpawner::SpawnActor()
{
	if (PlatformToSpawn)
	{
		if (UWorld* World = GetWorld())
		{
			FVector SpawnLocation = FMath::RandPointInBox(GetComponentsBoundingBox());
			FTransform SpawnTransform(GetActorRotation(), SpawnLocation, GetActorScale3D());
			FActorSpawnParameters SpawnParams;

			World->SpawnActor<APlatformActor>(
				PlatformToSpawn,
				SpawnTransform,
				SpawnParams
			);
		}
	}
}

void AMyActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		HandleTimer,
		this,
		&AMyActorSpawner::SpawnActor,
		FMath::FRandRange(0.0f, 3.0f),
		true
	);
}
