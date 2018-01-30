// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmPawn.h"
#include "GGJ.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "GrabbableComponent.h"

// Sets default values
AArmPawn::AArmPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>("root");
	SetRootComponent(root);

	armCollision = CreateDefaultSubobject<UCapsuleComponent>("armCollision");
	armCollision->SetupAttachment(root);

	armMesh = CreateDefaultSubobject<USkeletalMeshComponent>("armMesh");
	armMesh->SetupAttachment(armCollision);

	grabPathSpline = CreateDefaultSubobject<USplineComponent>("grabPathSpline");
	grabPathSpline->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AArmPawn::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetActorLocation();
	CurrentLocation = OriginalLocation;

	isRight = ActorHasTag("rightArm");

	armCollision->OnComponentBeginOverlap.AddDynamic(this, &AArmPawn::OnOverlapBegin);
	armCollision->OnComponentEndOverlap.AddDynamic(this, &AArmPawn::OnOverlapEnd);


	// TEST CODE:
	for (TObjectIterator<UGrabbableComponent> Itr; Itr; ++Itr)
	{
		grabbedObject = *Itr;
		break;
	}
}

// Called every frame
void AArmPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(userInput)
	{
		if (bMoveForward && distanceAlongSpline < grabPathSpline->GetSplineLength())
		{
			distanceAlongSpline += DeltaTime * armSpeedMultiplier;
		}
		else if (distanceAlongSpline > 0.0f)
		{
			distanceAlongSpline -= DeltaTime * armSpeedMultiplier;
		}
	}
	
	FVector Loc = grabPathSpline->GetLocationAtDistanceAlongSpline(distanceAlongSpline, ESplineCoordinateSpace::World);
	armCollision->SetWorldLocation(Loc);
	
	/*
	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	oooooooooooooooooooooooooooooossoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	ooooooooooooooooosyysyysoyyyydoosssoosyssooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	ooooooooooooooohhddyooo+//ssoh++/:::/ydso+++sysooooooooooooooooooooooooooooooooooooooooooooooooooooo
	ooooooooooooooshosyoooossoo+//:::::::///::::///+oysoosoooooooooooooooooooooooooooooooooooooooooooooo
	ooooooooooooooh/:/+oo+++//:::::///:://:::::::::::://++ssssoooooooooooooooooooooooooooooooooooooooooo
	oooooooooooooos:::::::::::::::::+o:++/::::::::::::::::///+ooosyysosssyyooooooooooooooooooooooooooooo
	oooooooooooooos::::::::::::::::ydmys/:::::::::::::::::::::::://+/++oso++syoooooooooooooooooooooooooo
	ooooooooooooooh//::::::::::::/ydmmss/:::::::::::::::::::::/o:::::o+//::oooohsooooooooooooooooooooooo
	oooooooooooooooys+///:::://+ohNdy+:+oo/::::::::::::::::::/+y:::::::://+//++ddyoooooooooooooooooooooo
	oooooooooooooooossoossssshyyyddso++//+so/////:::::::::::/os+ys+:::::/+:/oo//yysooooooooooooooooooooo
	ooooooooooooooooooooosyyyysss///////+oo/hhhhh+o+//:::/+/shdh///::::::::///::/ydooooooooooooooooooooo
	ooooooooooooooooooshyooooo/++::+/::/:::/+++od+ooo/ooooshydmh:::::::::::::::::+syoooooooooooooooooooo
	ooooooooooooosssso+//::::yo+/:/s+::s/:::///:/o+oo+++osooohmN+/:::::::::::::::/+yoooooooooooooooooooo
	ooooooooooosso+/:::/y+/+ss+++:y+//+s/:/+y+:/++/:://oss+ssydmmo/:::::::::::::::+dyooooooooooooooooooo
	oooooooooss+::::://+NNmmMh+sy:y+//y::+sh/:/oy::+ooosooohooosNNy/:::::::::::::::/osoooooooooooooooooo
	ooooooooyy/o+:::ossymNMNmddmds/o++h::yd/::sy:/+ss/so++s+//::+dmdo:::::::::::::::yyyooooooooooooooooo
	ooooooohm+:ss/:://+sNNmhoooyhdhdyos+/ym+:/sdymho+ho//+s/::::::sdNs/:::::::::::::/ohdsooooooooooooooo
	ooooooshdss++osoyhdmddmdoooooooyhddsohNdyhmMMMNmho:oss/:///::::+yNdo:::::::::::::oshNsysoooooooooooo
	oooooosdmhsooydhyyssoydhooooooooooosyyyhddddhhNNh:so+::oyo/::::::oddy/::::::::::::+ymdssyooooooooooo
	ooooooosy+ohhsooooooooyhoooooooooooooooooooooohmmy+//+ho/:/o::::::+ymmo/::::::::::/oyMo/+yoooooooooo
	oooooooooooooooooooooosyoooooooooooooooosssoooohms:/sh+:/oys:::::::/sdNs/::::::::::/smds/+yooooooooo
	oooooooooooooooooooosossoooooooooooooosdhhhdhdssymyyo::/yyo:+o+::::::/dNdo:::::::::/+sds/:sysooooooo
	ooooooooooooooooooooyoosooooooooooooshho/+hd/hdhyyNo//oho//o++//:+/:::/ymmy::::::::::smdy/hhhhsooooo
	ooooooooooooooooooooyoosooooooooooosys+/+dNmds/ymsydhyy/+os+s+++o+/:/:::+yMy/::::::::/dmh:s+sysooooo
	ooooooooooooooooooooyoosoooooooooooNo/+mhysydmhdmhoyhddosooy/+++:+o+:::::/oNms/:::::::ss+o++shsooooo
	oooooooooooooooooooodoosoooooooooooNo/+myyssNy+sdNooosyNdhyoy+++s+////:::::odmh/:::::::sdd+++sdooooo
	ooooooooooooooooooooNsoooooooooooooms+smhddhdyydNmooooooydmMMmhy+o+oo://::::/sdN/:::::/+yNo+oshooooo
	oooooooooooooooooooomhsooooooooooooyy+/yydsodomNdsoooooooosyNNdyo+//+so+/:::::+hmo/::::/+my/:/yosooo
	oooooooooooooooooooohdyoooooooooooooyyymdhyydmdysoooooooooooohmds++oo+/o+::::::/shs::::::/h+:::/ssoo
	oooooooooooooooooooyydyooooooooooooooossyyyyysooooooooooooooodNNdo++++/o+/:::::::ys/::::/s+/:::ooooo
	ooooooooooooooooooos/hyoooooooooooooooooooooooooooooooooooooyNdso/++oooso+:::::::o+:://:/o/::::dsooo
	oooooooooooooooooooy+ssoooooooooooooooooooooooooooooooooooooNds+ossoos+oo+:::::::+//o/:::::++//hsooo
	oooooooooooooooooooh/oooooooooooooooooooooooooooooooooooooshMy+++/++++o/++:::::::::/o/::::://+osoooo
	oooooooooooooooooosm+ooooooooooooooooooooooooooooooooooooosmmsss/++++/oo+/:::::::::/o+::::::/++soooo
	oooooooooooooooooosNhyooooooooooooooooooooooooooooooooooooyN+ossoooooo/:::::::::::://+/:::::+o+soooo
	oooooooosysoooosssymNNmdyooooooooooooooooooooooooooooooooshm:+++o++/:::::::::::::::/o+/:::::oy+soooo
	oooooosso++/:::/+++/o+ydyhsooooooooooooooooooooooooooooooydd+//::::::::::::::::::::+y+/:::::oy/soooo
	oooooyo//+ysoos/::::::::/shhsooooooooooooooooooooooooooyhdmmyo/::::::::::::::::::::+y/::::::os/soooo
	oooos+//oh++/+oo/:::::::::ohNhoooooooooooooossyyhhddddhmdhys//::::::::::::::::::::/+y:::::::+sosoooo
	ooooso/oyy::/++o/:/:::::::+ymmsoooossyyyhhhhhddhsohs++o++ossso+/::::::::::::::::::/+s:::::::/+ysoooo
	ooooohoshd/:/+sh+oy::::::/o++dddhhdsyhhs/oss/h+os/+s+//o+/+sooooo:::::::::::::::::///::::::::+msoooo
	ooooooosydhsooshdmm/::::::::/oyhs+h::oy:o+sy:++/+y:/oo:/so/+yoos+::::::::::::::::::::::::::::/osoooo
	ooooooooooooooooymNd+/++::::::syo+d:/++:h+oy::o+/y/:/+s::os:/+///::::::::::::::::::::::/++/+++/soooo
	ooooooooooooooooymms/oo/::::::/+/+d://+:y/+o::///s/::+h:://::/:::::::::::::::::::////:osys///+hyoooo
	oooooooooooooooooyh+h+::/::::::::/+:://:/::::::::::::::::::::::::::::::::::::::/+osyyhy+::::::/myooo
	oooooooooooooooooosmm+//oo/+o::::::::::::::::::::::::::::::::::::::::::::::://+o/so/+o/::::::/oddyoo
	oooooooooooooooooosNmy++y:sdmy+/:::::::::::::::::::::::::::::::::::::::::::+o+/:ho//sNs/:::::+h:hyoo
	*/

	if (userInput) {

		// DESIRE XXXXXXXXXXXXXXXXX

		if (target_x == 0) { // resolve back to no velocity
			if (FMath::Abs(vel_x) < DeltaTime) {
				vel_x = 0;
			}
			else if (vel_x < 0) {
				vel_x += DeltaTime;
			}
			else {//if (accel_x > 0) {
				vel_x -= DeltaTime;
			}
		} // move in the direction of desire
		else {
			if (current_x == target_x) {
			}
			else if (current_x < target_x) {
				vel_x += DeltaTime;
			}
			else if (current_x > target_x) {
				vel_x -= DeltaTime;
			}
			vel_x = FMath::Max(-1.0f, FMath::Min(1.0f, vel_x));
		}
		current_x += DeltaTime * vel_x * accel_scale * vel_scale;

		// DESIRE YYYYYYYYYYYYYYYYY

		if (target_y == 0) { // resolve back to no velocity
			if (FMath::Abs(vel_y) < DeltaTime) {
				vel_y = 0;
			}
			else if (vel_y < 0) {
				vel_y += DeltaTime;
			}
			else {//if (accel_x > 0) {
				vel_y -= DeltaTime;
			}
		} // move in the direction of desire
		else {
			if (current_y == target_y) {
			}
			else if (current_y < target_y) {
				vel_y += DeltaTime;
			}
			else if (current_y > target_y) {
				vel_y -= DeltaTime;
			}
			vel_y = FMath::Max(-1.0f, FMath::Min(1.0f, vel_y));
		}
		current_y += DeltaTime * vel_y * accel_scale * vel_scale;

		// END OF DESIRE

		SetActorLocation(CurrentLocation + FVector(0.0f, current_x*scalar, current_y*scalar));
	}
	else if(bGrabbing && grabbedObject) {
		FVector location = grabbedObject->grabLocation;
		location.X -= armCollision->RelativeLocation.X; //Offset to account for spline movement

		FVector newLocation = FMath::VInterpConstantTo(GetActorLocation(), location, DeltaTime, 200);
		SetActorLocation(newLocation); // Use armCollision->SetComponentLocation()... maybe?

		/*if ( FMath::Abs(currentPosAuto.X - targetPosAuto.X) < DeltaTime*scalar) {
			currentPosAuto.X = targetPosAuto.X;
		} else if (currentPosAuto.X < targetPosAuto.X) {
			currentPosAuto.X += DeltaTime * scalar;
		} else if (currentPosAuto.X > targetPosAuto.X) {
			currentPosAuto.X -= DeltaTime * scalar;
		}

		if (FMath::Abs(currentPosAuto.Y - targetPosAuto.Y) < DeltaTime*scalar) {
			currentPosAuto.Y = targetPosAuto.Y;
		}
		else if (currentPosAuto.Y < targetPosAuto.Y) {
			currentPosAuto.Y += DeltaTime * scalar;
		}
		else if (currentPosAuto.Y > targetPosAuto.Y) {
			currentPosAuto.Y -= DeltaTime * scalar;
		}

		if (FMath::Abs(currentPosAuto.Z - targetPosAuto.Z) < DeltaTime*scalar) {
			currentPosAuto.Z = targetPosAuto.Z;
		}
		else if (currentPosAuto.Z < targetPosAuto.Z) {
			currentPosAuto.Z += DeltaTime * scalar;
		}
		else if (currentPosAuto.Z > targetPosAuto.Z) {
			currentPosAuto.Z -= DeltaTime * scalar;
		}

		SetActorLocation(currentPosAuto);*/
	}
	
}

void AArmPawn::MoveForward(bool engage)
{
	bMoveForward = engage; // star trek joke
}

UGrabbableComponent* AArmPawn::GetGrabbedObject()
{
	return grabbedObject;
}

void AArmPawn::Grab(bool engage) {
	if (engage) {
		MoveTo(grabbedObject);
	}
	else {
		SetUserInput(true);
	}
}

void AArmPawn::Reset() {
	vel_x = 0.0f;
	vel_y = 0.0f;
	SetActorLocation(OriginalLocation);
}

void AArmPawn::RotateSpline()
{
	//grabPathSpline->SetComponentRotat DAMN YOU BRYAN el oh el
}

void AArmPawn::TranslateAlong(float x, float y) {
	
	if (userInput) {
		target_x = x;
		target_y = y;
	}
	
}

bool AArmPawn::MoveTo(UGrabbableComponent* obj) {
	/*FVector location = obj->grabLocation;

	currentPosAuto = FVector(CurrentLocation.X, CurrentLocation.Y + current_x * scalar, CurrentLocation.Z + current_y * scalar);
	oldPosAuto = currentPosAuto;
	targetPosAuto = FVector(location.X, location.Y, location.Z);

	FString str1 = "MoveFrom: (" + FString::FromInt(currentPosAuto.X) + "," + FString::FromInt(currentPosAuto.X) + ")";
	print(str1);
	FString str2 = "MoveTo: (" + FString::FromInt(targetPosAuto.X) + "," + FString::FromInt(targetPosAuto.X) + ")";
	print(str2);

	FRotator ActorRotation = GetActorRotation();
	FRotator TargetActorRotation = obj->GetComponentRotation();

	ActorRotation.Roll = TargetActorRotation.Roll;

	userInput = false;

	return target_x == current_x && target_y == current_y;*/

	return true;
}

void AArmPawn::GrabObject()
{
	bGrabbing = true;

	if (hoveredObject && !grabbedObject)
	{
		grabbedObject = hoveredObject;
		grabbedObject->bGrabbed = true;
		SetUserInput(false);
		Grab(true);
	}
}

void AArmPawn::ReleaseObject()
{
	bGrabbing = false;

	if (grabbedObject)
	{
		grabbedObject->bGrabbed = false;
		grabbedObject = nullptr;
		SetUserInput(true);
		Grab(false);
	}
}

void AArmPawn::SetUserInput(bool state) {
	userInput = state;
	if (state) {
		Reset();
	}
}

void AArmPawn::Rotate(float Val) {
	if (userInput) {
		FRotator ActorRotation = GetActorRotation();
		if (isRight) {
			ActorRotation.Roll = FMath::Max(-120.0f, FMath::Min(170.0f, ActorRotation.Roll + Val));
		}
		else {
			ActorRotation.Roll = FMath::Max(-170.0f, FMath::Min(120.0f, ActorRotation.Roll + Val));
		}
		SetActorRotation(ActorRotation);
	}
}

void AArmPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<UGrabbableComponent>(OtherComp))
	{
		hoveredObject = Cast<UGrabbableComponent>(OtherComp);
	}
}

void AArmPawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (hoveredObject == OtherComp)
	{
		hoveredObject = nullptr;
	}
}
