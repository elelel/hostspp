#pragma once

#include <memory>

#include "element.hpp"
#include "preservation.hpp"

namespace elelel {
  namespace hosts {
    template <typename Preservation>
    struct vector;
    
    template <typename Preservation>
    struct vector_line : Preservation, std::enable_shared_from_this<vector_line<Preservation>> {
      template <typename Preservation_>
      friend struct vector;
    
      using type = vector_line<Preservation>;
      using container_type = vector<Preservation>;

      bool operator==(const ip& v) const;
      bool operator!=(const ip& v) const;
      bool operator==(const canonical& v) const;
      bool operator!=(const canonical&v) const;
      bool operator==(const alias& v) const;
      bool operator!=(const alias& v) const;
      bool operator==(const comment& v) const;
      bool operator!=(const comment& v) const;
      bool operator==(const type& other) const;
      bool operator!=(const type& other) const;
    
      operator std::string() const;

      type& operator=(const ip& v);
      type& operator=(const canonical& v);
      type& operator+=(const alias& v);
      type& operator-=(const alias& v);
      type& operator=(const comment& v);
      type& operator=(ip&& v);
      type& operator=(canonical&& v);
      type& operator+=(alias&& v);
      type& operator=(comment&& v);

      const hosts::ip& ip() const;
      const hosts::canonical& canonical() const;
      const std::vector<hosts::alias>& aliases() const;
      const hosts::comment& comment() const;

      void set_separator(const char c);

    private:
      container_type& cont_;
      hosts::ip ip_;
      hosts::canonical canonical_;
      std::vector<hosts::alias> aliases_;
      hosts::comment comment_;
      char separator_ = '\t';

      inline vector_line(container_type& cont);
      inline vector_line(container_type& cont, const char* s);
      inline vector_line(container_type& cont, const type& other);

      // Constructors to build from elements
      inline vector_line(container_type& cont, hosts::ip&& ip, hosts::canonical&& canonical);
      template <typename... Args>
      inline vector_line(container_type& cont, hosts::ip&& ip, hosts::canonical&& canonical, Args&&... args);

      // Add alias or comment
      template <typename... Args>
      inline void build_variadic(hosts::alias&&, Args&&... args);
      template <typename... Args>
      inline void build_variadic(hosts::comment&& c);
      template <typename... Args>
      inline void build_variadic(hosts::alias&& a);
    };
  }
}
