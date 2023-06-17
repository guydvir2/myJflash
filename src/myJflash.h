#ifndef myjFlash_h
#define myjFlash_h

#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define LITFS LittleFS

#ifndef PRNT
#define PRNT(a)    \
    if (useSerial) \
    Serial.print(a)
#endif
#ifndef PRNTL
#define PRNTL(a)   \
    if (useSerial) \
    Serial.println(a)
#endif

class myJflash
{

protected:
    const char *ver = "jFlash_v0.2";

public:
    bool useSerial = false;

    myJflash(bool use_s = false);
    ~myJflash();
    void set_filename(const char *filename);
    bool readFile(JsonDocument &DOC, const char *filename = nullptr);
    bool writeFile(JsonDocument &DOC, const char *filename = nullptr);
    bool exists(const char *filename = nullptr);
    String readFile2String(const char *fileName = nullptr);

private:
    const char *_filename;

    void _endFS();
    void _startFS();
    bool _saveFile(JsonDocument &DOC, const char *filename = nullptr);
    const char *_retFilename(const char *f);
};
#endif
