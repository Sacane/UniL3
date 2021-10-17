#!/bin/bash
echo > ./tests/report.txt

test(){
    n=0
    passed=0
    files=($1)
    for f in ${files[@]}; do
        let n++
        printf "(%02d/%02d) - %s\n" $n ${#files[@]} "Testing $f..." 

        ./ex1 < $f >> ./tests/report.txt
        feedback=$PIPESTATUS

        echo $feedback >> ./tests/report.txt
        echo >> ./tests/report.txt

        if [ "$feedback" = "$2" ]; then
            let passed++
        fi
    done
    
    if [ $passed -eq ${#files[@]} ]; then
        echo -e "\033[0;32m$passed tests out of ${#files[@]} passed! \033[0;37m"
    elif [ $passed = "0" ]; then
        echo -e "\033[0;31m$passed tests out of ${#files[@]} passed! \033[0;37m"
    else
        echo -e "\033[0;33m$passed tests out of ${#files[@]} passed! \033[0;37m"
    fi
}

echo "=============== Valid tests  ===============" 
test "./tests/correct/*.txt" 0

echo "============== Invalid tests ==============" 
test "./tests/incorrect/*.txt" 1

echo "Done."