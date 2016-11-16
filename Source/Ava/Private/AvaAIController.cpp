#include "Ava.h"
#include "AvaAIController.h"


void AAvaAIController::BeginPlay()
{
	Super::BeginPlay();
	
	UBlackboardComponent* bbc;

	if (UseBlackboard(blackboard_type, bbc))
	{
		OnAssignBlackBoard(bbc);
		RunBehaviorTree(behaviour_type);
	}
	
}
