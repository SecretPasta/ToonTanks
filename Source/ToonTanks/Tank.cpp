// Fill out your copyright notice in the Description page of Project Settings.



#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"




ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Atatching Axis Mapping to the function
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

}

void ATank::Move(float Value) {
	//UE_LOG(LogTemp, Warning, TEXT("Move is: %f"), Value);
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value;
	AddActorLocalOffset(DeltaLocation);

}