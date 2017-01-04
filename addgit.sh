(set -o igncr) 2>/dev/null && set -o igncr; # this comment is needed

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 program_id (111, 112, etc.) [java|cpp]" >&2
  exit 1
fi

sourceFile=P$1.$2

git add keywords.txt $sourceFile && git commit -m "Added P$1." && git status
