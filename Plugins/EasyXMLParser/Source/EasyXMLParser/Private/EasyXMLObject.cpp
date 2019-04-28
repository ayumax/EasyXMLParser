// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyXMLObject.h"
#include "Utils/CustomXMLParser.h"

int32 UEasyXMLObject::GetIntValue(bool& isSuccess)
{
	isSuccess = false;

	if (Value.IsEmpty()) return 0;

	int32 _index = 0;

	if (Value.IsNumeric() && !Value.FindChar(TEXT('.'), _index))
	{
		isSuccess = true;
		return FCString::Atoi(*Value);
	}
		
	return 0;
}

float UEasyXMLObject::GetFloatValue(bool& isSuccess)
{
	isSuccess = false;
	if (Value.IsEmpty()) return 0;

	isSuccess = Value.IsNumeric();
	return isSuccess ? FCString::Atof(*Value) : 0;
}

FString UEasyXMLObject::GetStringValue(bool& isSuccess)
{
	return Value;
}

bool UEasyXMLObject::GetBoolValue(bool& isSuccess)
{
	isSuccess = false;
	if (Value.IsEmpty()) return false;

	if (Value.Equals(TEXT("true"), ESearchCase::IgnoreCase))
	{
		isSuccess = true;
		return true;
	}
	else if (Value.Equals(TEXT("false"), ESearchCase::IgnoreCase))
	{
		isSuccess = true;
		return false;
	}

	return false;
}
