#pragma once

namespace nn::util {

class IntrusiveListNode {
private:
    template <typename T, typename NodeTraits>
    friend class IntrusiveList;

    IntrusiveListNode* m_Prev = this;
    IntrusiveListNode* m_Next = this;
};

template <typename T, typename NodeTraits>
class IntrusiveList {
public:
    using pointer = T*;
    using reference = T&;

    class iterator {
    public:
        bool operator==(iterator other) const { return m_Node == other.m_Node; }

        bool operator!=(iterator other) const { return m_Node != other.m_Node; }

        iterator& operator++() { m_Node = m_Node->m_Next; }

        iterator operator++(int) {
            iterator old = *this;
            operator++();
            return old;
        }

        iterator& operator--() { m_Node = m_Node->m_Prev; }

        iterator operator--(int) {
            iterator old = *this;
            operator++();
            return old;
        }

    private:
        friend class IntrusiveList;

        explicit iterator(IntrusiveListNode* node) : m_Node(node) {}

        IntrusiveListNode* m_Node;
    };

    iterator begin() { return iterator(m_Sentinel.m_Next); }

    iterator end() { return iterator(&m_Sentinel); }

    iterator erase(iterator it) {
        if (it == end())
            return it;
        IntrusiveListNode* next = it.m_Node->m_Next;
        IntrusiveListNode* node = next->m_Prev;
        it.m_Node->m_Prev->m_Next = next;
        next->m_Prev = it.m_Node->m_Prev;
        node->m_Next = it.m_Node;
        it.m_Node->m_Prev = node;
        return iterator(next);
    }

    iterator insert(iterator pos, reference value) {
        IntrusiveListNode* first = NodeTraits::from_value(value);
        IntrusiveListNode* last = first->m_Prev;
        first->m_Prev = pos.m_Node->m_Prev;
        last->m_Next = pos.m_Node;
        pos.m_Node->m_Prev->m_Next = first;
        pos.m_Node->m_Prev = last;
        return iterator(first);
    }

    iterator iterator_to(reference value) { return iterator(NodeTraits::from_value(value)); }

private:
    IntrusiveListNode m_Sentinel;
};

template <typename Base, IntrusiveListNode Base::* Node, typename T>
class IntrusiveListMemberNodeTraits {
public:
    static IntrusiveListNode* from_value(T& value) { return &(value.*Node); }
};

template <typename T, typename>
class IntrusiveListBaseNodeTraits {
public:
    static IntrusiveListNode* from_value(T& value) {
        return dynamic_cast<IntrusiveListNode*>(&value);
    }
};

}  // namespace nn::util
