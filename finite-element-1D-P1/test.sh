
if make testmeshes; then
        cd test
        ./meshes_test
        cd ..
else
        echo 'Erreur de compilation'
fi
