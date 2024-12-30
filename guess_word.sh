#!/bin/bash
echo "I am going to read your mind!!"
echo "Think of a word and keep it in your mind"
read -p "Enter the number of letters in your word: " n

list1=("A" "F" "K" "P" "U")
list2=("B" "G" "L" "Q" "V")
list3=("C" "H" "M" "R" "W")
list4=("D" "I" "N" "S" "X")
list5=("E" "J" "O" "T" "Y")

# Display the lists to the user
echo "1 2 3 4 5"
for ((i = 0; i < ${#list1[@]}; i++)); do
    printf "%s %s %s %s %s\n" "${list1[i]}" "${list2[i]}" "${list3[i]}" "${list4[i]}" "${list5[i]}"
done

# Collect user input for each letter's column
user_inputs=()
for ((i = 1; i <= n; i++)); do
    read -p "Enter the column number (1-5) for letter $i: " first
    user_inputs+=("$first")
done

# Show the columns the user selected
echo "You selected the columns: ${user_inputs[@]}"

echo "1 2 3 4 5"
for ((i = 0; i < n; i++)); do
    column="${user_inputs[i]}"
    case $column in
        1) echo "${list1[@]}" ;;
        2) echo "${list2[@]}" ;;
        3) echo "${list3[@]}" ;;
        4) echo "${list4[@]}" ;;
        5) echo "${list5[@]}" ;;
        *) echo "Invalid input, please enter a number between 1 and 5." ;;
    esac
done

for ((i = 0; i < n; i++)); do
    column="${user_inputs[i]}"
    case $column in
        1) eval "choice$i=(\"\${list1[@]}\")" ;;
        2) eval "choice$i=(\"\${list2[@]}\")" ;;
        3) eval "choice$i=(\"\${list3[@]}\")" ;;
        4) eval "choice$i=(\"\${list4[@]}\")" ;;
        5) eval "choice$i=(\"\${list5[@]}\")" ;;
        *) echo "Invalid input, please enter a number between 1 and 5." ;;
    esac
done
user_inputs2=()
for ((i = 1; i <= n; i++)); do
    read -p "Enter the column number (1-5) for letter $i: " first
    user_inputs2+=("$first")
done
# Iterate over each of the user's choices
echo "The word in your mind is"
for ((i =0; i <n; i++)); do
          eval "printf \"%s \" \"\${choice$i[${user_inputs2[i]}-1]}\""
done
echo " "
