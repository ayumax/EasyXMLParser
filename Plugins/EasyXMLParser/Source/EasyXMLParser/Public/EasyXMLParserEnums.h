// Copyright 2019 ayumax. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEasyXMLParserErrorCode : uint8
{
	Successed,
	Failed
};

UENUM(BlueprintType)
enum class EEasyXMLParserFound : uint8
{
	Found,
	NotFound
};