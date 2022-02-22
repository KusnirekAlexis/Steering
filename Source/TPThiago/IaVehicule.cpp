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

FVector AIaVehicule::Seek(FVector TargetLocation) {
	FVector vector_dist = TargetLocation - GetActorLocation();
	vector_dist.Normalize();
	FVector desired_velocity = vector_dist * max_speed;
	return desired_velocity - Velocity;
}


FVector AIaVehicule::Flee(FVector TargetLocation)
{
	FVector vector_dist = TargetLocation - GetActorLocation();
	vector_dist.Normalize();
	FVector desired_velocity = vector_dist * -max_speed;
	return desired_velocity - Velocity;
}


FVector AIaVehicule::Pursuit()
{
	float product = FVector::DotProduct(Target->GetVelocity().GetSafeNormal(), (GetActorLocation() - Target->GetActorLocation()).GetSafeNormal());
	float turning_parameter;
	if (product >= 0) 
		turning_parameter = 1 - product;
	else 
		turning_parameter = 1;
	float dist = (Target->GetActorLocation() - GetActorLocation()).Size();
	float angle = dist / Velocity.Size() * turning_parameter;
	FVector futur_target = Target->GetVelocity() * angle;
	return Seek(Target->GetActorLocation() + futur_target);
}

FVector AIaVehicule::Evade()
{
	float product = FVector::DotProduct(Target->GetVelocity().GetSafeNormal(), (GetActorLocation() - Target->GetActorLocation()).GetSafeNormal());
	float turning_parameter;
	if (product >= 0)
		turning_parameter = 1 - product;
	else
		turning_parameter = 1;
	float dist = (Target->GetActorLocation() - GetActorLocation()).Size();
	float angle = dist / Velocity.Size() * turning_parameter;
	FVector FuturTarget = Target->GetVelocity() * angle;
	return -Seek(Target->GetActorLocation() + FuturTarget);
}

FVector AIaVehicule::Arrival(FVector TargetLocation)
{
	FVector target_offset = TargetLocation - GetActorLocation();
	float distance = target_offset.Size();
	//5 modifiable pour la distance de ralenticement
	float ramped_speed = max_speed * (distance / 5);
	float clipped_speed = FMath::Min(ramped_speed, max_speed);
	FVector desired_velocity = (clipped_speed / distance) * target_offset;
	return desired_velocity - Velocity;
}



void AIaVehicule::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector TargetLocation = Target->GetActorLocation();
	FVector TargetVelocity = Target->GetVelocity();
	FVector SteeringDirection;
	if (Algorithme == AlgoUsing::SEEK) SteeringDirection = Seek(TargetLocation);
	else if (Algorithme == AlgoUsing::FLEE) SteeringDirection = Flee(TargetLocation);
	else if (Algorithme == AlgoUsing::EVADE) SteeringDirection = Evade();
	else if (Algorithme == AlgoUsing::PURSUIT) SteeringDirection = Pursuit();
	else SteeringDirection = Arrival(TargetLocation);
	FVector SteeringForce = Truncate(SteeringDirection, max_force);
	FVector Acceleration = SteeringForce / masse;
	Velocity = Truncate(Velocity + Acceleration, max_speed);
	SetActorLocation(GetActorLocation() + Velocity);
	SetActorRotation(FRotator(Velocity.Rotation()));
}

AlgoUsing AIaVehicule::IntToEnum() {
	switch (Index) {
	case 0:
		return AlgoUsing::SEEK;
	case 1:
		return AlgoUsing::FLEE;
	case 2:
		return AlgoUsing::PURSUIT;
	case 3:
		return AlgoUsing::EVADE;
	case 4:
		return AlgoUsing::ARRIVAL;
	default:
		return AlgoUsing::ARRIVAL;
	}
}

