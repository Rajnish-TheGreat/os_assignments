#!/bin/bash
clear

# Function: Create Database
createDB()
{
    echo -n "Enter name of DB: "
    read db
    isFound=`ls | grep $db | wc -w`
    if [ $isFound -gt 0 ]
    then
        echo "ERROR: DB is already present!!!"
    else
        touch $db
        echo "Success: DB Created Successfully!!!"
    fi
}

# Function: Insert Record
insertRecord()
{
    echo -n "Enter name of DB: "
    read db
    isFound=`ls | grep $db | wc -w`
    if [ $isFound -gt 0 ]
    then
        echo "Enter email address: "
        read mail
        ismailFound=`cat $db | grep $mail | wc -w`
        if [ $ismailFound -gt 0 ]
        then
            echo "ERROR: Email already Exist!!! Try with another email"
        else
            echo -n -e "Enter Roll Number: "
            read rollNo
            echo -n -e "Enter Name: "
            read name
            echo -n -e "Enter Mobile Number: "
            read mobile
            echo -e "$rollNo\t\t $name\t $mail\t $mobile" >> $db
            echo "200!!!Record Inserted"
        fi
    else
    echo "404!!!DB Not Found"
    fi
}

# Function: Show Database
viewDB()
{
    echo -n "Enter name of DB: "
    read db
    isFound=`ls | grep $db | wc -w`
    if [ $isFound -gt 0 ]
    then
        printf "\nRoll Number\t Name\t\t Email\t\t Mobile Number\n"
    cat $db
    else
        echo "404!!!DB Not Found"
    fi
}

# Function: Search Record
searchRecord()
{
    echo -n "Enter name of DB: "
    read db
    isFound=`ls | grep $db | wc -w`
    if [ $isFound -gt 0 ]
    then
        echo -n "Enter Email Address: "
        read mail
        c=`grep $mail $db`
        if [ ${#c} -gt 5 ]
        then
            grep $mail $db
            echo "200!!!Record Found"
        else
            echo "404!!!Record Not Found"
        fi
    else
        echo "404!!!DB Not Found"
    fi
}

# Function: Modify Record
modifyRecord()
{
    echo -n "Enter name of DB: "
    read db
    isFound=`ls | grep $db | wc -w`
    if [ $isFound -gt 0 ]
    then
        echo -n "Enter Email Address: "
        read mail
        isEmailFound=`cat $db | grep $mail | wc -w`
        if [ $isEmailFound -gt 0 ]
        then
            echo -n "Enter New Roll Number: "
            read rollNo
            echo -n "Enter New Name: "
            read name
            echo -n "Enter New Mobile Number: "
            read mobile
            modifiedRecord=`echo -e "$rollNo\t\t $name\t $mail\t $mobile"`
            oldRecord=`cat $db | grep $mail`
            echo "OLD Record: $oldRecord"
            echo "NEW Record: $modifiedRecord"
            sed -i "s/$oldRecord/$modifiedRecord/g" $db
            echo "200!!!Record Modified"
        else
            echo "404!!!Record Not Found"
        fi
    else
        echo "404!!!DB Not Found"
    fi
}

# Function: Delete Record
deleteRecord()
{
    echo -n "Enter name of DB: "
    read db
    isFound=`ls | grep $db | wc -w`
    if [ $isFound -gt 0 ]
    then
        echo -n "Enter Email Address: "
        read mail
        isEmailFound=`cat $db | grep $mail | wc -w`
        if [ $isEmailFound -gt 0 ]
        then
            oldRecord=`cat $db | grep $mail`
            sed -i "s/$oldRecord//g" $db
            sed -i "/^$/d" $db
            echo "200!!!Record Deleted"
        else
            echo "404!!!Record Not Found"
        fi
    else
        echo "404!!!DB Not Found"
    fi
}

while [ true ]
    do
        echo "***************************"
        echo "*          MENU           *"
        echo "***************************"
        echo "*Press 1 * Create Database*"
        echo "*Press 2 * Insert Record  *"
        echo "*Press 3 * View Database  *"
        echo "*Press 4 * Search Record  *"
        echo "*Press 5 * Modify Record  *"
        echo "*Press 6 * Delete Record  *"
        echo "*Press 7 * Exit           *"
        echo "***************************"
        echo -e -n "\nEnter Your Choice: "
        read choice
        case $choice in
            1) createDB ;;
            2) insertRecord ;;
            3) viewDB ;;
            4) searchRecord ;;
            5) modifyRecord ;;
            6) deleteRecord ;;
            7)exit;;
            *) echo "Invalid Input!!! Please enter correct choice"
        esac
done


