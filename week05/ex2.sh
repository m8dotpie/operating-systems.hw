cnt=0
while [ -f 'file.lock' ]; do
    if [ $(expr $cnt % 150) == 0 ]; then
        echo 'Waiting for unlock' 
    fi
    cnt=$(expr $cnt + 1)
done

touch file.lock

its=0
while [[ $its -lt 1000 ]]; do
    num=`tail -1 seq.txt`
    num=$(expr $num + 1)
    echo $num >> seq.txt
    its=$(expr $its + 1)
done

rm file.lock
