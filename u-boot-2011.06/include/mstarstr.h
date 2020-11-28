#ifndef _MSTAR_STR_H_
#define _MSTAR_STR_H_

#if CONFIG_MSTAR_STR_ENABLE
extern int _is_str_resume(void);
#define is_str_resume()    _is_str_resume()
#else
#define is_str_resume()    (0)
#endif

#endif