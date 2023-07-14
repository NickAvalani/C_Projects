#
#  Nick Avalani
#  CSC 352, Fall 2022, Benjamin Dicken
#  sbt.py
#  This program emulates an executable tester in python
#  using the os and subprocess module. The program is
#  given a C file path and a test directory path. The tests
#  within the directory are used as input for the C file and
#  the result is printed out.
#

import subprocess
import os

def main():
    c_file = input("C source file path: \n").strip()
    executable = c_file.split("./")[-1][:-2]
    test_dir = input("Test file directory path: \n").strip()
    c_compile = subprocess.call("gcc -Wall -Werror -std=c11 -o " + executable + " " + c_file + " -lm", text = True, shell = True)
    if c_compile != 0:
        print("failed to compile code")
        return
    else:
        compiled(test_dir, executable)

def compiled(test_dir, executable):
    '''
    This functions runs the provided C program against the input file and saves the output.
    The saved output is then compared with the expected output in order to determine whether
    the program is valid or not.
    test_dir: directory of the test files
    executable: the executable command for the C program
    '''
    for file in os.listdir(test_dir):
            subprocess.call("cat " + test_dir + "/" + file + "/input.txt | " + executable + " > " + test_dir + "/" + file + "/my_output.txt", text = True, shell = True)
            diff = subprocess.run("diff " + test_dir + "/" + file + "/" + "my_output.txt " + test_dir + "/" + file + "/output.txt", capture_output = True, text = True, shell = True)
            if(diff.stdout != ""):
                print("#### Test: " + file + " failed! ####")
                print("#### EXPECTED TO SEE:")
                exp = open(test_dir + "/" + file + "/output.txt", "r")
                line_exp = exp.readline()
                while line_exp != "":
                    print(line_exp)
                    line_exp = exp.readline()
                print("#### INSTEAD GOT:")
                real = open(test_dir + "/" + file + "/my_output.txt")
                line_real = real.readline()
                while line_real != "":
                    print(line_real)
                    line_real = real.readline()
            else:
                print("#### Test: " + file + " passed! ####")

if __name__ == "__main__":
    main()
