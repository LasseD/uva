(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 program_id (111, 112, etc.) [test_file_id] ([a], b, ...)" >&2
  exit 1
fi

testFile=P$1a.txt
if [ "$#" -eq 2 ]; then
  testFile=P$1$2.txt
fi

cppFile=P$1.cpp
exeFile=P$1.exe

if [ ! -f "$cppFile" ]
then
  echo "Error: File $cppFile not found!"
  exit 2
fi
if [ ! -f "$testFile" ]
then
  echo "Error: File $testFile not found!"
  exit 2
fi

timeCPP=`stat -c "%Y" $cppFile`
timeA=0
if [ -f $exeFile ]
then
timeA=`stat -c "%Y" $exeFile`
fi

if [ $timeA -lt $timeCPP ]
then
  echo "Compiling $cppFile ..." 1>&2
  cat top.cpp P$1.cpp > tmp.cpp
  g++ -Wall tmp.cpp -o $exeFile
  if [ $? -ne 0 ]
  then
    echo "Compile error. Stop." 1>&2
    exit 3
  fi
  cat tmp.cpp > /dev/clipboard
fi

echo "Running ./$exeFile < $testFile" 1>&2
./$exeFile < $testFile
