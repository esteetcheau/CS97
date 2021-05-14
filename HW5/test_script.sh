
a=$(./randall 5 | wc -c); if [ $a -eq 5 ]; 
then echo "success"; 
else echo "fail"; fi;

a=$(./randall -i mrand48_r -o stdio 10 | wc -c); if [ $a -eq 10 ]; 
then echo "success"; 
else echo "fail"; fi;

if [ "$(./randall 5 -i /dev/urandom | wc -c)" = 5 ]; 
then echo "success -> ./randall 5 -i /dev/urandom"; 
else echo "fail -> ./randall 5 -i /dev/urandom"; fi

if [ `./randall 100 | wc -c` -eq 100 ];
then echo "success "; 
else echo "fail "; fi;
	
if [ `./randall -o 1 10 | wc -c` -eq 10 ]; 
then echo "success "; 
else echo "fail "; fi;

if [ "$(./randall 6 -o 1 | wc -c)" = 6 ]; 
then echo "success -> ./randall 6 -o 1"; 
else echo "fail -> ./randall 6 -o 1"; fi
	

if [ "$(./randall 25 | wc -c)" = 25 ]; 
then echo "success-> ./randall 25"; 
else echo "fail -> ./randall 25"; fi


if [ "$(./randall 10 -i rdrand | wc -c)" = 10 ]; 
then echo "success -> ./randall 10 -i rdrand"; 
else echo "fail -> ./randall 10 -i rdrand"; fi

if [ "$(./randall -i rdrand 20 -o 2 | wc -c)" = 20 ]; 
then echo "success-> ./randall -i rdrand 20 -o 2"; 
else echo "fail -> ./randall -i rdrand 20 -o 2"; fi

if [ "$(./randall 5 -i mrand48_r | wc -c)" = 5 ]; 
then echo "success -> ./randall 5 -i mrand48_r"; 
else echo "fail -> ./randall 5 -i mrand48_r"; fi

if [ "$(./randall 40 -i mrand48_r -o 1 | wc -c)" = 40 ]; 
then echo "success -> ./randall 40 -i mrand48_r -o 1"; 
else echo "fail -> ./randall 40 -i mrand48_r -o 1"; fi

if [ "$(./randall 10 -i /dev/urandom | wc -c)" = 10 ]; 
then echo "success -> ./randall 10 -i /dev/urandom"; 
else echo "fail -> ./randall 10 -i /dev/urandom"; fi

if [ "$(./randall -i /dev/urandom -o stdio 5 | wc -c)" = 5 ]; 
then echo "success -> ./randall -i /dev/urandom -o stdio 5";
else echo "fail -> ./randall -i /dev/urandom -o stdio 5"; fi

if [ "$(./randall 15 -o stdio | wc -c)" = 15 ]; 
then echo "success -> ./randall 15 -o stdio"; 
else echo "fail -> ./randall 15 -o stdio"; fi

