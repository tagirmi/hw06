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

template<typename T, T Default, size_t Dimension = 2>
class Matrix
{
public:
  using Index = std::array<size_t, Dimension>;
  using Data = std::map<Index, T>;

  template<size_t N, typename F = void>
  class Proxy
  {
  public:
    Proxy(const std::array<size_t, N>& index, Data& data)
      : m_index{index}
      , m_data{data}
    {
    }

    auto operator[](size_t i)
    {
      std::array<size_t, N + 1> index;
      std::copy(std::begin(m_index), std::end(m_index), std::begin(index));
      index[N] = i;
      return Proxy<N + 1>{index, m_data};
    }

  private:
    std::array<size_t, N> m_index;
    Data& m_data;
  };

  template<typename F>
  class Proxy<Dimension, F>
  {
  public:
    Proxy(const Index& index, Data& data)
      : m_index{index}
      , m_data{data}
    {
    }

    auto& operator=(const T& value)
    {
      if (value == Default) {
        m_data.erase(m_index);
        return m_default;
      }
      m_data[m_index] = value;
      return m_data[m_index];
    }

    operator const T&() const
    {
      auto i = m_data.find(m_index);
      if (i != m_data.end())
        return i->second;

      return m_default;
    }

  private:
    Index m_index;
    Data& m_data;
    T m_default{Default};
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

  Matrix(const Matrix& other)
    : m_data{other.m_data}
  {
  }

  Matrix(Matrix&& other) noexcept
  {
    m_data = std::move(other.m_data);
  }

  Matrix& operator=(const Matrix& other)
  {
    m_data = other.m_data;
    return *this;
  }

  Matrix& operator=(Matrix&& other) noexcept
  {
    m_data = std::move(other.m_data);
    return *this;
  }

  size_t size() const
  {
    return m_data.size();
  }

  auto operator[](size_t i)
  {
    const std::array<size_t, 1> index{i};
    return Proxy<1>{index, m_data};
  }

private:
  Data m_data;
};

} // namespace
