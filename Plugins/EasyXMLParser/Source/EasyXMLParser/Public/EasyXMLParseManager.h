// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyXMLObject.h"
#include "EasyXMLParseManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EASYXMLPARSER_API UEasyXMLParseManager : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * load xml file
	 * @param FilePath - xml file path
	 * @param IsAblolute - true:FilePath is absolute path, false:Relative path from "Content"
	 * @return xml object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser")
	static UEasyXMLObject* LoadFromFile(const FString& FilePath, bool IsAblolute = false);

	/**
	 * load xml string
	 * @param XMLString - xml file path
	 * @return xml object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser")
	static UEasyXMLObject* LoadFromString(const FString& XMLString);

};
