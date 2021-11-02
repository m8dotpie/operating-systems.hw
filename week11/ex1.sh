dd if=/dev/zero of=lofs.img bs=100M count=10
losetup -fP lofs.img
mkfs.ext4 lofs.img 
mkdir /loopfs
sudo cp file1 /loopfs
sudo cp file2 /loopfs
sudo cp ex2.out /loopfs
sudo mount -o loop /dev/loop0 /loopfs
