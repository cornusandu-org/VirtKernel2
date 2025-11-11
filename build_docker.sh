docker build -t virtkernel2 .
docker create --name virt_temp virtkernel2
rm -rf ./dist/linux_x64
mkdir -p ./dist/linux_x64
docker cp virt_temp:/app/dist/linux_x64 ./dist/
docker rm virt_temp
