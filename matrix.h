#pragma once

#include <array>
#include <map>

namespace hw06 {

namespace details {

template<typename T, std::size_t... I>
auto toTuple(const T& array, std::index_sequence<I...>)
{
    return std::make_tuple(array[I]...);
}

template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto toTuple(const std::array<T, N>& array)
{
    return toTuple(array, Indices{});
}

}

template<typename T, T Def>
class Matrix
{
public:
  using Index = std::array<size_t, 2>;
  using Data = std::map<Index, T>;

  class Proxy
  {
  public:
    Proxy(size_t index, Data& data)
      : m_index{index, 0}
      , m_data{data}
    {
    }

    Proxy(const Index& index, Data& data)
      : m_index{index}
      , m_data{data}
    {
    }

    auto operator[](size_t i)
    {
      m_index[1] = i;
      return Proxy{m_index, m_data};
    }

    auto& operator=(const T& value)
    {
      if (value == Def) {
        m_data.erase(m_index);
        return m_default;
      }
      m_data[m_index] = value;
    }

    operator const T&() const
    {
      auto i = m_data.find(m_index);
      return i == m_data.end() ? m_default : i->second;
    }

  private:
    Index m_index;
    Data& m_data;
    T m_default{Def};
  };

  using DataIterator = typename Data::iterator;

  struct iterator : std::iterator<std::forward_iterator_tag, DataIterator>
  {
      iterator() = default;

      explicit iterator(DataIterator it)
        : m_dataIterator(it)
      {
      }

      auto& operator++()
      {
        ++m_dataIterator;
        return *this;
      }

      auto operator++(int)
      {
        auto temp = *this;
        ++m_dataIterator;
        return temp;
      }

      auto operator*()
      {
        return std::tuple_cat(details::toTuple(m_dataIterator->first), std::make_tuple(m_dataIterator->second));
      }

      bool operator==(const iterator& other) const
      {
        return m_dataIterator == other.m_dataIterator;
      }

      bool operator!=(const iterator& other) const
      {
        return !(*this == other);
      }

    private:
      DataIterator m_dataIterator{};
  };

  iterator begin()
  {
    return iterator(m_data.begin());
  }

  iterator end()
  {
    return iterator(m_data.end());
  }

  Matrix() = default;

  size_t size() const
  {
    return m_data.size();
  }

  Proxy operator[](size_t index)
  {
    return Proxy{index, m_data};
  }

private:
  Data m_data;
};

} // namespace
