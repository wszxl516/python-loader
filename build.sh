mkdir $1
cd $1
cp /usr/lib/python3.6/* . -r
python3 -O -m compileall -b .
find . -name '*.py' -type f -print -exec rm {} \;
find . -name '__pycache__' -exec rm -rf {} \;
rm __pycache__ -rf
rm config-3.6m-x86_64-linux-gnu -rf
rm tkinter -rf
rm lib2to3 -rf
zip -r ../$1.zip ./*
cd ..
./bin2hex lib.zip lib.h
./bin2hex __main__.py main.h
sed -i "s/char data/char main_data/g" main.h
