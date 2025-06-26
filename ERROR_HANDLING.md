If in.txt doesn't exists
	- Ignore first cmd
	- Execute from second cmd forward
	- Exit (1)

If out.txt doesn't exists
	- It's gonna be created, even if all cmds are invalid

If out.txt has permission denied
	- Execute every cmd exept the last one

If first cmd is invalid
	- Ignore it and continue executing from the next cmd

If any cmd doesn't exists
	- Exit (127)

Need to protect from 'env -i'

// valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --track-fds=all

------------------------------------
No file:

./pipex isn.txt "cat -e" "grep .c" out.txt
isn.txt: No such file or directory
Exit 1

< isn.txt cat -e | grep .c > ref.txt
bash: isn.txt: No such file or directory
Exit 1

------------------------------------
No Access file1:

./pipex not.txt "cat -e" "grep .c" out.txt
not.txt: Permission denied
Exit 1

< not.txt cat -e | grep .c > ref.txt
bash: not.txt: Permission denied
Exit 1

------------------------------------
No Access file2:

./pipex in.txt "cat -e" "cat -e" not.txt
not.txt: Permission denied
Exit 1

< in.txt cat -e | cat -e not.txt
cat: not.txt: Permission denied
Exit 1

------------------------------------
Empty String cmd1:

./pipex in.txt "" "cat -e" out.txt
: command not found
Exit 0

< in.txt "" | cat -e > ref.txt
Command '' not found, but can be installed with:
Exit 0

------------------------------------
Empty String cmd2:

./pipex in.txt "cat -e" "" out.txt
: command not found
Exit 127

< in.txt cat -e | "" > ref.txt
Command '' not found, but can be installed with:
Exit 127

------------------------------------
Invalid cmd1:

./pipex in.txt "caat -e" "cat -e" out.txt
caat -e: command not found
Exit 0

< in.txt caat -e | cat -e > ref.txt
Command 'caat' not found, did you mean:
Exit 0

------------------------------------
Invalid cmd2:

./pipex in.txt "cat -e" "caat -e" out.txt
caat -e: command not found
Exit 127

< in.txt cat -e | caat -e > ref.txt
Command 'caat' not found, did you mean:
Exit 127

------------------------------------
No envp, just name:

env -i ./pipex in.txt "cat -e" "grep .c" out.txt
cat -e: command not found
grep .c: command not found
Exit 127

env -i < in.txt cat -e | grep .c > ref.txt
Exit 0

------------------------------------
No envp, with path:

env -i ./pipex in.txt "/usr/bin/cat -e" "/usr/bin/grep .c" out.txt
Exit 0

env -i < in.txt /usr/bin/cat -e | /usr/bin/grep .c > ref.txt
Exit 0

------------------------------------
Failing this??

./pipex infile "grep pipex" "tr x ' '" output/outfile14
tr: extra operand '\''
Exit 1

./pipex infile "echo 'Hi 42'" "tr 42 FT" output/outfile15


./pipex infile "tr ex ' X'" "tr pi 'P '" output/outfile16

------------------------------------