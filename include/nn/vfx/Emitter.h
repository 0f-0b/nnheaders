#pragma once

namespace nn {
namespace util::neon {
struct MatrixRowMajor4x3fType;
struct Vector4fType;
}  // namespace util::neon

namespace vfx::detail {
void _MatrixFromQuaternion(util::neon::MatrixRowMajor4x3fType* out,
                           const util::neon::Vector4fType& in);
}
}  // namespace nn
