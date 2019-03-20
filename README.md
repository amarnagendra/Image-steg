# Image-steg

use make file to generate .o file


command should be of type
1) ./a.out -e <image.bmp> <secret.txt> <output.bmp>
2) ./a.out -d <image.bmp> <outputfile>
NOTE:use -pe or -pd flag to steg or decode with password

Points to Note:
1)Image should be of .bmp only
2)If name for outputfile is not provided the name 'Ddefault' is used
3)If secret text too long to be accomidated in image appropriate error is shown