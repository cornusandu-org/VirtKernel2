# Virtkernel2
This project aims at virtualisation of executables by intercepting system calls and reinterpreting them safely, allowing for isolation.
## Version History
### 0.1.0
First functional and tested build. Still a debug build (contains debug messages in stdout).
## Project Roadmap
- [ ] Support common syscalls.
- [ ] Background threads for background tasks and monitoring (kernel)
- [ ] Multiple processes
    - [ ] Process tracking
    - [ ] Process privilege tracking
    - [ ] Kernel-level process escalation
## Building from source
### Manual
To build the project yourself, just run:
```bash
make clean
make build -j$(nproc)
```
Please note that you will need to have the GNU compiler set (`g++`, `gcc` etc.) installed (`build-essential`). If you do not wish to install it, please use Docker for building.
### Docker
To build the project with Docker, we provided a script to do everything for you. Simply run:
```bash
source build_docker.sh
```
Or, if you're on Windows (please note that the output binaries will not run on Windows):
```ps1
./w_build_docker.ps1  # Please note that this script is not tested, and issues may arise.
```
This will build the app and automatically copy the binaries into a seperate folder.
