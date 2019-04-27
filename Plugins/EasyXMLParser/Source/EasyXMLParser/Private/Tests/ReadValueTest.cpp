// Copyright 2019 ayumax. All Rights Reserved.
#include "Misc/AutomationTest.h"
#include "EasyXMLObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FReadValueTest_Int, "EasyXMLParser.ReadValueTest.Int", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FReadValueTest_Int::RunTest(const FString& Parameters)
{
	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("1")
								TEXT("</abc>")
							TEXT("</root>");

		auto xmlNode = UEasyXMLObject::CreateEasyXMLObject(xmlString);
		
		TestEqual(TEXT("success read int"), xmlNode->ReadInt("abc"), 1);
	}


	// parse ng
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		auto xmlNode = UEasyXMLObject::CreateEasyXMLObject(xmlString);

		TestEqual(TEXT("ng read int"), xmlNode->ReadInt("abc"), 0);
	}
	

	return true;
}