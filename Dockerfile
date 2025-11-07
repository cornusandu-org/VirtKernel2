FROM kali-rolling AS base

COPY . .

apt-get install build-essential -y
apt-get install g++-multilib -y
make rebuild