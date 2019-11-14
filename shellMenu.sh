#!/bin/bash
fact()
{
	echo -e "\n\nEnter a number : " #-e : enables interpretation of \ escapes
	read no

	fact=1
	while [ $no -gt 0 ]
	do
		fact=`expr $fact \* $no`
		no=` expr $no - 1`
	done
	echo -e "\n\nFactorial is : "
	echo "$fact"
}


greater()
{
	echo -e "\n\nEnter a, b, c : "
	read a b c


	if [ $a -gt $b -a $a -gt $c ]; #OR 	if [[ $a -gt $b && $a -gt $c ]]; 
 		then
			echo -e "\n\n $a IS GREATER"
	elif [ $b -gt $a -a $b -gt $c ];
		then
			echo -e "\n\n $b IS GREATER"
	elif [ $c -gt $a -a $c -gt $b ];
		then
			echo -e "\n\n $c IS GREATER"
	else
		echo -e "\n\n $a,$b,$c ARE EQUAL"
	fi
}
pal_no()
{
	echo -e "\n\nEnter a number"
	read no

	org=$no
	ans=0

	while [ $no -gt 0 ]
	do
		r=` expr $no % 10`  #OR 	r= $(($no % 10))
		no=` expr $no / 10`
		ans=` expr $ans \* 10 + $r`
	done
	if [ $org -eq $ans ]; then
			echo -e "\n\n$org IS A PALINDROME"
	else
		echo -e "\n\n$org IS NOT A PALINDROME"
	fi
}
pal_str()
{
	echo "Enter a string : "
	read s
	
	rev=""
	len=` expr length $s `
	
	while [ $len -ge 1 ]
	do
		temp=` expr $s | cut -c $len `  # -c : select only the character at index $len
		rev=$( echo $rev$temp )
		len=` expr $len - 1`
	done
	
	if [ $s == $rev ] ; then
			echo -e "\n\n$s IS A PALINDROME "
	else
		echo "$s IS NOT A PALINDROME"
	fi
}

prime()
{
	echo "Enter a number : "
	read no

	i=2

	while [ $i -lt $no ] 
	do
		r=` expr $no % $i `

		if [ $r -eq 0 ] 
			then
				echo -e "\n\n$no IS NOT A PRIME NUMBER"
				return
		fi
		
		i=` expr $i + 1 `
	done

	echo -e "\n\n$no IS A PRIME NUMBER"
}


while [ 1 ]
do
	echo -e "\n\nEnter your choice : "
	echo "1.Factorial"
	echo "2.Greater of three numbers"
	echo "3.Palindrome for numbers"
	echo "6.Exit"

	read ch

	case $ch in
		1) fact ;;
		2) greater ;;	
		3) pal_no ;;
		6) echo "Exiting"
		exit ;;
	*) echo "Invalid Choice; please re-enter "
	esac
done		
		
