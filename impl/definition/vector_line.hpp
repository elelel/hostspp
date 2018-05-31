#pragma once

#include "../vector_line.hpp"

#include <algorithm>
#include <cctype>

template <typename Preservation>
elelel::hosts::vector_line<Preservation>::vector_line(container_type& cont) :
  Preservation(),
  cont_(cont) {
}

template <typename Preservation>
elelel::hosts::vector_line<Preservation>::vector_line(container_type& cont, const char* s_) :
  Preservation(s_),
  cont_(cont) {

  enum class state_type {
    ip,
    canonical,
    alias,
    comment
  };

  state_type state{state_type::ip};
  auto s = std::string(s_);
  auto first = s.begin();
  while (first != s.end()) {
    // Skip leading spaces
    while ((first != s.end()) && std::isspace(*first)) { ++first; };
    if (first != s.end()) {
      if (*first == '#') {
        // It's comment, save it and finish
        state = state_type::comment;
        ++first;
        if (first != s.end()) {
          // Take till the end of the line
          std::string str(first, s.end());
          comment_ = elelel::hosts::comment(str);
          first = s.end();        
        }
      } else {
        // Take till next space character or #
        auto last = first;      
        while ((last != s.end()) && (*last != '#') && !std::isspace((int)*last)) { ++last; };
        std::string str(first, last);
        first = last;
        if (state == state_type::ip) {
          ip_ = std::move(elelel::hosts::ip(str));
          state = state_type::canonical;
        }
        else if (state == state_type::canonical) {
          canonical_ = std::move(elelel::hosts::canonical(str));
          state = state_type::alias;
        }
        else if (state == state_type::alias) {
          aliases_.push_back(std::move(elelel::hosts::alias(str)));
        }
      }
    }
  }
}

template <typename Preservation>
elelel::hosts::vector_line<Preservation>::vector_line(container_type& cont, const type& other) :
  cont_(cont),
  ip_(other.ip_),
  canonical_(other.canonical_),
  aliases_(other.aliases_),
  comment_(other.comment_),
  separator_(other.separator_) {
  Preservation::copy_state_from(other);  
}

// Constructors to build from elements

template <typename Preservation>
elelel::hosts::vector_line<Preservation>::vector_line(container_type& cont, hosts::ip&& ip, hosts::canonical&& canonical) :
  cont_(cont),
  ip_(ip),
  canonical_(canonical) {
}

template <typename Preservation>
template <typename... Args>
elelel::hosts::vector_line<Preservation>::vector_line(container_type& cont, hosts::ip&& ip, hosts::canonical&& canonical, Args&&... args)  :
  cont_(cont),
  ip_(ip),
  canonical_(canonical) {
  build_variadic(std::forward<Args>(args)...);
}

template <typename Preservation>
template <typename... Args>
void elelel::hosts::vector_line<Preservation>::build_variadic(hosts::alias&& a, Args&&... args) {
  aliases_.push_back(a);
  build_variadic(std::forward<Args>(args)...);
}

template <typename Preservation>
template <typename... Args>
void elelel::hosts::vector_line<Preservation>::build_variadic(hosts::comment&& c) {
  comment_ = c;
}

template <typename Preservation>
template <typename... Args>
void elelel::hosts::vector_line<Preservation>::build_variadic(hosts::alias&& a) {
  aliases_.push_back(a);
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator==(const hosts::ip& v) const {
  return ip_ == v;
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator!=(const hosts::ip& v) const {
  return !(*this == v);
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator==(const hosts::canonical& v) const {
  return canonical_ == v;
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator!=(const hosts::canonical& v) const {
  return !(*this == v);
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator==(const hosts::alias& v) const {
  for (const auto& a : aliases_) { if (a == v) return true; }
  return false;
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator!=(const hosts::alias& v) const {
  return !(*this == v);
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator==(const hosts::comment& v) const {
  return comment_ == v;
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator!=(const hosts::comment& v) const {
  return !(*this == v);
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator==(const type& other) const {
  if ((ip_ != other.ip_) || (canonical_ != other.canonical_) || (comment_ != other.comment_)) return false;
  for (auto it = aliases_.begin(); it != aliases_.end(); ++it) {
    if (std::find(other.aliases_.begin(), other.aliases_.end(), *it) == other.aliases_.end()) return false;
  }
  return true;
}

template <typename Preservation>
bool elelel::hosts::vector_line<Preservation>::operator!=(const type& other) const{
  return !(*this == other);
}

template <typename Preservation>
elelel::hosts::vector_line<Preservation>::operator std::string() const {
  const char* preserved = this->preserved_string();
  std::string rslt;
  if (preserved != nullptr) {
    // Will be nullptr if not preserving or not modified 
    return std::string(preserved);
  } else {
    // Create a new string from data
    if (ip_ && canonical_) {
      std::string rslt = std::string(ip_) + separator_ + std::string(canonical_);
      for (const auto& alias_ : aliases_) {
        rslt += separator_ + std::string(alias_);
      }
    }
    if (comment_) {
      if (rslt.size() > 0) rslt += separator_;
      rslt += "#" + std::string(comment_);
    }
    return rslt;
  }
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator=(const hosts::ip& v) -> type& {
  if (v != ip_) {
    ip_ = v;
    this->set_modified();
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator=(hosts::ip&& v) -> type& {
  if (v != ip_) {
    ip_ = std::move(v);
    this->set_modified();
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator=(const hosts::canonical& v) -> type& {
  if (v != canonical_) {
    auto l = this->shared_from_this();
    cont_.erase(v);
    this->set_modified();
    canonical_ = v;
    cont_.push_back(l);
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator=(hosts::canonical&& v) -> type& {
  if (v != canonical_) {
    auto l = this->shared_from_this();
    cont_.erase(v);
    this->set_modified();
    canonical_ = std::move(v);
    cont_.push_back(l);
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator+=(const hosts::alias& v) -> type& {
  if (std::find(aliases_.begin(), aliases_.end(), v) == aliases_.end()) {
    auto l = this->shared_from_this();
    cont_.erase(v);
    this->set_modified();
    aliases_.push_back(v);
    cont_.push_back(l);
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator+=(hosts::alias&& v) -> type& {
  if (std::find(aliases_.begin(), aliases_.end(), v) == aliases_.end()) {
    auto l = this->shared_from_this();
    cont_.erase(v);
    this->set_modified();
    aliases_.push_back(std::move(v));
    cont_.push_back(l);
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator=(const hosts::comment& v) -> type& {
  if (v != comment_) {
    comment_ = v;
    this->set_modified();
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::operator=(hosts::comment&& v) -> type& {
  if (v != comment_) {
    comment_ = std::move(v);
    this->set_modified();
  }
  return *this;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::ip() const -> const hosts::ip& {
  return ip_;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::canonical() const -> const hosts::canonical& {
  return canonical_;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::aliases() const -> const std::vector<hosts::alias>& {
  return aliases_;
}

template <typename Preservation>
auto elelel::hosts::vector_line<Preservation>::comment() const -> const hosts::comment& {
  return comment_;
}
