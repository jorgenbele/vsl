for p in *.py; do 
    echo "=== RUNNING $p ==="
    python3 "$p" 1 2 3 4 5 6 7 | tee "${p}.out"
done
