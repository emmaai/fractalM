#ifndef RWSOCKTHREAD
#define RWSOCKTHREAD
void *rSocket(void *); /* function prototype */
void *wSocket(void *);
/*
*   parse command string in the buffer
*   return status:
*	001 -- last head is COMD 
*	010 -- last head is PARA 
*	100 -- last head is DATA 
*/
int parsCmd(unsigned long buffer, int buffersize, short cmd);

#endif //RWSOCKTHREAD
