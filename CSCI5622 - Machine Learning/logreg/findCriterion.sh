for x in 1 2 3 4 5 6 7 8 9 10
do
	echo "Running logreg with $x passes"
	python logreg.py --passes $x --output "./output/passes_$x" #--positive ../data/toy_text/positive --negative ../data/toy_text/negative --vocab ../data/toy_text/vocab
done
