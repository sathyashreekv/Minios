#!/bin/bash

echo "Welcome to Mini-Os Simulator"
echo "This Simulator contains visualization of :"
while true
do
    echo "1) Process And Threads"
    echo "2) Context Switching "
    echo "3) Page Table "
    echo "4) Games Using Shell Script"
    echo "0) Exit"
    echo "What would you like to explore"
    read -p "Enter your choice (1, 2, 3, 4, 0): " choice
    echo ""
    if [ $choice -eq 0 ]; then
        echo "Thank you. Exiting..."
        break
    fi
    case $choice in
        1)
            ./process_and_threads
            ;;
        2)
            ./context_switching
            ;;
        3) 
            ./page_table
            ;;
        4)
            cat shell_script.txt
            echo ""
            echo "Which game do you want to play:"
            echo "1) Word Guess Game"
            echo "2) Number Guess Game"
            read -p "Enter your choice (1, 2 ): " choice

            case $choice in
                1)
                    ./guess_word.sh
                    ;;
                2)
                    ./guess_number.sh
                    ;;
                *)
                    echo "Invalid choice. Please enter 1, 2, or 3."
                    ;;
            esac 
            ;;
        *)
            echo "Invalid choice. Please enter 1, 2, 3, 4 or 0."
            ;;
    esac
    echo ""
done


