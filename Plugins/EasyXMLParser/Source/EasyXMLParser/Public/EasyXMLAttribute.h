// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "EasyXMLObject.h"
#include "EasyXMLAttribute.generated.h"

class UEasyXMLElement;

UCLASS(BlueprintType, Blueprintable)
class EASYXMLPARSER_API UEasyXMLAttribute : public UEasyXMLObject
{
	GENERATED_BODY()
	
public:
	static UEasyXMLAttribute* CreateAttribute(UEasyXMLElement* ParentObject, FString Name, FString Value);

};
