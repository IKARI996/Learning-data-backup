    org  07c00h					; ���ص� 0:7C00 ��
	jmp short LABEL_START		; Start to boot.
	nop							; ��� nop ������
	; ������ FAT12 ��������������BPB��EBPB�ṹ��51�ֽ�
	BS_OEMName		DB 'LingOs  ' ; OEM String, ���� 8 ���ֽڣ����㲹�ո�
	BPB_BytsPerSec	DW 512		; ÿ�����ֽ���
	BPB_SecPerClus	DB 1		; ÿ�ض�������
	BPB_RsvdSecCnt	DW 1		; Boot��¼ռ�ö�������
	BPB_NumFATs		DB 2		; ���ж��� FAT ��
	BPB_RootEntCnt	DW 224		; ��Ŀ¼�ļ������ֵ
	BPB_TotSec16	DW 2880		; �߼���������
	BPB_Media		DB 0xF0		; ����������
	BPB_FATSz16		DW 9		; ÿFAT������
	BPB_SecPerTrk	DW 18		; ÿ�ŵ�������
	BPB_NumHeads	DW 2		; ��ͷ��(����)
	BPB_HiddSec		DD 0		; ����������
	BPB_TotSec32	DD 0		; wTotalSectorCountΪ0ʱ���ֵ��¼������
	BS_DrvNum		DB 0		; �ж� 13 ����������
	BS_Reserved1	DB 0		; δʹ��
	BS_BootSig		DB 29h		; ��չ������� (29h)
	BS_VolID		DD 12345678h; �����к�
	BS_VolLab		DB 'LingOSv0.4' ; ���, ���� 11 ���ֽڣ����㲹�ո�
	BS_FileSysType	DB 'FAT12   '	; �ļ�ϵͳ����, ���� 8���ֽڣ����㲹�ո�  
LABEL_START:
	mov	ax, cs			; ��DS��ES=CS
	mov	ds, ax
	mov	es, ax
	Call	DispStr		; ������ʾ�ַ�������
	jmp	$				; ����ѭ��
DispStr:
	mov	ax, BootMessage
	mov	bp, ax			; ES:BP = ����ַ
	mov	cx, 16			; CX = ������
	mov	ax, 01301h		; AH = 13,  AL = 01h
	mov	bx, 000ch			; ҳ��Ϊ0(BH = 0) �ڵ׺���(BL = 0Ch,����)
	mov	dx, 0
	int	10h				; int 10h
	ret
BootMessage:	db	"LingOSv0.4!"
	times 510-($-$$)	db	0	; ��0�����������ʣ�µĿռ�
	db 	55h,0aah				; ��������������־
; �������FAT���ͷ�����ÿ��FATռ9��������
	db 0f0h, 0ffh, 0ffh			; ������������F0h����Fh�������ر�־��FFFh
	times 512*9-3		db	0	; ��0���FAT#1ʣ�µĿռ�
	db 0f0h, 0ffh, 0ffh			; ������������F0h����Fh�������ر�־��FFFh
	times 512*9-3		db	0	; ��0���FAT#2ʣ�µĿռ�
; ��Ŀ¼�еľ����Ŀ
	db 'LingOS_Disk' 			; ���, ���� 11 ���ֽڣ����㲹�ո�
	db 8						; �ļ�����ֵ�������Ŀ��Ϊ08h��
	dw 0,0,0,0,0				; 10�������ֽ�
	dw 0,4070h				    ; ����ʱ�䣬��Ϊ2012��3��16��0ʱ0��0��
	dw 0						; ��ʼ�غţ������Ŀ�ı���Ϊ0��
	dd 0						; �ļ���С��Ҳ��Ϊ0��
