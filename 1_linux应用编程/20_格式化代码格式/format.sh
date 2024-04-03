
dir=$1
filelist=`find $dir -type f -name "*.c" -or -name "*.h"`
for file in $filelist
do
	astyle --style=linux --convert-tabs --indent=spaces=4 -f -A2 -p -k3 -W3 -S -M120 -y -Y  $file
done
