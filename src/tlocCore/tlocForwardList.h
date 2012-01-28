#ifndef TLOC_FORWARD_LIST_H
#define TLOC_FORWARD_LIST_H

#include "tlocList.h"
#include "tlocIterator.h"

namespace tloc { namespace core {

  template <typename T>
  class ForwardList
    : private List<T, ListNode<T, singly_linked_tag>, List_Dynamic(), false>
  {
  private:
    //--------------------------------------------------------------------------
    // typedefs
    typedef List
      <T, ListNode<T, singly_linked_tag>, List_Dynamic(), false>
                                                              this_type;
    typedef ListNode<T, singly_linked_tag>                    node_type;

  public:
    //--------------------------------------------------------------------------
    // typedefs (similar to forward_list)
    typedef T                                                 value_type;
    typedef tl_size                                           size_type;
    typedef tl_ptrdiff                                        difference_type;
    typedef T&                                                reference;
    typedef const T&                                          const_reference;
    typedef T*                                                pointer;
    typedef const T*                                          const_pointer;

    typedef list_iterator
      <node_type, typename node_type::iterator_category, T>
                                                              iterator;
    typedef list_iterator
      <node_type, typename node_type::iterator_category, T, const T*, const T&>
                                                              const_iterator;

    //--------------------------------------------------------------------------
    // Functions
    //
    // Notes: The following methods, unlike all other methods in the engine
    // are started with lower case and match std::forward_list. This is to
    // facilitate switching between the containers easily if need be

    //--------------------------------------------------------------------------
    // Constructors

    TL_FI ForwardList();
    TL_FI ForwardList(size_type aCount, const T& value = T());
    template <typename T_InputIterator>
    TL_FI ForwardList(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd);
    TL_FI ForwardList(const this_type& aOther);

    //--------------------------------------------------------------------------
    // Assignment

    TL_FI this_type&            operator= (const this_type& aOther);
    TL_FI void                  assign(size_type aCount, const T& aValue);
    template <typename T_InputIterator>
    TL_FI void                  assign(T_InputIterator aFirst,
                                       T_InputIterator aLast);

    //--------------------------------------------------------------------------
    // Element Access

    TL_FI reference             front();
    TL_FI const_reference       front() const;

    //--------------------------------------------------------------------------
    // Iterators

    TL_FI iterator              before_begin();
    TL_FI const_iterator        before_begin() const;
    TL_FI const_iterator        cbefore_begin() const;

    TL_FI iterator              begin();
    TL_FI const_iterator        begin() const;
    TL_FI const_iterator        cbegin() const;

    TL_FI iterator              end();
    TL_FI const_iterator        end() const;
    TL_FI const_iterator        cend() const;

    //--------------------------------------------------------------------------
    // Capacity

    TL_FI bool                  empty() const;
    TL_FI size_type             max_size() const;

    //--------------------------------------------------------------------------
    // Modifiers

    TL_FI void                  clear();

    TL_FI iterator              insert_after(const_iterator aPos,
                                             const value_type& aValue);
    TL_FI void                  insert_after(const_iterator aPos,
                                             size_type aNumOfValues,
                                             const value_type& aValue);
    template <typename T_Iterator>
    TL_FI void                  insert_after(const_iterator aPos,
                                            T_Iterator aFirst,
                                            T_Iterator aLast);

    TL_FI iterator              erase_after(const_iterator aPos);
    TL_FI iterator              erase_after(const_iterator aFirst,
                                            const_iterator aLast);

    TL_FI void                  push_front(const T& aValue);

    TL_FI void                  pop_front();

    TL_FI void                  swap(this_type& aOther);

    //--------------------------------------------------------------------------
    // Operations

    TL_FI void                  merge(this_type& aOther);
    template <typename T_Compare>
    TL_FI void                  merge(this_type& aOther, T_Compare aComp);

    TL_FI void                  splice_after(iterator aPos, this_type& aFrom);
    TL_FI void                  splice_after(iterator aPos, this_type& aFrom,
                                             iterator aOther);
    TL_FI void                  splice_after(iterator aPos, this_type& aFrom,
                                             iterator aOtherBegin,
                                             iterator aOtherEnd);

    template <typename T_Pred>
    TL_FI void                  remove_if(T_Pred aFunctionToCompare);

    TL_FI void                  reverse();

    TL_FI void                  unique();
    template <typename T_Pred>
    TL_FI void                  unique(T_Pred aBinaryPred);

    TL_FI void                  sort();
    template <typename T_Compare>
    TL_FI void                  sort(T_Compare aComp);

  };

};};

#endif