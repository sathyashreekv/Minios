#!/bin/bash
#NumberGuess game
target=$(( $RANDOM % 100 + 1 ))
echo "Guess a number between 1 and 100."
while true; do
    read -p "Enter your guess: " guess
    if [[ $guess -eq $target ]]; then
        echo "Congratulations! You guessed it!"
        break
    elif [[ $guess -lt $target ]]; then
        echo "Higher!"
    else
        echo "Lower!"
    fi
done
