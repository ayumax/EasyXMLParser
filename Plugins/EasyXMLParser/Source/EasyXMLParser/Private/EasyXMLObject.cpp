// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyXMLObject.h"
#include "Utils/CustomXMLParser.h"

int32 UEasyXMLObject::GetIntValue(int32 DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	int32 _index = 0;

	if (Value.IsNumeric() && !Value.FindChar(TEXT('.'), _index))
	{
		return FCString::Atoi(*Value);
	}
		
	return DefaultValue;
}

float UEasyXMLObject::GetFloatValue(float DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	auto isSuccess = Value.IsNumeric();
	return isSuccess ? FCString::Atof(*Value) : DefaultValue;
}

FString UEasyXMLObject::GetStringValue(FString DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	return Value;
}

bool UEasyXMLObject::GetBoolValue(bool DefaultValue)
{
	if (Value.IsEmpty()) return DefaultValue;

	if (Value.Equals(TEXT("true"), ESearchCase::IgnoreCase))
	{
		return true;
	}
	else if (Value.Equals(TEXT("false"), ESearchCase::IgnoreCase))
	{
		return false;
	}

	return DefaultValue;
}
