// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//Find the distance to the tank
	if (!Tank) {
		return;
	}
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Distance is: %f"), Distance);
	//Check to see if the tank is in range
	if (Distance <= FireRange) {
		//if in range rotate turret to tank
		RotateTurret(Tank->GetActorLocation());
		
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}