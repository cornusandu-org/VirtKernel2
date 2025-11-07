.PHONY: build

additionalargs="-Iinclude"

build: build_x64
	@echo "\n\n[+] Build completed!"

.PHONY: build_x64

build_x64: ./dist/linux_x64/libtrace.so ./dist/linux_x64/main.exe
	@echo "[+] x64 Build completed!\n"

./dist/linux_x64/libtrace.so:
	@printf "[/] Building trace.so\r"
	@g++ ./src/userspace/trace.cpp -shared -fPIC -o ./dist/linux_x64/trace.so -O2 $(additionalargs)
	@echo "[+] Built trace.so                "

./dist/linux_x64/main.exe: ./dist/linux_x64/libtrace.so
	@printf "[/] Building main.exe (x64)\r"
	@g++ ./src/main.cpp -O2 -o ./dist/linux_x64/main.exe $(additionalargs)
	@printf "[+] Built main.exe (x64)                \n"

.PHONY: clear
.PHONY: rebuild

clear:
	rm -rf ./dist/*
	mkdir ./dist/linux_x64

rebuild: clear build
