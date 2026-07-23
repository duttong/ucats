#! /bin/sh
#
#  Shell script to batch convert binary snafu spreadsheets to
#  text spreadsheets.  GSD 060622.
#
#  $1 = analysis directory,  $2 = YYMMDD.#,  $3 = Home directory 

# instrument code
DATADIR=/home/uav/data
# 1 for create archive
let ARC=1	

cp snafuEXT $1/snafuEXT
cd $1
snafu -bsnafuEXT > /dev/null
mv eng1 eng1_$2.dat
mv eng2 eng2_$2.dat
mv o3data o3_$2.dat
mv o3xdata o3x_$2.dat
grep -v 999.0 h2odata > h2o_$2.dat
rm h2odata
rm *.sps snafuEXT

# real-time integration files
for file in int-*; do
	mv -v $file $file.$2.txt
done

# cleanup
cd $3
rm *.sps int-*

# move chroms from chrom dir
#mv -f chroms $1
#
slay rdr
renameitx.pl uav

if [ $ARC -eq 1 ]; then 
	# move all data to /home/uav/data directory and make an archive
	if [ ! -d $DATADIR ]; then
		mkdir $DATADIR
	fi
	mkdir $DATADIR/$2
	cd $3
	mv $2 raw
	mv anal/$2 anal/ext
	mv raw $DATADIR/$2
	mv anal/ext $DATADIR/$2
	cd $DATADIR
	tar -cv $2 | gzip > uav$2.tgz
fi
