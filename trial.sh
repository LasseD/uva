(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed

if [ "$#" -ne 3 ]; then
  echo "Usage: $0 program1.exe program2.exe generator.exe" >&2
  exit 1
fi

p1=$1
p2=$2
gen=$3

if [ ! -f "$p1" ]
then
  echo "Error: File $p1 not found!"
  exit 2
fi
if [ ! -f "$p2" ]
then
  echo "Error: File $p2 not found!"
  exit 2
fi
if [ ! -f "$gen" ]
then
  echo "Error: File $gen not found!"
  exit 2
fi

echo "Comparing!"
while :
do
./$gen > in.txt
./$p1 < in.txt > out1.txt
./$p2 < in.txt > out2.txt

ret=`cmp out1.txt out2.txt`

if [ "$ret" != "" ]
then
  echo "Found something! $ret"
  diff out1.txt out2.txt
  cmp out1.txt out2.txt

  exit 2
fi
done
