// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/NoExportTypes.h"
#include "EasyXMLElement.h"
#include "EasyXMLAsyncLoadFromFile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEasyXMLAsyncLoadFromFile_Result, UEasyXMLElement*, XMLObject, FString, ErrorMessage);


UCLASS()
class EASYXMLPARSER_API UEasyXMLAsyncLoadFromFile : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FEasyXMLAsyncLoadFromFile_Result Successed;

	UPROPERTY(BlueprintAssignable)
		FEasyXMLAsyncLoadFromFile_Result Failed;

private:
	UPROPERTY(Transient)
		FString _XMLFile;
	UPROPERTY(Transient)
		bool _IsAblolute;

public:
	UEasyXMLAsyncLoadFromFile(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser", meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UEasyXMLAsyncLoadFromFile * AsyncLoadFromFile(UObject * WorldContextObject, const FString& FilePath, bool IsAblolute);


	virtual void Activate() override;

};