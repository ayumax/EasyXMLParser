# EasyXMLParser

EasyXMLParser is an XML parser for Unreal Engine.

You can get the value by using a simple access string.


To get a text node, create an access string for the value you want to get.

Access strings are created by connecting tag names with dots.

If there are multiple nodes with the same tag name, you can specify an index number starting from 0 (eg [2]-> third).
If you do not specify the index, the first element will be acquired.

![GALLERY 4](https://user-images.githubusercontent.com/8191970/57173329-f35b1e80-6e68-11e9-9cd7-a3910fb9159e.png)

The access string for acquiring the attribute is specified by (at mark + attribute name).

![GALLERY5](https://user-images.githubusercontent.com/8191970/57173330-f8b86900-6e68-11e9-9e52-4974c4dd3718.png)

# Get value

Acquisition of the value from XML prepares the following 4 functions.
+ ReadInt
+ ReadFloat
+ ReadString
+ ReadBool


Enter the access string in "AccessString".

Specify the default value for "DefaultValue". 

If the specified value does not exist in the XML, a default value is returned.

![GALLERY 1](https://user-images.githubusercontent.com/8191970/57173340-29000780-6e69-11e9-8d55-5a473a631732.png)

# Get object

There are also "ReadElement" and "ReadElements" methods that get nodes as objects rather than as values.

ReadElement gets one targeted node.

ReadElements gets an array of multiple nodes.

![GALLERY 2](https://user-images.githubusercontent.com/8191970/57173342-34533300-6e69-11e9-86af-d9bda9dafc5b.png)

# XML parsing method

There are two methods to load XML: "LoadFromFile" to load an XML file and "LoadFromString" to load an XML string.

There is also an asynchronous version that performs parsing in the background.

![GALLERY 3](https://user-images.githubusercontent.com/8191970/57173344-3cab6e00-6e69-11e9-805c-b55093fd139e.png)
