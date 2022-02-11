#!/bin/bash
# Данный скрипт изменяет значение пермемнной окружения VAR
# Это нужно, чтобы проверить, не изменяется ли ее значение в файле /proc/{pid}/environ
# Для этого нужно сделать:
# 1. export VAR="some value"
# 2. запустить программу, чтобы ассоциировать с ней некий процесс ОС 
# 3. узнав его pid, просмотреть файл /proc/{pid}/environ и проверить значение переменной VAR
# 3. запустить скрипт /change_env_var.sh, который изменит значение VAR
# 4. повторить шаг 2.

for i in {1..15} 
do 
    sleep 1
    echo "$i: $VAR" 

done
echo "change value of env variable"
VAR="arch linux"
for i in {1..1000}
do
   sleep 1
   echo "$i: $VAR"
done
