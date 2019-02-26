for p in *.vsl; do 
    echo "Building $p"
    ../vsl2py < "$p" > "${p}.py";
done
