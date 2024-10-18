#ifndef __EXPORTRULE_H
#define __EXPORTRULE_H

#ifdef _WIN32	// Windows DLL export signature

#define ENGINE_API __declspec(dllexport)

#else

#define ENGINE_API

#endif
#endif