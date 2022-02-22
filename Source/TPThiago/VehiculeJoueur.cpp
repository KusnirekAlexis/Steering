// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputComponent.h"
#include "VehiculeJoueur.h"
#include "IaVehicule.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
AVehiculeJoueur::AVehiculeJoueur()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AActor::AutoReceiveInput = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AVehiculeJoueur::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
	
}

// Called every frame
void AVehiculeJoueur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVehiculeJoueur::MoveForward(float DeltaTime)
{
	FVector Location = GetActorLocation();
	Location.X += 10 * DeltaTime;
	SetActorLocation(Location);
}

void AVehiculeJoueur::MoveRight(float DeltaTime)
{
	FVector Location = GetActorLocation();
	Location.Y += 10 * DeltaTime;
	SetActorLocation(Location);
}

void AVehiculeJoueur::SetupInput()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &AVehiculeJoueur::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AVehiculeJoueur::MoveRight);

		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

/*void AIaVehicule::SwitchSteering() {
	Index += 1;
	if (Index == 5)
		Index = 0;
	UsingAlgo = IntToEnum();
}*/


