#pragma once

#include "../vector.hpp"

#include <algorithm>

template <typename Preservation>
elelel::hosts::vector<Preservation>::vector() {
}

template <typename Preservation>
elelel::hosts::vector<Preservation>::vector(size_type count, const value_type& value) {
  for (size_type i = size_type(); i < count; ++i) push_back(value);
}

template <typename Preservation>
template <typename InputIt>
elelel::hosts::vector<Preservation>::vector(InputIt first, InputIt last) {
  for (auto it = first; it != last; ++it) push_back(*it);
}

template <typename Preservation>
elelel::hosts::vector<Preservation>::vector(const type& other) :
  lines_(other.lines_) {
}

template <typename Preservation>
elelel::hosts::vector<Preservation>::vector(type&& other) noexcept :
  lines_(other.lines_) {
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::operator[](size_type pos) -> value_type& {
  return *lines_[pos];
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::operator[](size_type pos) const -> const value_type& {
  return *lines_[pos];
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::begin() noexcept -> iterator {
  return iterator(this, lines_.begin());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::begin() const noexcept -> const_iterator {
  return const_iterator(this, lines_.begin());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::cbegin() const noexcept -> const_iterator {
  return const_iterator(this, lines_.cbegin());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::end() noexcept -> iterator {
  return iterator(this, lines_.end());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::end() const noexcept -> const_iterator {
  return const_iterator(this, lines_.end());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::cend() const noexcept -> const_iterator {
  return const_iterator(this, lines_.cend());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::rbegin() noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(iterator(this, lines_.begin()));
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::rbegin() const noexcept -> const_reverse_iterator {
  return std::reverse_iterator<const_iterator>(iterator(this, lines_.begin()));
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::crbegin() const noexcept -> const_reverse_iterator {
  return std::reverse_iterator<const_iterator>(iterator(this, lines_.cbegin()));
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::rend() noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(iterator(this, lines_.end()));
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::rend() const noexcept -> const_reverse_iterator {
  return std::reverse_iterator<const_iterator>(*this, lines_.rend());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::crend() const noexcept -> const_reverse_iterator {
  return std::reverse_iterator<const_iterator>(*this, lines_.crend());
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::size() const noexcept -> size_type {
  return lines_.size();
}

template <typename Preservation>
void elelel::hosts::vector<Preservation>::clear() noexcept {
  lines_.clear();
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::insert(const_iterator pos, const value_type& value) -> iterator {
  std::shared_ptr<value_type> l = value.shared_from_this();
  remove_conflicts(*l);
  if (&value.cont_ != this) {
    l = std::shared_ptr<value_type>(new value_type(*this, *l));
  }
  auto std_it = lines_.insert(pos.std_iterator(), l);
  return iterator(this, std_it);
}

template <typename Preservation>
void elelel::hosts::vector<Preservation>::push_back(const value_type& value) {
  std::shared_ptr<value_type> l = value.shared_from_this();
  remove_conflicts(*l);
  if (&value.cont_ != this) {
    l = std::shared_ptr<value_type>(new value_type(*this, *l));
  }
  lines_.push_back(l);
}

template <typename Preservation>
template <typename... Args>
void elelel::hosts::vector<Preservation>::push_back(Args&&... args) {
  std::shared_ptr<value_type> l = std::shared_ptr<value_type>(new value_type(*this, std::forward<Args>(args)...));
  remove_conflicts(*l);
  lines_.push_back(l);
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::erase(const_iterator pos) -> iterator {
  auto std_it = lines_.erase(pos.std_iterator(), lines_.end());
  return iterator(this, std_it);
}

template <typename Preservation>
auto elelel::hosts::vector<Preservation>::erase(const_iterator first, const_iterator last) -> iterator {
  auto std_it = lines_.erase(first.std_iterator(), last.std_iterator(), lines_.end());
  return iterator(this, std_it);
}

template <typename Preservation>
template <typename Element>
auto elelel::hosts::vector<Preservation>::erase(const Element& v) -> iterator {
  auto std_it = lines_.erase(std::remove_if(lines_.begin(), lines_.end(),
                                            [&v] (const std::shared_ptr<value_type>& l) {
                                              return *l == v;
                                            }), lines_.end());
  return iterator(this, std_it);
}

template <typename Preservation>
void elelel::hosts::vector<Preservation>::pop_back() {
  lines_.pop_back();
}

template <typename Preservation>
void elelel::hosts::vector<Preservation>::resize(size_type count, value_type value) {
  lines_.resize(count, value);
}

template <typename Preservation>
void elelel::hosts::vector<Preservation>::resize(size_type count, const value_type& value) {
  lines_.resize(count, value);
}

template <typename Preservation>
void elelel::hosts::vector<Preservation>::remove_conflicts(const value_type& value) {
  auto v = value.shared_from_this();
  lines_.erase(std::remove_if(lines_.begin(), lines_.end(),
                              [&v] (const std::shared_ptr<value_type>& l) {
                                return (*l != hosts::ip("")) && (*l != hosts::canonical("")) && (*l == v->canonical_);
                              }), lines_.end());
  for (const auto& a : v->aliases_) {
    lines_.erase(std::remove_if(lines_.begin(), lines_.end(),
                                [&a] (const std::shared_ptr<value_type>& l) {
                                  return (*l != hosts::ip("")) && (*l != hosts::canonical("")) && (*l == a);
                                }), lines_.end());
  }
}

template <typename Container, typename T>
elelel::hosts::vector_iterator<Container, T>::vector_iterator(Container* cont, std_iterator_type pos) :
  cont_(cont),
  pos_(pos) {
}

template <typename Container, typename T>
elelel::hosts::vector_iterator<Container, T>::vector_iterator(const type& other) :
  cont_(other.cont_),
  pos_(other.pos_) {
}

template <typename Container, typename T>
elelel::hosts::vector_iterator<Container, T>::vector_iterator(type&& other) :
  cont_(std::move(other.cont_)),
  pos_(std::move(other.pos_)) {
}

template <typename Container, typename T>
void elelel::hosts::vector_iterator<Container, T>::swap(type& other) {
  std::swap(cont_, other.cont_);
  std::swap(pos_, other.pos_);
}

template <typename Container, typename T>
auto elelel::hosts::vector_iterator<Container, T>::operator=(const type& other) -> type& {
  type tmp(other);
  swap(tmp);
  return *this;
}

template <typename Container, typename T>
auto elelel::hosts::vector_iterator<Container, T>::operator=(type&& other) -> type& {
  cont_ = std::move(other.cont_);
  pos_ = std::move(other.pos_);
  return *this;
}

template <typename Container, typename T>
auto elelel::hosts::vector_iterator<Container, T>::operator==(const type& other) const -> bool {
  return (cont_ == other.cont_) && (pos_ == other.pos_);
}
