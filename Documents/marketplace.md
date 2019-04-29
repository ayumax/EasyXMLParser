EasyXMLParser

Library to easily get value from xml

---

EasyXMLParser is a library to easily get values ​​from xml.


---

Features:

Values ​​in XML can be obtained by the following types.
+ string
+ int
+ float
+ bool


For example, you can easily refer to values ​​by simply connecting tags with dots as follows:

<Root>
  <ABC id="1">123</ABC>
  <ABC id="2">456</ABC>
  <ABC id="3">789</ABC>
</Root>

Root.ABC[1] => 456
Root.ABC[2].@id => 3


Code Modules: EasyXMLParser
Intended Platform: Win,Mac,LinuxIntended Platform: All
Platforms Tested: Windows
Documentation: https://github.com/ayumax/EasyXMLParserSample/blob/master/README.md
Example Project:https://github.com/ayumax/EasyXMLParserSample

Changelog
(04/29/2019) Version 1.00: Initial release