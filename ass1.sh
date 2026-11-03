#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo "========== ADDRESS BOOK =========="
    echo "a) Create Address Book"
    echo "b) View Address Book"
    echo "c) Insert a Record"
    echo "d) Delete a Record"
    echo "e) Modify a Record"
    echo "f) Exit"

    read -p "Enter your choice: " ch

    case $ch in

    a)
        touch "$FILE"
        > "$FILE"
        echo "Address book created successfully."
        ;;

    b)
        if [ ! -s "$FILE" ]; then
            echo "Address book is empty."
        else
            echo "Name | Roll No | Phone | Email | Department"
            cat "$FILE"
        fi
        ;;

    c)
        read -p "Enter Name: " name
        read -p "Enter Roll No: " roll
        read -p "Enter Phone: " phone
        read -p "Enter Email: " email
        read -p "Enter Department: " dept

        echo "$name|$roll|$phone|$email|$dept" >> "$FILE"

        echo "Record inserted successfully."
        ;;

    d)
        read -p "Enter Roll No to delete: " roll

        if grep -q "^[^|]*|$roll|" "$FILE"; then
            awk -F'|' -v r="$roll" '$2 != r' "$FILE" > temp.txt
            mv temp.txt "$FILE"
            echo "Record deleted successfully."
        else
            echo "Record not found."
        fi
        ;;

    e)
        read -p "Enter Roll No to modify: " roll

        if grep -q "^[^|]*|$roll|" "$FILE"; then
            read -p "Enter New Name: " name
            read -p "Enter New Roll No: " nr
            read -p "Enter New Phone: " phone
            read -p "Enter New Email: " email
            read -p "Enter New Department: " dept

            awk -F'|' -v r="$roll" -v n="$name" \
            -v nr="$nr" -v p="$phone" -v e="$email" \
            -v d="$dept" 'BEGIN {OFS="|"}
            $2 == r {print n,nr,p,e,d; next}
            {print}' "$FILE" > temp.txt

            mv temp.txt "$FILE"
            echo "Record modified successfully."
        else
            echo "Record not found."
        fi
        ;;

    f)
        echo "Exiting Address Book."
        break
        ;;

    *)
        echo "Invalid choice."
        ;;

    esac
done
command:chmod +x ass1.sh
./ass1.sh