#pragma once

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
 #include "BehaviorTree/BehaviorTreeComponent.h"
#include "AvaAIController.generated.h"

/**
 * 
 */
UCLASS()
class AVA_API AAvaAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Ava|AI")
	UBlackboardData* blackboard_type;

	UPROPERTY(EditDefaultsOnly, Category = "Ava|AI")
	UBehaviorTree* behaviour_type;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Ava|AI")
	void OnAssignBlackBoard(const UBlackboardComponent* board);
};
