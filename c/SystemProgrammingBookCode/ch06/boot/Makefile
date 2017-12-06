CC=gcc
LD=ld
LDFILE=boot.ld # 使用上面提供的連接腳本 boot.ld
OBJCOPY=objcopy

all: boot.img

# Step 1: gcc 調用 as 將 boot.S 編譯成目的檔案 boot.o
boot.o: boot.S
	$(CC) -c boot.S

# Step 2: ld 調用連接腳本 solrex_x86.ld 將 boot.o 連接成可執行檔 boot.elf
boot.elf: boot.o
	$(LD) boot.o -o boot.elf -e c -T$(LDFILE)

# Step 3: objcopy 移除 boot.elf 中沒有用的 section(.pdr,.comment,.note),
# strip 掉所有符號資訊，輸出為二進位檔案 boot.bin 。
boot.bin : boot.elf
	@$(OBJCOPY) -R .pdr -R .comment -R.note -S -O binary boot.elf boot.bin

 # Step 4: 生成可啟動軟碟鏡像。
 boot.img: boot.bin
	@dd if=boot.bin of=boot.img bs=512 count=1 #用 boot.bin 生成鏡像檔第一個磁區
	# 在 bin 生成的鏡像檔後補上空白，最後成為合適大小的軟碟鏡像
	@dd if=/dev/zero of=boot.img skip=1 seek=1 bs=512 count=2879

clean:
	@rm -rf boot.o boot.elf boot.bin boot.img
