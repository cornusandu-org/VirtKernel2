.PHONY: build

additionalargs="-Iinclude"
compileonly="-c"

build: build_x64
	@echo "\n\n[+] Build completed!"

.PHONY: build_x64

build_x64: ./dist/linux_x64/main.exe
	@echo "[+] x64 Build completed!\n"

./tmp/trace.o:
	@mkdir -p ./tmp
	@printf "[/] Building trace.o\r"
	@g++ ./src/userspace/trace.cpp -fPIC -o ./tmp/trace.o -O2 $(additionalargs) $(compileonly)
	@echo "[+] Built trace.o                "

./tmp/main.o:
	@mkdir -p ./tmp
	@printf "[/] Building main.o (x64)\r"
	@g++ ./src/main.cpp -O2 -o ./tmp/main.o $(additionalargs) $(compileonly)
	@printf "[+] Built main.o (x64)                \n"

./tmp/runproc.o:
	@mkdir -p ./tmp
	@printf "[/] Building runproc.o (x64)\r"
	@g++ ./src/userspace/runproc.cpp -O2 -o ./tmp/runproc.o $(additionalargs) $(compileonly)
	@printf "[+] Built runproc.o (x64)                \n"

./tmp/startup.o:
	@mkdir -p ./tmp
	@printf "[/] Building startup.o (x64)\r"
	@g++ ./src/startup.cpp -O2 -o ./tmp/startup.o $(additionalargs) $(compileonly)
	@printf "[+] Built startup.o (x64)                \n"

./tmp/exit_.o:
	@mkdir -p ./tmp
	@printf "[/] Building exit_handler.o (x64)\r"
	@g++ ./src/exit_.cpp -O2 -o ./tmp/exit_handler.o $(additionalargs) $(compileonly)
	@printf "[+] Built exit_handler.o (x64)                \n"

./tmp/procmanager.o:
	@mkdir -p ./tmp
	@printf "[/] Building procmanger.o (x64)\r"
	@g++ ./src/userspace/procmanager.cpp -O2 -o ./tmp/procmanager.o $(additionalargs) $(compileonly)
	@printf "[+] Built procmanger.o (x64)                \n"

./dist/linux_x64/main.exe: ./tmp/main.o ./tmp/trace.o ./tmp/runproc.o ./tmp/exit_.o ./tmp/startup.o ./tmp/procmanager.o
	@printf "[/] Linking main.exe (x64)\r"
	@g++ ./tmp/*.o -o ./dist/linux_x64/main.exe -O2
	@printf "[+] Linked main.exe (x64)                \n"

.PHONY: clear
.PHONY: rebuild

clean:
	@rm -rf ./dist/*
	@rm -rf ./tmp/*.o
	@mkdir ./dist/linux_x64

rebuild: clean
	@make build
