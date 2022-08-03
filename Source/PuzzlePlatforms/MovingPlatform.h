// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AMovingPlatform();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;



	UPROPERTY(EditAnywhere)
	float Speed = 30;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(VisibleAnywhere)
	float JourneyLength;

	UPROPERTY(VisibleAnywhere)
	float JourneyTraveled;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 1;
};
