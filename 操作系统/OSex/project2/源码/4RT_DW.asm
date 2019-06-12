;�û�����4�����½���ʾ
; ���������ı���ʽ��ʾ���ϴ�������һ��*��,��45���������˶���ײ���߿����,�������.
	Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
    Up_Rt equ 2                  ;
    Up_Lt equ 3                  ;
    Dn_Lt equ 4                  ;
    delay equ 50000				; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
    ddelay equ 580				; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
    org 8700h

start:
    mov ax,cs
	mov ds,ax
	mov es,ax					; ES = CS
	mov ax,0B800h				; �ı������Դ���ʼ��ַ
	mov gs,ax					; GS = B800h
    mov byte[char],'A'
	
loop1:
	dec word[count]				; �ݼ���������
	jnz loop1					; !=0����ת;
	mov word[count],delay
	dec word[dcount]				; �ݼ���������
    jnz loop1
	mov word[count],delay
	mov word[dcount],ddelay

    mov al,1
    cmp al,byte[rdul]
	jz  DnRt
    mov al,2
    cmp al,byte[rdul]
	jz  UpRt
    mov al,3
    cmp al,byte[rdul]
	jz  UpLt
    mov al,4
    cmp al,byte[rdul]
	jz  DnLt

DnRt:
	inc word[x]
	inc word[y]
	mov bx,word[x]
	mov ax,25
	sub ax,bx
    jbe  dr2ur
	mov bx,word[y]
	mov ax,80
	sub ax,bx
    jbe  dr2dl
	jmp show
	
dr2ur:
    mov word[x],23
    mov byte[rdul],Up_Rt
    jmp show
	
dr2dl:
    mov word[y],79
    mov byte[rdul],Dn_Lt
    jmp show

UpRt:
	dec word[x]
	inc word[y]
	mov bx,word[y]
	mov ax,80
	sub ax,bx
    jbe  ur2ul
	mov bx,word[x]
	mov ax,11
	sub ax,bx
    jge  ur2dr
	jmp show
	
ur2ul:
    mov word[y],78
    mov byte[rdul],Up_Lt
    jmp show
	
ur2dr:
    mov word[x],13
    mov byte[rdul],Dn_Rt
    jmp show
	
UpLt:
	dec word[x]
	dec word[y]
	mov bx,word[x]
	mov ax,11
	sub ax,bx
    jge  ul2dl
	mov bx,word[y]
	mov ax,40
	sub ax,bx
	jge  ul2ur
	jmp show

ul2dl:
    mov word[x],13
    mov byte[rdul],Dn_Lt
    jmp show
	
ul2ur:
    mov word[y],42
    mov byte[rdul],Up_Rt
    jmp show
	
DnLt:
	inc word[x]
	dec word[y]
	mov bx,word[y]
	mov ax,40
	sub ax,bx
    jge  dl2dr
	mov bx,word[x]
	mov ax,25
	sub ax,bx
    jbe  dl2ul
	jmp show

dl2dr:
    mov word[y],42
    mov byte[rdul],Dn_Rt
    jmp show
	
dl2ul:
    mov word[x],23
    mov byte[rdul],Up_Lt
    jmp show
	
show:
	;����A�ĺۼ�
	mov ax, word[tmp]
	mov bp, ax
	mov ah, 07h
	mov al, ' '
	mov word[gs:bp],ax
	
	; �����Դ��ַ
    xor ax,ax                 
    mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bp,ax
	mov word[tmp],ax
	mov ah,byte[color1]				;  0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
	mov al,byte[char]			;  AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո����
	mov word[gs:bp],ax  		;  ��ʾ�ַ���ASCII��ֵ
	
	;����ɫ
	cmp byte[color1], 0Fh					
	jnz change
	mov byte[color1], 0
change:
	add byte[color1], 1
	
	;��ʾ����
	mov cx, 34
	mov si, myname
	mov di, 2
dis:
	mov al, byte[ds:si]
	inc si
	mov ah, 07h
	mov word [gs:di],ax
	add di,2
	loop dis
	
	int 20h
	jmp loop1
    jmp $                   ; ֹͣ��������ѭ�� 

data:
	myname db "16337341 ZhuZhiru's fourth program"
	tmp dw 0
	color1 db 0Fh
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; �������˶�
    x    dw 15 
    y    dw 41
    char db 'A'