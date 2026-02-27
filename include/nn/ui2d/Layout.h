/**
 * @file Layout.h
 * @brief UI Layout implementation.
 */

#pragma once

#include "nn/font/font_Util.h"
#include "nn/gfx/gfx_Types.h"
#include "nn/util/util_IntrusiveList.h"

namespace nn {
namespace font {
template <typename T>
class TagProcessorBase;
}

namespace ui2d {
class AnimResource;
class AnimTransform;
class BuildArgSet;
class BuildResSet;
class BuildResultInformation;
class DrawInfo;
class Group;
class ResourceAccessor;
class Pane;

class Layout {
public:
    class PartsBuildDataSet;

    NN_RUNTIME_TYPEINFO_BASE()

    Layout();
    virtual ~Layout();

    virtual void DeleteAnimTransform(AnimTransform*);
    virtual void BindAnimation(AnimTransform*);
    virtual void UnbindAnimation(AnimTransform*);
    virtual void UnbindAnimation(Pane*);
    virtual void UnbindAllAnimation();
    virtual void BindAnimationAuto(gfx::Device*, const AnimResource&);
    virtual void Animate();
    virtual void UpdateAnimFrame(f32 frame);
    virtual void AnimateAndUpdateAnimFrame(f32 frame);
    virtual void Draw(DrawInfo&, gfx::CommandBuffer&);
    virtual void SetTagProcessor(font::TagProcessorBase<u16>*);
    virtual void BuildImpl(BuildResultInformation*, gfx::Device*, const void*, ResourceAccessor*,
                           const BuildArgSet&, const PartsBuildDataSet*);
    virtual void BuildPartsImpl(BuildResultInformation*, gfx::Device*, const void*,
                                const PartsBuildDataSet*, BuildArgSet&, BuildResSet&, u32);
    virtual void BuildPaneObj(BuildResultInformation*, gfx::Device*, u32, const void*, const void*,
                              const BuildArgSet&);
    virtual void BuildPartsLayout(BuildResultInformation*, gfx::Device*, const char*,
                                  const PartsBuildDataSet&, const BuildArgSet&);
    virtual void CalculateImpl(DrawInfo&, bool);

    static void SetAllocator(void* (*)(size_t, size_t, void*), void (*)(void*, void*), void*);
    static void AllocateMemory(size_t, size_t);
    static void AllocateMemory(size_t);
    static void FreeMemory(void* src);

    Pane* GetRootPane() const { return m_RootPane; }

private:
    util::IntrusiveListNode _8;
    Pane* m_RootPane = nullptr;
    s64 _20 = 0;
    s64 _28 = 0;
    s64 _30 = 0;
    s64 _38;
    s64 _40 = 0;
    util::IntrusiveListNode _48;
    s64 _58 = 0;
    s64 _60 = 0;
    s64 _68;
    s64 _70;
    s64 _78;
    s64 _80;
    s64 _88;
    s64 _90;
    s64 _98;

    static void* (*g_pAllocateFunction)(size_t, size_t, void*);
    static void (*g_pFreeFunction)(void*, void*);
    static void* g_pUserDataForAllocator;
};

static_assert(sizeof(Layout) == 0xa0);

}  // namespace ui2d
}  // namespace nn
