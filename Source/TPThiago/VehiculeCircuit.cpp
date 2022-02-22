// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiculeCircuit.h"

AVehiculeCircuit::AVehiculeCircuit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVehiculeCircuit::BeginPlay()
{
	Super::BeginPlay();
}

void AVehiculeCircuit::Tick(float DeltaTime)
{
	if (AlgoCircuit == AlgoCuircuit::CIRCUIT) ChangeTargetCircuit();
	else if (AlgoCircuit == AlgoCuircuit::ONE_PATH) ChangeTargetOne();
	else if (AlgoCircuit == AlgoCuircuit::TWO_PATH) ChangeTargetTwo();

	FVector SteeringDirection = CalculDirection();

	FVector SteeringForce = Truncate(SteeringDirection, max_force);
	FVector Acceleration = SteeringForce / masse;
	Velocity = Truncate(Velocity + Acceleration, max_speed);
	SetActorLocation(GetActorLocation() + Velocity);
	SetActorRotation(FRotator(Velocity.Rotation()));
}

void AVehiculeCircuit::ChangeTargetCircuit()
{
	FVector target = ListeTarget[NbListe]->GetActorLocation();
	float dist = (target - GetActorLocation()).Size();
	if (dist <= DistanceChangeTarget) NbListe += Direction;
	if (NbListe >= ListeTarget.Num()) NbListe = 0;
}

void AVehiculeCircuit::ChangeTargetTwo()
{
	FVector target = ListeTarget[NbListe]->GetActorLocation();
	float dist = (target - GetActorLocation()).Size();

	if (Arriver){
		if (dist <= 1.f) 
			IsTarget = true;
		if (IsTarget){
			TimeWaitCurrent -= 5;
			if (TimeWaitCurrent <= 0){
				Direction = -Direction;
				Arriver = false;
				IsTarget = false;
			}
		}
		return;
	}

	if (dist <= DistanceChangeTarget) NbListe += Direction;
	if (NbListe >= ListeTarget.Num()){
		Arriver = true;
		NbListe = ListeTarget.Num() - 1;
		TimeWaitCurrent = TempsDattente;
	}
	else if (NbListe <= 0 && Direction == -1){
		Arriver = true;
		NbListe = 0;
		TimeWaitCurrent = TempsDattente;
	}
}

void AVehiculeCircuit::ChangeTargetOne()
{
	if (Arriver) return;
	FVector target = ListeTarget[NbListe]->GetActorLocation();
	float dist = (target - GetActorLocation()).Size();

	if (dist <= DistanceChangeTarget) NbListe += Direction;
	if (NbListe >= ListeTarget.Num())
	{
		Arriver = true;
		NbListe = ListeTarget.Num() - 1;
	}
}

FVector AVehiculeCircuit::CalculDirection()
{
	FVector target = ListeTarget[NbListe]->GetActorLocation();

	if (Arriver) return Arrival(target);
	return Seek(target);
}

