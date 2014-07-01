(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 program_id (111, 112, etc.) test_file_id (a, b, ...)" >&2
  exit 1
fi

cppFile=P$1.cpp
exeFile=P$1.exe
testFile=P$1$2.txt

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
  echo "Compiling $cppFile ..."
  g++ -Wall $cppFile
  if [ $? -ne 0 ]
  then
    echo "Compile error. Stop."
    exit 3
  fi
  mv a.exe $exeFile
fi

echo "Running ./$exeFile < $testFile"
./$exeFile < $testFile
