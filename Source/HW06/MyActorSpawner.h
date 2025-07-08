// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorSpawner.generated.h"

UCLASS()
class HW06_API AMyActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActorSpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APlatformActor> PlatformToSpawn;
	
	FTimerHandle HandleTimer;
	virtual void BeginPlay() override;

};
