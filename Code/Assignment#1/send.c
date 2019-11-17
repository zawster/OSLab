#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#define MSGSZ 128
typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
} message_buf;
void main()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	size_t buf_length;
	key = 1234;
	msqid = msgget(key, msgflg );
	sbuf.mtype = 1;
	strcpy(sbuf.mtext, "Did you get this?");
	buf_length = strlen(sbuf.mtext) + 1 ;
	msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT);
}