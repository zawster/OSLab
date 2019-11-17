[org 0x0100]
		jmp start
TaskState:	dw 	0, 0, 0, 0, 0				
			dw	0, 0, 0, 0, 0 				
			dw 	0, 0, 0, 0, 0 				
curnt:	db	0 							
shapes: 		db 	'||' 						


Task1: 	mov al, [shapes+bx] 				
			mov [es:0], al 					
			inc bx 							
			and bx, 3 						
			jmp Task1						


Task2:	mov al, [shapes+bx]  
			mov [es:158], al 	         
			inc bx 							
			and bx, 3 						
			jmp Task2 			


;ISR  Timer
Timer: 		push ax
			push bx

			mov bl, [cs:curnt] 			
			mov ax, 10 					
			mul bl 						
			mov bx, ax 					

			pop ax						
			mov [cs:TaskState+bx+2], ax	
			pop ax 						
			mov [cs:TaskState+bx+0], ax 
			pop ax 						
			mov [cs:TaskState+bx+4], ax 
			pop ax 						
			mov [cs:TaskState+bx+6], ax 
			pop ax							
			mov [cs:TaskState+bx+8], ax 	
			
			inc byte [cs:curnt]			
			cmp byte [cs:curnt], 3  	
			jne SkipR  				
			mov byte [cs:curnt], 0 		


SkipR: 	mov bl, [cs:curnt]			
 			mov ax, 10 					
 			mul bl 							
 			mov bx, ax 						


 			mov al, 0x20					
 			out 0x20, al 

 			push word[cs:TaskState+bx+8] 	
 			push word[cs:TaskState+bx+6]	
 			push word[cs:TaskState+bx+4]	
 			mov ax, word[cs:TaskState+bx+0]
 			mov bx, word[cs:TaskState+bx+2]
 			iret 							


 start: 	mov word [TaskState+10+4], Task1 	
 			mov word [TaskState+10+6], cs 		
 			mov word [TaskState+10+8], 0x0200 	
 			mov word [TaskState+20+4], Task2 	
 			mov word [TaskState+20+6], cs 		
 			mov word [TaskState+20+8], 0x0200 			
 			mov byte [curnt], 0 						
 			xor ax, ax
 			mov es, ax 									
 			cli 
 			mov  word[es:8*4], Timer
 			mov [es:8*4+2], cs  						
 			mov ax, 0xb800
 			mov es, ax 									
 			xor bx, bx 									
 			sti 
 			jmp $