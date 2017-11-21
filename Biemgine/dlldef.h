#pragma once

#ifdef BIEMGINE_EXPORTS
#define BIEMGINE __declspec(dllexport)
#else  
#define BIEMGINE __declspec(dllimport)
#endif
