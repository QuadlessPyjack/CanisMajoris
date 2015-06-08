#ifndef ENGINE_DLL_EXPORT_H

 //! Engine DLL ENTRY
 #define CM_ENGINE_API __declspec(dllimport)
 #define ENGINE_DLL_EXPORT_H

#else

 //! Engine DLL ENTRY
 #define CM_ENGINE_API __declspec(dllexport)

#endif // ENGINE_DLL_EXPORT_H