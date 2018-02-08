#Run learning rate tests
for x in .001 .005 .01 .05 .1 .5 1 2 5 
do
	echo "Training model with eta=$x"
	python logreg.py --eta $x --output "./output/lr_$x" #--positive ../data/toy_text/positive --negative ../data/toy_text/negative --vocab ../data/toy_text/vocab
done
