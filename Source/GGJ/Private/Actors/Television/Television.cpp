// Fill out your copyright notice in the Description page of Project Settings.

#include "Television.h"
#include "GGJ.h"

#include "Antenna.h"
#include "TVKnob.h"
#include "AudioManager.h"
#include "TVMaterialManager.h"
#include "GGJPlayerController.h"
#include "ArmPawn.h"

// Sets default values
ATelevision::ATelevision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("tvMesh");
	SetRootComponent(mesh);

	antennaLeft = CreateDefaultSubobject<UAntenna>("antennaLeft");
	antennaLeft->SetupAttachment(mesh);

	antennaRight = CreateDefaultSubobject<UAntenna>("antennaRight");
	antennaRight->SetupAttachment(mesh);

	knobLarge = CreateDefaultSubobject<UTVKnob>("knobLarge");
	knobLarge->SetupAttachment(mesh);

	knobSmall = CreateDefaultSubobject<UStaticMeshComponent>("knobSmall");
	knobSmall->SetupAttachment(mesh);

	staticAudioComponent = CreateDefaultSubobject<UAudioComponent>("staticAudio");
	staticAudioComponent->SetupAttachment(mesh);

	channelAudioComponent = CreateDefaultSubobject<UAudioComponent>("channelAudio");
	channelAudioComponent->SetupAttachment(mesh);

	audioManager = CreateDefaultSubobject<UAudioManager> ("audioManager");

	materialManager = CreateDefaultSubobject<UTVMaterialManager>("materialManager");
}

// Called when the game starts or when spawned
void ATelevision::BeginPlay()
{
	Super::BeginPlay();
	
	audioManager->tvStaticAudioComponent = staticAudioComponent;
	audioManager->tvChannelAudioComponent = channelAudioComponent;

	materialManager->staticMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(2), this);
	materialManager->channelImageMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(3), this);

	mesh->SetMaterial(2, materialManager->staticMaterial);
	mesh->SetMaterial(3, materialManager->channelImageMaterial);

	knobLarge->numOfChannels = audioManager->ChannelSounds.Num();

	if (camera && AttractCameraLocation) {
		OriginalCameraLocation = camera->GetActorLocation();
		camera->SetActorLocation(AttractCameraLocation->GetActorLocation());
	}
	else {
		print("Either the camera or the attract camera is not set up in television (~seppi)");
	}

	controller = Cast<AGGJPlayerController>(GetWorld()->GetFirstPlayerController());

	materialManager->ChangeStaticAmount(0.0);
	materialManager->ChangeSaturationAmount(0.0);

}

// Called every frame
void ATelevision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// find the arms!
	if (!leftArm) {
		leftArm = Cast<AGGJPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->armPawn;
	}
	if (!rightArm) {
		rightArm = Cast<AGGJPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1))->armPawn;
	}

	if (camera && AttractCameraLocation) {
		FVector newLocation;
		if (isAttractMode) {
			newLocation = FMath::VInterpConstantTo(camera->GetActorLocation(), AttractCameraLocation->GetActorLocation(), DeltaTime, 200);
		}
		else {
			newLocation = FMath::VInterpConstantTo(camera->GetActorLocation(), OriginalCameraLocation, DeltaTime, 200);
		}
		camera->SetActorLocation(newLocation);
	}

	if (antennaRight->bCorrectPosition && antennaRight->bCorrectPosition && knobLarge->bCorrectPosition && isAttractMode == false) { // todo: add knobLarge->bCorrectPosition
		print("You win!");
		isAttractMode = true;
		materialManager->ChangeStaticAmount(0.0);
		materialManager->ChangeSaturationAmount(0.0);
		gameOver = true;
	}


	if (controller->wasStartPressed() && isAttractMode == true) {
		isAttractMode = false;
		antennaLeft->Randomize();
		antennaRight->Randomize();
		if (leftArm) {
			leftArm->Reset();
		}
		else {
			print("NO LEFT ARMS MAN");
		}
		if (rightArm) {
			rightArm->Reset();
		}
		else {
			print("NO RIGHT ARMS MAN");
		}
		materialManager->ChangeStaticAmount(1.0);
		materialManager->ChangeSaturationAmount(1.0);
	}

	if (gameOver && camera->GetActorLocation().Equals(AttractCameraLocation->GetActorLocation())) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}

}