#!/bin/bash
echo 'Привет! Введи путь к файлам:'
read way
if [ -z "$way" ] 
then
echo 'Ты похоже сделал что-то не так. Иди потренируйся...'
exit 1
   fi
cd $way
if ! [ -d "$way" ]; then
echo 'Ты похоже сделал что-то не так. Иди потренируйся...'
exit 1
   fi
echo
echo 'Ты говорил, что нужно редактировать файл? Посмотри и выбери, какой? - '
ls -l
echo 
echo 'Напиши имя файла полностью по маске "Имя.расширение" >>'
echo 'Введи файл для замены:'
read file
if [ -z "$file" ] 
then
echo 'Ты ничего не ввёл. Иди потренируйся...'
exit 1
   fi
if ! [ -f "$file" ]; then
echo 'Нет такого файла. Иди потренируйся...'
exit 1
   fi
echo 
echo 'Посмотри, что в нем и выбери строку (или текст) для замены:'
echo
cat $file
echo
echo 'Набери строку (текст), который надо поменять:'
read old_str
# if [ -z "$old_str" ] 
# then
# echo 'Ты ничего не ввёл. Будь внимательнее, повтори сначала!'
# exit 1
#    fi
# if ! [ -f "$file" ]; then
# echo 'Нет такого файла. Иди потренируйся...'
# exit 1
#    fi
echo 'Набери строку (текст), который вставить:'
read new_str
sed -i -e "s/$old_str/$new_str/g" $file
echo 'Смотри, что получилось:'
cat $file
echo 'Считаем checksum вносим изменения в LOG:'
stat --format=%n-%s-%y $file  >> test.log
sha256sum "$file" >> test.log
cat test.log



