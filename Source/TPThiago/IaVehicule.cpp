// Fill out your copyright notice in the Description page of Project Settings.


#include "IaVehicule.h"

// Sets default values
AIaVehicule::AIaVehicule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIaVehicule::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AIaVehicule::SeekVelocity(FVector TargetLocation) {
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("SEEK"));
	FVector VectorDist = TargetLocation - GetActorLocation();
	VectorDist.Normalize();
	FVector VelocityDesired = VectorDist * max_speed;
	return VelocityDesired - Velocity;
}


FVector AIaVehicule::FleeVelocity(FVector TargetLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("FLEE"));
	FVector VectorDist = TargetLocation - GetActorLocation();
	VectorDist.Normalize();
	FVector VelocityDesired = VectorDist * -max_speed;
	return VelocityDesired - Velocity;
}


FVector AIaVehicule::PursuitVelocity(FVector TargetLocation, FVector TargetVelocity)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("PURSUIT"));
	FVector VectorDist = (TargetLocation + TargetVelocity * 3) - GetActorLocation();
	VectorDist.Normalize();
	FVector VelocityDesired = VectorDist * max_speed;
	return VelocityDesired - Velocity;
}

/*FVector AIaVehicule::EvadeVelocity(float DeltaTime, FVector TargetLocation, FVector TargetVelocity)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("EVADE"));
	FVector VectorDist = (TargetLocation + TargetVelocity * 3) - GetActorLocation();
	VectorDist.Normalize();
	FVector VelocityDesired = VectorDist * max_speed;
	return VelocityDesired - Velocity;
}

FVector AIaVehicule::ArrivalVelocity(FVector TargetLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("ARRIVAL"));
	FVector VectorDist = TargetLocation - GetActorLocation();
	VectorDist.Normalize();
	distance = length(VectorDist);
	ramped_speed = max_speed * (distance / slowing_distance);
	clipped_speed = minimum(ramped_speed, max_speed);
	FVector VelocityDesired = (clipped_speed / distance) * target_offset;
	return VelocityDesired - Velocity;
}*/



void AIaVehicule::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector TargetLocation = Target->GetActorLocation();
	FVector TargetVelocity = Target->GetVelocity();
	FVector SteeringDirection;
	if (UsingAlgo == AlgoUsing::SEEK) SteeringDirection = SeekVelocity(TargetLocation);
	else if (UsingAlgo == AlgoUsing::FLEE) SteeringDirection = FleeVelocity(TargetLocation);
	//else if (UsingAlgo == AlgoUsing::ARRIVAL) SteeringDirection = ArrivalVelocity(TargetLocation);
	else if (UsingAlgo == AlgoUsing::PURSUIT) SteeringDirection = PursuitVelocity(TargetLocation, TargetVelocity);
	//else SteeringDirection = EvadeVelocity(TargetLocation);
	FVector SteeringForce = Truncate(SteeringDirection, max_force);
	FVector Acceleration = SteeringForce / masse;
	Velocity = Truncate(Velocity + Acceleration, max_speed);
	SetActorLocation(GetActorLocation() + Velocity);
	SetActorRotation(FRotator(Velocity.Rotation()));
}

void AIaVehicule::ChangeAlgo() {
	Index = (Index + 1) % 5;
	UsingAlgo = IntToEnum();
}

AlgoUsing AIaVehicule::IntToEnum() {
	switch (Index) {
	case 0:
		return AlgoUsing::SEEK;
	default:
		return AlgoUsing::FLEE;
	case 2:
		return AlgoUsing::PURSUIT;
	}
	/*case 3:
		return AlgoUsing::PURSUIT;
	default:
		return AlgoUsing::EVADE;
	}*/
}

