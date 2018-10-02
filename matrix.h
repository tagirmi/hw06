#pragma once

#include <array>
#include <map>

namespace hw06 {

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

    auto operator [](size_t i)
    {
      m_index[1] = i;
      return Proxy{m_index, m_data};
    }

    auto& operator =(const T& value)
    {
      if (value == Def) {
        m_data.erase(m_index);
        return m_default;
      }
      m_data[m_index] = value;
    }

    operator const T& () const
    {
      auto i = m_data.find(m_index);
      return i == m_data.end() ? m_default : i->second;
    }

  private:
    Index m_index;
    Data& m_data;
    T m_default{Def};
  };

  Matrix() = default;

  size_t size() const
  {
    return m_data.size();
  }

  Proxy operator [](size_t index)
  {
    return Proxy{index, m_data};
  }

private:
  Data m_data;
};

} // namespace
