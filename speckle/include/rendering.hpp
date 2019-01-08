#ifndef SPECKLE_RENDERING_H
#define SPECKLE_RENDERING_H

#ifdef _WIN32
#define DLLExport __declspec(dllexport)
#else
#define DLLExport
#endif

namespace speckle {
namespace rendering {

extern "C" {

using ID = int;
typedef void* (* LoadProcess)(const char *name);


DLLExport void InitializeWith(LoadProcess loading);
DLLExport ID MakeRenderer();

DLLExport void Resize(ID self, unsigned int width, unsigned int height);
DLLExport void Render(ID self);
DLLExport void DisposeRenderer(ID id);

}

} // namespace rendering
} // namespace speckle

#endif //SPECKLE_RENDERING_H
