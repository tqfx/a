set key reverse
set terminal pngcairo
set datafile separator ','
set output sprintf("%s.png", ARGV[1][:strlen(ARGV[1])-4])
plot ARGV[1] using 1:2 with lines title '0',\
          '' using 3:4 with points title '1'
