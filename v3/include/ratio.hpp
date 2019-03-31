#include <ratio>
#include <string>
/* https://stackoverflow.com/questions/23843758/high-resolution-clocks-highest-resolution-is-1000ns */

namespace Hamilton{
namespace ratio{

  using std::ratio;
  using std::yocto;
  using std::zepto;
  using std::atto;
  using std::femto;
  using std::pico;
  using std::nano;
  using std::micro;
  using std::milli;
  using std::centi;
  using std::deci;
  using std::deca;
  using std::hecto;
  using std::kilo;
  using std::mega;
  using std::giga;
  using std::tera;
  using std::peta;
  using std::exa;
  using std::zetta;
  using std::yotta;

  template <class Ratio, class CharT>
  struct ratio_string
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('[')) +
                 std::to_string(Ratio::num) + CharT('/') +
                 std::to_string(Ratio::den) + CharT(']');
      }
  };

  template <class CharT>
  struct ratio_string<std::yocto, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('y'));
      }
  };

  template <class CharT>
  struct ratio_string<std::zepto, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('z'));
      }
  };

  template <class CharT>
  struct ratio_string<std::atto, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('a'));
      }
  };

  template <class CharT>
  struct ratio_string<std::femto, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('f'));
      }
  };

  template <class CharT>
  struct ratio_string<std::pico, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('p'));
      }
  };

  template <class CharT>
  struct ratio_string<std::nano, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('n'));
      }
  };

  template <>
  struct ratio_string<std::micro, char>
  {
      static std::string symbol() {return std::string("\xC2\xB5");}
  };

  template <>
  struct ratio_string<std::micro, char16_t>
  {
      static std::u16string symbol() {return std::u16string(1, u'\xB5');}
  };

  template <>
  struct ratio_string<std::micro, char32_t>
  {
      static std::u32string symbol() {return std::u32string(1, U'\xB5');}
  };

  template <>
  struct ratio_string<std::micro, wchar_t>
  {
      static std::wstring symbol() {return std::wstring(1, L'\xB5');}
  };

  template <class CharT>
  struct ratio_string<std::milli, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('m'));
      }
  };

  template <class CharT>
  struct ratio_string<std::centi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('c'));
      }
  };

  template <class CharT>
  struct ratio_string<std::deci, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('d'));
      }
  };
  
  template <class CharT>
  struct ratio_string<ratio<1,1>, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>();
      }
  };

  template <class CharT>
  struct ratio_string<std::deca, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('da'));
      }
  };

  template <class CharT>
  struct ratio_string<std::hecto, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('h'));
      }
  };

  template <class CharT>
  struct ratio_string<std::kilo, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('k'));
      }
  };

  template <class CharT>
  struct ratio_string<std::mega, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('M'));
      }
  };

  template <class CharT>
  struct ratio_string<std::giga, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('G'));
      }
  };

  template <class CharT>
  struct ratio_string<std::tera, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('T'));
      }
  };

  template <class CharT>
  struct ratio_string<std::peta, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('P'));
      }
  };

  template <class CharT>
  struct ratio_string<std::exa, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('E'));
      }
  };

  template <class CharT>
  struct ratio_string<std::zetta, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('Z'));
      }
  };

  template <class CharT>
  struct ratio_string<std::yotta, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>(1, CharT('Y'));
      }
  };
  
  using kibi = ratio<1024,1>;
  using mebi = ratio<1048576L,1>;
  using gibi = ratio<1073741824L,1>;
  using tebi = ratio<1099511627776LL,1>;
  using pebi = ratio<1125899906842624LL,1>;
  using exbi = ratio<1152921504606846976LL,1>;
  using zebi = ratio<static_cast<intmax_t>(1073741824L)*static_cast<intmax_t>(1099511627776LL),1>;
  using yobi = ratio<static_cast<intmax_t>(1099511627776LL)*static_cast<intmax_t>(1099511627776LL),1>;
  
  template <class CharT>
  struct ratio_string<kibi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('K'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<mebi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('M'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<gibi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('G'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<tebi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('T'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<pebi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('P'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<exbi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('E'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<zebi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('Z'), CharT('i')};
      }
  };
  
  template <class CharT>
  struct ratio_string<yobi, CharT>
  {
      static std::basic_string<CharT> symbol()
      {
          return std::basic_string<CharT>{CharT('Y'), CharT('i')};
      }
  };
}
}
