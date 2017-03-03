// -*- mode: c++; tab-width: 8; c-basic-offset: 4 -*-
//-< WSTRING.H >-----------------------------------------------------*--------*
// GOODS                     Version 1.0         (c) 1997  GARRET    *     ?  *
// (Generic Object Oriented Database System)                         *   /\|  *
//                                                                   *  /  \  *
//                          Created:     10-Aug-2000  K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Aug-2000  K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Wide character string with variable length (compatible with Java string type)
//-------------------------------------------------------------------*--------*

#ifndef __WSTRING_H__
#define __WSTRING_H__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


#ifndef NO_OS_UNICODE_SUPPORT
#if (defined(__FreeBSD__) && __FreeBSD__ < 5) && !defined(__APPLE__)
#define NO_OS_UNICODE_SUPPORT 1
#else
#define NO_OS_UNICODE_SUPPORT 0
#endif
#endif


#if NO_OS_UNICODE_SUPPORT

#if !defined(__APPLE__)
typedef unsigned short wchar_t;
#endif

#define U_NULL ((wchar_t)0)

inline size_t wcslen(const wchar_t *cs)
{
    int n = 0;
    while (*cs++) { 
        n++;
    }
    return n;
}

inline wchar_t *wcscpy(wchar_t *s, const wchar_t *ct)
{
    wchar_t *ptr;
    for (ptr = s; *ct; ptr++, ct++) { 
        *ptr = *ct;
    }
    *ptr = U_NULL;
    
    return s;
}

inline wchar_t *wcsncpy(wchar_t *s, const wchar_t *ct, size_t n)
{
    wchar_t *ptr;
    for (ptr = s; *ct && n-- > 0; ptr++, ct++) { 
        *ptr = *ct;
    }
    while (n-- > 0) { 
        *ptr++ = U_NULL;
    }
    return s;
}

inline wchar_t *wcscat(wchar_t *s, const wchar_t *ct)
{
    wchar_t *ptr = s;
    
    while (*ptr) { 
        ptr++;
    }
    wcscpy(ptr, ct);

    return s;
}

inline int wcscmp(const wchar_t *cs, const wchar_t *ct)
{
    while (*cs == *ct && *cs && *ct)
    {
        cs++;
        ct++;
    }
    
    return (*cs == *ct ? 0 : (*cs < *ct ? -1 : 1));
}

inline int wcsncmp(const wchar_t *cs, const wchar_t *ct, size_t n)
{
    while (*cs == *ct && *cs && *ct && n-- > 0)
    {
        cs++;
        ct++;
    }
    
    return (n <= 0 || *cs == *ct ? 0 : (*cs < *ct ? -1 : 1));
}

inline int wcscoll(const wchar_t *s1, const wchar_t *s2)
{
    wchar_t c1, c2;
    do { 
        c1 = *s1++;
        c2 = *s2++;
    } while (c1 != 0 && c2 != 0 && c1 == c2);
    
    if (c1 == c2) { 
        return 0;
    }
    
    if ((wchar_t)((char)c1) == c1 && (wchar_t)((char)c2) == c2) { 
        char str[2][2];
        str[0][0] = (char)c1;
        str[0][1] = '\0';
        str[1][0] = (char)c2;
        str[1][1] = '\0';
        return strcoll(str[0], str[1]);

    }
    return (c1 == c2 ? 0 : (c1 < c2 ? -1 : 1));
}


inline size_t wcstombs(char *s, const wchar_t *pwcs, size_t n)
{
    if (s == NULL) {
        return wcslen(pwcs);
    }
    char* start = s;    
    while (--n >= 0 && *pwcs != 0) { 
        *s++ = (char)*pwcs++;
    }
    if (n >= 0) { 
        *s = U_NULL;
    }
    return s - start;
}

inline size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n)
{
    if (pwcs == NULL) { 
        return strlen(s);
    }
    wchar_t* start = pwcs;
    while (--n >= 0 && *s != 0) { 
        *pwcs++ = (wchar_t)(*s++ & 0xFF);
    }
    if (n >= 0) { 
        *pwcs = U_NULL;
    }
    return pwcs - start;
}

#define towupper(ch) toupper((ch) & 0xFF)
#define towlower(ch) tolower((ch) & 0xFF)
    
#else

#include <wchar.h>
#include <wctype.h>


#endif

#if !defined(_WIN32) && __USE_FORTIFY_LEVEL < 1
#include <alloca.h>
inline wchar_t* fgetws(wchar_t *s, int n, FILE *stream)
{
    char* p = (char*)alloca(n);
    *p = 0;
    if (fgets(p, n, stream) == NULL) { 
        return NULL;
    }
    mbstowcs(s, p, n);
    return s;
}
#endif

BEGIN_GOODS_NAMESPACE

class Runtime;

class wstring_t { 
    friend class field_descriptor;
  public:
    //
    // Construct null string, can be checked with isNull
    //
    wstring_t() {
        chars = NULL;
        len = 0;
    }

    boolean isNull() const { 
        return len == 0;
    }

    void setNull() { 
        destroy();
        len = 0;
    }

    wstring_t& operator=(wstring_t const& str) {
        destroy();
        chars = new wchar_t[len = str.len];
        memcpy(chars, str.chars, len*sizeof(wchar_t));
        return *this;
    }

    wstring_t& operator=(wchar_t const* str) {
        destroy();
        chars = new wchar_t[len = (int)wcslen(str)+1];
        wcscpy(chars, str);
        return *this;
    }

    wstring_t& operator=(char const* str) {
        destroy();
        size_t n = mbstowcs(NULL, str, 0) + 1;
        chars = new wchar_t[n];
        len = (int)mbstowcs(chars, str, n) + 1;
        assert((size_t)len == n);
        return *this;
    }

    wstring_t& operator=(wchar_t ch) {
        destroy();
        len = 2;
        chars = new wchar_t[2];
        chars[0] = ch;
        chars[1] = '\0';
        return *this;
    }

    //
    // Construct substring of "str" string [from,till)
    // Character at "till" position is not included.
    // 
    wstring_t(wstring_t const& str, int from, int till) {
        assert(from >= 0 && till >= 0 && from <= till && till < str.len);
        len = till - from + 1; 
        chars = new wchar_t[len];
        memcpy(chars, str.chars+from, (till-from)*sizeof(wchar_t));
        chars[len-1] = 0;
    }
    wstring_t(wstring_t const& str) {
        chars = new wchar_t[len = str.len];
        memcpy(chars, str.chars, len*sizeof(wchar_t));
    }
    wstring_t(wchar_t const* str) {
        chars = new wchar_t[len = wcslen(str)+1];
        wcscpy(chars, str);
    }
    wstring_t(char const* str) {
        size_t n = mbstowcs(NULL, str, 0) + 1;
        chars = new wchar_t[n];
        len = (int)mbstowcs(chars, str, n) + 1;
        assert((size_t)len == n);
    }
    wstring_t(wchar_t ch) {
        len = 2;
        chars = new wchar_t[2];
        chars[0] = ch;
        chars[1] = '\0';
    }

    boolean operator == (wstring_t const& str) const {
        return wcscmp(chars, str.chars) == 0;
    }
    boolean operator != (wstring_t const& str) const {
        return wcscmp(chars, str.chars) != 0;
    }
    boolean operator >= (wstring_t const& str) const {
        return compareTo(str) >= 0;
    }
    boolean operator <= (wstring_t const& str) const {
        return compareTo(str) <= 0;
    }
    boolean operator >  (wstring_t const& str) const {
        return compareTo(str) > 0;
    }
    boolean operator <  (wstring_t const& str) const {
        return compareTo(str) < 0;
    }

    int compareTo(wstring_t const& str) const {
        return wcscoll(chars, str.chars);
    }

    int compareToIgnoreCase(wstring_t const& str) const {
        int n = len < str.len ? len : str.len;
        for (int i = 0; i < n; i++) { 
            int diff = towupper(chars[i]) - towupper(str.chars[i]);
            if (diff != 0) { 
                return diff;
            }
        }
        return len - str.len;
    }

    //
    // Extract suiubstring [from,till) from sepcified string. 
    // Character at "till" position is not included.
    //
    wstring_t substring(int from, int till) const { 
        return wstring_t(*this, from, till);
    }

    //
    // Return True is target string contains prefix "str" at position "offs"
    //
    boolean startsWith(wstring_t const& str, int offs = 0) const { 
        if (offs >= len) { 
            return False;
        }
        return wcsncmp(chars + offs, str.chars, str.len-1);
    }

    //
    // Return True is target string is terminated with suffix "str"
    //
    boolean endsWith(wstring_t const& str) const { 
        if (len < str.len) { 
            return False;
        }
        return wcscmp(chars + len - str.len, str.chars);
    }

    //
    // Extract substring of target string from position "from" till end of string 
    //
    wstring_t substring(int from) const { 
        return wstring_t(*this, from, len-1);
    }
    
    int length() const { 
        return len-1;
    }

    //
    // Return index of first occurrence of character "ch" in target string 
    // starting from position "from", -1 if there is no such symbol
    // i = indexOf(s, offs) => 
    //    i == -1 && not exists k: k >= offs && s[k] == ch
    // or
    //    i >= 0 && s[i] == ch && not exists k: k >= offs && k < i && s[k] == ch
    //
    int indexOf(wchar_t ch, int from = 0) const { 
        if (from >= len) { 
            return -1;
        }
        for (int i = from, n = len-1; i < n; i++) { 
            if (chars[i] == ch) { 
                return i;
            }
        }
        return -1;
    }

    //
    // Return index of last occurrence of character "ch" in target string 
    // starting from position "from", -1 if there is no such symbol
    // i = lastIndexOf(s, offs) => 
    //    i == -1 && not exists k: k <= offs && s[k] == ch
    // or
    //    i >= 0 && s[i] == ch && not exists k: k >= offs && k < i && s[k] == ch
    //
    int lastIndexOf(wchar_t ch, int i = INT_MAX) const { 
        if (i > len) {  
            i = len;
        }
        while (i >= 0 && chars[i] != ch) { 
            i -= 1;
        }
        return i;
    }

    //
    // Return index of first occurrence of string "str" in target string 
    // starting from position "from", -1 if there is no such symbol
    //
    int indexOf(wstring_t const& str, int from = 0) const { 
        wchar_t* p = chars; 
        wchar_t* q = str.chars; 
        int i1, i2;
        int n2 = str.len;
        int n1 = len - n2;      
        for (i1 = from; i1 < n1; i1++) { 
            for (i2 = 0; i2 < n2; i2++) { 
                if (p[i1] != q[i2]) { 
                    break;
                }
            }
            if (i2 == n2) { 
                return i1;
            }
        }
        return -1;
    }

    wchar_t& operator[](int i) { 
        assert(i < len);
        return chars[i];
    }

    wchar_t operator[](int i) const { 
        assert(i < len);
        return chars[i];
    }

    wstring_t operator+(wstring_t const& str) const { 
        return concat(str);
    }
    
    wstring_t concat(wstring_t const& str) const { 
        wstring_t newStr;
        newStr.chars = new wchar_t[newStr.len = len + str.len - 1];
        memcpy(newStr.chars, chars, (len-1)*sizeof(wchar_t));
        memcpy(newStr.chars + len - 1, str.chars, str.len*sizeof(wchar_t));
        return newStr;
    }

    wstring_t toLowerCase() const { 
        wstring_t newStr;
        newStr.chars = new wchar_t[newStr.len = len];
        for (int i = len; --i >= 0; newStr.chars[i] = towlower(chars[i]));
        return newStr;
    }

    wstring_t toUpperCase() const { 
        wstring_t newStr;
        newStr.chars = new wchar_t[newStr.len = len];
        for (int i = len; --i >= 0; newStr.chars[i] = towupper(chars[i]));
        return newStr;
    }

    wstring_t trim() const {
        int left, right;
        for (left = 0; left < len && chars[left] <= ' '; left++);
        for (right = len; --right >= 0 && chars[right] <= ' ';);
        return wstring_t(*this, left, right+1);
    }

    ~wstring_t() { 
        destroy();
    }

    //
    // Returns wide character zero terminated string. 
    // Should not be deallocated, because it will be deallocated by wstring
    //
    wchar_t* getWideChars() const { 
        return chars;
    }
    
    operator wchar_t*() const { return chars; }

    //
    // Returns multibyte zero terminated string. 
    // Should be deallocated by delete[] after use.
    //
    char* getChars() const { 
        char* p = new char[len*4+1];
        wcstombs(p, chars, len*4+1);
        return p;
    }

    //
    // Extract multibyte characters to buffer. It returns the number of bytes written 
    // into the multibyte output string buffer, excluding the terminating '\0' (if any). 
    //
    int getChars(char* buf, size_t bufSize) const {
        return (int)wcstombs(buf, chars, bufSize);
    }

  protected:
    wchar_t* chars;
    int      len;

    void destroy() { 
        delete[] chars;
        chars = NULL;
    }
};

END_GOODS_NAMESPACE

#endif
