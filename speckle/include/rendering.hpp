#ifndef SPECKLE_RENDERING_H
#define SPECKLE_RENDERING_H

namespace speckle {
namespace rendering {

extern "C" {

using ID = int;
typedef void* (* LoadProcess)(const char *name);


void InitializeWith(LoadProcess loading);
ID MakeRenderer();

void Resize(ID self, unsigned int width, unsigned int height);
void Render(ID self);
void DisposeRenderer(ID id);

}

} // namespace rendering
} // namespace speckle

#endif //SPECKLE_RENDERING_H
