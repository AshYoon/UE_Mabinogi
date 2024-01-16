#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//Input
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "COptionComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->SocketOffset = FVector(0.0f, 0.0f,700.f);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	Camera->SetRelativeRotation(FRotator(0.0f, -30.f, 0.0f));

	Option = CreateDefaultSubobject<UCOptionComponent>(TEXT("Option"));
	
	


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();




	APlayerController* PC = Cast<APlayerController>(Controller);
;

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;


		
	}

	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}

		// Bind Here
		if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			Input->BindAction(CameraAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveCameraStart);
			Input->BindAction(Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		}
	}









}



void APlayerCharacter::MoveCameraStart(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();
	IsCamearaMode = InputValue.Get<bool>();
	if(IsCamearaMode) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "true");
	else  GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "false");


	if (IsValid(Controller) && IsCamearaMode)
	{
		float horizontalrate = Option->GetHorizontalLookRate();
		float verticalrate = Option->GetVerticalLookRate();

		AddControllerYawInput(InputVector.X * horizontalrate * GetWorld()->GetDeltaSeconds());
		AddControllerPitchInput(InputVector.Y * verticalrate * GetWorld()->GetDeltaSeconds());
	}

}

void APlayerCharacter::CameraMode()
{
	//if (IsCamearaMode)
	//{
	//	IsCamearaMode = false;
	//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "false");
	//}
	//else
	//{
	//	IsCamearaMode = true;
	//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "true");
	//}


}

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector3d InputVector = InputValue.Get<FVector3d>();
	

	FVector3d WorldLocation;
	FVector3d WorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	FString value = FString::Printf(TEXT("X : %f , Y : %f , Z : %f"), WorldLocation.X, WorldLocation.Y, WorldLocation.Z);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, value);

	UKismetSystemLibrary::LineTraceSingle(GetWorld() , WorldLocation , )

}





