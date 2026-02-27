#include "nn/vfx/Emitter.h"

#include "nn/types.h"
#include "nn/util/MathTypes.h"

namespace nn::vfx::detail {

void _MatrixFromQuaternion(util::neon::MatrixRowMajor4x3fType* out,
                           const util::neon::Vector4fType& q) {
    f32 factor = 2 / (q.v[0] * q.v[0] + q.v[1] * q.v[1] + q.v[2] * q.v[2] + q.v[3] * q.v[3]);
    f32 wx = factor * q.v[0] * q.v[3];
    f32 wy = factor * q.v[1] * q.v[3];
    f32 wz = factor * q.v[2] * q.v[3];
    f32 xx = factor * q.v[0] * q.v[0];
    f32 xy = factor * q.v[1] * q.v[0];
    f32 xz = factor * q.v[2] * q.v[0];
    f32 yy = factor * q.v[1] * q.v[1];
    f32 yz = factor * q.v[2] * q.v[1];
    f32 zz = factor * q.v[2] * q.v[2];
    out->m[0] = {1 - (yy + zz), xy + wz, xz - wy, 0};
    out->m[1] = {xy - wz, 1 - (xx + zz), yz + wx, 0};
    out->m[2] = {xz + wy, yz - wx, 1 - (xx + yy), 0};
    out->m[3] = {0, 0, 0, 0};
}

}  // namespace nn::vfx::detail
