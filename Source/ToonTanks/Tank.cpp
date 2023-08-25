// Fill out your copyright notice in the Description page of Project Settings.



#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"





ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
	

}

// Called every frame
void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	if (PlayerControllerRef) {
		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, 
			false, 
			HitResult);
			DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint,
				20.f,
				8,
				FColor::Red,
				false,
				-1.f);
	}

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Atatching Axis Mapping to the function
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

}

void ATank::Move(float Value) {
	//UE_LOG(LogTemp, Warning, TEXT("Move is: %f"), Value);
	FVector DeltaLocation = FVector::ZeroVector;

	//X = Value * Delta Time * Speed
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	AddActorLocalOffset(DeltaLocation, true);

}

void ATank::Turn(float Value) {
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}