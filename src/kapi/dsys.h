#ifndef INC_KAPI_DSYS
#define INC_KAPI_DSYS

void	uartinit(void);
/* returns 0 if no char available */
char 	uartreadc(void); 
void	uartwrite(char *str);

#endif /* INC_KAPI_DSYS */
