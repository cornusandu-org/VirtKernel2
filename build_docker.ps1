docker build -t virtkernel2 .
docker create --name virt_temp virtkernel2
rm -Recurse -Force ./dist/linux_x64
docker cp virt_temp:/app/dist/linux_x64 ./dist/linux_x64
docker rm virt_temp
