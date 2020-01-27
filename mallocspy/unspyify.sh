perl -pi -e "s/(?<![\w_])spymalloc(?=\()/malloc/m" $(find * -name "*.c")
perl -pi -e "s/(?<![\w_])spyfree(?=\()/free/m" $(find * -name "*.c")
