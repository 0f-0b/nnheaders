#pragma once

namespace nn::ui2d {
class Pane;
class ResGroup;

class Group {
public:
    Group();
    Group(const char* name);
    Group(const ResGroup*, Pane*);
    Group(const Group&, Pane*);
    virtual ~Group();

    void AppendPane(Pane*);
    void CompareCopiedInstanceTest(const Group&) const;

private:
    void* _padding[0x6];
};

static_assert(sizeof(Group) == 0x38);

}  // namespace nn::ui2d
