#ifndef INC_KAPI_MSYS
#define INC_KAPI_MSYS

void	initpagealloc(void);
void	*allocpage(void);
void	freepage(void * page);

void	printpageallocstate(void);

#endif /* INC_KAPI_MSYS */
