#pragma once

namespace elelel {
  namespace hosts {
    template <typename T>
    struct element {
      inline element();
      inline element(const std::string& s);
      inline element(std::string&& s);
      inline element(const element<T>& other);
      inline element(element<T>&& other);
      inline void swap(element<T>& other);
      inline element<T>& operator=(const element<T>& other);
      inline element<T>& operator=(element<T>&& other);
      inline element<T>& operator=(const std::string& s);
      inline element<T>& operator=(std::string&& s);
      inline bool operator==(const element<T>& other) const;
      inline bool operator!=(const element<T>& other) const;

      explicit inline operator std::string() const;
      explicit inline operator bool() const;
    protected:
      std::string s_;
    };

    struct element_ip_trait {};
    struct element_hostname_trait {};
    struct element_comment_trait {};

    // Actual columns in hosts file
    using ip = element<element_ip_trait>;
    struct canonical;
    struct alias;
    struct comment;
    
    struct canonical : element<element_hostname_trait> {
      friend struct alias;
      
      inline canonical();
      inline canonical(const std::string& s);
      inline canonical(std::string&& s);
      inline canonical(const canonical& other);
      inline canonical(canonical&& other);
      inline void swap(canonical& other);
      inline canonical& operator=(const canonical& other);
      inline canonical& operator=(canonical&& other);
      inline canonical& operator=(const std::string& s);
      inline canonical& operator=(std::string&& s);
      inline bool operator==(const canonical& other) const;
      inline bool operator!=(const canonical& other) const;

      explicit inline operator std::string() const;
      explicit inline operator bool() const;

      // Compatibility with alias struct
      // Disallow implicit assignment/conversion for now
      /*inline canonical(const alias& other);
      inline canonical(alias&& other);
      inline void swap(alias& other);
      inline canonical& operator=(const alias& other);
      inline canonical& operator=(alias&& other);*/
      inline bool operator==(const alias& other) const;
      inline bool operator!=(const alias& other) const;
    };
  
    struct alias : element<element_hostname_trait> {
      friend struct canonical;
      
      inline alias();
      inline alias(const std::string& s);
      inline alias(std::string&& s);
      inline alias(const alias& other);
      inline alias(alias&& other);
      inline void swap(alias& other);
      inline alias& operator=(const alias& other);
      inline alias& operator=(alias&& other);
      inline alias& operator=(const std::string& s);
      inline alias& operator=(std::string&& s);
      inline bool operator==(const alias& other) const;
      inline bool operator!=(const alias& other) const;

      inline explicit operator std::string() const;
      inline explicit operator bool() const;

      // Compatibility with canonical struct
      // Disallow implicit assignment/conversion for now
      /*inline alias(const canonical& other);
      inline alias(canonical&& other);
      inline void swap(canonical& other);
      inline alias& operator=(const canonical& other);
      inline alias& operator=(canonical&& other);*/
      inline bool operator==(const canonical& other) const;
      inline bool operator!=(const canonical& other) const;
    
    };

    struct comment : element<element_comment_trait> {
      inline comment();
      inline comment(const std::string& s);
      inline comment(std::string&& s);
      inline comment(const comment& other);
      inline comment(comment&& other);
      inline void swap(comment& other);
      inline comment& operator=(const comment& other);
      inline comment& operator=(comment&& other);
      inline comment& operator=(const std::string& s);
      inline comment& operator=(std::string&& s);
      inline bool operator==(const comment& other) const;
      inline bool operator!=(const comment& other) const;

      explicit inline operator std::string() const;
      explicit inline operator bool() const;
    };    
  }
}
