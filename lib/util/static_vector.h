/*
 * Surveyor - A UCI Chess Engine
 * Copyright (C) 2026 Amber Goulding
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Affero General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SURVEYOR_STATIC_VECTOR_H
#define SURVEYOR_STATIC_VECTOR_H
#include "integer.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <ranges>

namespace surveyor {

template<typename T, usize n>
class static_vector {
public:
  using value_type             = T;
  using pointer                = T*;
  using const_pointer          = const T*;
  using reference              = T&;
  using const_reference        = const T&;
  using size_type              = usize;
  using difference_type        = isize;
  using iterator               = pointer;
  using const_iterator         = const_pointer;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // Constructors

  constexpr static_vector()
      : m_size(0) {
  }

  ~static_vector() {
    clear();
  }

  static_vector(std::initializer_list<T> inlist)
      : m_size(inlist.size()) {
    namespace rg = std::ranges;

    rg::uninitialized_copy_n(inlist.begin(), inlist.end(), data());
  }

  // Methods
  constexpr auto clear() -> void {
    destroy(begin(), end());
    m_size = 0;
  }

  constexpr auto data() const -> const T* {
    return ptr(0);
  }

  constexpr auto data() -> T* {
    return ptr(0);
  }

  [[nodiscard]] constexpr auto size() const -> usize {
    return m_size;
  }

  [[nodiscard]] constexpr auto empty() const -> bool {
    return m_size == 0;
  }

  template<typename... Args>
  auto emplace_back(Args... args) -> T*
    requires(std::constructible_from<T, Args...>)
  {
    auto* end = ptr(m_size);
    std::construct_at(end, std::forward<Args>(args)...);
    ++m_size;
    return end;
  }

  auto push_back(T&& e) -> void {
    auto* end = ptr(m_size);
    *end = e;
    ++m_size;
  }

  constexpr auto operator[](usize idx) -> T& {
    return ref(idx);
  }

  constexpr auto operator[](usize idx) const -> const T& {
    return ref(idx);
  }

  // Iterator
  constexpr auto begin() -> T* {
    return ptr(0);
  }

  constexpr auto end() -> T* {
    return ptr(m_size);
  }

  constexpr auto begin() const -> const T* {
    return ptr(0);
  }

  constexpr auto end() const -> const T* {
    return ptr(m_size);
  }

  constexpr auto cbegin() const -> const T* {
    return ptr(0);
  }

  constexpr auto cend() const -> const T* {
    return ptr(m_size);
  }

private:
  template<std::input_iterator InputIt>
    requires(std::constructible_from<T, std::iter_reference_t<InputIt>>)
  constexpr auto destroy(InputIt begin, InputIt end) -> void {
    namespace rg = std::ranges;

    if (std::is_trivially_destructible_v<T>) {
      return;
    }

    rg::for_each(begin, end, [](const auto& e) {
      std::destroy_at(std::addressof(e));
    });
  }

  constexpr auto ptr(usize i) noexcept -> T* {
    return reinterpret_cast<T*>(m_data.data()) + i;
  }

  constexpr auto ptr(usize i) const noexcept -> const T* {
    return reinterpret_cast<const T*>(m_data.data()) + i;
  }

  constexpr auto ref(usize i) noexcept -> T& {
    return *ptr(i);
  }

  constexpr auto ref(usize i) const noexcept -> const T& {
    return *ptr(i);
  }

  alignas(T) std::array<std::byte, sizeof(T) * n> m_data;

  usize m_size = 0;
};

}  // namespace surveyor
#endif  // SURVEYOR_STATIC_VECTOR_H
