
#include <stdarg.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <common.h>
#include <bootlogo/iniparser.h>
#define assert(e)

#define _tcschr   strchr
#define _tcslen   strlen
#define _tcsncpy  strncpy
#define _tcsnicmp strnicmp //strncasecmp //strnicmp
#define _tcstol   simple_strtol

#if !defined LINE_BUFFERSIZE
#define LINE_BUFFERSIZE  512
#endif

static char * g_BufferAddr = NULL;
static unsigned int g_BufferLen;
static unsigned int g_BufferPos;
void Profile_Init(char *BufferAddr,unsigned int BufLen)
{
    g_BufferAddr = BufferAddr;
    g_BufferLen = BufLen;
    g_BufferPos = 0;
}
char * Profile_gets(char * s, int nchar)
{
    int n;
    if (g_BufferAddr == NULL)
    return NULL;

    n = 0;
    while(g_BufferPos<g_BufferLen)
    {
    s[n] = g_BufferAddr[g_BufferPos];
    g_BufferPos++;
    if (s[n] == '\n')
    {
    s[n+1] = '\0';
    return s;
    }
    n++;
    if (n>=nchar-1)
    {
    s[n] = '\0';
    return s;
    }
    }
    if (n)
    {
    s[n] = '\0';
    return s;
    }
    return NULL;
}
void Profile_seek(unsigned int pos)
{
    g_BufferPos = pos;
}

int strnicmp(const char *s1, const char *s2, size_t n)
{
    char c1, c2;

    while (n-- != 0 && (*s1 || *s2))
    {
        c1 = *(char *)s1++;
        if ('a' <= c1 && c1 <= 'z')
            c1 += ('A' - 'a');
        c2 = *(char *)s2++;
        if ('a' <= c2 && c2 <= 'z')
            c2 += ('A' - 'a');
        if (c1 != c2)
        return c1 - c2;
    } /* while */
    return 0;
}

char String_ToUpperCase(char ch)
{
    return (ch<0x7F)? toupper(ch): ch;
}
unsigned int String_AParseHexU32(char * str)
{
    unsigned int i, ret = 0;

    assert(str != NULL);

    if (str[0] == '0' && String_ToUpperCase(str[1]) == 'X')
        str += 2;
    for (i = 0; i < 8 && (*str != 0); i++, str++) //note: atmost 8*4=32bits
    {
        char ch = String_ToUpperCase(*str);
        if ('0' <= ch && ch <= '9')
        ret = (ret << 4) | (ch-'0');
        else if ('A' <= ch && ch <= 'F')
        ret = (ret << 4) | (10+ch-'A');
        else
        break;
    }
    return ret;
}

enum quote_option
{
    QUOTE_NONE,
    QUOTE_ENQUOTE,
    QUOTE_DEQUOTE,
};

static char *skipleading(const char *str)
{
    assert(str != NULL);
    while (*str != '\0' && *str <= ' ')
    str++;
    return (char *)str;
}

static char *skiptrailing(const char *str, const char *base)
{
    assert(str != NULL);
    assert(base != NULL);
    while (str > base && *(str-1) <= ' ')
    str--;
    return (char *)str;
}

static char *striptrailing(char *str)
{
    char *ptr = skiptrailing(_tcschr(str, '\0'), str);
    assert(ptr != NULL);
    *ptr='\0';
    return str;
}

static char *save_strncpy(char *dest, const char *source, size_t maxlen, enum quote_option option)
{
    int d, s;

    assert(maxlen>0);
    if (option == QUOTE_ENQUOTE && maxlen < 3)
    option = QUOTE_NONE;  /* cannot store two quotes and a terminating zero in less than 3 characters */

    switch (option)
    {
    case QUOTE_NONE:
    _tcsncpy(dest,source,maxlen);
    dest[maxlen-1]='\0';
    break;
    case QUOTE_ENQUOTE:
    d = 0;
    dest[d++] = '"';
    for (s = 0; source[s] != '\0' && d < maxlen - 2; s++, d++)
    {
    if (source[s] == '"')
    {
    if (d >= maxlen - 3)
    break;  /* no space to store the escape character plus the one that follows it */
    dest[d++] = '\\';
    } /* if */
    dest[d] = source[s];
    } /* for */
    dest[d++] = '"';
    dest[d] = '\0';
    break;
    case QUOTE_DEQUOTE:
    for (d = s = 0; source[s] != '\0' && d < maxlen - 1; s++, d++)
    {
    if ((source[s] == '"' || source[s] == '\\') && source[s + 1] == '"')
    s++;
    dest[d] = source[s];
    } /* for */
    dest[d] = '\0';
    break;
    default:
    assert(0);
    } /* switch */

    return dest;
}

static int getkeystring( const char *Section, const char *Key,
int idxSection, int idxKey, char *Buffer, int BufferSize)
{
    char *sp, *ep;
    int len, idx, isstring;
    char LocalBuffer[LINE_BUFFERSIZE];

    assert(g_BufferAddr != NULL);
    /* Move through file 1 line at a time until a section is matched or EOF. If
    * parameter Section is NULL, only look at keys above the first section. If
    * idxSection is postive, copy the relevant section name.
    */
    len = (Section != NULL) ? _tcslen(Section) : 0;
    if (len > 0 || idxSection >= 0)
    {
    idx = -1;
    do
    {
    if (!Profile_gets(LocalBuffer, LINE_BUFFERSIZE))
    return 0;
    sp = skipleading(LocalBuffer);
    ep = _tcschr(sp, ']');
    }
    while (*sp != '[' || ep == NULL || (((int)(ep-sp-1) != len || _tcsnicmp(sp+1,Section,len) != 0) && ++idx != idxSection));
    if (idxSection >= 0)
    {
    if (idx == idxSection)
    {
    assert(ep != NULL);
    assert(*ep == ']');
    *ep = '\0';
    save_strncpy(Buffer, sp + 1, BufferSize, QUOTE_NONE);
    return 1;
    } /* if */
    return 0; /* no more section found */
    } /* if */
    } /* if */

/* Now that the section has been found, find the entry.
* Stop searching upon leaving the section's area.
*/
    assert(Key != NULL || idxKey >= 0);
    len = (Key != NULL) ? (int)_tcslen(Key) : 0;
    idx = -1;
    do
    {
    if (!Profile_gets(LocalBuffer,LINE_BUFFERSIZE) || *(skipleading(LocalBuffer)) == '[')
    return 0;
    sp = skipleading(LocalBuffer);
    ep = _tcschr(sp, '='); /* Parse out the equal sign */
    if (ep == NULL)
    ep = _tcschr(sp, ':');
    }
    while (*sp == ';' || *sp == '#' || ep == NULL || (((int)(skiptrailing(ep,sp)-sp) != len || _tcsnicmp(sp,Key,len) != 0) && ++idx != idxKey));
    if (idxKey >= 0)
    {
    if (idx == idxKey)
    {
    assert(ep != NULL);
    assert(*ep == '=' || *ep == ':');
    *ep = '\0';
    striptrailing(sp);
    save_strncpy(Buffer, sp, BufferSize, QUOTE_NONE);
    return 1;
    } /* if */
    return 0;   /* no more key found (in this section) */
} /* if */

    /* Copy up to BufferSize chars to buffer */
    assert(ep != NULL);
    assert(*ep == '=' || *ep == ':');
    sp = skipleading(ep + 1);
    /* Remove a trailing comment */
    isstring = 0;
    for (ep = sp; *ep != '\0' && ((*ep != ';' && *ep != '#') || isstring); ep++)
    {
    if (*ep == '"')
    {
    if (*(ep + 1) == '"')
    ep++;                 /* skip "" (both quotes) */
    else
    isstring = !isstring; /* single quote, toggle isstring */
    }
    else if (*ep == '\\' && *(ep + 1) == '"')
    {
    ep++;                   /* skip \" (both quotes */
    } /* if */
    } /* for */
    assert(ep != NULL && (*ep == '\0' || *ep == ';' || *ep == '#'));
    *ep = '\0';                 /* terminate at a comment */
    striptrailing(sp);
    /* Remove double quotes surrounding a value */
    isstring = QUOTE_NONE;
    if (*sp == '"' && (ep = _tcschr(sp, '\0')) != NULL && *(ep - 1) == '"')
    {
    sp++;
    *--ep = '\0';
    isstring = QUOTE_DEQUOTE; /* this is a string, so remove escaped characters */
    } /* if */
    save_strncpy(Buffer, sp, BufferSize, (enum quote_option)isstring);
    return 1;
}

/** Profile_GetString()
* \param Section     the name of the section to search for
* \param Key         the name of the entry to find the value of
* \param DefValue    default string in the event of a failed read
* \param Buffer      a pointer to the buffer to copy into
* \param BufferSize  the maximum number of characters to copy
*
* \return            the number of characters copied into the supplied buffer
*/
int Profile_GetString(const char *Section, const char *Key, const char *DefValue,
char *Buffer, int BufferSize)
{
    int ok = 0;

    if (Buffer == NULL || BufferSize <= 0 || Key == NULL)
    return 0;
    if (g_BufferAddr != NULL)
    {
    ok = getkeystring(Section, Key, -1, -1, Buffer, BufferSize);
    Profile_seek(0);
    } /* if */
    if (!ok)
    save_strncpy(Buffer, DefValue, BufferSize, QUOTE_NONE);
    return _tcslen(Buffer);
}

/** Profile_GetInteger()
* \param Section     the name of the section to search for
* \param Key         the name of the entry to find the value of
* \param DefValue    the default value in the event of a failed read
*
* \return            the value located at Key
*/
long Profile_GetInteger(const char *Section, const char *Key, long DefValue)
{
    char buff[64];
    int len = Profile_GetString(Section, Key, "", buff, sizearray(buff));
    //  printf("int %s \n",buff);

    if (len == 0)
    return DefValue;

    if (buff[0] == '0' && String_ToUpperCase(buff[1]) == 'X')
    return String_AParseHexU32(buff);
        else
            return _tcstol(buff,NULL,10);
}
int Profile_GetBoolean(const char *Section, const char *Key, int DefValue)
{
    char buff[64];
    int len = Profile_GetString(Section, Key, "", buff, sizearray(buff));
    int ret = 0;
    //  printf("int %s \n",buff);

    if (len == 0)
    {
        return DefValue;
    }

    if((buff[0] == 'y') || (buff[0] == 'Y') || (buff[0] == '1') || (buff[0] == 't') || (buff[0] == 'T'))
    {
        ret = 1 ;
    }
    else if((buff[0] == 'n') || (buff[0] == 'N') || (buff[0] == '0') || (buff[0] == 'f') || (buff[0] == 'F'))
    {
        ret = 0 ;
    }
    else
    {
        ret = DefValue ;
    }
    return ret;
}

