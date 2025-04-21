#include "nn/ui2d/Pane.h"

namespace nn::ui2d {
namespace detail {

PaneBase::PaneBase() = default;

PaneBase::~PaneBase() = default;

}  // namespace detail

Pane::Pane() = default;

Pane::~Pane() = default;

static void copyString(const char* src, char* dest, s32 maxlen) {
    for (s32 i = 0; i < maxlen && *src != 0; i++)
        *dest++ = *src++;
    *dest = 0;
    if (*src != 0)
        while (*src != 0)
            src++;
}

void Pane::SetName(const char* name) {
    copyString(name, m_Name, 24);
}

void Pane::SetUserData(const char* user_data) {
    copyString(user_data, m_UserData, 8);
}

void Pane::AppendChild(Pane* child) {
    InsertChild(m_Children.end(), child);
}

void Pane::InsertChild(
    util::IntrusiveList<Pane, util::IntrusiveListMemberNodeTraits<
                                  detail::PaneBase, &detail::PaneBase::m_Link, Pane>>::iterator pos,
    Pane* child) {
    m_Children.insert(pos, *child);
    child->m_Parent = this;
    child->m_Flags |= 16;
}

void Pane::PrependChild(Pane* child) {
    InsertChild(m_Children.begin(), child);
}

void Pane::InsertChild(Pane* position, Pane* child) {
    InsertChild(m_Children.iterator_to(*position), child);
}

void Pane::RemoveChild(Pane* child) {
    m_Children.erase(m_Children.iterator_to(*child));
    child->m_Parent = nullptr;
}

}  // namespace nn::ui2d
