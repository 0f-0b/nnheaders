/**
 * @file Pane.h
 * @brief Base UI panel.
 */

#pragma once

#include "nn/font/font_Util.h"
#include "nn/gfx/gfx_Types.h"
#include "nn/util/MathTypes.h"
#include "nn/util/util_IntrusiveList.h"

namespace nn::ui2d {
class AnimTransform;
class BuildArgSet;
class DrawInfo;
class Layout;
class Material;
class ResExtUserDataList;
class ResPane;
class Pane;

namespace detail {

class PaneBase {
public:
    PaneBase();
    virtual ~PaneBase();

private:
    friend class ui2d::Pane;

    util::IntrusiveListNode m_Link;
};

}  // namespace detail

class Pane : public detail::PaneBase {
public:
    struct CalculateContext {
        void SetDefault();
        void Set(const DrawInfo&, const Layout*);
    };

    NN_RUNTIME_TYPEINFO_BASE()

    Pane();
    Pane(const ResPane*, const BuildArgSet&);
    Pane(const Pane&);
    ~Pane() override;

    virtual void Finalize(gfx::Device*);
    virtual const util::Unorm8x4& GetVertexColor(s32) const;
    virtual void SetVertexColor(s32, const util::Unorm8x4&);
    virtual u8 GetColorElement(s32) const;
    virtual void SetColorElement(s32, u8);
    virtual u8 GetVertexColorElement(s32) const;
    virtual void SetVertexColorElement(s32, u8);
    virtual s32 GetMaterialCount() const;
    virtual Material* GetMaterial(s32) const;
    virtual Pane* FindPaneByName(const char*, bool);
    virtual Pane* FindPaneByName(const char*, bool) const;
    virtual Material* FindMaterialByName(const char*, bool);
    virtual Material* FindMaterialByName(const char*, bool) const;
    virtual void BindAnimation(AnimTransform*, bool, bool);
    virtual void UnbindAnimation(AnimTransform*, bool);
    virtual void UnbindAnimationSelf(AnimTransform*);
    virtual void Calculate(DrawInfo&, CalculateContext&, bool);
    virtual void Draw(DrawInfo&, gfx::CommandBuffer&);
    virtual void DrawSelf(DrawInfo&, gfx::CommandBuffer&);
    virtual void LoadMtx(DrawInfo&);
    virtual Pane* FindPaneByNameRecursive(const char* name);
    virtual Pane* FindPaneByNameRecursive(const char* name) const;
    virtual Material* FindMaterialByNameRecursive(const char* name);
    virtual Material* FindMaterialByNameRecursive(const char* name) const;

    void Initialize();
    void SetName(const char* name);
    void SetUserData(const char* user_data);
    void AllocateAndCopyAnimatedExtUserData(const ResExtUserDataList*);
    void CalculateScaleFromPartsRoot(util::Float2*, Pane*) const;
    void AppendChild(Pane* child);
    void InsertChild(
        util::IntrusiveList<Pane, util::IntrusiveListMemberNodeTraits<PaneBase, &PaneBase::m_Link,
                                                                      Pane>>::iterator pos,
        Pane* child);
    void PrependChild(Pane* child);
    void InsertChild(Pane* pos, Pane* child);
    void RemoveChild(Pane* child);
    void GetPaneRect() const;
    void GetVertexPos() const;
    void CalculateGlobalMatrixSelf(CalculateContext&);
    void CompareCopiedInstanceTest(const Pane&) const;
    void CalculateGlobalMatrix(CalculateContext&, bool);
    void GetMaterial() const;
    void GetExtUserDataCount() const;
    void GetExtUserDataArray() const;
    void FindExtUserDataByName(const char*) const;
    void GetExtUserDataArrayForAnimation() const;
    void FindExtUserDataByNameForAnimation(const char*) const;

    const util::Float3& GetPosition() const { return m_Position; }

private:
    Pane* m_Parent = nullptr;
    util::IntrusiveList<Pane,
                        util::IntrusiveListMemberNodeTraits<PaneBase, &PaneBase::m_Link, Pane>>
        m_Children;
    util::Float3 m_Position = {{{0, 0, 0}}};
    util::Float3 m_Rotation = {{{0, 0, 0}}};
    util::Float2 m_Scale = {{{1, 1}}};
    util::Float2 m_Size = {{{0, 0}}};
    u8 m_Flags = 0x11;
    u8 m_Alpha = 0xff;
    u8 m_AlphaInfluence = 0xff;
    u8 m_OriginFlags = 0;
    u8 _0x5c = 0;
    s64 _0x60;
    s64 _0x68;
    util::neon::MatrixColumnMajor4x3fType _0x70 = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
    }};
    s64 _0xa0 = 0;
    s64 _0xa8 = 0;
    s64 _0xb0 = 0;
    char m_Name[25] = {};
    char m_UserData[9] = {};
};

}  // namespace nn::ui2d
