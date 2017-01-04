(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 program_id (111, 112, etc.) [java|cpp]. 'cpp' is default type" >&2
  exit 1
fi

sourceFile=P$1.cpp
if [ "$#" -eq 2 ]; then
  sourceFile=P$1.$2
fi

git add keywords.txt $sourceFile && git commit -m "Added P$1." && git status
