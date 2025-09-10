ASM=nasm

NAME=main.img
SRC_DIR=src
BUILD_DIR=build

# To create image, requires main.bin file
# truncate to fill out the full 'floppy drive'
# I guess an valid image needs to take up the full media size?
$(BUILD_DIR)/$(NAME): $(BUILD_DIR)/main.bin
	cp $(BUILD_DIR)/main.bin $(BUILD_DIR)/main.img
	truncate -s 1440k $(BUILD_DIR)/main.img

# To create the main.bin file
# Creating a bin file out of main.s an placing output in $BUILD_DIR
$(BUILD_DIR)/main.bin: $(SRC_DIR)/main.s
	$(ASM) $(SRC_DIR)/main.s -f bin -o $(BUILD_DIR)/main.bin

clean:
	rm $(BUILD_DIR)/*

re: clean all

.PHONY: re clean all
