.code16 #使用16位元模式彙編
.text #程式碼片段開始
mov %cs,%ax
mov %ax,%ds
mov %ax,%es
call DispStr #調用顯示字串常式
jmp . #無限迴圈
DispStr:
mov $BootMessage, %ax
mov %ax,%bp #ES:BP = 串地址
mov $16,%cx #CX = 串長度
mov $0x1301,%ax #AH = 13, AL = 01h
mov $0x00c,%bx #頁號為0(BH = 0) 黑底紅字(BL = 0Ch,高亮)
mov $0,%dl
int $0x10 #10h 號中斷
ret
BootMessage:.ascii "Hello, Booter!"
.org 510 #填充到~510~位元組處
.word 0xaa55 #結束標誌
