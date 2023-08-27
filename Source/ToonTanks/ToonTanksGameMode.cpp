// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor) {

	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) {
		DestroyedTower->HandleDestruction();
		TargetTower--;
	}
	if (TargetTower == 0) {
		GameOver(true);
	}
}

void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
	
}

void AToonTanksGameMode::HandleGameStart() {
	if(AmbientMusic)
		UGameplayStatics::PlaySound2D(this, AmbientMusic);
	TargetTower = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate PlayerEnableTimerDelage = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, 
			PlayerEnableTimerDelage, 
			StartDelay, 
			false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount() {
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), OutActors);
	return OutActors.Num();
}