#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#define msgSize 100
typedef struct msgbuf{
	long msgtype;
	char msg[msgSize];
} msgbuf_struct;
int msgID;

int Reciever(int key){	
	msgbuf_struct buf;   // object of struct
	//key = 121;
	msgID = msgget(key, 0666);
	msgrcv(msgID, &buf, msgSize, 1, 0);
	printf("\n %s \n", buf.msg);		//  Actual message is printing here
	return 0;
}

int main(){
	int msgflg = IPC_CREAT | 0666;
	msgbuf_struct buf;
	size_t buf_len;
	key_t key=121;    // key form authntication of msg
	msgID = msgget(key, msgflg );
	buf.msgtype = 1;
	strcpy(buf.msg, "Message is Recieved");
	buf_len = strlen(buf.msg) + 1 ;
	msgsnd(msgID, &buf, buf_len, IPC_NOWAIT);  // Message is send here

	Reciever(key);    //   call to Reciever with key for authentication
	
	return 0;
}

