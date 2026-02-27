/**
 * @file Pane.h
 * @brief Base UI panel.
 */

#pragma once

#include <nn/font/font_Util.h>
#include <nn/gfx/gfx_Device.h>
#include <nn/types.h>
#include <nn/ui2d/Types.h>
#include <nn/util.h>
#include <nn/util/MathTypes.h>
#include <nn/util/util_IntrusiveList.h>

namespace nn::util {
struct Unorm8x4;
}

namespace nn::ui2d::detail {

class PaneBase {
    NN_NO_COPY(PaneBase);

public:
    PaneBase();
    virtual ~PaneBase();

    util::IntrusiveListNode m_Link;
};

}  // namespace nn::ui2d::detail

namespace nn::ui2d {
class AnimTransform;
class Layout;
class DrawInfo;
class ResPane;
struct BuildArgSet;
class Material;
struct ResExtUserDataList;

class Pane : public detail::PaneBase {
public:
    NN_RUNTIME_TYPEINFO_BASE()

    struct CalculateContext {
        void SetDefault();
        void Set(const DrawInfo&, const Layout*);
    };

    typedef util::IntrusiveList<Pane, util::IntrusiveListMemberNodeTraits<
                                          detail::PaneBase, &detail::PaneBase::m_Link, Pane>>
        PaneList;

    Pane();
    Pane(const ResPane*, const BuildArgSet&);
    Pane(const Pane&);

    ~Pane() override;
    virtual void Finalize(gfx::Device*);
    virtual s32 GetVertexColor(s32);
    virtual void SetVertexColor(s32, const util::Unorm8x4&);
    virtual u8 GetColorElement(s32);
    virtual void SetColorElement(u32, u8);
    virtual u8 GetVertexColorElement(s32);
    virtual void SetVertexColorElement(u32, u8);
    virtual u32 GetMaterialCount() const;
    virtual Material* GetMaterial(s32) const;
    virtual Pane* FindPaneByName(const char*, bool);
    virtual const Pane* FindPaneByName(const char*, bool) const;
    virtual Material* FindMaterialByName(const char*, bool);
    virtual const Material* FindMaterialByName(const char*, bool) const;
    virtual void BindAnimation(AnimTransform*, bool, bool);
    virtual void UnbindAnimation(AnimTransform*, bool);
    virtual void UnbindAnimationSelf(AnimTransform*);
    virtual void Calculate(DrawInfo&, CalculateContext&, bool);
    virtual void Draw(DrawInfo&, gfx::CommandBuffer&);
    virtual void DrawSelf(DrawInfo&, gfx::CommandBuffer&);

    void SetName(const char*);
    void SetUserData(const char*);
    Material* GetMaterial() const;
    void AppendChild(Pane*);
    void PrependChild(Pane*);
    void InsertChild(Pane*, Pane*);
    void InsertChild(PaneList::iterator, Pane*);
    void RemoveChild(Pane*);

    void Show() { SetVisible(true); }
    void Hide() { SetVisible(false); }

    bool IsVisible() const { return detail::TestBit(mFlags, PaneFlag_Visible); }
    bool IsInfluencedAlpha() const { return detail::TestBit(mFlags, PaneFlag_InfluencedAlpha); }
    bool IsLocationAdjust() const { return detail::TestBit(mFlags, PaneFlag_LocationAdjust); }
    bool IsUserAllocated() const { return detail::TestBit(mFlags, PaneFlag_UserAllocated); }
    bool IsGlobalMatrixDirty() const {
        return detail::TestBit(mFlags, PaneFlag_IsGlobalMatrixDirty);
    }
    bool IsUserMatrix() const { return detail::TestBit(mFlags, PaneFlag_UserMatrix); }
    bool IsUserGlobalMatrix() const { return detail::TestBit(mFlags, PaneFlag_UserGlobalMatrix); }
    bool IsConstantBufferReady() const {
        return detail::TestBit(mFlags, PaneFlag_IsConstantBufferReady);
    }
    bool IsMaxPanelFlag() const { return detail::TestBit(mFlags, PaneFlag_MaxPaneFlag); }

    const util::Float3& GetPosition() const { return mPosition; }
    void SetPosition(const util::Float3& position) {
        mPosition = position;
        SetGlobalMatrixDirty(true);
    }

    const util::Float3& GetRotation() const { return mRotation; }
    void SetRotation(const util::Float3& rotation) {
        mRotation = rotation;
        SetGlobalMatrixDirty(true);
    }

    const util::Float2& GetScale() const { return mScale; }
    void SetScale(const util::Float2& scale) {
        mScale = scale;
        SetGlobalMatrixDirty(true);
    }

    const Size& GetSize() const { return mSize; }
    void SetSize(const Size& size) {
        mSize.Set(size.width, size.height);
        SetGlobalMatrixDirty(true);
    }

    void SetAlpha(u8 alpha) { mAlpha = alpha; }

    u8 GetGlobalAlpha() const { return mGlobalAlpha; }

    const util::MatrixT4x3fType& GetMtx() const { return mMtx; }

protected:
    virtual void LoadMtx(DrawInfo&);
    virtual Pane* FindPaneByNameRecursive(const char*);
    virtual const Pane* FindPaneByNameRecursive(const char*) const;
    virtual Material* FindMaterialByNameRecursive(const char*);
    virtual const Material* FindMaterialByNameRecursive(const char*) const;

    const util::Float2& GetVertexPos() const;

    void SetVisible(bool state) { detail::SetBit(&mFlags, PaneFlag_Visible, state); }
    void SetInfluencedAlpha(bool state) {
        detail::SetBit(&mFlags, PaneFlag_InfluencedAlpha, state);
    }
    void SetLocationAdjust(bool state) { detail::SetBit(&mFlags, PaneFlag_LocationAdjust, state); }
    void SetUserAllocated(bool state) { detail::SetBit(&mFlags, PaneFlag_UserAllocated, state); }
    void SetGlobalMatrixDirty(bool state) {
        detail::SetBit(&mFlags, PaneFlag_IsGlobalMatrixDirty, state);
    }
    void SetUserMatrix(bool state) { detail::SetBit(&mFlags, PaneFlag_UserMatrix, state); }
    void SetUserGlobalMatrix(bool state) {
        detail::SetBit(&mFlags, PaneFlag_UserGlobalMatrix, state);
    }
    void setConstantBufferReady(bool state) {
        detail::SetBit(&mFlags, PaneFlag_IsConstantBufferReady, state);
    }
    void setMaxPanelFlag(bool state) { detail::SetBit(&mFlags, PaneFlag_MaxPaneFlag, state); }

private:
    void Initialize();
    const Pane& operator=(const Pane&);
    void CalculateScaleFromPartsRoot(util::Float2*, Pane*) const;
    void AllocateAndCopyAnimatedExtUserData(const ResExtUserDataList*);
    void CalculateGlobalMatrixSelf(CalculateContext&);

    Pane* mParent = nullptr;
    PaneList mChildList;
    util::Float3 mPosition = {{{0, 0, 0}}};
    util::Float3 mRotation = {{{0, 0, 0}}};
    util::Float2 mScale = {{{1, 1}}};
    Size mSize = {0, 0};
    u8 mFlags = 0x11;
    u8 mAlpha = 0xff;
    u8 mGlobalAlpha = 0xff;
    u8 mBasePosition = 0;
    u8 mFlagEx = 0;
    u32 mSystemDataFlags;
    Layout* mLayout;
    util::MatrixT4x3fType mMtx = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
    }};
    const util::MatrixT4x3fType* mUserMtx = nullptr;
    const ResExtUserDataList* mExtUserDataList = nullptr;
    void* mAnimExtUserData = nullptr;
    char mPanelName[25] = {};
    char mUserData[9] = {};
};
}  // namespace nn::ui2d
