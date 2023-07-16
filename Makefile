##
# C-Whois
#
# @file
# @version 0.1

default: build

build:
	gcc -Wall -o whois main.c -l curl

# end
