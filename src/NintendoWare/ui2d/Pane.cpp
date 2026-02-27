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
    copyString(name, mPanelName, 24);
}

void Pane::SetUserData(const char* user_data) {
    copyString(user_data, mUserData, 8);
}

void Pane::AppendChild(Pane* child) {
    InsertChild(mChildList.end(), child);
}

void Pane::InsertChild(PaneList::iterator pos, Pane* child) {
    mChildList.insert(pos, *child);
    child->mParent = this;
    child->mFlags |= 16;
}

void Pane::PrependChild(Pane* child) {
    InsertChild(mChildList.begin(), child);
}

void Pane::InsertChild(Pane* position, Pane* child) {
    InsertChild(mChildList.iterator_to(*position), child);
}

void Pane::RemoveChild(Pane* child) {
    mChildList.erase(mChildList.iterator_to(*child));
    child->mParent = nullptr;
}

}  // namespace nn::ui2d
