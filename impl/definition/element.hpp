#pragma once

namespace elelel {
  namespace hosts {
    inline void ltrim(std::string &s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [] (int c) {
            return !std::isspace(c);
          }));
    }

    inline void rtrim(std::string &s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), [] (int c) {
            return !std::isspace(c);
          }).base(), s.end());
    }

    inline void trim(std::string &s) {
      ltrim(s);
      rtrim(s);
    }
  }
}

template <typename T>
elelel::hosts::element<T>::element() {
}

template <typename T>
elelel::hosts::element<T>::element(const std::string& s) :
  s_(s) {
  trim(s_);
}

template <typename T>
elelel::hosts::element<T>::element(std::string&& s) :
  s_(std::move(s)) {
  trim(s_);
}

template <typename T>
elelel::hosts::element<T>::element(const element<T>& other) :
  s_(other.s_) {
}

template <typename T>
elelel::hosts::element<T>::element(element<T>&& other) :
  s_(std::move(other.s_)) {
}

template <typename T>
void elelel::hosts::element<T>::swap(element<T>& other) {
  std::swap(s_, other.s_);
}

template <typename T>
auto elelel::hosts::element<T>::operator=(const element<T>& other) -> element<T>& {
  s_ = other.s_;
  return *this;
}

template <typename T>
auto elelel::hosts::element<T>::operator=(element<T>&& other) -> element<T>& {
  s_ = std::move(other.s_);
  return *this;
}

template <typename T>
auto elelel::hosts::element<T>::operator=(const std::string& s) -> element<T>& {
  s_ = s;
  trim(s_);
  return *this;
}

template <typename T>
auto elelel::hosts::element<T>::operator=(std::string&& s) -> element<T>& {
  s_ = std::move(s);
  trim(s_);
  return *this;
}

template <typename T>
bool elelel::hosts::element<T>::operator==(const element<T>& other) const {
  return s_ == other.s_;
}

template <typename T>
bool elelel::hosts::element<T>::operator!=(const element<T>& other) const {
  return !(*this == other);
}


template <typename T>
elelel::hosts::element<T>::operator std::string() const {
  return s_;
}

template <typename T>
elelel::hosts::element<T>::operator bool() const {
  return s_.size() > 0;
}

elelel::hosts::canonical::canonical() :
  element() {
}

elelel::hosts::canonical::canonical(const std::string& s) :
  element(s) {
}

elelel::hosts::canonical::canonical(std::string&& s) :
  element(std::move(s)) {
}

elelel::hosts::canonical::canonical(const canonical& other) :
  element(other) {
}

elelel::hosts::canonical::canonical(canonical&& other) :
  element(std::move(other)) {
}

void elelel::hosts::canonical::swap(canonical& other) {
  element::swap(other);
}

auto elelel::hosts::canonical::operator=(const canonical& other) -> canonical& {
  element::operator=(other);
  return *this;
}

auto elelel::hosts::canonical::operator=(canonical&& other) -> canonical& {
  element::operator=(other);
  return *this;
}

auto elelel::hosts::canonical::operator=(const std::string& s) -> canonical& {
  element::operator=(s);
  return *this;
}

auto elelel::hosts::canonical::operator=(std::string&& s) -> canonical& {
  element::operator=(s);
  return *this;
}

auto elelel::hosts::canonical::operator==(const canonical& other) const -> bool {
  return element::operator==(other);
}

auto elelel::hosts::canonical::operator!=(const canonical& other) const -> bool {
  return element::operator!=(other);
}

elelel::hosts::canonical::operator std::string() const {
  return s_;
}

elelel::hosts::canonical::operator bool() const {
  return s_.size() > 0;
}

/*
elelel::hosts::canonical::canonical(const alias& other) :
  element(other) {
}

elelel::hosts::canonical::canonical(alias&& other) :
  element(std::move(other)) {
}

void elelel::hosts::canonical::swap(alias& other) {
  std::swap(s_, other.s_);
}

auto elelel::hosts::canonical::operator=(const alias& other) -> canonical& {
  s_ = other.s_;
  return *this;
}

auto elelel::hosts::canonical::operator=(alias&& other) -> canonical& {
  s_ = std::move(other.s_);
  return *this;
  }*/

bool elelel::hosts::canonical::operator==(const alias& other) const {
  return s_ == other.s_;
}

bool elelel::hosts::canonical::operator!=(const alias& other) const {
  return !(*this == other);
}


elelel::hosts::alias::alias() :
  element() {
}

elelel::hosts::alias::alias(const std::string& s) :
  element(s) {
}

elelel::hosts::alias::alias(std::string&& s) :
  element(std::move(s)) {
}

elelel::hosts::alias::alias(const alias& other) :
  element(other) {
}

elelel::hosts::alias::alias(alias&& other) :
  element(std::move(other)) {
}

void elelel::hosts::alias::swap(alias& other) {
  element::swap(other);
}

auto elelel::hosts::alias::operator=(const alias& other) -> alias& {
  element::operator=(other);
  return *this;
}

auto elelel::hosts::alias::operator=(alias&& other) -> alias& {
  element::operator=(other);
  return *this;
}

auto elelel::hosts::alias::operator=(const std::string& s) -> alias& {
  element::operator=(s);
  return *this;
}

auto elelel::hosts::alias::operator=(std::string&& s) -> alias& {
  element::operator=(s);
  return *this;
}

auto elelel::hosts::alias::operator==(const alias& other) const -> bool {
  return element::operator==(other);
}

auto elelel::hosts::alias::operator!=(const alias& other) const -> bool {
  return element::operator!=(other);
}

elelel::hosts::alias::operator std::string() const {
  return s_;
}

elelel::hosts::alias::operator bool() const {
  return s_.size() > 0;
}

/*
elelel::hosts::alias::alias(const canonical& other) :
  element(other) {
}

elelel::hosts::alias::alias(canonical&& other) :
  element(std::move(other)) {
}

void elelel::hosts::alias::swap(canonical& other) {
  std::swap(s_, other.s_);
}

auto elelel::hosts::alias::operator=(const canonical& other) -> alias& {
  s_ = other.s_;
  return *this;
}

auto elelel::hosts::alias::operator=(canonical&& other) -> alias& {
  s_ = std::move(other.s_);
  return *this;
  }*/

bool elelel::hosts::alias::operator==(const canonical& other) const {
  return s_ == other.s_;
}

bool elelel::hosts::alias::operator!=(const canonical& other) const {
  return !(*this == other);
}


elelel::hosts::comment::comment() :
  element() {
}

elelel::hosts::comment::comment(const std::string& s) {
  s_ = s;
}

elelel::hosts::comment::comment(std::string&& s) {
  s_ = std::move(s);
}

elelel::hosts::comment::comment(const comment& other) :
  element(other) {
}

elelel::hosts::comment::comment(comment&& other) :
  element(std::move(other)) {
}

void elelel::hosts::comment::swap(comment& other) {
  element::swap(other);
}

auto elelel::hosts::comment::operator=(const comment& other) -> comment& {
  element::operator=(other);
  return *this;
}

auto elelel::hosts::comment::operator=(comment&& other) -> comment& {
  element::operator=(other);
  return *this;
}

auto elelel::hosts::comment::operator=(const std::string& s) -> comment& {
  element::operator=(s);
  return *this;
}

auto elelel::hosts::comment::operator=(std::string&& s) -> comment& {
  element::operator=(s);
  return *this;
}

auto elelel::hosts::comment::operator==(const comment& other) const -> bool {
  return element::operator==(other);
}

auto elelel::hosts::comment::operator!=(const comment& other) const -> bool {
  return element::operator!=(other);
}

elelel::hosts::comment::operator std::string() const {
  return s_;
}

elelel::hosts::comment::operator bool() const {
  return s_.size() > 0;
}
