#ifndef RENDER_HPP
#define RENDER_HPP

#include <Crunch/core/renderer/Renderer3D.hpp>
#include <Crunch/core/renderer/Matrix/Matrix.hpp>

namespace nml::coreutils::render {

void Render(Crunch::Renderer3D r, Crunch::Matrix::RenderList l);

};          // namespace nml::coreutils::render

#endif      // RENDER_HPP
