#pragma once

#include "preservation.hpp"
#include "vector_line.hpp"

namespace elelel {
  namespace hosts {
    template <typename Preservation>
    struct vector_line;

    template <typename Container, typename T>
    struct vector_iterator;

    template <typename Preservation = preserve_original_strings>
    struct vector  {
      using type = vector<Preservation>;
      using value_type = vector_line<Preservation>;
      using size_type = std::size_t;
      using difference_type = std::ptrdiff_t;

      friend vector_iterator<type, value_type>;
      friend vector_iterator<type, const value_type>;
      
      using iterator = vector_iterator<type, value_type>;
      using const_iterator = vector_iterator<type, const value_type>;
      using reverse_iterator = std::reverse_iterator<iterator>;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;


      vector();
      explicit vector(size_type count, const value_type& value);
      template <typename InputIt>
      vector(InputIt first, InputIt last);
      vector(const type& other);
      vector(type&& other) noexcept;
    
      value_type& operator[](size_type pos);
      const value_type& operator[](size_type post) const;

      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      const_iterator cbegin() const noexcept;

      iterator end() noexcept;
      const_iterator end() const noexcept;
      const_iterator cend() const noexcept;

      reverse_iterator rbegin() noexcept;
      const_reverse_iterator rbegin() const noexcept;
      const_reverse_iterator crbegin() const noexcept;

      reverse_iterator rend() noexcept;
      const_reverse_iterator rend() const noexcept;
      const_reverse_iterator crend() const noexcept;

      size_type size() const noexcept;

      void clear() noexcept;

      iterator insert(const_iterator pos, const value_type& value);
      iterator insert(const_iterator pos, size_type count, const value_type& value);
      template <typename InputIt>
      iterator insert(const_iterator pos, InputIt first, InputIt last);
    
      iterator erase(const_iterator pos);
      iterator erase(const_iterator first, const_iterator last);
      template <typename Element>
      iterator erase(const Element& v);
      
      void push_back(const value_type& value);
      template <typename... Args>
      void push_back(Args&&... args);
    
      void pop_back();
      void resize(size_type count, value_type value = value_type());
      void resize(size_type count, const value_type& value);
    private:
      std::vector<std::shared_ptr<value_type>> lines_;

      inline void remove_conflicts(const value_type& value);
    };

    template <typename Container, typename T>
    struct vector_iterator {
      using type = vector_iterator<Container, T>;
      using value_type = typename Container::value_type;
      using difference_type = std::ptrdiff_t;

      using pointer = T*;
      using reference = T&;
      using iterator_category = std::random_access_iterator_tag;

      using std_iterator_type = typename decltype(Container::lines_)::iterator;

      vector_iterator(Container* cont, std_iterator_type pos);
      vector_iterator(const type& other);
      vector_iterator(type&& other);

      void swap(type& other);
      type& operator=(const type& other);
      type& operator=(type&& other);

      bool operator==(const type& other) const;

      const std_iterator_type& std_iterator() const;
    private:
      Container* cont_;
      mutable std_iterator_type pos_;
    };
  }
}
