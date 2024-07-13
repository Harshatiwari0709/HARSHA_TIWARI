#Write a script to search for a given pattern in all files in a directory and its subdirectories.

echo "Enter pattern: "
read pattern

find -type f | ls -l [$pattern]*


