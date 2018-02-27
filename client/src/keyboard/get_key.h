#ifdef ARM
#ifndef GET_KEY_H
#define GET_KEY_H

#ifdef __cplusplus
extern "C"
{
#endif
    int   kbd_init();
    int   kbd_close();
    char  get_key(void);
    char *get_line(char *cmd);

#ifdef __cplusplus
}  /* end extern "C" */
#endif


#endif // GET_KEY_H
#endif
