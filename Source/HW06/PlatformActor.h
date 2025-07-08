#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

UCLASS()
class HW06_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USceneComponent* RootComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;
	float Direction;
	float BounceDist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector DirectionVector;
	float CurrentDist;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	bool bMovable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	bool bRotatable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeed;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle HandleTimer;
	
	void RotatingPlatform(float DeltaTime);
	void MovingPlatform(float DeltaTime);

	void DestroyPlatformActor();
};
