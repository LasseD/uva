REQUIREMENTS:

A C++ 5.3.0 compiler, such as the GNU C++ compiler.


VERIFY:

You are about to compile and run a C++ generated executable. Ensure that the content of the CPP file looks safe before you do this. Don't trust stuff you have downloaded from the net.


COMPILE:

Compile the source using the collowing command:

g++ -Wall -o2 oxl.cpp -o oxl.exe


FOLDER STRUCTURE:

Ensure the following files are present and readable by oxl.exe:

- ads_data.csv
- user_data.csv
- user_messages.csv
- user_messages_test.csv

These must lie in the same folder as oxl.exe.


RUN:

Run the oxl.exe:

./oxl.exe

The ads_recommendation.csv file will be generated. Check out the progress using "tail -f ads_recommendation.csv" or simply open the file.


CONTACT:

For any problems, please contact Lasse Deleuran at lassedeleuran@gmail.com
