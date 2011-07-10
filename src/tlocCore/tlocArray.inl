namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Macros


#define TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(index) \
#index _CRT_WIDE(" is out of range!")

#define TLOC_ASSERT_ARRAY_INDEX(index) \
  TLOC_ASSERT_ARRAY(index < size(), "Index out of bounds!")

#define TLOC_ASSERT_ARRAY_NOT_EMPTY() \
  TLOC_ASSERT_ARRAY(size > 0, "Array is empty!")

#define TLOC_ASSERT_ARRAY_NOT_FULL() \
  TLOC_ASSERT_ARRAY(full() == false, "Array is full!")

#define TLOC_ASSERT_ARRAY_POSITION(position) \
  TLOC_ASSERT_ARRAY(position >= m_begin && position <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(position) )

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN(rangeBegin) \
  TLOC_ASSERT_ARRAY(rangeBegin >= m_begin && rangeBegin < m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeBegin) )

#define TLOC_ASSERT_ARRAY_RANGE_END(rangeEnd) \
  TLOC_ASSERT_ARRAY(rangeEnd <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeEnd) )

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd) \
  TLOC_ASSERT_ARRAY_RANGE_BEGIN(aRangeBegin);\
  TLOC_ASSERT_ARRAY_RANGE_END(aRangeEnd);\
  TLOC_ASSERT_ARRAY(aRangeBegin < aRangeEnd,\
# aRangeBegin _CRT_WIDE(" must be smaller than ") _CRT_WIDE(# aRangeEnd) L"!")

  //////////////////////////////////////////////////////////////////////////
  // Constants

  template <typename T>
  const tl_sizet ArrayBase<T>::sm_defaultCapacity = 2;

  //////////////////////////////////////////////////////////////////////////
  // ArrayBase<T>

  template <typename T>
  ArrayBase<T>::ArrayBase()
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
  }

  template <typename T>
  ArrayBase<T>::ArrayBase( tl_sizet aSize )
  {
    m_begin = DoAllocate(aSize);
    TLOC_ASSERT_CONTAINERS(m_begin != NULL,
                            "Could not allocate Array!");
    m_end = m_begin;
    m_capacity = m_begin + aSize;
  }

  template <typename T>
  ArrayBase<T>::~ArrayBase()
  {
    if (m_begin)
    {
      DoDestroyValues(m_begin, m_end);
      DoFree(m_begin);
    }
  }

  //------------------------------------------------------------------------
  // Element access

  template <typename T>
  TL_I T& ArrayBase<T>::at( tl_sizet aIndex )
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::at( tl_sizet aIndex ) const
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& ArrayBase<T>::operator[]( tl_sizet aIndex )
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::operator[]( tl_sizet aIndex ) const
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& ArrayBase<T>::front()
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return m_begin;
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::front() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return m_begin;
  }

  template <typename T>
  TL_I T& ArrayBase<T>::back()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return m_end;
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::back() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return m_end;
  }

  template <typename T>
  TL_I T* ArrayBase<T>::data()
  {
    return m_begin;
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <typename T>
  TL_I T* ArrayBase<T>::begin()
  {
    return m_begin;
  }

  template <typename T>
  TL_I const T* ArrayBase<T>::begin() const
  {
    return m_begin;
  }

  template <typename T>
  TL_I T* ArrayBase<T>::end()
  {
    return m_end;
  }

  template <typename T>
  TL_I const T* ArrayBase<T>::end() const
  {
    return m_end;
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I tl_sizet ArrayBase<T>::size() const
  {
    return (m_end - m_begin);
  }

  template <typename T>
  TL_I tl_sizet ArrayBase<T>::capacity() const
  {
    return (m_capacity - m_begin);
  }

  template <typename T>
  TL_I bool ArrayBase<T>::empty() const
  {
    return size() > 0 ? true : false;
  }

  template <typename T>
  TL_I bool ArrayBase<T>::full() const
  {
    return (m_end == m_capacity);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_I void ArrayBase<T>::pop_back()
  {
    --m_end;
    m_end->~T();
  }

  template <typename T>
  TL_I void ArrayBase<T>::pop_back( T& aOut )
  {
    aOut = *(m_end);
    --m_end;
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::erase( iterator aPosition )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN(aPosition);

    aPosition->~T();
    Copy(aPosition + 1, m_end, aPosition);
    --m_end;
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::erase( iterator aRangeBegin, iterator aRangeEnd )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd);

    iterator copyRemainingTo = aRangeBegin;

    while (aRangeBegin != aRangeEnd)
    {
      aRangeBegin->~T();
      ++aRangeBegin;
    }

    Copy(aRangeEnd, m_end, copyRemainingTo);

    m_end = m_begin;
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::clear()
  {
    erase(m_begin, m_end);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I T* ArrayBase<T>::DoAllocate( tl_sizet aSize )
  {
    return aSize ? (T*)TL_MALLOC(aSize * sizeof(T)) : NULL;
  }

  template <typename T>
  TL_I T* ArrayBase<T>::DoReAllocate( tl_sizet aSize )
  {
    return (T*)TL_REALLOC(m_begin, sizeof(T) * aSize);
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoFree( T* aPtr)
  {
    TL_FREE(aPtr);
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoDestroyValues(T* aRangeBegin, T* aRangeEnd)
  {
    while (aRangeBegin != aRangeEnd)
    {
      aRangeBegin->~T();
      ++aRangeBegin;
    }
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoAddToEnd( const T& aValueToCopy )
  {
    TLOC_ASSERT_ARRAY_NOT_FULL();

    new(m_end) T(aValueToCopy); // placement new
    ++m_end;
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoReAllocate()
  {
    tl_sizet prevSize = size();
    tl_sizet prevCap  = capacity();
    tl_sizet newCap  = prevCap ? (2 * prevCap) : sm_defaultCapacity;
    T* ptr;

    // DoReallocate may malloc or realloc depending on the initial size
    ptr = DoReAllocate(newCap);

    TLOC_ASSERT_ARRAY(ptr != NULL, "Could not allocate/re-allocate!");

    if (ptr)
    {
      m_begin = ptr;
      m_end = m_begin + prevSize;
      m_capacity = m_begin + newCap;
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Array<T>

  //------------------------------------------------------------------------
  // Constructors

  template <typename T>
  Array<T>::Array() : ArrayBase()
  {
  }

  template <typename T>
  Array<T>::Array( tl_sizet aSize ) : ArrayBase(aSize)
  {
    Allocate(aSize);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I void Array<T>::resize( tl_sizet aNewSize )
  {
    /*tl_sizet currSize = size();
    if (aNewSize > currSize)
    {
      insert(m_end, aNewSize - currSize, T());
    }
    else
    {
      erase(m_begin + aNewSize, m_end);
    }*/
  }

  template <typename T>
  TL_I void Array<T>::resize( tl_sizet aNewSize, const T& aValue )
  {
    /*tl_sizet currSize = size();
    if (aNewSize > currSize)
    {
      insert(m_end, aNewSize - currSize, aValue);
    }
    else
    {
      erase(m_begin + aNewSize, m_end);
    }*/
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_I void Array<T>::assign( tl_sizet aRepetitionNum, const T& aElemToCopy )
  {
    if (capacity() < aRepetitionNum)
    {
      resize(aRepetitionNum);
    }

    Fill(m_begin, m_begin + aRepetitionNum, aElemToCopy);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::assign( T_InputIterator aRangeBegin,
                              T_InputIterator aRangeEnd )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd);

    tl_sizet projectedSize = aRangeEnd - aRangeBegin;
    if (capacity() < projectedSize)
    {
      resize(projectedSize);
    }

    Copy(aRangeBegin, aRangeEnd, m_begin);
  }

  template <typename T>
  void Array<T>::push_back( const T& aValueToCopy )
  {
    if (m_end < m_capacity)
    {
      DoAddToEnd(aValueToCopy);
    }
    else
    {
      DoReAllocate();
      DoAddToEnd(aValueToCopy);
    }
  }

  template <typename T>
  TL_I typename Array<T>::iterator
    Array<T>::insert( iterator aPosition, const T& aValueToCopy )
  {
    TLOC_ASSERT_ARRAY_POSITION(aPosition);

    const tl_sizet posIndex = aPosition - m_begin;

    if (full() || aPosition != m_end)
    {
      DoInsertValue(aPosition, aValueToCopy);
    }
    else
    {
      ::new(m_end++) T(aValueToCopy);
    }

    return m_begin + posIndex;;
  }

  template <typename T>
  TL_I typename Array<T>::iterator
    Array<T>::insert( iterator aPosition, tl_sizet aNumElemsToInsert,
                      const T& aValueToCopy )
  {

  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I typename Array<T>::iterator
    Array<T>::insert( iterator aPosition, T_InputIterator aRangeBegin,
                      T_InputIterator aRangeEnd )
  {

  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I void Array<T>::DoInsertValue( T* aPosition, const T& aValue )
  {
    TLOC_ASSERT_ARRAY_POSITION(aPosition);

    if (m_end != m_capacity)
    {
      // Value may be from within the range of the array, in which case, it will
      // be moved by one
      const T* valuePtr = &aValue;
      if (valuePtr >= aPosition && valuePtr < m_end)
      {
        ++valuePtr;
      }

      ::new(m_end) T(*(m_end - 1)); // We need to allocate it first
      Copy_Backward(aPosition, m_end - 1, m_end);
      *aPosition = *valuePtr;
      ++m_end;
    }
    else
    {
      // Value may be from within the range of the array, in which case, it may
      // be destroyed, so make a copy
      const T valueCopy = aValue;
      tl_sizet posIndex = aPosition - m_begin;
      DoReAllocate();
      insert(m_begin + posIndex, valueCopy);
    }
  }

  template <typename T>
  TL_I void tloc::Array<T>::DoInsertValues( T* position,
                                            tl_sizet aNumElemsToInsert,
                                            const T& aValue )
  {
    TLOC_ASSERT_ARRAY_POSITION(position);
    TLOC_ASSERT_ARRAY(aNumElemsToInsert > 0, "Inserting 0 elements!");

    // Check if we have enough capacity to store the elements
    if (aNumElemsToInsert <= m_capacity - m_end)
    {
      // value may be from within the array, copy it
      const T valueCopy = aValue;
      const tl_sizet spaceRequired = (tl_sizet)(m_end - position);
      const T* prevEnd = m_end;

      T* itr = m_end - position;
      while (m_end != position + spaceRequired)
      {
        ::new(m_end++) T(*(itr++));
      }

      while (position != position + aNumElemsToInsert)
      {
        *(position++) = aValue;
      }
    }
    else
    {

    }
  }
};