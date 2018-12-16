#ifndef SPECKLE_RENDERING_H
#define SPECKLE_RENDERING_H

namespace speckle {
namespace rendering {

using ID = unsigned int;

typedef void *(*ProcAddressFactoryFun)(const char *name);

ID MakeRenderer(ProcAddressFactoryFun procAddressFactory);
void Resize(ID self, unsigned int width, unsigned int height);
void Render(ID self);
void DisposeRenderer(ID id);

} // namespace rendering
} // namespace speckle

#endif //SPECKLE_RENDERING_H
