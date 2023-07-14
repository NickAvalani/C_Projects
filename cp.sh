# Name: Nick Avalani
# Course: CSc 352, Fall 2022, Benjamin Dicken
# File: cp.sh
# Description: This bash script copies the file permissions
#              of the file provided in the command line and
#              ensures al the files in the directory (which
#              is also given in the command line) have the
#              same permissions.
#

#!/bin/bash

# Program to copy permissions

dir=${1}
perm_a="$(stat -c '%a' ${2})" #Permissions of the reference file (file to be copied from)

cd ${dir}

changed=0
unchanged=0

for file in *;
do 
	perm_b="$(stat -c '%a' ${file})"
	if [ ${perm_a} == ${perm_b} ]; then
		unchanged=$((unchanged + 1))
	else
		chmod ${perm_a} ${file}   #Copies the permissions from reference file to file in directory
		changed=$((changed + 1))
	fi
done

echo "Updated permissions for ${changed} file(s)."
echo "${unchanged} file(s) unchanged.";
