// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	SetPivotOffset(FVector(0.5));
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HasAuthority())
	{
		FVector Location = GetActorLocation();
		JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		JourneyTraveled = (Location - GlobalStartLocation).Size();

		if(JourneyTraveled >= JourneyLength)
		{
			const FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal(); //GetSafeNormal is better than Normalize
		Location += Speed * DeltaSeconds * Direction;
		SetActorLocation(Location);
	}	

}
