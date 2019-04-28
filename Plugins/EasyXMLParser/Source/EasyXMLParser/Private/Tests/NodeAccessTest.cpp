// Copyright 2019 ayumax. All Rights Reserved.
#include "Misc/AutomationTest.h"
#include "EasyXMLParseManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNodeAccessTest, "EasyXMLParser.NodeAccessTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FNodeAccessTest::RunTest(const FString& Parameters)
{
	{
		FString xmlString = TEXT("<root>\r")
								TEXT("<!-- comment desu -->\r")
								TEXT("<abc attr1=\"10\" attr2=\"false\">\r")								
									TEXT("123\r")
								TEXT("</abc>\r")
								TEXT("<abc/>\r")
								TEXT("<abc>40</abc>\r")
								TEXT("<abc>ZZZZ</abc>\r")
								TEXT("<bbb>\r")
									TEXT("bbbChild\r")
								TEXT("</bbb>\r")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);
		
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc", isSuccess), "123");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[0]", isSuccess), "123");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[1]", isSuccess), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[2]", isSuccess), "40");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[3]", isSuccess), "ZZZZ");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.bbb", isSuccess), "bbbChild");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[0].@attr1", isSuccess), "10");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[0].@attr2", isSuccess), "false");
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNodeAccessTest2, "EasyXMLParser.NodeAccessTest2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FNodeAccessTest2::RunTest(const FString& Parameters)
{
	{
		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		TestEqual(TEXT("success read"), rootNode->ReadInt("PurchaseOrder.@PurchaseOrderNumber", isSuccess), 99503);
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.@OrderDate", isSuccess), "1999-10-20");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].@Type", isSuccess), "Shipping");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Name", isSuccess), "Ellen Adams");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Street", isSuccess), "123 Maple Street");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].City", isSuccess), "Mill Valley");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].State", isSuccess), "CA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Zip", isSuccess), "10999");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Country", isSuccess), "USA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].@Type", isSuccess), "Billing");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Name", isSuccess), "Tai Yee");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Street", isSuccess), "8 Oak Avenue");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].City", isSuccess), "Old Town");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].State", isSuccess), "PA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Zip", isSuccess), "95819");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Country", isSuccess), "USA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.DeliveryNotes", isSuccess), "Please leave packages in shed by driveway.");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].@PartNumber", isSuccess), "872-AA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].ProductName", isSuccess), "Lawnmower");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].Quantity", isSuccess), "1");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].USPrice", isSuccess), "148.95");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].Comment", isSuccess), "Confirm this is electric");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].@PartNumber", isSuccess), "926-AA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].ProductName", isSuccess), "Baby Monitor");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].Quantity", isSuccess), "2");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].USPrice", isSuccess), "39.98");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].ShipDate", isSuccess), "1999-05-21");
	}

	{
		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		auto Address0Node = rootNode->ReadElement("PurchaseOrder.Address[0]", isSuccess);
		auto Address1Node = rootNode->ReadElement("PurchaseOrder.Address[1]", isSuccess);
		auto Item0Node = rootNode->ReadElement("PurchaseOrder.Items.Item[0]", isSuccess);
		auto Item1Node = rootNode->ReadElement("PurchaseOrder.Items.Item[1]", isSuccess);

		TestEqual(TEXT("success read"), rootNode->ReadInt("PurchaseOrder.@PurchaseOrderNumber", isSuccess), 99503);
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.@OrderDate", isSuccess), "1999-10-20");
		TestEqual(TEXT("success read"), Address0Node->ReadString("@Type", isSuccess), "Shipping");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Name", isSuccess), "Ellen Adams");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Street", isSuccess), "123 Maple Street");
		TestEqual(TEXT("success read"), Address0Node->ReadString("City", isSuccess), "Mill Valley");
		TestEqual(TEXT("success read"), Address0Node->ReadString("State", isSuccess), "CA");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Zip", isSuccess), "10999");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Country", isSuccess), "USA");
		TestEqual(TEXT("success read"), Address1Node->ReadString("@Type", isSuccess), "Billing");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Name", isSuccess), "Tai Yee");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Street", isSuccess), "8 Oak Avenue");
		TestEqual(TEXT("success read"), Address1Node->ReadString("City", isSuccess), "Old Town");
		TestEqual(TEXT("success read"), Address1Node->ReadString("State", isSuccess), "PA");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Zip", isSuccess), "95819");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Country", isSuccess), "USA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.DeliveryNotes", isSuccess), "Please leave packages in shed by driveway.");
		TestEqual(TEXT("success read"), Item0Node->ReadString("@PartNumber", isSuccess), "872-AA");
		TestEqual(TEXT("success read"), Item0Node->ReadString("ProductName", isSuccess), "Lawnmower");
		TestEqual(TEXT("success read"), Item0Node->ReadString("Quantity", isSuccess), "1");
		TestEqual(TEXT("success read"), Item0Node->ReadString("USPrice", isSuccess), "148.95");
		TestEqual(TEXT("success read"), Item0Node->ReadString("Comment", isSuccess), "Confirm this is electric");
		TestEqual(TEXT("success read"), Item1Node->ReadString("@PartNumber", isSuccess), "926-AA");
		TestEqual(TEXT("success read"), Item1Node->ReadString("ProductName", isSuccess), "Baby Monitor");
		TestEqual(TEXT("success read"), Item1Node->ReadString("Quantity", isSuccess), "2");
		TestEqual(TEXT("success read"), Item1Node->ReadString("USPrice", isSuccess), "39.98");
		TestEqual(TEXT("success read"), Item1Node->ReadString("ShipDate", isSuccess), "1999-05-21");
	}

	return true;
}