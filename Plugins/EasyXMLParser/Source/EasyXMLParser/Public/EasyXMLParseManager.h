// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyXMLElement.h"
#include "EasyXMLParserEnums.h"
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
	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser", meta = (ExpandEnumAsExecs = "Result"))
	static UEasyXMLElement* LoadFromFile(const FString& FilePath, bool IsAblolute, EEasyXMLParserErrorCode& Result, FString& ErrorMessage);

	/**
	 * load xml string
	 * @param XMLString - xml file path
	 * @return xml object
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser", meta = (ExpandEnumAsExecs = "Result"))
	static UEasyXMLElement* LoadFromString(const FString& XMLString, EEasyXMLParserErrorCode& Result, FString& ErrorMessage);

};
