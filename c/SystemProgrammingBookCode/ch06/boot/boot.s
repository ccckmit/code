.code16 #�ϥ�16�줸�Ҧ��J�s
.text #�{���X���q�}�l
mov %cs,%ax
mov %ax,%ds
mov %ax,%es
call DispStr #�ե���ܦr��`��
jmp . #�L���j��
DispStr:
mov $BootMessage, %ax
mov %ax,%bp #ES:BP = ��a�}
mov $16,%cx #CX = �����
mov $0x1301,%ax #AH = 13, AL = 01h
mov $0x00c,%bx #������0(BH = 0) �©����r(BL = 0Ch,���G)
mov $0,%dl
int $0x10 #10h �����_
ret
BootMessage:.ascii "Hello, Booter!"
.org 510 #��R��~510~�줸�ճB
.word 0xaa55 #�����лx
