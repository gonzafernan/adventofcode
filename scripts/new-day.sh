#!/bin/bash

read -p "Enter year nuber: " year
read -p "Enter day nuber: " day
read -p "Enter challenge title: " challenge

mkdir $year/$day
cp template/day_template_py.txt ${year}/${day}/day${day}.py
sed -i -e "s/{DAY}/${day}/g" ${year}/${day}/day${day}.py
sed -i -e "s/{YEAR}/${year}/g" ${year}/${day}/day${day}.py
sed -i -e "s/{CHALLENGE_TITLE}/${challenge}/g" ${year}/${day}/day${day}.py