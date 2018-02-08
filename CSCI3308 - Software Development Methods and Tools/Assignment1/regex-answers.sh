#!/bin/bash
## Raymond Duncan

filename=regex_practice_data.txt

echo "Starting"
egrep '[0-9]+$' $filename | wc -l 				#15371
egrep '^[^aeiouAEIOU]' $filename | wc -l			#52331
egrep '^[a-zA-Z]{12}$' $filename | wc -l			#1257
egrep '[0-9]{3}-[0-9]{3}-[0-9]{4}' $filename | wc -l		#770
egrep '303-[0-9]{3}-[0-9]{4}' $filename | wc -l			#407
egrep '^[aeiou](.)*[0-9]$' $filename | wc -l			#1571	1338
egrep '.+@geocities.com' $filename | wc -l			#6619
egrep '@' $filename | egrep '([^a-zA-Z0-9.@-]|(^\.com|^\.org|^\.int|^\.gov|^\.net|^\.edu|^\.mil))' | wc -l	#25
