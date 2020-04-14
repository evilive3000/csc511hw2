# csc511hw2

git clone git@github.com:evilive3000/csc511hw2.git
cd csc511hw2

# build c++ app
mkdir cmake-build
cd cmake-build
cmake ..
make 

# prepare node server
cd ../visaulization/
npm i
npm run start
