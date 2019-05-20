// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/NoExportTypes.h"
#include "EasyXMLElement.h"
#include "EasyXMLAsyncLoadFromString.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEasyXMLAsyncLoadFromString_Result, UEasyXMLElement*, XMLObject, FString, ErrorMessage);


UCLASS()
class EASYXMLPARSER_API UEasyXMLAsyncLoadFromString : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FEasyXMLAsyncLoadFromString_Result Successed;

	UPROPERTY(BlueprintAssignable)
	FEasyXMLAsyncLoadFromString_Result Failed;

private:
	UPROPERTY(Transient)
	FString _XMLString;

public:
	UEasyXMLAsyncLoadFromString(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser", meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UEasyXMLAsyncLoadFromString* AsyncLoadFromString(UObject * WorldContextObject, const FString& XMLString);

	
	virtual void Activate() override;

};