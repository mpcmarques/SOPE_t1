# sfind


Criado por Mateus Pedroza
Programa imita a função find do linux.


Exemplos de invocação com find:

shell> find ~ -name lixo.txt -print
/home/user/tmp/lixo.txt
/home/user/mbin/myscanf/tmp/lixo.txt

shell> find ~ -name lixo.txt -exec file '{}' \;  
/home/user/tmp/lixo.txt: ASCII text
/home/user/mbin/myscanf/tmp/lixo.txt: HTML document text  

shell> find ~ -name lixo.txt -delete
shell>

shell> find . -type l -print
./so/www
./so/material
...

shell> find / -perm 0400 -print
/bak/multimedia/figs/bear.jpg
/bak/multimedia/figs/cubs.jpg
