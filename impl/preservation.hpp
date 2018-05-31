#pragma once

namespace elelel {
  namespace hosts {

    struct preserve_original_strings {
      preserve_original_strings() :
        modified_(true) {
      }
      
      preserve_original_strings(const char* s) :
        modified_(false) {
        if (s) s_ = s; else modified_ = true;
      }

      void set_modified() {
        modified_ = true;
      }

      const char* preserved_string() const {
        if (!modified_) return s_.c_str();
        return nullptr;
      }

      template <typename Other>
      void copy_state_from(const Other& other) {
        s_ = other.s_;
        modified_ = other.modified_;
      }
      
    private:
      std::string s_;
      bool modified_;
    };

    struct discard_original_strings {
      discard_original_strings() {};
      discard_original_strings(const char* s) {};
      void set_modified() {};
      const char* preserved_string() const { return nullptr; };
      template <typename Other>
      void copy_state_from(const Other& other) {
      }
    };
  }
}
