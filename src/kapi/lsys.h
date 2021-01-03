#ifndef INC_KAPI_LSYS
#define INC_KAPI_LSYS

/* The in-kernel libc. Really simple stuff,
 * just useful for strcpy, memset, etc.
 */

void 	*memset(void *region, char byte, unsigned int count);	

/* Panic */
void	ultimateyeet(char *reason);

#endif /* INC_KAPI_LSYS */
