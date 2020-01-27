perl -pi -e "s/(?<![\w_])malloc(?=\()/spymalloc/m" $(find * -name "*.c")
perl -pi -e "s/(?<![\w_])free(?=\()/spyfree/m" $(find * -name "*.c")
