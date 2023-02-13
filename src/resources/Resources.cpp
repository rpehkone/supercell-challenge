#include "Resources.h"

#ifdef TARGET_OS_MAC
#include "ResourcePath.h"
#else
#include <windows.h>
#include <iostream>
#endif

std::string Resources::getAssetPath()
{
#ifdef TARGET_OS_MAC
	return resourcePath() + "assets/";
#else
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf)  + "\\assets" + '\\';
#endif
}
