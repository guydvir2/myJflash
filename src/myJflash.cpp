#include "myJflash.h"

myJflash::myJflash(bool use_s)
{
	useSerial = use_s;
}
myJflash::~myJflash()
{
	_endFS();
}
void myJflash::set_filename(const char *filename)
{
	_filename = filename;
}
bool myJflash::readFile(JsonDocument &DOC, const char *filename)
{
	_startFS();
	File readFile = LITFS.open(_retFilename(filename), "r");
	DeserializationError error = deserializeJson(DOC, readFile);
	readFile.close();

	PRNT(F("\n>>> "));
	PRNT(_retFilename(filename));

	if (error)
	{
		PRNTL(F(":Read [failed]"));
		PRNT(F("error:"));
		PRNTL(error.c_str());
		Serial.flush();
		return 0;
	}
	else
	{
		PRNTL(F(":Read [OK]"));
		Serial.flush();
		return 1;
	}
}
String myJflash::readFile2String(const char *fileName)
{
	_startFS();
	File file = LITFS.open(_retFilename(fileName), "r");

	if (file)
	{
		String t = file.readString();
		file.close();
		return t;
	}
	else
	{
		file.close();
		return "";
	}
}
bool myJflash::writeFile(JsonDocument &DOC, const char *filename)
{
	_startFS();
	return _saveFile(DOC, filename);
}
void myJflash::_startFS()
{
#if defined(ESP8266)
	LITFS.begin();
#elif defined(ESP32)
	if(LITFS.begin(true)){
		Serial.println("MOUNT_OK");
	}
	else{
		Serial.println("MOUNT_FAIL");
	}
#endif
}
void myJflash::_endFS()
{
	LITFS.end();
}
const char *myJflash::_retFilename(const char *f)
{
	if (f != nullptr)
	{
		return f;
	}
	else
	{
		return _filename;
	}
}
bool myJflash::_saveFile(JsonDocument &DOC, const char *filename)
{
	File writefile = LITFS.open(_retFilename(filename), "w");
	if (!writefile || (serializeJson(DOC, writefile) == 0))
	{
		writefile.close();
		return 0;
	}
	writefile.close();
	return 1;
}